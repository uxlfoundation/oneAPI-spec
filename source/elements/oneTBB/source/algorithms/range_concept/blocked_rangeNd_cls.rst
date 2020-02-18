==============================
blocked_rangeNd Template Class
==============================


Summary
-------

Template class that represents recursively divisible N-dimensional half-open interval.
The use of ``blocked_rangeNd`` requires C++11 support.

Header
------


.. code:: cpp

   #define TBB_PREVIEW_BLOCKED_RANGE_ND 1
   #include "tbb/blocked_rangeNd.h"


Syntax
------

.. code:: cpp

   template<typename Value, unsigned int N> class blocked_rangeNd;


Description
-----------

A ``blocked_rangeNd<Value, N>`` is the N-dimensional extension of the
``blocked_range``. Each dimension of the range is represented by a
``blocked_range<Value>``. The ``Value`` must meet
the requirements of the *Value Concept* described in the corresponding
table of the *blocked_range Template Class* section.

A ``blocked_rangeNd`` models the Range Concept.
A ``blocked_rangeNd`` is divisible if either its axis is divisible, and
is empty if either its axis is empty. It supports proportional splitting.

Members
-------

.. code:: cpp

   namespace tbb {
   
       template<typename Value, unsigned int N>
       class blocked_rangeNd {
       public:
           // Types
           using value_type = Value;
   
           // Constructor
           blocked_rangeNd(const blocked_range<Value>& dim0, ..., const blocked_range<Value>& dimN-1);
   
           // Splitting constructors
           blocked_rangeNd(blocked_rangeNd& r, split proportion);
           blocked_rangeNd(blocked_rangeNd& r, proportional_split proportion);
   
           // Proportional split is enabled
           static const bool is_splittable_in_proportion = true;
   
           // Capacity
           static constexpr unsigned int ndims();
           bool empty() const;
   
           // Access
           const tbb::blocked_range<Value>& dim(unsigned int k) const;
           bool is_divisible() const;
       };
   
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``value_type``
  \
  The type of a ``Value`` in any of N dimensions constituting a range.
------------------------------------------------------------------------------------------
\ ``blocked_rangeNd<Value, N>(const blocked_range<Value>& dim0, ..., const blocked_range<Value>& dim_Nminus1)``
  \
  Constructor accepts exactly N ``blocked_range<value_type>``
  objects representing each dimension.
  
  **Effects:** Constructs a ``blocked_rangeNd`` as a Cartesian
  product of N half-open one-dimensional intervals:
  
  ``[ dim0.begin(), dim0.end() ) x ... x [ dim_Nminus1.begin(), dim_Nminus1.end() )``
  
  with the given grain sizes.
  
  **Example:** Statements
  
  ``blocked_rangeNd<std::size_t, 2> r({1, 17}, {3, 284, 5});``
  
  and
  
  ``blocked_rangeNd<std::size_t, 2> r(blocked_range<std::size_t>{1, 17}, blocked_range<std::size_t>{3, 284, 5});``
  
  construct two equal two-dimensional spaces. Each of them contains all value pairs of
  the form ``(i, j)``, where ``i`` ranges from 1 to 16
  with a grain size of 1, and ``j`` ranges from 3 to 283
  with a grain size of 5.
------------------------------------------------------------------------------------------
\ ``blocked_rangeNd<Value, N>(blocked_rangeNd& r, split proportion)``
  \
  Basic splitting constructor.
  
  **Requirements**:
  ``is_divisible()`` is true.
  
  **Effects**: Partitions ``r`` into two subranges across one
  of the dimensions. The axis to split is chosen for maximal ratio of its range size
  to the respective grain size. In that dimension, the newly constructed blocked_range
  is approximately the second half of the original range, and the range is updated to
  be the remainder. Other dimensions and the grain sizes for each subrange remain the
  same as in the original range.
------------------------------------------------------------------------------------------
\ ``blocked_rangeNd<Value, N>(blocked_rangeNd& r, proportional_split proportion)``
  \
  Proportional splitting constructor.
  
  **Requirements**:
  ``is_divisible()`` is ``true``.
  
  **Effects**: Partitions ``r`` into two subranges in the given
  proportion across one of the dimensions. Except for proportional splitting of the
  chosen axis, the behavior and effects are the same as those of the
  basic splitting constructor.
------------------------------------------------------------------------------------------
\ ``static const bool is_splittable_in_proportion``
  \
  Denotes the ability of ``blocked_rangeNd`` instances to be
  split proportionally. Set to ``true``.
------------------------------------------------------------------------------------------
\ ``static constexpr unsigned int ndims()``
  \
  **Returns**: the dimensionality of the range, which is ``N``.
  The method can be used in constant expressions.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Effects**: Determines if range is empty.
  
  **Returns**: ``true`` if at least one dimension is empty,
  otherwise ``false``.
------------------------------------------------------------------------------------------
\ ``const blocked_range<Value>& dim(unsigned int k) const``
  \
  **Requirements**:
  ``0 <= k < N``
  
  **Returns**: ``blocked_range`` for the ``k``-th
  dimension. The dimensions are numbered in the order of constructor arguments,
  starting from 0.
  
  **Example:** For the range ``r``, defined as:
  
  ``blocked_rangeNd<std::size_t, 2> r({1, 17}, {3, 284, 5});``
  
  ``r.dim(0)`` returns
  ``blocked_range<std::size_t>(1, 17)`` and
  ``r.dim(1)`` returns
  ``blocked_range<std::size_t>(3, 284, 5)``.
------------------------------------------------------------------------------------------
\ ``bool is_divisible() const``
  \
  **Effects**: Determines if range can be split into subranges.
  
  **Returns**: ``true`` if at least one dimension is divisible,
  otherwise false.
------------------------------------------------------------------------------------------
= ========================================================================================


Example
-------

The example demonstrates calculation of a 3-dimensional filter over the pack of
feature maps applying 3-dimensional kernel to subrange of features.

The ``convolution3d`` function iterates over the output cells and sets
cell values to the result of the ``kernel3d`` function. For the iteration
to be performed in parallel, ``tbb::parallel_for`` is called with a
``tbb::blocked_rangeNd<int, 3>`` as an argument.

The ``kernel3d`` function summarizes the values from feature maps
in the scope of a 3-dimensional kernel.

.. include:: ../examples/blocked_rangeNd_example.h
   :code: cpp

