*************
Meeting notes
*************

2021-03-31
##########

Agenda
------

- Deprecation of some methods of ``dal::array`` class.

Problem statement
-----------------

Objects of ``dal::array`` class can hold mutable or immutable data. The
``dal::array::need_mutable_data`` method allows users to replace immutable data
previously held in the array with the newly allocated mutable data block. The
data are copied from the previous immutable memory block.

This method has two overloadings:

1. Without any arguments: ``dal::array::need_mutable_data()``. This method
   assumes that data are located on the host and performs memory allocations,
   data copies on the host.

2. With queue and alloc_kind parameters:
   ``dal::array::need_mutable_data(sycl::queue&, const
   sycl::usm::alloc::kind&)``. This method allocates a new memory block with the
   requested memory kind using the queue passed as a parameter. The queue is
   also used to copy the data from the previous immutable data block.

The second overloading does not only change the data mutability attribute, but also
a data location and memory kind. This behavior can be unexpected in user
applications:

.. code-block:: cpp

    template <typename T>
    void bar(sycl::queue& q, array<T>& x) {
        // ...
        x.need_mutable_data(q, sycl::usm::alloc::device);
        // ...
    }

    template <typename T>
    void foo(sycl::queue& q, array<T>& x) {
        // `x` is allocated on HOST
        const T a = x[0] // <- OK
        bar(q, x);
        // Allocation is changed to USM-device
        // This happens implicitly to the caller
        // Super unexpected behavior!
        const T b = x[0]; // <- SEGFAULT
    }

Proposal
--------

To simplify the behavior of ``dal::array`` objects, it is proposed to:

- deprecate ``need_mutable_data(sycl::queue&, const sycl::usm::alloc::kind&)``
  method.

- change the behavior of ``need_mutable_data()`` method to create a
  mutable data block with the same memory kind as the immutable data block
  previously held in the array.

- deprecate ``static wrap(T*, std::int64_t count,
  const std::vector<sycl::event>& dependencies)`` method since it does not include
  the information about the context where the data block of type ``T`` is
  allocated.

- create ``static wrap(const sycl::queue&, T*, std::int64_t count,
  const std::vector<sycl::event>& dependencies)`` method instead of deprecated one

Decision
--------

1. Approve proposed changes

2. Look one more time on the ``dal::array`` API:
   some methods may require similar changes too (``reset`` method for example).

3. Example on array use cases in the spec requires modification because of
   proposed API changes.

4. Descriptions of methods behavior in the spec may require modifications
   because of proposed changes.

5. Need to perform synchronization between oneDAL spec and documentation of
   Intel(R) oneDAL product, and eliminate a possible difference in the current
   implementation of Intel(R) oneDAL and the behavior required by the spec. This
   work can be done iteratively on regular basis by including particular tasks
   in the sprints of the developer team.
