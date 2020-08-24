#include "onedal/table.hpp"

namespace oneapi::dal {

/// @tparam T The type of data values in blocks returned by the accessor.
///           Shall be const-qualified for read-only access.
template <typename T>
class column_accessor {
public:
    using data_t = std::remove_const_t<T>;

public:
    /// Creates a new read-only accessor object from an object of type $K$
    ///
    /// @tparam K The type that can be used to create an accessor.
    ///           At least, $K$ shall be :expr:`std::is_base_of_v<onedal::table, K>`.
    template <typename K>
    column_accessor(const K& obj);

    /// Provides an access to the column values of accessed object.
    /// This method should avoid data copy and conversions when possible.
    ///
    /// @param[in] queue        The object used to perform computations
    /// @param[in] column_index The index of column that data shall be returned from the accessor.
    /// @param[in] rows         Range of rows that should be read in the $column_index$ block.
    /// @param[in] alloc        The requested kind of memory in the returned block.
    /// @return array           The array that contains data of selected column and range of rows
    ///                         of that column from accessed object.
    ///                         It shall point directly to the memory inside the accessed object
    ///                         whether it is possible. In that case, it shall refer to it as to immutable memory block.
    ///
    /// @pre :expr:`rows` are in appropriate range for accessed object.
    /// @pre :expr:`column_index` is an appropriate index for column range of accessed object.
    array<data_t> pull(sycl::queue& queue,
                       std::int64_t column_index,
                       const range& rows             = { 0, -1 },
                       const sycl::usm::alloc& alloc = sycl::usm::alloc::shared) const;

    /// Provides an access to the column values of accessed object.
    /// This method should avoid data copy and conversions when possible.
    ///
    /// @param[in] queue        The object used to perform computations
    /// @param[in,out] block    The block which memory is reused whether it is possible and
    ///                         needed to get data from accessed object. It shall be reset when
    ///                         its size is not big enough or direct memory from accessed object can be used.
    ///                         If the block is reset to use direct memory pointer from the object,
    ///                         it shall refer to this pointer as to immutable memory block.
    /// @param[in] column_index The index of column that data shall be returned from the accessor.
    /// @param[in] rows         Range of rows that should be read in the $column_index$ block.
    /// @param[in] alloc        The requested kind of memory in the returned block.
    /// @return pointer      The raw pointer that $block$ contains after this operation.
    ///                      The same as :expr:`block.get_data()`
    ///
    /// @pre :expr:`rows` are in appropriate range for accessed object.
    /// @pre :expr:`column_index` is an appropriate index for column range of accessed object.
    T* pull(sycl::queue& queue,
            array<data_t>& block,
            std::int64_t column_index,
            const range& rows             = { 0, -1 },
            const sycl::usm::alloc& alloc = sycl::usm::alloc::shared) const;
};

} // namespace oneapi::dal
