.. SPDX-FileCopyrightText: 2019-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===================
ParallelForEachBody
===================
**[req.parallel_for_each_body]**

A type `Body` satisfies `ParallelForBody` if it meets the `Function Objects`
requirements described in the [function.objects] section of the ISO C++ standard.
It should also meet one of the following requirements:

----------------------------------------------------------------

**ParallelForEachBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::operator()( ItemType item ) const

    Process the received item.

.. cpp:function:: Body::operator()( ItemType item, oneapi::tbb::feeder<ItemType>& feeder ) const

    Process the received item. May invoke the ``feeder.add(T)`` function to spawn additional items.

-----------------------------------------------------------------

.. note::

    ``ItemType`` may be optionally passed to ``Body::operator()`` by reference.
    ``const`` and ``volatile`` type qualifiers are also applicable.

Terms
-----

* ``iterator`` determines the type of the iterator passed into the ``parallel_for_each`` algorithm,
  which is ``decltype(std::begin(c))`` for the overloads that accept the ``Container`` template argument or ``InputIterator``.
* ``value_type`` - the type ``std::iterator_traits<iterator>::value_type``.
* ``reference`` -  the type ``std::iterator_traits<iterator>::reference``.

``oneapi::tbb::parallel_for_each`` requires the ``Body::operator()`` call with an object of the ``reference`` type to be well-formed if
the ``iterator`` meets the `Forward iterator` requirements described in the [forward.iterators] section of the 
ISO C++ Standard.

`oneapi::tbb::parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`_
requires the ``Body::operator()`` call with an object of type ``const value_type&`` or ``value_type&&`` to be well-formed if following requirements are met:

* the iterator meets the `Input iterator` requirements described in the [input.iterators] section of the ISO C++ Standard
* the iterator does not meet the `Forward iterator` requirements described in the [forward.iterators] section of the ISO C++ Standard

.. caution::

  If the ``Body`` only takes non-const lvalue reference to the ``value_type``, the requirements described above
  are violated, and the program can be ill-formed.

Additional elements submitted into ``oneapi::tbb::parallel_for_each`` through the ``feeder::add`` are passed to the ``Body`` as rvalues. In this case, the corresponding
execution of the ``Body`` is required to be well-formed.

See also:

* :doc:`parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`
* :doc:`feeder class<../../algorithms/functions/feeder>`
