.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
.. SPDX-FileCopyrightText: Contributors to the oneAPI Specification project.
..
.. SPDX-License-Identifier: CC-BY-4.0

Buffer Wrappers
---------------

.. code:: cpp

  // Defined in <oneapi/dpl/iterator>

  namespace oneapi {
    namespace dpl {

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             TagT tag = sycl::read_write );

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             TagT tag, sycl::property::no_init );

      template < typename T, typename AllocatorT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             sycl::property::no_init );


      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           TagT tag = sycl::read_write );

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           TagT tag, sycl::property::no_init );

      template < typename T, typename AllocatorT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           sycl::property::no_init );

    }
  }

``oneapi::dpl::begin`` and ``oneapi::dpl::end`` are helper functions
for passing SYCL buffers to oneDPL algorithms.
These functions accept a buffer and return an object
of an unspecified type that satisfies the following requirements:

- it is ``CopyConstructible``, ``CopyAssignable``, and comparable
  with operators ``==`` and ``!=``;
- the following expressions are valid: ``a + n``, ``a - n``,
  ``a - b``, where ``a`` and ``b`` are objects of the type,
  and ``n`` is an integer value;
- it provides the ``get_buffer()`` method that returns the buffer
  passed to the ``begin`` or ``end`` function.

When invoking an algorithm, the buffer passed to ``begin`` should be the same
as the buffer passed to ``end``. Otherwise, the behavior is undefined.

SYCL deduction tags (the ``TagT`` parameters) and ``sycl::property::no_init`` 
allow to specify an access mode to be used by algorithms for accessing the buffer.
The mode serves as a hint, and can be overridden depending on semantics of the algorithm.
When invoking an algorithm, the same access mode arguments should be used
for ``begin`` and ``end``. Otherwise, the behavior is undefined.

.. code:: cpp
      
      using namespace oneapi;
      auto buf_begin = dpl::begin(buf, sycl::write_only);
      auto buf_end_1 = dpl::end(buf, sycl::write_only);
      auto buf_end_2 = dpl::end(buf, sycl::write_only, sycl::no_init);
      dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_1, 42); // allowed
      dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_2, 42); // not allowed
