==============================
blocked_range3d Template Class
==============================


Summary
-------
Template class that represents recursively divisible three-dimensional half-open interval.

Header
------


.. code:: cpp

   #include "tbb/blocked_range3d.h"


Syntax
------

.. code:: cpp

   template<typename PageValue, typename RowValue, typename ColValue> class blocked_range3d;


Description
-----------

A ``blocked_range3d<PageValue,RowValue,ColValue>`` is the three-dimensional extension of ``blocked_range2d``.

Members
-------

.. code:: cpp

   namespace tbb {
   template<typename PageValue, typename RowValue=PageValue, typename ColValue=RowValue>
       class blocked_range3d {
       public:
           // Types
           typedef blocked_range<PageValue> page_range_type;
           typedef blocked_range<RowValue> row_range_type;
           typedef blocked_range<ColValue> col_range_type;
   
           // Constructors
           blocked_range3d( 
               PageValue page_begin, PageValue page_end,  
               typename page_range_type::size_type page_grainsize,
               RowValue row_begin, RowValue row_end, 
               typename row_range_type::size_type row_grainsize,
               ColValue col_begin, ColValue col_end, 
               typename col_range_type::size_type col_grainsize);
           blocked_range3d( PageValue page_begin, PageValue page_end,  
                            RowValue row_begin, RowValue row_end, 
                            ColValue col_begin, ColValue col_end);
           blocked_range3d( blocked_range3d& r, split );
           blocked_range3d( blocked_range3d& r, proportional_split& proportion );
   
           //! Proportional split is enabled
           static const bool is_splittable_in_proportion = true;
   
           // Capacity
           bool empty() const;
   
           // Access
           bool is_divisible() const;
           const page_range_type& pages() const;
           const row_range_type& rows() const;
           const col_range_type& cols() const;
       };
   }

Constructors of ``blocked_range3d`` support class template argument deduction for C++17. For example

.. code:: cpp

   tbb::blocked_range3d range(0, 100, size_t(0), size_t(50), 1u, 10u);

declares ``range`` as ``tbb::blocked_range3d<int, size_t, unsigned int>``.