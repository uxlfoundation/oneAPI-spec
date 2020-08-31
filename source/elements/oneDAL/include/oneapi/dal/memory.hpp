namespace oneapi::dal {

/// @tparam Data The type of elements to be freed
template <typename Data>
class empty_delete {
public:
    void operator()(Data*) const noexcept {}
};

/// @tparam Data   The type of elements to be freed
template <typename Data, /*implementation defined*/>
class default_delete {
public:
    /*implementation defined*/

    /// @param data The pointer to array of elements to be freed.
    void operator()(Data* data) const;
};

/// @tparam Data   The type of elements to be freed
/// @param  queue  The SYCL* queue object.
template <typename Data>
inline auto make_default_delete(const sycl::queue& queue);

} // namespace oneapi::dal
