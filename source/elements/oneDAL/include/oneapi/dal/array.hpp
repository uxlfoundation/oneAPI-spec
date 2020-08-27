namespace oneapi::dal {

/// @tparam Data The type of the memory block elements inside the array.
///
/// @pre $Data$ cannot be const-qualified.
template <typename Data>
class array {
public:
    using data_t = Data;

public:
    /// Allocates a new memory block, but do not initialize it with any value.
    /// Creates a new array that manages the lifetime of the block.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type $Data$ to allocate.
    /// @param alloc The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    static array<Data> empty(const sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Allocates a new memory block, then fills it with scalar value.
    /// Creates a new array that manages the lifetime of the block.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @tparam Element The type that array elements of type $Data$ can be constructed from.
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type $Data$ to allocate.
    /// @param element The value that is used to fill memory block.
    /// @param alloc   The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    /// @pre Elements of type ``Data`` are constructible from ``Element`` type.
    template <typename Element>
    static array<Data> full(sycl::queue& queue,
                            std::int64_t count,
                            Element&& element,
                            const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Allocates a new memory block, then fills it with zeros.
    /// Creates a new array that manages the lifetime of the block.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type $Data$ to allocate.
    /// @param alloc   The kind of memory to be allocated.
    /// @pre :expr:`count > 0`
    static array<Data> zeros(sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array that holds unmanaged memory block on mutable data.
    /// Responsibility to free this block remains on the user side.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @param data         The pointer to user-allocated memory block.
    /// @param count        The number of elements of type $Data$ in memory block.
    /// @param dependencies Events that indicate when $data$ becomes ready to be read or written.
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<Data> wrap(Data* data,
                            std::int64_t count,
                            const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates a new array that hold unmanaged memory block on immutable data.
    /// Responsibility to free this block remains on the user side.
    /// Shall set :expr:`data` pointer to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @param data         The pointer to user-allocated memory block.
    /// @param count        The number of elements of type $Data$ in memory block.
    /// @param dependencies Events that indicate when $data$ becomes ready to be read or written.
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<Data> wrap(const Data* data,
                            std::int64_t count,
                            const sycl::vector_class<sycl::event>& dependencies = {});

public:
    /// Creates a new instance of the class without any data.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to ``nullptr``.
    /// Shall set :expr:`count` to zero.
    array();

    /// Creates new array object that shares an ownership with $other$ on its memory
    /// block: no data are copied, but just a reference count on the original
    /// memory block is incremented.
    /// Shall set :expr:`mutable_data` to :expr:`other.mutable_data` and :expr:`data` to :expr:`other.data`.
    /// Shall set :expr:`count` to :expr:`other.count`.
    array(const array<Data>& other);

    /// Moves $other$ into the new array instance with its memory block and ownership information.
    /// Shall not create a new ownership information objects or increment reference count.
    array(array<Data>&& other);

    /// Creates a new array instance which holds a pointer to user-allocated data.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the input $data$ pointer.
    /// Shall set :expr:`count` to input $count$ value.
    /// Shall hold ownership information on the data - the $deleter$ object, $dependencies$,
    /// and the number of references that shall be set to one by this constructor.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$ when count
    ///                     of references on it becomes zero.
    ///                     The deleter shall implement ``void operator()(Data*)`` member function.
    ///
    /// @param queue        The SYCL* queue object.
    /// @param data         The pointer to user-allocated memory block.
    /// @param count        The number of elements of type $Data$ in the memory block.
    /// @param deleter      The object used to free $data$ when reference
    ///                     count on the memory block becomes zero.
    /// @param dependencies Events that indicate when $data$ becomes ready to be read or written
    template <typename Deleter>
    explicit array(const sycl::queue& queue,
                   Data* data,
                   std::int64_t count,
                   Deleter&& deleter,
                   const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates a new array instance which holds a pointer to user-allocated data.
    /// Shall set :expr:`data` pointer to the input $data$ pointer.
    /// Shall set :expr:`mutable_data` pointer to ``nullptr``.
    /// Shall set :expr:`count` to input $count$ value.
    /// Shall hold ownership information on the data - the $deleter$ object, $dependencies$,
    /// and the number of references that shall be set to one by this constructor.
    ///
    /// @tparam ConstDeleter The type of deleter used to free the $data$ when count
    ///                      of references on it becomes zero.
    ///                      The deleter shall implement ``void operator()(const Data*)`` member function.
    ///
    /// @param queue         The SYCL* queue object.
    /// @param data          The pointer to user-allocated memory block.
    /// @param count         The number of elements of type $Data$ in the $data$.
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the memory block becomes zero.
    /// @param dependencies  Events that indicate when $data$ becomes ready to be read or written
    template <typename ConstDeleter>
    explicit array(const sycl::queue& queue,
                   const Data* data,
                   std::int64_t count,
                   ConstDeleter&& deleter,
                   const sycl::vector_class<sycl::event>& dependencies = {});

    /// An aliasing constructor: creates a new array that hold $data$ pointer
    /// and shares ownership information with $ref$. If this array is the last
    /// reference to go out of the scope, than deleter of the $ref$ is called.
    /// Array returns $data$ pointer as its mutable or immutable block depending
    /// on the $K$ type. Shall set :expr:`count` to input $count$ value.
    ///
    /// @tparam Y    The type of elements in the reference array
    /// @tparam K    Either $Data$ or $const Data$ type.
    ///
    /// @param ref   The array which shares ownership information with created
    ///              one.
    /// @param data  Mutable or immutable unmanaged pointer hold by
    ///              created array.
    /// @param count The number of elements of type $Data$ in the $data$
    ///
    /// @pre  :expr:`std::is_same_v<K, const Data> || std::is_same_v<K, Data>`
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
    array<Data> operator=(const array<Data>& other);

    /// Moves the memory block of $other$ into this one.
    /// Ownership information is moved from $other$ to this object.
    /// Shall replace :expr:`data`, :expr:`mutable_data`, and :expr:`count` property values
    /// by the corresponding property values of :expr:`other`.
    ///
    /// @param other The object which is moved into this one.
    array<Data> operator=(array<Data>&& other);

    /// The pointer to memory block holding mutable data.
    /// @pre :expr:`has_mutable_data() == true`, othewise throws `domain_error`
    /// @invariant :expr:`mutable_data != nullptr` if :expr:`has_mutable_data() && count > 0`
    Data* get_mutable_data() const;

    /// The pointer to memory block holding immutable data.
    /// @invariant :expr:`data != nullptr` if :expr:`count > 0`
    /// @invariant if :expr:`has_mutable_data() == true` then `data == mutable_data`
    const Data* get_data() const noexcept;

    /// Returns whether array contains :expr:`mutable_data` or not
    ///
    /// @invariant :expr:`mutable_data != nullptr` if this returns `true` and :expr:`count > 0`
    bool has_mutable_data() const noexcept;

    /// If array do not contain :expr:`mutable_data`,
    /// allocates new mutable memory block and copies the data held in the :expr:`data` into it.
    /// Resets ownership information to target newly allocated block by
    /// decrementing reference count on previous immutable block and incrementing it for the new one.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the new block.
    /// Shall not perform all these operations if array already contains :expr:`mutable_data`.
    ///
    /// @param queue The SYCL* queue object.
    /// @param alloc The kind of memory to be allocated
    ///
    /// @post :expr:`has_mutable_data() == true`
    array& need_mutable_data(sycl::queue& queue,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// The number of elements of type $Data$ in a memory block
    std::int64_t get_count() const noexcept;

    /// The size of memory block in bytes
    /// @invariant :expr:`size == count * sizeof(Data)`
    std::int64_t get_size() const noexcept;

    /// Decrements the number of references to the memory block held in the array.
    /// Shall set :expr:`count` to zero, :expr:`data` and :expr:`mutable_data` to :expr:`nullptr`.
    void reset();

    /// Decrements the number of references to the memory block held in the array.
    /// Allocates a new block, increments the number of references to it in the array.
    /// Shall set :expr:`mutable_data` and :expr:`data` pointers to the start of the block.
    /// Shall set :expr:`count` to the number of allocated elements.
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type $Data$ to allocate in a new memory block
    /// @param alloc The kind of memory to be allocated
    void reset(const sycl::queue& queue,
               std::int64_t count,
               const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Decrements the number of references to the memory block held in the array.
    /// Shall set :expr:`data` and :expr:`mutable_data` pointers to the input $data$ pointer.
    /// Shall set :expr:`count` to input $count$ value.
    /// Shall hold ownership information on the data - the $deleter$ object, $dependencies$,
    /// and the number of references that shall be set to one by this method.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$ when count
    ///                     of references on it becomes zero.
    ///                     The deleter shall implement ``void operator()(Data*)`` member function.
    ///
    /// @param data         The mutable memory block pointer to be assigned into the array
    /// @param count        The number of elements of type $Data$ into the block
    /// @param deleter      The object used to free $data$ when reference
    ///                     count on the array becomes zero.
    /// @param dependencies Events that indicate when $data$ becomes ready to be read or written
    template <typename Deleter>
    void reset(Data* data,
               std::int64_t count,
               Deleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Shall set :expr:`data` pointer to the input $data$ pointer.
    /// Shall set :expr:`mutable_data` pointer to ``nullptr``.
    /// Shall set :expr:`count` to input $count$ value.
    /// Shall hold ownership information on the data - the $deleter$ object, $dependencies$,
    /// and the number of references that shall be set to one by this constructor.
    ///
    /// @tparam ConstDeleter The type of deleter used to free the $data$ when count
    ///                      of references on it becomes zero.
    ///                     The deleter shall implement `void operator()(const Data*)`` member function.
    ///
    /// @param data          The immutable memory block pointer to be assigned into the array
    /// @param count         The number of elements of type $Data$ into the block
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the array becomes zero.
    /// @param dependencies  Events that indicate when $data$ becomes ready to be read or written
    template <typename ConstDeleter>
    void reset(const Data* data,
               std::int64_t count,
               ConstDeleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Resets array with new memory block, shares ownership information with $ref$.
    /// Increments the number of references to the memory block held in $ref$.
    /// If this array goes out of scope with the reference count equal to 1,
    /// the destructor on shared data block is called.
    /// Shall set expr:`data` and :expr:`mutable_data` pointers to the input $data$ pointer.
    /// Shall set :expr:`count` to input $count$ value.
    ///
    /// @tparam Y    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership information with current one.
    /// @param data  Mutable unmanaged pointer to be assigned to the array.
    /// @param count The number of elements of type $Data$ in the $data$
    template <typename Y>
    void reset(const array<Y>& ref, Data* data, std::int64_t count);

    /// Resets array with new memory block, shares ownership information with $ref$.
    /// Increments the number of references to the memory block held in $ref$.
    /// If this array goes out of scope with the reference count equal to 1,
    /// the destructor on shared data block is called.
    /// Shall set expr:`data` pointer to the input $data$ pointer.
    /// Shall set :expr:`mutable_data` pointer to ``nullptr``.
    /// Shall set :expr:`count` to input $count$ value.
    ///
    /// @tparam Y    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership information with current one.
    /// @param data  Immutable unmanaged pointer to be assigned to the array.
    /// @param count The number of elements of type $Data$ in the $data$
    template <typename Y>
    void reset(const array<Y>& ref, const Data* data, std::int64_t count);

    /// Provides a read-only access to the elements of array.
    /// Shall not perform boundary checks.
    const Data& operator[](std::int64_t index) const noexcept;
};

} // namespace oneapi::dal
