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
for passing `SYCL`_ buffers to oneDPL algorithms.
These functions accept a SYCL buffer and return an object of an unspecified type
(referred below as *buffer position*) that satisfies the following requirements:

- It is ``CopyConstructible`` and ``CopyAssignable``.
- It is comparable with operators ``==`` and ``!=``.
- It provides the ``get_buffer()`` method that returns the SYCL buffer, over which an object was built.
- The expressions ``a + n`` and ``a - n``, where ``a`` is a buffer position object and ``n``
  is an integer value, are valid and evaluate to a buffer position object representing
  a position in the buffer that follows or precedes the position of ``a`` by ``n``.
  If this new position is out of the buffer bounds, the behavior is undefined.
- The expression ``a - b``, where ``a`` and ``b`` are buffer position objects,
  is valid and evaluates to an integer value ``n`` such that ``a == b + n``.

These operations are only valid for objects built over the same SYCL buffer.
If an expression operates with buffer position objects that are not built
over the same buffer, the behavior is undefined.

When invoking an algorithm, the buffer passed to ``begin`` should be the same
as the buffer passed to ``end``. Otherwise, the behavior is undefined.

An algorithm may return a buffer position object, which can then be compared and used
in expressions with other objects built over the same buffer.

.. code:: cpp

   namespace dpl = oneapi::dpl; // see "Namespaces"
   sycl::buffer buf {/*...*/};
   auto pos = dpl::find(dpl::execution::dpcpp_default, dpl::begin(buf), dpl::end(buf), value);
   int value_index = (pos == dpl::end(buf))? -1 : pos - dpl::begin(buf);

SYCL deduction tags (the ``TagT`` parameters) and ``sycl::property::no_init`` 
allow to specify an access mode to be used by algorithms for accessing a SYCL buffer.
The mode serves as a hint, and can be overridden depending on semantics of the algorithm.
When invoking an algorithm, the same access mode arguments should be used
for ``begin`` and ``end``. Otherwise, the behavior is undefined.

.. code:: cpp

   namespace dpl = oneapi::dpl;
   sycl::buffer buf {/*...*/};
   auto buf_begin = dpl::begin(buf, sycl::write_only);
   auto buf_end_1 = dpl::end(buf, sycl::write_only);
   auto buf_end_2 = dpl::end(buf, sycl::write_only, sycl::no_init);
   dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_1, 42); // allowed
   dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_2, 42); // not allowed

.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
