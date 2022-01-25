.. SPDX-FileCopyrightText: 2019-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===============
blocked_range3d
===============
**[algorithms.blocked_range3d]**

Class template that represents a recursively divisible three-dimensional half-open interval.

A ``blocked_range3d`` is the three-dimensional extension of ``blocked_range2d``.

.. code:: cpp

    namespace oneapi {
        namespace tbb {
            template<typename PageValue, typename RowValue=PageValue, typename ColValue=RowValue>
            class blocked_range3d {
            public:
                // Types
                using page_range_type = blocked_range<PageValue>;
                using row_range_type = blocked_range<RowValue>;
                using col_range_type = blocked_range<ColValue>;

                // Constructors
                blocked_range3d(
                    PageValue page_begin, PageValue page_end,
                    typename page_range_type::size_type page_grainsize,
                    RowValue row_begin, RowValue row_end,
                    typename row_range_type::size_type row_grainsize,
                    ColValue col_begin, ColValue col_end,
                    typename col_range_type::size_type col_grainsize );
                blocked_range3d( PageValue page_begin, PageValue page_end
                                RowValue row_begin, RowValue row_end,
                                ColValue col_begin, ColValue col_end );
                blocked_range3d( blocked_range3d& r, split );
                blocked_range3d( blocked_range3d& r, proportional_split& proportion );

                // Capacity
                bool empty() const;

                // Access
                bool is_divisible() const;
                const page_range_type& pages() const;
                const row_range_type& rows() const;
                const col_range_type& cols() const;
            };

        } // namespace tbb
    } // namespace oneapi        

Requirements:

* The *PageValue*, *RowValue* and *ColValue* must meet the :doc:`blocked_range requirements <../../named_requirements/algorithms/blocked_range_val>`

c

See also:

* :doc:`blocked_range <blocked_range_cls>`
* :doc:`blocked_range2d <blocked_range2d_cls>`

