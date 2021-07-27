.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===================
ParallelForEachBody
===================
**[req.parallel_for_each_body]**

A type `Body` satisfies `ParallelForBody` if it meets the `Function Objects`
requirements from the [function.objects] ISO C++ Standard section.
It should also meet one of the following requirements:

----------------------------------------------------------------

**ParallelForEachBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::operator()( ItemType item ) const

    Process the received item.

.. cpp:function:: Body::operator()( ItemType item, tbb::feeder<ItemType>& feeder ) const

    Process the received item. May invoke the ``feeder.add(T)`` function to spawn additional items.

-----------------------------------------------------------------

.. note::

    ``ItemType`` may be optionally passed to ``Body::operator()`` by reference.
    ``const`` and ``volatile`` type qualifiers are also applicable.

Terms
-----

* ``iterator`` determines the type of the iterator passed into ``parallel_for_each`` algorithm
  (which is ``InputIterator`` or ``decltype(std::begin(c))`` for the overloads which accepts the `Container` template argument)
* ``value_type`` - the type ``std::iterator_traits<iterator>::value_type``
* ``reference`` -  the type ``std::iterator_traits<iterator>::reference``.

If the ``iterator`` satisfies `Input iterator` named requirements from [input.iterators]
ISO C++ Standard section and do not satisfies `Forward iterator` named requirements from
[forward.iterators] ISO C++ Standard section, `tbb::parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`
requires the ``Body::operator()`` call with an object of type ``const value_type&`` or ``value_type&&`` to be well-formed.
If both forms are well-formed, an overload with rvalue reference will be preferred.

.. caution::

  If the ``Body`` only takes non-const lvalue reference to ``value_type``, named requirements above
  are violated and the program can be ill-formed.

If the ``iterator`` satisfies `Forward iterator` named requirements from [forward.iterators]
ISO C++Standard section, ``tbb::parallel_for_each`` requires the ``Body::operator()`` call
with an object of type ``reference`` to be well-formed.

Additional elements submitted into ``tbb::parallel_for_each`` through the ``feeder::add`` passes to the ``Body`` as rvalues and therefore the corresponding
execution of the ``Body`` is required to be well-formed.

See also:

* :doc:`parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`
* :doc:`feeder class<../../algorithms/functions/feeder>`
