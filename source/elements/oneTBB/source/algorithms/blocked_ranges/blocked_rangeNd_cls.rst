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
We can interpret it as a Cartesian product of N instances of ``blocked_range``.
Different to ``blocked_range2d`` and ``blocked_range3d``, all ranges have to be specified over the same type ``Value``.
Therefore, ``blocked_rangeNd<int,2>`` is a specialisation of ``blocked_range2d`` where both dimensions are of type ``int``.

.. code:: cpp

    namespace oneapi {
        namespace tbb {

            template<typename Value, unsigned int N>
            class blocked_rangeNd {
            public:
                // Types
                using value_type = Value;
                using dim_range_type = blocked_range<value_type>;
                using size_type = typename dim_range_type::size_type;

                // Constructors
                blocked_rangeNd(const dim_range_type& dim0 /*, ... - exactly N parameters of the same type*/);
                blocked_rangeNd(value_type size[N], size_type grainsize = 1);
                blocked_rangeNd(blocked_rangeNd& r, split); 
                blocked_rangeNd(blocked_rangeNd& r, proportional_split proportion); 

                // Capacity
                static constexpr unsigned int dim_count();
                bool empty() const;

                // Access
                bool is_divisible() const;
                const dim_range_type& dim(unsigned int dimension) const;
            };

        } // namespace tbb
    } // namespace oneapi        

Requirements:

* The *Value* must meet the :doc:`BlockedRangeValue requirements <../../named_requirements/algorithms/blocked_range_val>`

Member types
------------

.. code:: cpp

    using value_type = Value;

The type of the range values.

.. code:: cpp

    using dim_range_type = blocked_range<value_type>;

The type that represents one out of the N dimensions.

.. code:: cpp

    using size_type = typename dim_range_type::size_type;

The type for measuring the size of a dimension.

Member functions
----------------

.. code:: cpp

    blocked_rangeNd( const dim_range_type& dim0 /*, ... - exactly N parameters of the same type*/ );

**Effects:**  Constructs a ``blocked_rangeNd`` representing an N-dimensional space of values.
The space is the half-open Cartesian product of ranges ``dim0 x ...`` each having its own grain size.
The constructor must take exactly N arguments which types match to ``const dim_range_type&``.

**Example:** For ``blocked_rangeNd<int,4>``, this constructor is equivalent to
``blocked_rangeNd( const blocked_range<int>&, const blocked_range<int>&, const blocked_range<int>&, const blocked_range<int>& )``.

.. note::
    A variadic template constructor ``template <typename... Dims> blocked_rangeNd( const Dims&... dims )``,
    even if constrained by the size and type requirements for its parameter pack ``Dims``, would not
    be fully compliant because types in ``Dims`` would not be deductible for arguments specified as
    braced initialization lists, and so expressions like ``blocked_rangeNd<int, 4>{{0,1},{0,2},{0,3},{0,4}}``
    would fail to compile.

.. code:: cpp

    blocked_rangeNd( value_type size[N], size_type grainsize = 1 );

**Effects:**  Constructs a ``blocked_rangeNd`` representing an N-dimensional space of values.
The space is the half-open Cartesian product of ranges ``[0, size[0]) x [0, size[1]) x ...``
each having the same grain size.

**Example:**  The statement ``blocked_rangeNd<int,4> r( {5,6,7,8}, 4 );`` constructs a four-dimensional
space that contains all value pairs of the form ``(i, j, k, l)``, where ``i`` ranges from 0 (included)
to 5 (excluded) with a grain size of 4, ``j`` ranges from 0 to 6 with a grain size of 4, and so forth.
    

.. code:: cpp

    blocked_rangeNd( blocked_rangeNd& range, split );

Basic splitting constructor.

**Requirements**: ``is_divisible()`` is true.

**Effects**: Partitions ``range`` into two subranges. The newly constructed ``blocked_rangeNd`` is approximately
the half of the original ``range``, and ``range`` is updated to be the remainder.
Splitting is done in one dimension, while other dimensions and the grain sizes for
each subrange remain the same as in the original ``range``.
The choice of which dimension to split is intended to cause, after repeated splitting, 
subranges of approximately square/cubic/hypercubic shape if all grain sizes are the same.

.. code:: cpp

    blocked_rangeNd( blocked_rangeNd& range, proportional_split proportion );

Proportional splitting constructor.

**Requirements**: ``is_divisible()`` is true.

**Effects**: Partitions ``range`` into two subranges in the given ``proportion`` across one of its dimensions.
The choice of which dimenstion to split is made in the same way as for the basic splitting constructor;
then, proportional splitting is done for the chosen one. Other dimensions and the grain sizes for
each subrange remain the same as in the original ``range``.

.. code:: cpp

   static constexpr unsigned int dim_count();

**Returns:** The number of dimensions, as specified by the class template argument ``N``.

.. code:: cpp

    bool empty() const;

**Effects**: Determines if range is empty.

**Returns:** True if any of the range dimensions is empty; false, otherwise.

.. code:: cpp

    bool is_divisible() const;

**Effects**: Determines if the range can be split into subranges.

**Returns:** True if for any of the range dimensions ``is_divisible()`` is true; false, otherwise.

.. code:: cpp

    const dim_range_type& dim(unsigned int dimension) const;

**Requirements**: 0 <= ``dimension`` < N.

**Returns:**  ``blocked_range`` containing the value space along the dimension specified by the argument.

See also:

* :doc:`blocked_range <blocked_range_cls>`
* :doc:`blocked_range2d <blocked_range2d_cls>`
* :doc:`blocked_range3d <blocked_range3d_cls>`

