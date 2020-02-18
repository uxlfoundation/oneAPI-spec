==================
Splittable Concept
==================


Summary
-------

Requirements for a type whose instances can be split into two pieces.

Requirements
------------

The following table lists the requirements for a
splittable type 
``X`` with instance 
``x``.

= ========================================================================================
\ Splittable Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``X::X(X& x, split)``
  \
  Split 
  ``x`` into 
  ``x`` and newly constructed object.
------------------------------------------------------------------------------------------
= ========================================================================================


Description
-----------

A type is splittable if it has a 
*splitting constructor* that allows an instance to be split into
two pieces. The splitting constructor takes as arguments a reference to the
original object, and a dummy argument of type 
``split``, which is defined by the library. The dummy
argument distinguishes the splitting constructor from a copy constructor. After
the constructor runs, 
``x`` and the newly constructed object should
represent the two pieces of the original 
``x.`` The library uses splitting constructors in
two contexts:

* *Partitioning* a range into two subranges that can be processed
  concurrently.
* *Forking* a body (function object) into two bodies that can run
  concurrently.

Range classes might additionally define an optional
*proportional splitting constructor*, distinguished by an
argument of type ``proportional_split``. See the
``proportional_split`` Class and
``blocked_range`` Template Class sections for
more info.

The following model types provide examples.

Model Types
-----------

``blocked_range`` and 
``blocked_range2d`` represent splittable ranges. For each
of these, splitting partitions the range into two subranges. See the 
``blocked_range`` Template Class section for an example of
the splitting constructor for 
``blocked_range``.

The bodies for 
``parallel_reduce`` and 
``parallel_scan`` must be splittable. For each of these,
splitting results in two bodies that can be run concurrently.

See also:

* :doc:`Range Concept <range_concept>`
* :doc:`blocked_range Template Class <range_concept/blocked_range_cls>`
* :doc:`blocked_range2d Template Class <range_concept/blocked_range2d_cls>`
* :doc:`parallel_reduce Template Function <parallel_reduce_func>`
* :doc:`parallel_scan Template Function <parallel_scan_func>`

.. toctree::

   splittable_concept/split_cls.rst
   splittable_concept/proportional_split_cls.rst
