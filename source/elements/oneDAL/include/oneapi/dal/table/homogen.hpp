#include "oneapi/dal/table/common.hpp"

namespace oneapi::dal {

template <typename T>
struct is_homogen_table_impl {
    ONEAPI_DAL_SIMPLE_HAS_METHOD_TRAIT(const void*, get_data, () const)

    using base = is_table_impl<T>;

    static constexpr bool value = base::template has_method_get_column_count_v<T> &&
                                  base::template has_method_get_row_count_v<T> &&
                                  base::template has_method_get_metadata_v<T> &&
                                  base::template has_method_get_data_layout_v<T> &&
                                  has_method_get_data_v<T>;
};

template <typename T>
inline constexpr bool is_homogen_table_impl_v = is_homogen_table_impl<T>::value;

class homogen_table : public table {
public:
    /// Returns the unique id of ``homogen_table`` class.
    static std::int64_t kind();

    /// Constructs new ``homogen_table`` from user-defined data block. Table
    /// object refers to the data but does not own it. All the responsibilities of
    /// memory management like deallocation remain on the user side.
    ///
    /// @tparam Data        The type of elements in the data block that will be stored into the table.
    ///                     The table shall reflect this type information in the metadata.
    /// @param queue        The SYCL* queue object
    /// @param data_pointer The pointer to homogeneous data block that will be stored into the table.
    /// @param row_count    The count of rows in the table.
    /// @param column_count The count of columns in the table.
    /// @param dependencies The list of dependencies that incates whether data_pointer can be read or written.
    /// @param layout       The layout of accepting data. Shall be ``data_layout::row_major`` or
    ///                     ``data_layout::column_major``. Indicates whether increment of $data_pointer@ will lead to
    ///                      selection of next column or a next row.
    template <typename Data>
    static homogen_table wrap(const sycl::queue& queue,
                              const Data* data_pointer,
                              std::int64_t row_count,
                              std::int64_t column_count,
                              const sycl::vector_class<sycl::event>& dependencies = {},
                              data_layout layout = data_layout::row_major);

public:
    /// Creates an empty homogen_table - with zero row and column count. This table
    /// shall not contain any data, other properties are set to default values.
    homogen_table();

    /// Creates table from an implementation object. $Impl$ shall be the
    /// appropriate implementation type: it shall implement all the properties
    /// of ``homogen_table`` class with the getter semantics as defined in the table class.
    /// The checks can be done in compile-time using SFINAE technique or in
    /// run-time using $impl$ object API. $Impl$ shall not be derived from table
    /// type.
    /// `template <typename T> static constexpr bool oneapi::dal::is_homogen_table_impl_v<T>`
    /// implements the mentioned optional compile-time checks on $Impl$ type.
    template <typename Impl,
              typename ImplType = std::decay_t<Impl>,
              typename          = std::enable_if_t<!std::is_base_of_v<table, ImplType> &&
                                                   is_homogen_table_impl_v<ImplType>>>
    homogen_table(Impl&& impl);

    /// Creates a new homogen_table object from user-defined data block.
    ///
    /// @tparam Data         The type of elements in the data block that will be stored into the table.
    /// @tparam ConstDeleter The type of deleter called on $data_pointer$ when
    ///                      the last table that refers to it goes out of the scope.
    ///
    /// @param queue         The SYCL* queue object
    /// @param data_pointer  The pointer to homogeneous data block that will be stored into the table.
    /// @param row_count     The count of rows in the table.
    /// @param column_count  The count of columns in the table.
    /// @param data_deleter  The deleter that is called on the $data_pointer$ when last table that refers to it
    ///                      goes out of the scope.
    /// @param dependencies  The list of dependencies that incates whether data_pointer can be read or written.
    /// @param layout        The layout of accepting data. Shall be ``data_layout::row_major`` or
    ///                      ``data_layout::column_major``. Indicates whether increment of $data_pointer@ will lead to
    ///                       selection of next column or a next row.
    template <typename Data, typename ConstDeleter>
    homogen_table(const sycl::queue& queue,
                  const Data* data_pointer,
                  std::int64_t row_count,
                  std::int64_t column_count,
                  ConstDeleter&& data_deleter,
                  const sycl::vector_class<sycl::event>& dependencies = {},
                  data_layout layout                                  = data_layout::row_major);

    /// The data block that table can own or just reference depending on how it
    /// was created from this block.
    ///
    /// @tparam Data The type that data pointer will be casted to. No checks is
    ///              performed that this type is the actual types of data elements.
    template <typename Data>
    const Data* get_data() const {
        return reinterpret_cast<const Data*>(this->get_data());
    }

    /// The data block that table can own or just reference depending on how it
    /// was created from this block.
    const void* get_data() const;

    /// The unique id of the homogen table type.
    std::int64_t get_kind() const {
        return kind();
    }
};

} // namespace oneapi::dal
