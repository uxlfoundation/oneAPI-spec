****************************************
Deprecation of methods in ``dal::array``
****************************************

Deprecation: Problem statement
------------------------------

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

In addition, the ``dal::array`` class has a static method ``wrap()`` that allows
the user to create an array from a raw pointer. In case of USM data, this method
does not accept information about the context that was used to allocate the
pointer used to create an array object. That prevents us to have additional
input parameter checks to avoid undefined behavior on the user side.

Proposal
--------

To simplify the behavior of ``dal::array`` objects, it is proposed to:

- deprecate ``need_mutable_data(sycl::queue&, const sycl::usm::alloc::kind&)``
  method.

- change the behavior of ``need_mutable_data()`` method to create a
  mutable data block with the same memory kind as the immutable data block
  previously held in the array.

- recommend user to make an explicit copy via DPC++ capabilities followed by
  ``array::reset()`` call rather than using deprecated method
  ``array::need_mutable_data()``.

- deprecate ``static wrap(T*, std::int64_t count,
  const std::vector<sycl::event>& dependencies)`` method since it does not include
  the information about the context where the data block of type ``T`` is
  allocated.

- create ``static wrap(const sycl::queue&, T*, std::int64_t count,
  const std::vector<sycl::event>& dependencies)`` method instead of deprecated one


Another options that allow not to deprecate ``need_mutable_data()`` can be considered:

a. Change the logic of ``need_mutable_data()`` the way it works only with the
   same queue and allocation kind that are already used in the array for
   immutable data, otherwise throw an exception. This option makes the API of
   the method useless because this case can be covered by
   ``need_mutable_data()`` without input parameters.
b. Leave the method as is, but do not use it internally. This option has bad
   impact on the customers that can face unexpected errors and undefined
   behavior explained in the problem statement section.
