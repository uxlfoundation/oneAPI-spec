#include "oneapi/dal/table/common.hpp"

namespace oneapi::dal {

class homogen_table : public table {
public:
    /// Returns the unique id of ``homogen_table`` class.
    static std::int64_t kind();

    /// Creates a new ``homogen_table`` instance from externally-defined data block. Table
    /// object refers to the data but does not own it. The responsibility to
    /// free the data remains on the user side.
    /// The :expr:`data` shall point to the ``data_pointer`` memory block.
    ///
    /// @tparam Data        The type of elements in the data block that will be stored into the table.
    ///                     The table shall initialize data types of metadata with this data type.
    ///                     The feature types shall be set to default values for $Data$ type: contiguous for floating-point,
    ///                     ordinal for integer types.
    ///                     The $Data$ type shall be at least :expr:`float`, :expr:`double` or :expr:`std::int32_t`.
    /// @param queue        The SYCL* queue object
    /// @param data_pointer The pointer to a homogeneous data block.
    /// @param row_count    The number of rows in the table.
    /// @param column_count The number of columns in the table.
    /// @param dependencies Events indicating availability of the $data$ for reading or writing.
    /// @param layout       The layout of the data. Shall be ``data_layout::row_major`` or
    ///                     ``data_layout::column_major``.
    template <typename Data>
    static homogen_table wrap(const sycl::queue& queue,
                              const Data* data_pointer,
                              std::int64_t row_count,
                              std::int64_t column_count,
                              const sycl::vector_class<sycl::event>& dependencies = {},
                              data_layout layout = data_layout::row_major);

public:
    /// Creates a new ``homogen_table`` instance with zero number of rows and columns.
    /// The :expr:`kind` shall be set to``homogen_table::kind()``.
    /// All the properties shall be set to default value (see the Properties section).
    homogen_table();

    /// Creates a new ``homogen_table`` instance from externally-defined data block.
    /// Table object owns the data pointer.
    /// The :expr:`data` shall point to the ``data_pointer`` memory block.
    ///
    /// @tparam Data         The type of elements in the data block that will be stored into the table.
    ///                      The $Data$ type shall be at least :expr:`float`, :expr:`double` or :expr:`std::int32_t`.
    /// @tparam ConstDeleter The type of deleter called on ``data_pointer`` when
    ///                      the last table that refers to it goes out of the scope.
    ///
    /// @param queue         The SYCL* queue object
    /// @param data_pointer  The pointer to a homogeneous data block.
    /// @param row_count     The number of rows in the table.
    /// @param column_count  The number of columns in the table.
    /// @param data_deleter  The deleter that is called on the ``data_pointer`` when last table that refers to it
    ///                      goes out of the scope.
    /// @param dependencies  Events indicating availability of the $data$ for reading or writing.
    /// @param layout        The layout of the data. Shall be ``data_layout::row_major`` or
    ///                     ``data_layout::column_major``.
    template <typename Data, typename ConstDeleter>
    homogen_table(const sycl::queue& queue,
                  const Data* data_pointer,
                  std::int64_t row_count,
                  std::int64_t column_count,
                  ConstDeleter&& data_deleter,
                  const sycl::vector_class<sycl::event>& dependencies = {},
                  data_layout layout                                  = data_layout::row_major);

    /// Returns the :expr:`data` pointer casted to the $Data$ type. No checks are
    /// performed that this type is the actual type of the data within the table.
    template <typename Data>
    const Data* get_data() const {
        return reinterpret_cast<const Data*>(this->get_data());
    }

    /// The pointer to the data block within the table.
    /// Shall be equal to ``nullptr`` when :expr:`row_count == 0` and :expr:`column_count == 0`.
    const void* get_data() const;

    /// The unique id of the homogen table type.
    std::int64_t get_kind() const {
        return kind();
    }
};

} // namespace oneapi::dal
