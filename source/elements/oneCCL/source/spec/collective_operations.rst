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

``communicator`` shall provide the ability to perform collective communication operations on host memory buffers.

``device_communicator`` shall provide the ability to perform collective communication operations on device memory buffers. Additionally, device collective operations shall accept the device's execution context and a vector of events that the device collective operation should depend on. The output ``request`` object shall provide the ability to retrieve the ``event`` object that is signaled when the collective operation completes on the device.

``BufferType`` is used below to define the C++ type of elements in data buffers (``buf``, ``send_buf`` and  ``recv_buf``) of collective operations. At least the following types shall be supported: ``[u]int{8/16/32/64}_t``, ``float``, ``double``. The explicit ``datatype`` parameter shall be used to enable data types which cannot be inferred from the function arguments.

.. note::
    See also: :ref:`Custom Datatypes`

If the arguments provided to a collective operation call do not comply to the requirements of the operation, the behavior is undefined unless it is specified otherwise.

.. code:: cpp

    using request_t = unique_ptr_class<request>;

.. _Allgatherv:

Allgatherv
**********

Allgatherv is a collective communication operation that collects data from all the ranks within a communicator into a single buffer. Different ranks may contribute segments of different sizes. The resulting data in the output buffer must be the same for each rank.

.. code:: cpp

    template<class BufferType>
    request_t communicator::allgatherv(const BufferType* send_buf,
                                       size_t send_count,
                                       BufferType* recv_buf,
                                       const vector_class<size_t>& recv_counts,
                                       const allgatherv_attr_t& attr = allgatherv_attr_t());

    request_t communicator::allgatherv(const void* send_buf,
                                       size_t send_count,
                                       void* recv_buf,
                                       const vector_class<size_t>& recv_counts,
                                       datatype dtype,
                                       const allgatherv_attr_t& attr = allgatherv_attr_t());

.. code:: cpp

    template<class BufferType>
    request_t device_communicator::allgatherv(const BufferType* send_buf,
                                              size_t send_count,
                                              BufferType* recv_buf,
                                              const vector_class<size_t>& recv_counts,
                                              const stream_t& stream,
                                              const vector_class<event_t>& deps = {},
                                              const allgatherv_attr_t& attr = allgatherv_attr_t());

    request_t device_communicator::allgatherv(const void* send_buf,
                                              size_t send_count,
                                              void* recv_buf,
                                              const vector_class<size_t>& recv_counts,
                                              datatype dtype,
                                              const stream_t& stream,
                                              const vector_class<event_t>& deps = {},
                                              const allgatherv_attr_t& attr = allgatherv_attr_t());

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
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. _Allreduce:

Allreduce
*********

Allreduce is a collective communication operation that performs the global reduction operation on values from all ranks of communicator and distributes the result back to all ranks.

