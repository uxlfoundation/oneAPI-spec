
namespace oneapi::dal {

/// @tparam T The type of the memory block elements inside the array.
///
/// @pre $T$ cannot be const-qualified.
template <typename T>
class array {
public:
    using data_t = T;

public:
    /// Creates a new array with allocated but non-initialized data.
    /// Array owns these data as mutable memory block.
    ///
    /// @param queue The object used to allocate and free the data
    ///              (when reference count on memory block becomes zero).
    /// @param count The number of elements to allocate.
    /// @param alloc The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    static array<T> empty(const sycl::queue& queue,
                          std::int64_t count,
                          const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array with the data filled by single value.
    /// Array owns these data as mutable memory block.
    ///
    /// @tparam K      The type that array elements of type $T$ can be constructed from.
    ///
    /// @param queue   The object used to allocate, fill, and free the data
    ///                (when reference count on memory block becomes zero).
    /// @param count   The number of elements to allocate.
    /// @param element The value that is used to fill memory block.
    /// @param alloc   The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    /// @pre Elements of the ``array`` are constructible from ``K`` type.
    template <typename K>
    static array<T> full(sycl::queue& queue,
                         std::int64_t count,
                         K&& element,
                         const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array with the data filled by zero value.
    /// Array owns these data as mutable memory block.
    ///
    /// @param queue   The object used to allocate, fill, and free the data.
    ///                (when reference count on memory block becomes zero)
    /// @param count   The number of elements to allocate.
    /// @param alloc   The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    static array<T> zeros(sycl::queue& queue,
                          std::int64_t count,
                          const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array that holds unmanaged mutable memory block.
    /// Responsibility to free this block remains on the user side.
    ///
    /// @param data         The pointer to user-allocated data.
    /// @param count        The number of elements in memory block.
    /// @param dependencies Events that say when $data$ becomes ready to be read or written
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<T> wrap(T* data,
                         std::int64_t count,
                         const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates a new array that hold unmanaged immutable memory block.
    /// Responsibility to free this block remains on the user side.
    ///
    /// @param data         The pointer to user-allocated data.
    /// @param count        The number of elements in memory block.
    /// @param dependencies Events that say when $data$ becomes ready to be read or written
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<T> wrap(const T* data,
                         std::int64_t count,
                         const sycl::vector_class<sycl::event>& dependencies = {});

public:
    /// Creates a new instance of the class without any data.
    array();

    /// Creates new array object that shares an ownership with $a$ on its memory
    /// block: no data are copied, but just a reference count on the original
    /// memory block is incremented.
    array(const array<T>& a);

    /// Moves $a$ into the new array instance with its memory block and ownership information.
    array(array<T>&& a);

    /// Creates a new array instance which holds a pointer to user-allocated data.
    /// Array considers these data as mutable memory block.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$ when count
    ///                     of references on it becomes zero.
    ///
    /// @param queue        The queue used to perform computations.
    /// @param data         The pointer to user-allocated data.
    /// @param count        Count of elements in the $data$.
    /// @param deleter      The object used to free $data$ when reference
    ///                     count on the memory block becomes zero.
    /// @param dependencies Events that say when $data$ becomes ready to be read or written
    template <typename Deleter>
    explicit array(const sycl::queue& queue,
                   T* data,
                   std::int64_t count,
                   Deleter&& deleter,
                   const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates a new array instance which holds a pointer to user-allocated data.
    /// Array considers these data as immutable memory block.
    ///
    /// @tparam ConstDeleter The type of deleter used to free the $data$ when count
    ///                      of references on it becomes zero.
    ///
    /// @param queue         The queue object used to perform computations.
    /// @param data          The pointer to user-allocated data.
    /// @param count         Count of the $data$.
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the memory block becomes zero.
    /// @param dependencies  Events that say when $data$ becomes ready to be read or written
    template <typename ConstDeleter>
    explicit array(const sycl::queue& queue,
                   const T* data,
                   std::int64_t count,
                   ConstDeleter&& deleter,
                   const sycl::vector_class<sycl::event>& dependencies = {});

    /// An aliasing constructor: creates a new array that hold $data$ pointer
    /// and shares ownership information with $ref$. If this array is the last
    /// reference to go out of the scope, than deleter of the $ref$ is called.
    /// Array returns $data$ pointer as its mutable or immutable block depending
    /// on the $K$ type.
    ///
    /// @tparam Y    The type of elements in the reference array
    /// @tparam K    The type that array elements of type $T$ can be constructed from.
    ///
    /// @param ref   The array which shares ownership information with created
    ///              one.
    /// @param data  Mutable or immutable unmanaged data pointer hold by
    ///              created array.
    /// @param count The number of elements in $data$
    ///
    /// @pre  :expr:`std::is_same_v<K, const T> || std::is_same_v<K, T>`
    template <typename Y, typename K>
    explicit array(const array<Y>& ref, K* data, std::int64_t count);

    /// Replaces the reference to memory block of this object with
    /// reference to block managed by $other$.
    /// Ownership information is shared between this object and $other$.
    ///
    /// @param other The object which shares ownership information with this one.
    ///
    /// @post :expr:`data == other.data`
    /// @post :expr:`mutable_data == other.mutable_data`
    /// @post :expr:`count == other.count`
    array<T> operator=(const array<T>& other);

    /// Moves the memory block of $other$ into this one.
    /// Ownership information is moved from $other$ to this object.
    ///
    /// @param other The object which is moved into this one.
    array<T> operator=(array<T>&& other);

    /// The mutable pointer to memory block.
    /// @pre :expr:`has_mutable_data() == true`, othewise throws `domain_error`
    /// @invariant :expr:`mutable_data != nullptr` if :expr:`has_mutable_data() && count > 0`
    T* get_mutable_data() const;

    /// The immutable pointer to memory block.
    /// @invariant :expr:`data != nullptr` if :expr:`count > 0`
    /// @invariant if :expr:`has_mutable_data() == true` then `data == mutable_data`
    const T* get_data() const noexcept;

    /// Returns whether array contains :expr:`mutable_data` or not
    ///
    /// @invariant :expr:`mutable_data != nullptr` if this returns `true` and :expr:`count > 0`
    bool has_mutable_data() const noexcept;

    /// Assures that array holds :expr:`mutable_data`. If
    /// :expr:`has_mutable_data() == false && count > 0` then allocates
    /// :expr:`mutable_data` block and copies :expr:`data` in it. Forgets about
    /// previous immutable memory block. If array has :expr:`mutable_data`
    /// already, no allocation and copy are performed.
    ///
    /// @param queue The object that specifies where and how to perform an
    ///              operation
    /// @param alloc The kind of memory to be allocated
    ///
    /// @post :expr:`has_mutable_data() == true`
    array& need_mutable_data(sycl::queue& queue,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// The count of elements of type $T$ in a memory block
    std::int64_t get_count() const noexcept;

    /// The size of memory block in bytes
    /// @invariant :expr:`size == count * sizeof(T)`
    std::int64_t get_size() const noexcept;

    /// Leaves the memory block currently held in the array.
    /// Makes the array empty.
    ///
    /// @post :expr:`count == 0`
    /// @post :expr:`has_mutable_data() == false`
    /// @post :expr:`data == nullptr`
    void reset();

    /// Leaves the memory block currently held in the array, then
    /// allocates and assigns a new block to the array.
    ///
    /// @param queue The object that specifies where and how perform an operation
    /// @param count The number of elements to allocate in a new memory block
    /// @param alloc The kind of memory to be allocated
    void reset(const sycl::queue& queue,
               std::int64_t count,
               const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Leaves the memory block currently held in the array, then
    /// assigns a new user-provided block to the array.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$ when count
    ///                     of references on it becomes zero.
    ///
    /// @param data         The mutable memory block pointer to be assigned into the array
    /// @param count        The number of elements into the block
    /// @param deleter      The object used to free $data$ when reference
    ///                     count on the array becomes zero.
    /// @param dependencies Events that say when $data$ becomes ready to be read or written
    template <typename Deleter>
    void reset(T* data,
               std::int64_t count,
               Deleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Leaves the memory block currently held in the array, then
    /// assigns a new user-provided block to the array.
    ///
    /// @tparam ConstDeleter The type of deleter used to free the $data$ when count
    ///                      of references on it becomes zero.
    ///
    /// @param data          The immutable memory block pointer to be assigned into the array
    /// @param count         The number of elements into the block
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the array becomes zero.
    /// @param dependencies  Events that say when $data$ becomes ready to be read or written
    template <typename ConstDeleter>
    void reset(const T* data,
               std::int64_t count,
               ConstDeleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Leaves the memory block currently held in the array, then
    /// assigns a new user-provided block to the array.
    ///
    /// @tparam Y    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership information with current one.
    /// @param data  Mutable unmanaged data pointer to be assigned to the array.
    /// @param count The number of elements in $data$
    template <typename Y>
    void reset(const array<Y>& ref, T* data, std::int64_t count);

    /// Leaves the memory block currently held in the array, then
    /// assigns a new user-provided block to the array.
    ///
    /// @tparam Y    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership information with current one.
    /// @param data  Immutable unmanaged data pointer to be assigned to the array.
    /// @param count The number of elements in $data$
    template <typename Y>
    void reset(const array<Y>& ref, const T* data, std::int64_t count);

    /// Provides a read-only access to the elements of array.
    /// Does not perform boundary checks.
    const T& operator[](std::int64_t index) const noexcept;
};

} // namespace oneapi::dal
