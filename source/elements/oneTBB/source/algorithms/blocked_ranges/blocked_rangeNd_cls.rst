.. SPDX-FileCopyrightText: 2019-2024 Intel Corporation
.. SPDX-FileCopyrightText: Contributors to the oneAPI Specification project.
..
.. SPDX-License-Identifier: CC-BY-4.0

===============
blocked_rangeNd
===============
**[algorithms.blocked_rangeNd]**

Class template that represents a recursively divisible N-dimensional half-open interval.

A ``blocked_rangeNd`` is the N-dimensional extension of ``blocked_range``, ``blocked_range2d`` and ``blocked_range3d``.
We can interpret it as a tensor-product of N instances of ``blocked_range``.
Different to ``blocked_range2d`` and ``blocked_range3d``, all ranges have to be specified over the same type Value.
Therefore, blocked_rangeNd<int,2> is a specialisation of blocked_range2d where both dimensions have int type.

.. code:: cpp

    namespace oneapi {
        namespace tbb {
            template<typename Value, unsigned int N>
            class blocked_rangeNd {
            public:
                // Types
                using value_type = Value;
                using dim_range_type = tbb::blocked_range<Value>;

                // Constructors
                blocked_rangeNd(const dim_range_type<Is>&... args);
                blocked_rangeNd(
                  Value size[N], 
                  typename tbb::blocked_range<value_type>::size_type grainsize = 1
                );
                blocked_rangeNd(blocked_rangeNd& r, proportional_split proportion); 
                blocked_rangeNd(blocked_rangeNd& r, split proportion); 
               
                // Capacity
                bool empty() const;

                // Access
                bool is_divisible() const;
                static constexpr unsigned int dim_count();
                const tbb::blocked_range<value_type>& dim(unsigned int dimension) const;
            };

        } // namespace tbb
    } // namespace oneapi        

Requirements:

* The *Value* must meet the :doc:`BlockedRangeValue requirements <../../named_requirements/algorithms/blocked_range_val>`

Member types
------------

.. code:: cpp

    using value_type = Value;

The type of the page values.

.. code:: cpp

    using dim_range_type = blocked_range<Value>;

The type of the values in one dimension out of the N dimensions.

Member functions
----------------

.. code:: cpp

    blocked_rangeNd(const dim_range_type<Is>&... args);

**Effects:**  Constructs a ``blocked_rangeNd`` representing an N-dimensional space of values.
The space is the half-open Cartesian product of ranges each having its own grain size.
The number of args has to match N.


.. code:: cpp

    blocked_rangeNd(
      Value size[N],
      typename tbb::blocked_range<value_type>::size_type grainsize = 1
    );

**Effects:**  Constructs a ``blocked_rangeNd`` representing an N-dimensional space of values.
The space is the half-open Cartesian product of ranges with ``[0, size[0]) x [0, size[1]) x ...`` each having the same grain size.

**Example:**  The statement ``blocked_rangeNd<int,4> r( {5,6,7,8}, 4 );`` constructs a four-dimensional
space that contains all value pairs of the form ``(i, j, k, l)``, where ``i`` ranges from 0 (included) to 5 (excluded) with a grain size of 4,
``j`` ranges from 0 to 6 with a grain size of 4, and so forth.
    

.. code:: cpp

    blocked_rangeNd( blocked_rangeNd& range, split );

Basic splitting constructor.

**Requirements**: ``is_divisible()`` is true.

**Effects**: Partitions ``range`` into two subranges. The newly constructed ``blocked_rangeNd`` is approximately
the half of the original ``range``, and ``range`` is updated to be the remainder.
Each subrange has the same grain size as the original ``range``. Splitting is done in any dimension.
The choice of which axis to split is intended to cause, after repeated splitting, 
subranges of approximately square/cubic/hypercubic shape if all grain sizes are the same.

.. code:: cpp

    blocked_rangeNd( blocked_rangeNd& range, proportional_split proportion );

Proportional splitting constructor.

**Requirements**: ``is_divisible()`` is true.

**Effects**: Partitions ``range`` into two subranges in the given ``proportion``
across one of its axes. The choice of which axis to split is made in the same way as for the basic splitting
constructor; then, proportional splitting is done for the chosen axis. The second axis and the grain sizes for
each subrange remain the same as in the original range.

.. code:: cpp

    bool empty() const;

**Effects**: Determines if range is empty.

**Returns:** Any one-dimensional range hosted is empty.

.. code:: cpp

    bool is_divisible() const;

**Effects**: Determines if the range can be split into subranges.

**Returns:** any dim(int) returns is_divisible().

.. code:: cpp

   static constexpr unsigned int dim_count();

**Returns:** Number of dimensions specified by the template argument ``N``.

.. code:: cpp

    const dim_range_type& dim(int) const;

**Returns:**  Range containing the range of the value space along dimension specified by argument.

See also:

* :doc:`blocked_range <blocked_range_cls>`
* :doc:`blocked_range2d <blocked_range2d_cls>`
* :doc:`blocked_range3d <blocked_range3d_cls>`