.. code:: cpp

    template <class BufferType>
    request_t communicator::allreduce(const BufferType* send_buf,
                                      BufferType* recv_buf,
                                      size_t count,
                                      reduction reduction,
                                      const allreduce_attr_t& attr = allreduce_attr_t());

    request_t communicator::allreduce(const void* send_buf,
                                      void* recv_buf,
                                      size_t count,
                                      reduction reduction,
                                      datatype dtype,
                                      const allreduce_attr_t& attr = allreduce_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::allreduce(const BufferType* send_buf,
                                             BufferType* recv_buf,
                                             size_t count,
                                             reduction reduction,
                                             const stream_t& stream,
                                             const vector_class<event_t>& deps = {},
                                             const allreduce_attr_t& attr = allreduce_attr_t());

    request_t device_communicator::allreduce(const void* send_buf,
                                             void* recv_buf,
                                             size_t count,
                                             reduction reduction,
                                             datatype dtype,
                                             const stream_t& stream,
                                             const vector_class<event_t>& deps = {},
                                             const allreduce_attr_t& attr = allreduce_attr_t());

send_buf
    the buffer with ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    the buffer to store the reduced result, must have the same dimension as ``send_buf``
count
    the number of elements of type ``BufferType`` in ``send_buf`` and ``recv_buf``
reduction
    the type of the reduction operation to be applied
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
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
    request_t communicator::alltoall(const BufferType* send_buf,
                                     BufferType* recv_buf,
                                     size_t count,
                                     const alltoall_attr_t& attr = alltoall_attr_t());

    request_t communicator::alltoall(const void* send_buf,
                                     void* recv_buf,
                                     size_t count,
                                     datatype dtype,
                                     const alltoall_attr_t& attr = alltoall_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::alltoall(const BufferType* send_buf,
                                            BufferType* recv_buf,
                                            size_t count,
                                            const stream_t& stream,
                                            const vector_class<event_t>& deps = {},
                                            const alltoall_attr_t& attr = alltoall_attr_t());

    request_t device_communicator::alltoall(const void* send_buf,
                                            void* recv_buf,
                                            size_t count,
                                            datatype dtype,
                                            const stream_t& stream,
                                            const vector_class<event_t>& deps = {},
                                            const alltoall_attr_t& attr = alltoall_attr_t());

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
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
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
    request_t communicator::alltoallv(const BufferType* send_buf,
                                      const vector_class<size_t>& send_counts,
                                      BufferType* recv_buf,
                                      const vector_class<size_t>& recv_counts,
                                      const alltoallv_attr_t& attr = alltoallv_attr_t());

    request_t communicator::alltoallv(const void* send_buf,
                                      const vector_class<size_t>& send_counts,
                                      void* recv_buf,
                                      const vector_class<size_t>& recv_counts,
                                      datatype dtype,
                                      const alltoallv_attr_t& attr = alltoallv_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::alltoallv(const BufferType* send_buf,
                                             const vector_class<size_t>& send_counts,
                                             BufferType* recv_buf,
                                             const vector_class<size_t>& recv_counts,
                                             const stream_t& stream,
                                             const vector_class<event_t>& deps = {},
                                             const alltoallv_attr_t& attr = alltoallv_attr_t());

    request_t device_communicator::alltoallv(const void* send_buf,
                                             const vector_class<size_t>& send_counts,
                                             void* recv_buf,
                                             const vector_class<size_t>& recv_counts,
                                             datatype dtype,
                                             const stream_t& stream,
                                             const vector_class<event_t>& deps = {},
                                             const alltoallv_attr_t& attr = alltoallv_attr_t());

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
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. _Barrier:

Barrier
*******

Barrier synchronization is performed across all ranks of the communicator
and it is completed only after all the ranks in the communicator have called it.

.. code:: cpp

    request_t communicator::barrier(const barrier_attr_t& attr = barrier_attr_t());

.. code:: cpp

    request_t device_communicator::barrier(const stream_t& stream,
                                           const vector_class<event_t>& deps = {},
                                           const barrier_attr_t& attr = barrier_attr_t());

stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. _Broadcast:

Broadcast
*********

Broadcast is a collective communication operation that broadcasts data
from one rank of communicator (denoted as root) to all other ranks.

.. code:: cpp

    template <class BufferType>
    request_t communicator::bcast(BufferType* buf,
                                  size_t count,
                                  size_t root,
                                  const bcast_attr_t& attr = bcast_attr_t());

    request_t communicator::bcast(void* buf,
                                  size_t count,
                                  datatype dtype,
                                  size_t root,
                                  const bcast_attr_t& attr = bcast_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::bcast(BufferType* buf,
                                         size_t count,
                                         size_t root,
                                         const stream_t& stream,
                                         const vector_class<event_t>& deps = {},
                                         const bcast_attr_t& attr = bcast_attr_t());

    request_t device_communicator::bcast(void* buf,
                                         size_t count,
                                         datatype dtype,
                                         size_t root,
                                         const stream_t& stream,
                                         const vector_class<event_t>& deps = {},
                                         const bcast_attr_t& attr = bcast_attr_t());

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
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. _Reduce:

Reduce
******

Reduce is a collective communication operation that performs the global reduction operation
on values from all ranks of the communicator and returns the result to the root rank

.. code:: cpp

    template <class BufferType>
    request_t communicator::reduce(const BufferType* send_buf,
                                   BufferType* recv_buf,
                                   size_t count,
                                   reduction reduction,
                                   size_t root,
                                   const reduce_attr_t& attr = reduce_attr_t());

    request_t communicator::reduce(const void* send_buf,
                                   void* recv_buf,
                                   size_t count,
                                   datatype dtype,
                                   reduction reduction,
                                   size_t root,
                                   const reduce_attr_t& attr = reduce_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::reduce(const BufferType* send_buf,
                                          BufferType* recv_buf,
                                          size_t count,
                                          reduction reduction,
                                          size_t root,
                                          const stream_t& stream,
                                          const vector_class<event_t>& deps = {},
                                          const reduce_attr_t& attr = reduce_attr_t());

    request_t device_communicator::reduce(const void* send_buf,
                                          void* recv_buf,
                                          size_t count,
                                          datatype dtype,
                                          reduction reduction,
                                          size_t root,
                                          const stream_t& stream,
                                          const vector_class<event_t>& deps = {},
                                          const reduce_attr_t& attr = reduce_attr_t());

send_buf
    the buffer with ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    | the buffer to store the reduced result, must have the same dimension as ``send_buf``.
    | Used by the ``root`` rank only, ignored by other ranks.
count
    the number of elements of type ``BufferType`` in ``send_buf`` and ``recv_buf``
reduction
    the type of the reduction operation to be applied
root
    the rank that gets the result of the reduction
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. _ReduceScatter:

ReduceScatter
**************

Reduce-scatter is a collective communication operation that performs the global reduction operation
on values from all ranks of the communicator and scatters the result in blocks back to all ranks.

.. code:: cpp

    template <class BufferType>
    request_t communicator::reduce_scatter(const BufferType* send_buf,
                                           BufferType* recv_buf,
                                           size_t recv_count,
                                           reduction reduction,
                                           const reduce_scatter_attr_t& attr = reduce_scatter_attr_t());

    request_t communicator::reduce_scatter(const void* send_buf,
                                           void* recv_buf,
                                           size_t recv_count,
                                           datatype dtype,
                                           reduction reduction,
                                           const reduce_scatter_attr_t& attr = reduce_scatter_attr_t());

.. code:: cpp

    template <class BufferType>
    request_t device_communicator::reduce_scatter(const BufferType* send_buf,
                                                  BufferType* recv_buf,
                                                  size_t recv_count,
                                                  reduction reduction,
                                                  const stream_t& stream,
                                                  const vector_class<event_t>& deps = {},
                                                  const reduce_scatter_attr_t& attr = reduce_scatter_attr_t());

    request_t device_communicator::reduce_scatter(const void* send_buf,
                                                  void* recv_buf,
                                                  size_t recv_count,
                                                  datatype dtype,
                                                  reduction reduction,
                                                  const stream_t& stream,
                                                  const vector_class<event_t>& deps = {},
                                                  const reduce_scatter_attr_t& attr = reduce_scatter_attr_t());

send_buf
    the buffer with ``comm_size`` * ``count`` elements of ``BufferType`` that stores local data to be reduced
recv_buf [out]
    the buffer to store the result block containing ``recv_count`` elements of type ``BufferType``
recv_count
    the number of elements of type ``BufferType`` in the received block
reduction
    the type of the reduction operation to be applied
dtype
    | the datatype of elements in ``send_buf`` and ``recv_buf``
    | must be skipped if ``BufferType`` can be inferred
    | otherwise must be passed explicitly
stream
    | the stream associated with the operation
    | relevant for device communicator
deps
    | an optional vector of the events that the operation should depend on
    | relevant for device communicator
attr
    optional attributes to customize the operation
return ``request_t``
    an object to track the progress of the operation


.. note::
    See also:

    - :ref:`Communicator`
    - :ref:`Device Communicator`
    - :ref:`Request`
    - :ref:`Stream`
    - :ref:`Event`
    - :doc:`operation_progress`
