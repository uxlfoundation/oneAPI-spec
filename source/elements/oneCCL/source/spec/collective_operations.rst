Collective Operations
=====================

oneCCL specification defines the following collective communication operations:

- `Allgatherv`_
- `Allreduce`_
- `Alltoall`_
- `Alltoallv`_
- `Barrier`_
- `Broadcast`_
- `Reduce`_
- `ReduceScatter`_

These operations are collective, meaning that all participants (ranks) of oneCCL communicator should make a call.
The order of collective operation calls should be the same across all ranks, unless the ``match_id`` attribute is used to match calls done without a strict order.

``communicator`` shall provide the ability to perform communication operations on host memory buffers.

``device_communicator`` shall provide the ability to perform communication operations on device memory buffers. Additionally, device communication operations shall accept the device's execution context and a vector of events that the device communication operation should depend on. The output ``request`` object shall provide the ability to retrieve the ``event`` object that is signaled when the communication operation completes.

``BufferType`` is used below to define the C++ type of elements in data buffers (``buf``, ``send_buf`` and  ``recv_buf``) of communication operations. At least the following types shall be supported: ``[u]int{8/16/32/64}_t``, ``float``, ``double``. The explicit ``datatype`` parameter shall be used to enable data types which cannot be inferred from the function arguments.

.. note::
    See also: :ref:`Custom Datatypes`

The communication operation may accept attribute object. If that parameter is missed then default attribute object will be used (default_<op_name>_attr) which shall be provided by the library.

.. note::
    See also: :doc:`operation_attributes`

If the arguments provided to a communication operation call do not comply to the requirements of the operation, the behavior is undefined unless it is specified otherwise.

.. _Allgatherv:

Allgatherv
**********

Allgatherv is a collective communication operation that collects data from all the ranks within a communicator into a single buffer. Different ranks may contribute segments of different sizes. The resulting data in the output buffer must be the same for each rank.

.. code:: cpp

    template<class BufferType>
    request communicator::allgatherv(const BufferType* send_buf,
                                     size_t send_count,
                                     BufferType* recv_buf,
                                     const vector_class<size_t>& recv_counts,
                                     const allgatherv_attr& attr = default_allgatherv_attr);

    request communicator::allgatherv(const void* send_buf,
                                     size_t send_count,
                                     void* recv_buf,
                                     const vector_class<size_t>& recv_counts,
                                     datatype dtype,
                                     const allgatherv_attr& attr = default_allgatherv_attr);

.. code:: cpp

    template<class BufferType>
    request device_communicator::allgatherv(const BufferType* send_buf,
                                            size_t send_count,
                                            BufferType* recv_buf,
                                            const vector_class<size_t>& recv_counts,
                                            stream op_stream,
                                            const allgatherv_attr& attr = default_allgatherv_attr,
                                            const vector_class<event>& deps = {});

    request device_communicator::allgatherv(const void* send_buf,
                                            size_t send_count,
                                            void* recv_buf,
                                            const vector_class<size_t>& recv_counts,
                                            datatype dtype,
                                            stream op_stream,
                                            const allgatherv_attr& attr = default_allgatherv_attr,
                                            const vector_class<event>& deps = {});

send_buf
    the buffer with ``send_count`` elements of ``BufferType`` that stores local data to be gathered
send_count
    the number of elements of type ``BufferType`` in ``send_buf``
recv_buf [out]
    the buffer to store the gathered result, must be large enough to hold values from all ranks
recv_counts
    | an array with the number of elements of type ``BufferType`` to be received from each rank
    | the array's size must be equal to the number of ranks
    | the values in the array are expected to be the same for all ranks
    | the value at the position of the caller's rank must be equal to ``send_count``
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Allreduce:

Allreduce
*********

Allreduce is a collective communication operation that performs the global reduction operation on values from all ranks of communicator and distributes the result back to all ranks.

