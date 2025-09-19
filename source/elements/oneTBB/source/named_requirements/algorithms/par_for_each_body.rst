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

.. cpp:function:: void Body::operator()( ReferenceType item ) const

    Process the received item.

.. cpp:function:: void Body::operator()( ItemType&& item, oneapi::tbb::feeder<ItemType>& feeder ) const

    Process the received item. May invoke the ``feeder.add`` function to spawn additional items.

-----------------------------------------------------------------

where ``ItemType`` is ``std::iterator_traits<InputIterator>::value_type`` for the type of the iterator
the ``parallel_for_each`` algorithm operates with, and ``ReferenceType`` is

* ``std::iterator_traits<InputIterator>::reference`` if the iterator type is a forward iterator
  as described in the [forward.iterators] section of the ISO C++ Standard;
* otherwise, ``ItemType&&``.

.. note::

    The usual rules for :ref:`pseudo-signatures <pseudo_signatures>` apply.
    Therefore, ``Body::operator()`` may optionally take ``ItemType`` by value.
    ``const`` and ``volatile`` type qualifiers are also applicable.

See also:

* :doc:`parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`
* :doc:`feeder class<../../algorithms/functions/feeder>`
