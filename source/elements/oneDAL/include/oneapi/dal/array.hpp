namespace oneapi::dal {

/// @tparam Data The type of the memory block elements within the array.
///
/// @pre $Data$ cannot be const-qualified.
template <typename Data>
class array {
public:
    using data_t = Data;

public:
    /// Allocates a new memory block for mutable data, does not initialize it,
    /// creates a new array instance by passing a pointer to memory block.
    /// The array shall own the memory block (for details, see :txtref:`data_ownership_requirements`).
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type $Data$ to allocate.
    /// @param alloc The kind of USM to be allocated.
    /// @pre :expr:`count > 0`
    static array<Data> empty(const sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Allocates a new memory block for mutable data, fills it with a scalar value,
    /// creates a new array instance by passing a pointer to memory block.
    /// The array shall own the memory block (for details, see :txtref:`data_ownership_requirements`).
    ///
    /// @tparam Element The type from which array elements of type $Data$ can be constructed.
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type $Data$ to allocate.
    /// @param element The value that is used to fill a memory block.
    /// @param alloc   The kind of USM to be allocated.
    /// @pre :expr:`count > 0`
    /// @pre Elements of type ``Data`` are constructible from ``Element`` type.
    template <typename Element>
    static array<Data> full(sycl::queue& queue,
                            std::int64_t count,
                            Element&& element,
                            const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Allocates a new memory block on mutable data, fills it with zeros,
    /// creates a new array instance by passing a pointer to memory block.
    /// The array shall own the memory block (for details, see :txtref:`data_ownership_requirements`).
    ///
    /// @param queue   The SYCL* queue object.
    /// @param count   The number of elements of type $Data$ to allocate.
    /// @param alloc   The kind of USM to be allocated.
    /// @pre :expr:`count > 0`
    static array<Data> zeros(sycl::queue& queue,
                             std::int64_t count,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates a new array instance by passing the pointer to externally-allocated memory block
    /// for mutable data. It is responsibility of the calling application to free memory block
    /// as the array shall not free it when reference counter equals to zero.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type $Data$ in the memory block.
    /// @param dependencies Events indicating availability of the $data$ for reading or writing.
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<Data> wrap(Data* data,
                            std::int64_t count,
                            const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates a new array instance by passing the pointer to externally-allocated memory block
    /// for immutable data. It is responsibility of the calling application to free memory block
    /// as the array shall not free it when reference counter equals to zero.
    ///
    /// @param data         The pointer to externally-allocated memory block.
    /// @param count        The number of elements of type $Data$ in the memory block.
    /// @param dependencies Events indicating availability of the $data$ for reading or writing.
    /// @pre :expr:`data != nullptr`
    /// @pre :expr:`count > 0`
    static array<Data> wrap(const Data* data,
                            std::int64_t count,
                            const sycl::vector_class<sycl::event>& dependencies = {});

public:
    /// Creates a new instance of the class without memory allocation:
    /// :expr:`mutable_data` and :expr:`data` pointers shall be set to ``nullptr``,
    /// :expr:`count` shall be to zero; the pointer to the ownership structure shall be set to ``nullptr``.
    array();

    /// Creates new array instance that shares an ownership with $other$ on its memory block.
    array(const array<Data>& other);

    /// Moves :expr:`data`, :expr:`mutable_data` pointers, :expr:`count`, and pointer to the ownership structure
    /// in $other$ to the new array instance
    array(array<Data>&& other);

    /// Creates a new array instance which owns a memory block of externally-allocated mutable data.
    /// The ownership structure shall be created for a block, the input $deleter$
    /// shall be assigned to it.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$.
    ///                     The deleter shall provide ``void operator()(Data*)`` member function.
    ///
    /// @param queue        The SYCL* queue object.
    /// @param data         The pointer to externally-allocated memory block.
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

    /// Creates a new array instance which owns a memory block of externally-allocated immutable data.
    /// The ownership structure shall be created for a block, the input $deleter$
    /// shall be assigned to it.
    ///
    /// @tparam ConstDeleter The type of deleter used to free the $data$.
    ///                      The deleter shall implement ``void operator()(const Data*)`` member function.
    ///
    /// @param queue         The SYCL* queue object.
    /// @param data          The pointer to externally-allocated memory block.
    /// @param count         The number of elements of type $Data$ in the $data$.
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the memory block becomes zero.
    /// @param dependencies  Events indicating availability of the $data$ for reading or writing.
    template <typename ConstDeleter>
    explicit array(const sycl::queue& queue,
                   const Data* data,
                   std::int64_t count,
                   ConstDeleter&& deleter,
                   const sycl::vector_class<sycl::event>& dependencies = {});

    /// An aliasing constructor: creates a new array instance that stores $data$ pointer,
    /// assigns the pointer to the ownership structure of $ref$ to the new instance, and increments
    /// its reference counter.
    /// Array shall return $data$ pointer as its mutable or immutable block depending
    /// on the $ExtData$ type.
    ///
    /// @tparam RefData    The type of elements in the reference array
    /// @tparam ExtData    Either $Data$ or $const Data$ type.
    ///
    /// @param ref   The array which shares ownership structure with created
    ///              one.
    /// @param data  Mutable or immutable unmanaged pointer hold by
    ///              created array.
    /// @param count The number of elements of type $Data$ in the $data$
    ///
    /// @pre  :expr:`std::is_same_v<ExtData, const Data> || std::is_same_v<ExtData, Data>`
    template <typename RefData, typename ExtData>
    explicit array(const array<RefData>& ref, ExtData* data, std::int64_t count);

    /// Decrements the reference counter,
    /// calls the deleter if number of references becomes zero,
    /// replaces the :expr:`data`, :expr:`mutable_data` pointers, :expr:`count`, and pointer
    /// to the ownership structure in the array instance by the values in $other$, increments its reference counter.
    /// If the deleter on the previous block is called, the replaced ownership structure shall also be freed.
    ///
    /// @post :expr:`data == other.data`
    /// @post :expr:`mutable_data == other.mutable_data`
    /// @post :expr:`count == other.count`
    array<Data> operator=(const array<Data>& other);

    /// Swaps the values of :expr:`data`, :expr:`mutable_data` pointers, :expr:`count`, and pointer
    /// to the ownership structure in the array instance and $other$.
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

    /// If the array does not contain :expr:`mutable_data`,
    /// allocates new memory block to mutable data and copies the data held in the :expr:`data` pointer inside it.
    /// The ownership structure on new memory block shall be created and set to the array.
    /// Reference counter in previos ownership structure shall be decremented.
    /// Shall not perform all these operations if array contains :expr:`mutable_data`.
    ///
    /// @param queue The SYCL* queue object.
    /// @param alloc The kind of USM to be allocated
    ///
    /// @post :expr:`has_mutable_data() == true`
    array& need_mutable_data(sycl::queue& queue,
                             const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// The number of elements of type $Data$ in a memory block
    std::int64_t get_count() const noexcept;

    /// The size of memory block in bytes
    /// @invariant :expr:`size == count * sizeof(Data)`
    std::int64_t get_size() const noexcept;

    /// Resets ownership structure not to hold any memory block,
    /// decrements the reference counter to the memory block held in the array.
    /// Shall set :expr:`count` to zero, :expr:`data` and :expr:`mutable_data` to :expr:`nullptr`.
    void reset();

    /// Allocates a new memory block for mutable data, does not initialize it,
    /// creates ownership structure for this block, assigns the structure inside the array.
    /// Decrements the reference counter in the ownership structure previously held in the array.
    /// The array shall own allocated memory block.
    ///
    /// @param queue The SYCL* queue object.
    /// @param count The number of elements of type $Data$ to allocate in a new memory block
    /// @param alloc The kind of USM to be allocated
    void reset(const sycl::queue& queue,
               std::int64_t count,
               const sycl::usm::alloc& alloc = sycl::usm::alloc::shared);

    /// Creates the ownership structure for memory block of externally-allocated mutable data,
    /// assigns input $deleter$ object to it,
    /// sets :expr:`data` and :expr:`mutable_data` pointers to this block.
    /// Decrements the reference counter in the ownership structure previously held in the array.
    ///
    /// @tparam Deleter     The type of deleter used to free the $data$.
    ///                     The deleter shall implement ``void operator()(Data*)`` member function.
    ///
    /// @param data         The mutable memory block pointer to be assigned inside the array
    /// @param count        The number of elements of type $Data$ into the block
    /// @param deleter      The object used to free $data$ when reference
    ///                     count on the array becomes zero.
    /// @param dependencies Events indicating availability of the $data$ for reading or writing.
    template <typename Deleter>
    void reset(Data* data,
               std::int64_t count,
               Deleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Creates the ownership structure for memory block of externally-allocated immutable data,
    /// assigns input $deleter$ object to it,
    /// sets :expr:`data` pointer to this block.
    /// Decrements the reference counter in the ownership structure previously held in the array.
    ///
    /// @tparam ConstDeleter The type of deleter used to free.
    ///                      The deleter shall implement `void operator()(const Data*)`` member function.
    ///
    /// @param data          The immutable memory block pointer to be assigned inside the array
    /// @param count         The number of elements of type $Data$ into the block
    /// @param deleter       The object used to free $data$ when reference
    ///                      count on the array becomes zero.
    /// @param dependencies  Events indicating availability of the $data$ for reading or writing.
    template <typename ConstDeleter>
    void reset(const Data* data,
               std::int64_t count,
               ConstDeleter&& deleter,
               const sycl::vector_class<sycl::event>& dependencies = {});

    /// Passes $data$ pointer to :expr:`data` and :expr:`mutable_data` pointers,
    /// assigns the pointer to ownership structure of $ref$ to the current instance, and increments
    /// its reference counter.
    /// Decrements the reference counter in the ownership structure previously held in the array.
    /// Array shall return $data$ pointer as its mutable block.

    /// @tparam RefData    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership structure with current one.
    /// @param data  Mutable unmanaged pointer to be assigned to the array.
    /// @param count The number of elements of type $Data$ in the $data$
    template <typename RefData>
    void reset(const array<RefData>& ref, Data* data, std::int64_t count);

    /// Passes $data$ pointer to the :expr:`data` property,
    /// assigns the pointer to ownership structure of $ref$ to the current instance, and increments
    /// its reference counter.
    /// Decrements the reference counter in the ownership structure previously held in the array.
    /// Array shall return $data$ pointer as its immutable block.
    ///
    /// @tparam RefData    The type of elements in the reference array
    ///
    /// @param ref   The array which is used to share ownership structure with current one.
    /// @param data  Immutable unmanaged pointer to be assigned to the array.
    /// @param count The number of elements of type $Data$ in the $data$
    template <typename RefData>
    void reset(const array<RefData>& ref, const Data* data, std::int64_t count);

    /// Provides a read-only access to the elements of array.
    /// Shall not perform boundary checks.
    const Data& operator[](std::int64_t index) const noexcept;
};

} // namespace oneapi::dal
