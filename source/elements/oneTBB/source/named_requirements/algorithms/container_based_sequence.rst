.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

======================
ContainerBasedSequence
======================
**[req.container_based_sequence]**

A type `C` satisfies `ContainerBasedSequence` if the following expressions are valid
for a (possibly ``const``) object ``c`` of the type ``C``:

----------------------------------------------------------------

**ContainerBasedSequence Requirements: Expression, Semantics**

.. cpp:function:: std::begin(c)

    Returns an input iterator to the beginning of the sequence represented by ``c``.

.. cpp:function:: std::end(c)

    Returns an input iterator one past the end of the sequence represented by ``c``.

----------------------------------------------------------------

.. note::

   Templates that use ``ContainerBasedSequence`` may impose stricter requirements on the iterator type
   returned by ``std::begin``/``std::end``.

See also:

* :doc:`parallel_for_each algorithm <../../algorithms/functions/parallel_for_each_func>`
* :doc:`parallel_sort algorithm <../../algorithms/functions/parallel_sort_func>`
