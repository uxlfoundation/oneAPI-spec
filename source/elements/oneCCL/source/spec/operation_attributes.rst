Operation Attributes
====================

oneCCL specification defines collective attributes that serve as modifiers of a collective operation's behavior.
Optionally, they may be passed to the corresponding collective operations.

- allgatherv_attr
- allreduce_attr
- alltoall_attr
- alltoallv_attr
- barrier_attr
- bcast_attr
- reduce_attr
- reduce_scatter_attr

oneCCL specification defines attribute identifiers that may be used to fill collective attribute objects.

The list of attribute identifiers that may be used for any communication operation:

.. code:: cpp

    enum class operation_attr_id {
        priority    = /* unspecified */,
        to_cache    = /* unspecified */,
        synchronous = /* unspecified */,
        match_id    = /* unspecified */
    };

operation_attr_id::priority
    the priority of the communication operation
operation_attr_id::to_cache
    | persistent/non-persistent communication operation
    | should be used in conjunction with ``match_id``
operation_attr_id::synchronous
    synchronous/asynchronous communication operation
operation_attr_id::match_id
    | the unique identifier of the operation
    | enables correct matching and execution of the operations started in different order on different ranks
    | in conjunction with ``to_cache``, it also enables the caching of the communication operation

The list of attribute identifiers that may be used for :ref:`Allreduce`, :ref:`Reduce` and :ref:`ReduceScatter` collective operations:

.. code:: cpp

    enum class allreduce_attr_id {
        reduction_fn = /* unspecified */
    };

    enum class reduce_attr_id {
        reduction_fn = /* unspecified */
    };

    enum class reduce_scatter_attr_id {
        reduction_fn = /* unspecified */
    };

allreduce_attr_id::reduction_fn / reduce_attr_id::reduction_fn / reduce_scatter_attr_id::reduction_fn
    a function pointer for the custom reduction operation that follows the signature:

.. code:: cpp

        typedef void (*ccl_reduction_fn_t)
        (
            const void*,      // in_buf
            size_t,           // in_count
            void*,            // inout_buf
            size_t*,          // out_count
            datatype,         // datatype
            const fn_context* // context
        );

        typedef struct {
            const char* match_id;
            const size_t offset;
        } fn_context;

The ``environment`` class shall provide the ability to create an attribute object for a collective communication operation.

Creating an operation attribute object, which may be used in a corresponding collective communication operation:

.. code:: cpp

    using allgatherv_attr_t = unique_ptr_class<allgatherv_attr>;
    using allreduce_attr_t = unique_ptr_class<allreduce_attr>;
    using alltoall_attr_t = unique_ptr_class<alltoall_attr>;
    using alltoallv_attr_t = unique_ptr_class<alltoallv_attr>;
    using barrier_attr_t = unique_ptr_class<barrier_attr>;
    using bcast_attr_t = unique_ptr_class<bcast_attr>;
    using reduce_attr_t = unique_ptr_class<reduce_attr>;
    using reduce_scatter_attr_t = unique_ptr_class<reduce_scatter_attr>;

    allgatherv_attr_t environment::create_allgatherv_attr() const;
    allreduce_attr_t environment::create_allreduce_attr() const;
    alltoall_attr_t environment::create_alltoall_attr() const;
    alltoallv_attr_t environment::create_alltoallv_attr() const;
    barrier_attr_t environment::create_barrier_attr() const;
    bcast_attr_t environment::create_bcast_attr() const;
    reduce_attr_t environment::create_reduce_attr() const;
    reduce_scatter_attr_t environment::create_reduce_scatter_attr() const;

return ``<coll_name>_attr_t``
    an object containing attributes for a specific collective communication operation