.. code:: cpp

    template <class BufferType>
    request communicator::allreduce(const BufferType* send_buf,
                                    BufferType* recv_buf,
                                    size_t count,
                                    reduction rtype,
                                    const allreduce_attr& attr = default_allreduce_attr);

    request communicator::allreduce(const void* send_buf,
                                    void* recv_buf,
                                    size_t count,
                                    reduction rtype,
                                    datatype dtype,
                                    const allreduce_attr& attr = default_allreduce_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::allreduce(const BufferType* send_buf,
                                           BufferType* recv_buf,
                                           size_t count,
                                           reduction rtype,
                                           stream op_stream,
                                           const allreduce_attr& attr = default_allreduce_attr,
                                           const vector_class<event>& deps = {});

    request device_communicator::allreduce(const void* send_buf,
                                           void* recv_buf,
                                           size_t count,
                                           reduction rtype,
                                           datatype dtype,
                                           stream op_stream,
                                           const allreduce_attr& attr = default_allreduce_attr,
                                           const vector_class<event>& deps = {});

send_buf
    the buffer with ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    the buffer to store the reduced result, must have the same dimension as ``send_buf``
count
    the number of elements of type ``BufferType`` in ``send_buf`` and ``recv_buf``
rtype
    the type of the reduction operation to be applied
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Alltoall:

Alltoall
********

Alltoall is a collective communication operation in which each rank
sends separate equal-sized blocks of data to each rank.
The j-th block of send buffer sent from the i-th rank is received by the j-th rank
and is placed in the i-th block of receive buffer.

.. code:: cpp

    template <class BufferType>
    request communicator::alltoall(const BufferType* send_buf,
                                   BufferType* recv_buf,
                                   size_t count,
                                   const alltoall_attr& attr = default_alltoall_attr);

    request communicator::alltoall(const void* send_buf,
                                   void* recv_buf,
                                   size_t count,
                                   datatype dtype,
                                   const alltoall_attr& attr = default_alltoall_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::alltoall(const BufferType* send_buf,
                                          BufferType* recv_buf,
                                          size_t count,
                                          stream op_stream,
                                          const alltoall_attr& attr = default_alltoall_attr,
                                          const vector_class<event>& deps = {});

    request device_communicator::alltoall(const void* send_buf,
                                          void* recv_buf,
                                          size_t count,
                                          datatype dtype,
                                          stream op_stream,
                                          const alltoall_attr& attr = default_alltoall_attr,
                                          const vector_class<event>& deps = {});

send_buf
    the buffer with ``count`` elements of ``BufferType`` that stores local data to be sent
recv_buf [out]
    | the buffer to store the received result, must be large enough
    | to hold values from all ranks, i.e. at least ``comm_size`` * ``count``
count
    the number of elements to be send to or to received from each rank
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Alltoallv:

Alltoallv
*********

Alltoall is a collective communication operation in which each rank
sends separate blocks of data to each rank. Block sizes may differ.
The j-th block of send buffer sent from the i-th rank is received by the j-th rank
and is placed in the i-th block of receive buffer.

.. code:: cpp

    template <class BufferType>
    request communicator::alltoallv(const BufferType* send_buf,
                                    const vector_class<size_t>& send_counts,
                                    BufferType* recv_buf,
                                    const vector_class<size_t>& recv_counts,
                                    const alltoallv_attr& attr = default_alltoallv_attr);

    request communicator::alltoallv(const void* send_buf,
                                    const vector_class<size_t>& send_counts,
                                    void* recv_buf,
                                    const vector_class<size_t>& recv_counts,
                                    datatype dtype,
                                    const alltoallv_attr& attr = default_alltoallv_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::alltoallv(const BufferType* send_buf,
                                           const vector_class<size_t>& send_counts,
                                           BufferType* recv_buf,
                                           const vector_class<size_t>& recv_counts,
                                           stream op_stream,
                                           const alltoallv_attr& attr = default_alltoallv_attr,
                                           const vector_class<event>& deps = {});

    request device_communicator::alltoallv(const void* send_buf,
                                           const vector_class<size_t>& send_counts,
                                           void* recv_buf,
                                           const vector_class<size_t>& recv_counts,
                                           datatype dtype,
                                           stream op_stream,
                                           const alltoallv_attr& attr = default_alltoallv_attr,
                                           const vector_class<event>& deps = {});

send_buf
    the buffer with elements of ``BufferType`` that stores local blocks to be sent to each rank
send_counts
    | an array with number of elements of type ``BufferType`` in the blocks sent for each rank
    | the array's size must be equal to the number of ranks
    | the values at the position of the caller's rank in ``send_counts`` and ``recv_counts`` must be equal
recv_buf [out]
    the buffer to store the received result, must be large enough to hold blocks from all ranks
recv_counts
    | an array with number of elements of type ``BufferType`` in the blocks received from each rank
    | the array's size must be equal to the number of ranks
    | the values at the position of the caller's rank in ``send_counts`` and ``recv_counts`` must be equal
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Barrier:

Barrier
*******

Barrier synchronization is performed across all ranks of the communicator
and it is completed only after all the ranks in the communicator have called it.

.. code:: cpp

    request communicator::barrier(const barrier_attr& attr = default_barrier_attr);

.. code:: cpp

    request device_communicator::barrier(stream op_stream,
                                         const barrier_attr& attr = default_barrier_attr,
                                         const vector_class<event>& deps = {});

op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Broadcast:

Broadcast
*********

Broadcast is a collective communication operation that broadcasts data
from one rank of communicator (denoted as root) to all other ranks.

.. code:: cpp

    template <class BufferType>
    request communicator::broadcast(BufferType* buf,
                                    size_t count,
                                    size_t root,
                                    const broadcast_attr& attr = default_broadcast_attr);

    request communicator::broadcast(void* buf,
                                    size_t count,
                                    datatype dtype,
                                    size_t root,
                                    const broadcast_attr& attr = default_broadcast_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::broadcast(BufferType* buf,
                                           size_t count,
                                           size_t root,
                                           stream op_stream,
                                           const broadcast_attr& attr = default_broadcast_attr,
                                           const vector_class<event>& deps = {});

    request device_communicator::broadcast(void* buf,
                                           size_t count,
                                           datatype dtype,
                                           size_t root,
                                           stream op_stream,
                                           const broadcast_attr& attr = default_broadcast_attr,
                                           const vector_class<event>& deps = {});

buf [in,out]
    | the buffer with ``count`` elements of ``BufferType``
    | serves as ``send_buf`` for root and as ``recv_buf`` for other ranks
count
    the number of elements of type ``BufferType`` in ``buf``
root
    the rank that broadcasts ``buf``
dtype
    | the datatype of elements in ``buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _Reduce:

Reduce
******

Reduce is a collective communication operation that performs the global reduction operation
on values from all ranks of the communicator and returns the result to the root rank

.. code:: cpp

    template <class BufferType>
    request communicator::reduce(const BufferType* send_buf,
                                 BufferType* recv_buf,
                                 size_t count,
                                 reduction rtype,
                                 size_t root,
                                 const reduce_attr& attr = default_reduce_attr);

    request communicator::reduce(const void* send_buf,
                                 void* recv_buf,
                                 size_t count,
                                 datatype dtype,
                                 reduction rtype,
                                 size_t root,
                                 const reduce_attr& attr = default_reduce_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::reduce(const BufferType* send_buf,
                                        BufferType* recv_buf,
                                        size_t count,
                                        reduction rtype,
                                        size_t root,
                                        stream op_stream,
                                        const reduce_attr& attr = default_reduce_attr,
                                        const vector_class<event>& deps = {});

    request device_communicator::reduce(const void* send_buf,
                                        void* recv_buf,
                                        size_t count,
                                        datatype dtype,
                                        reduction rtype,
                                        size_t root,
                                        stream op_stream,
                                        const reduce_attr& attr = default_reduce_attr,
                                        const vector_class<event>& deps = {});

send_buf
    the buffer with ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    | the buffer to store the reduced result, must have the same dimension as ``send_buf``.
    | Used by the ``root`` rank only, ignored by other ranks.
count
    the number of elements of type ``BufferType`` in ``send_buf`` and ``recv_buf``
rtype
    the type of the reduction operation to be applied
root
    the rank that gets the result of the reduction
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. _ReduceScatter:

ReduceScatter
**************

Reduce-scatter is a collective communication operation that performs the global reduction operation
on values from all ranks of the communicator and scatters the result in blocks back to all ranks.

.. code:: cpp

    template <class BufferType>
    request communicator::reduce_scatter(const BufferType* send_buf,
                                         BufferType* recv_buf,
                                         size_t recv_count,
                                         reduction rtype,
                                         const reduce_scatter_attr& attr = default_reduce_scatter_attr);

    request communicator::reduce_scatter(const void* send_buf,
                                         void* recv_buf,
                                         size_t recv_count,
                                         datatype dtype,
                                         reduction rtype,
                                         const reduce_scatter_attr& attr = default_reduce_scatter_attr);

.. code:: cpp

    template <class BufferType>
    request device_communicator::reduce_scatter(const BufferType* send_buf,
                                                BufferType* recv_buf,
                                                size_t recv_count,
                                                reduction rtype,
                                                stream op_stream,
                                                const reduce_scatter_attr& attr = default_reduce_scatter_attr,
                                                const vector_class<event>& deps = {});

    request device_communicator::reduce_scatter(const void* send_buf,
                                                void* recv_buf,
                                                size_t recv_count,
                                                datatype dtype,
                                                reduction rtype,
                                                stream op_stream,
                                                const reduce_scatter_attr& attr = default_reduce_scatter_attr,
                                                const vector_class<event>& deps = {});

send_buf
    the buffer with ``comm_size`` * ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    the buffer to store the result block containing ``recv_count`` elements of type ``BufferType``
recv_count
    the number of elements of type ``BufferType`` in the received block
rtype
    the type of the reduction operation to be applied
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
op_stream
    | the stream associated with the operation
    | relevant for device communicator
attr
    optional attributes to customize the operation
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
return ``request``
    an object to track the progress of the operation


.. note::
    See also:

    - :ref:`Communicator`
    - :ref:`Device Communicator`
    - :ref:`Request`
    - :ref:`Stream`
    - :ref:`Event`
    - :doc:`operation_progress`
