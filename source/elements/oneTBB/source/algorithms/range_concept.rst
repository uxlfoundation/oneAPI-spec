=============
Range Concept
=============


Summary
-------

Requirements for type representing a recursively divisible set of
values.

Requirements
------------

The following table lists the requirements for a
Range type
``R``.

= ========================================================================================
\ Range Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``R::R( const R& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``R::~R()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``bool R::empty() const``
  \
  True if range is empty.
------------------------------------------------------------------------------------------
\ ``bool R::is_divisible() const``
  \
  True if range can be partitioned into two
  subranges.
------------------------------------------------------------------------------------------
\ ``R::R( R& r, split )``
  \
  Basic splitting constructor. Splits ``r`` into two
  subranges.
------------------------------------------------------------------------------------------
\ ``R::R( R& r, proportional_split proportion )``
  \
  **Optional**. Proportional splitting constructor. Splits
  ``r`` into two subranges in accordance with
  ``proportion``.
------------------------------------------------------------------------------------------
\ ``static const bool R::is_splittable_in_proportion``
  \
  **Optional**. If true, the proportional splitting
  constructor is defined for the range and may be used by
  parallel algorithms.
------------------------------------------------------------------------------------------
= ========================================================================================


Description
-----------

A Range can be recursively subdivided into two parts. Subdivision is
done by calling
*splitting constructor* of Range. There are two types of splitting
constructors:

* Basic splitting constructor. It is recommended that the division be
  into nearly equal parts in this constructor, but it is not required. Splitting
  as evenly as possible typically yields the best parallelism.
* Proportional splitting constructor. This constructor is optional and
  can be omitted along with
  *is_splittable_in_proportion* class variable. When using this
  type of constructor, for the best results, follow the given proportion with
  rounding to the nearest integer if necessary.

Ideally, a range is recursively splittable until the parts represent
portions of work that are more efficient to execute serially rather than split
further. The amount of work represented by a Range typically depends upon
higher level context, hence a typical type that models a Range should provide a
way to control the degree of splitting. For example, the template class
``blocked_range`` has a
*grainsize* parameter that specifies the biggest range considered
indivisible.

If the set of values has a sense of direction, then by convention the
splitting constructor should construct the second part of the range, and update
its argument to be the first part of the range. This enables
``parallel_for``, ``parallel_reduce`` and
``parallel_scan`` algorithms, when running sequentially,
to work across a range in the increasing order, typical of an ordinary
sequential loop.

Since a Range declares a splitting and copy constructors, the default
constructor for it will not be automatically generated. You will need to
explicitly define the default constructor or add any other constructor to
create an instance of Range type in the program.

Example
-------

The following code defines a type ``TrivialNaturalRange`` that models the Range concept. It
represents a half-open interval [lower,upper) that is divisible down to a single natural number. Splitting can be done
via basic or proportional splitting constructors. The basic splitting constructor divides the range in half. The
proportional splitting constructor divides the range in the given proportion ``p``, with
``r`` updated to be the left part and a new ``TrivialNaturalRange`` constructed for
the right part. Note that special care has been taken to ensure non-emptiness of the involved
``TrivialNaturalRange`` instances.

.. include:: ./examples/range_concept.h
   :code: cpp


``TrivialNaturalRange`` is for demonstration purpose only and not
practical. Use the library class
``blocked_range`` instead.

Model Types
-----------

Type
``blocked_range`` models a one-dimensional range.

Type
``blocked_range2d`` models a two-dimensional range.

Type
``blocked_range3d`` models a three-dimensional range.

Type
``blocked_rangeNd`` models a N-dimensional range.

The Container Range Concept models a container as a range.

See also:

* :doc:`parallel_for Template Function <parallel_for_func>`
* :doc:`parallel_reduce Template Function <parallel_reduce_func>`
* :doc:`parallel_scan Template Function <parallel_scan_func>`
* :doc:`Container Range Concept <../containers/container_range_concept>`
* :doc:`proportional_split Class <splittable_concept/proportional_split_cls>`

.. toctree::

   range_concept/blocked_range_cls.rst
   range_concept/blocked_range2d_cls.rst
   range_concept/blocked_range3d_cls.rst
   range_concept/blocked_rangeNd_cls.rst
