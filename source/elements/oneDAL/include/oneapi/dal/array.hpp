namespace oneapi::dal {

/// @tparam Data The type of the memory block elements within the array.
///              ``Data`` can represent any :capterm:`data type`.
///
/// @pre ``Data`` cannot be const-qualified.
template <typename Data>
class array {
public:
    using data_t = Data;

    /// Creates a new array instance by allocating a mutable memory block. The created array manages
    /// lifetime of the allocated memory block.
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type ``Data`` to allocate memory for.
    /// @param alloc The kind of USM to be allocated.
    ///
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`has_mutable_data() == true`
    static array<Data> empty(const sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array instance by allocating a mutable memory block and filling its content
    /// with a scalar value. The created array manages lifetime of the allocated memory block.
    ///
    /// @tparam Element The type from which array elements of type ``Data`` can be constructed.
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type ``Data`` to allocate memory for.
    /// @param element The value that is used to fill a memory block.
    /// @param alloc   The kind of USM to be allocated.
    ///
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`has_mutable_data() == true`
    /// @post :literal:`get_data()[i] == element, 0 <= i < count`
    template <typename Element>
    static array<Data> full(sycl::queue& queue,
                            std::int64_t count,
                            Element&& element,
                            const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array instance by allocating a mutable memory block and filling its content
    /// with zeros. The created array manages lifetime of the allocated memory block.
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type ``Data`` to allocate memory for.
    /// @param alloc   The kind of USM to be allocated.
    ///
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`has_mutable_data() == true`
    /// @post :literal:`get_data()[i] == element, 0 <= i < count`
    static array<Data> zeros(sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array instance from a pointer to externally-allocated mutable memory block.
    /// The created array does not manage lifetime of the user-provided memory block. It is the
    /// responsibility of the calling application to deallocate the memory block.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type ``Data`` in the memory block.
    /// @param dependencies Events indicating availability of the ``data`` for reading or writing.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == true`
    /// @post :literal:`get_mutable_data() == data`
    static array<Data> wrap(Data* data,
                            std::int64_t count,
                            const std::vector<sycl::event>& dependencies = {});

    /// Creates a new array instance from a pointer to externally-allocated immutable memory block.
    /// The created array does not manage lifetime of the user-provided memory block. It is the
    /// responsibility of the calling application to deallocate the memory block.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type ``Data`` in the memory block.
    /// @param dependencies Events indicating availability of the ``data`` for reading or writing.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == false`
    static array<Data> wrap(const Data* data,
                            std::int64_t count,
                            const std::vector<sycl::event>& dependencies = {});

    /// Creates an empty array without memory allocation.
    ///
    /// @post :literal:`get_count() == 0`
    /// @post :literal:`get_data() == nullptr`
    /// @post :literal:`has_mutable_data() == false`
    array();

    /// Creates a new array instance that shares an ownership with the ``other`` array.
    array(const array<Data>& other);

    /// Creates a new array instance that transfers an ownership from the ``other`` array. After
    /// construction of the new instance, the ``other`` behaviour is implementation defined.
    ///
    /// @post :literal:`other.get_count() == 0`
    /// @post :literal:`other.get_data() == nullptr`
    /// @post :literal:`has_mutable_data() == false`
    array(array<Data>&& other);

    /// Creates a new array instance from a pointer to externally-allocated mutable memory block.
    /// The created array manages lifetime of the user-provided memory block. The memory block is
    /// deallocated using a custom deleter object provided by the user.
    ///
    /// @tparam Deleter The type of a deleter used to deallocate the ``data``.
    ///                 The expression :literal:`deleter(data)` must be well-formed
    ///                 and not throw any exceptions.
    ///
    /// @param queue        The SYCL* queue object.
    /// @param data         The pointer to externally-allocated mutable data.
    /// @param count        The number of elements of type ``Data`` in the memory block.
    /// @param deleter      The object used to deallocate ``data``.
    /// @param dependencies Events that indicate when ``data`` becomes ready to be read or written.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == true`
    /// @post :literal:`get_mutable_data() == data`
    template <typename Deleter>
    explicit array(const sycl::queue& queue,
                   Data* data,
                   std::int64_t count,
                   Deleter&& deleter,
                   const std::vector<sycl::event>& dependencies = {});

    /// Creates a new array instance from a pointer to externally-allocated immutable memory block.
    /// The created array manages lifetime of the user-provided memory block. The memory block is
    /// deallocated using a custom deleter object provided by the user.
    ///
    /// @tparam ConstDeleter The type of a deleter used to deallocate the ``data``.
    ///                      The expression :literal:`deleter(data)` must be well-formed
    ///                      and not throw any exceptions.
    ///
    /// @param queue         The SYCL* queue object.
    /// @param data          The pointer to externally-allocated memory block.
    /// @param count         The number of elements of type ``Data`` in the ``data``.
    /// @param deleter       The object used to dellocate ``data``.
    /// @param dependencies  Events indicating availability of the ``data`` for reading or writing.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == false`
    template <typename ConstDeleter>
    explicit array(const sycl::queue& queue,
                   const Data* data,
                   std::int64_t count,
                   ConstDeleter&& deleter,
                   const std::vector<sycl::event>& dependencies = {});

    /// Creates a new array instance that shares ownership with the reference array while storing
    /// pointer to another memory block provided by the user. Lifetime of the user-provided memory
    /// block is not managed by the created array. One of use cases of this constructor is creation
    /// of an array with offset, for example, :literal:`array{ other, other.get_data() + offset }`.
    /// The array created this way, shared ownership with the ``other`` array, but points to its
    /// data with offset.
    ///
    /// @tparam RefData The type of elements in the reference array.
    /// @tparam ExtData Either ``Data`` or ``const Data`` type.
    ///
    /// @param ref   The reference array which shares ownership with the created one.
    /// @param data  The mutable or immutable unmanaged pointer hold by the created array.
    /// @param count The number of elements of type ``Data`` in the ``data``.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    template <typename RefData, typename ExtData>
    explicit array(const array<RefData>& ref, ExtData* data, std::int64_t count);

    /// Replaces the immutable, mutable data pointers and the number of elements by the values
    /// stored in the ``other`` array.
    ///
    /// @post :literal:`get_data() == other.get_data()`
    /// @post :literal:`get_count() == other.get_count()`
    /// @post :literal:`get_mutable_data() == other.get_mutable_data()`
    array<Data> operator=(const array<Data>& other);

    /// Replaces the immutable, mutable data pointers and the number of elements by the values
    /// stored in the ``other`` array.
    ///
    /// @post :literal:`get_data() == other.get_data()`
    /// @post :literal:`get_count() == other.get_count()`
    /// @post :literal:`get_mutable_data() == other.get_mutable_data()`
    array<Data> operator=(array<Data>&& other);

    /// The pointer to the immutable memory block.
    ///
    /// @invariant :literal:`get_data() != nullptr` if :literal:`get_count() > 0`
    /// @invariant :literal:`get_data() == get_mutable_data()` if :literal:`has_mutable_data() == true`
    const Data* get_data() const noexcept;

    /// Returns whether array contains mutable data or not.
    bool has_mutable_data() const noexcept;

    /// The pointer to the mutable memory block.
    ///
    /// @pre :literal:`has_mutable_data() == true`, othewise throws :literal:`domain_error`
    /// @invariant :literal:`get_mutable_data() != get_data()` if :literal:`has_mutable_data() == true`
    Data* get_mutable_data() const;

    /// Does nothing if array contains mutable data. Otherwise, allocates a mutable memory block and
    /// copies content of the immutable memory block into it. The array manages lifetime of the
    /// allocated mutable memory block. Returns reference to the same array instance.
    ///
    /// @param queue The SYCL* queue object.
    /// @param alloc The kind of USM to be allocated.
    ///
    /// @post :literal:`has_mutable_data() == true`
    array& need_mutable_data(sycl::queue& queue,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// The number of elements of type ``Data`` in a memory block
    std::int64_t get_count() const noexcept;

    /// The size of memory block in bytes
    /// @invariant :literal:`get_size() == get_count() * sizeof(Data)`
    std::int64_t get_size() const noexcept;

    /// Provides a read-only access to the elements of array.
    const Data& operator[](std::int64_t index) const noexcept;

    /// Releases ownership of the managed memory block.
    ///
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`has_mutable_data() == true`
    void reset();

    /// Releases ownership of the managed memory block and replace it by a newly allocated mutable
    /// memory block. The lifetime of the allocated memory block is managed by the array.
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type ``Data`` to allocate memory for.
    /// @param alloc The kind of USM to be allocated.
    ///
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() > count`
    /// @post :literal:`get_count() > count`
    void reset(const sycl::queue& queue,
               std::int64_t count,
               const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Releases ownership of the managed memory block and replace it by a pointer to
    /// externally-allocated mutable memory block. The lifetime of the memory block is managed by
    /// the array. The memory block is deallocated using a custom deleter object provided by the
    /// user.
    ///
    /// @tparam Deleter The type of a deleter used to deallocate the ``data``.
    ///                 The expression :literal:`deleter(data)` must be well-formed
    ///                 and not throw any exceptions.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type ``Data`` in the ``data``.
    /// @param deleter      The object used to free ``data``.
    /// @param dependencies Events indicating availability of the ``data`` for reading or writing.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == true`
    /// @post :literal:`get_mutable_data() == data`
    template <typename Deleter>
    void reset(Data* data,
               std::int64_t count,
               Deleter&& deleter,
               const std::vector<sycl::event>& dependencies = {});

    /// Releases ownership of the managed memory block and replace it by a pointer to
    /// externally-allocated mutable memory block. The lifetime of the memory block is managed by
    /// the array. The memory block is deallocated using a custom deleter object provided by the
    /// user.
    ///
    /// @tparam ConstDeleter The type of a deleter used to deallocate the ``data``.
    ///                      The expression :literal:`deleter(data)` must be well-formed
    ///                      and not throw any exceptions.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type ``Data`` in the ``data``.
    /// @param deleter      The object used to free ``data``.
    /// @param dependencies Events indicating availability of the ``data`` for reading or writing.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    /// @post :literal:`has_mutable_data() == false`
    template <typename ConstDeleter>
    void reset(const Data* data,
               std::int64_t count,
               ConstDeleter&& deleter,
               const std::vector<sycl::event>& dependencies = {});

    /// Releases ownership of the managed memory block and start managing lifetime of the reference
    /// array while storing pointer to another memory block provided by the user. Lifetime of the
    /// user-provided memory block is not managed.
    ///
    /// @tparam RefData The type of elements in the reference array.
    /// @tparam ExtData Either ``Data`` or ``const Data`` type.
    ///
    /// @param ref   The reference array which shares ownership with the created one.
    /// @param data  The mutable or immutable unmanaged pointer hold by the created array.
    /// @param count The number of elements of type ``Data`` in the ``data``.
    ///
    /// @pre :literal:`data != nullptr`
    /// @pre :literal:`count > 0`
    /// @post :literal:`get_count() == count`
    /// @post :literal:`get_data() == data`
    template <typename RefData, typename ExtData>
    void reset(const array<RefData>& ref, ExtData* data, std::int64_t count);
};

} // namespace oneapi::dal
