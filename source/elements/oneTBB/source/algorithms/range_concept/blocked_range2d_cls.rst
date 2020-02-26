==============================
blocked_range2d Template Class
==============================


Summary
-------

Template class that represents recursively divisible two-dimensional
half-open interval.

Header
------


.. code:: cpp

   #include "tbb/blocked_range2d.h"


Syntax
------


.. code:: cpp

   template<typename RowValue, typename ColValue> class blocked_range2d;


Description
-----------

A ``blocked_range2d<RowValue ,ColValue >`` represents a half-open
two-dimensional range
``[i0,j0)×[i1,j1)``. Each
axis of the range has its own splitting threshold. The *RowValue* and *ColValue* must meet the
requirements in the table in the blocked_range Template Class section. A ``blocked_range2d`` is
divisible if either axis is divisible. A ``blocked_range2d`` models the Range concept.

Members
-------

.. code:: cpp

    
   namespace tbb {
   template<typename RowValue, typename ColValue=RowValue>
       class blocked_range2d {
       public:
           // Types
           typedef blocked_range<RowValue> row_range_type;
           typedef blocked_range<ColValue> col_range_type;
   
           // Constructors
           blocked_range2d( 
               RowValue row_begin, RowValue row_end, 
               typename row_range_type::size_type row_grainsize,
               ColValue col_begin, ColValue col_end, 
               typename col_range_type::size_type col_grainsize);
           blocked_range2d( RowValue row_begin, RowValue row_end, 
                            ColValue col_begin, ColValue col_end);
           // Splitting constructors
           blocked_range2d( blocked_range2d& r, split );
           blocked_range2d( blocked_range2d& r, proportional_split proportion );
   
           // Proportional split is enabled
           static const bool is_splittable_in_proportion = true;
   
           // Capacity
           bool empty() const;
   
           // Access
           bool is_divisible() const;
           const row_range_type& rows() const;
           const col_range_type& cols() const;
       };
   }

Constructors of ``blocked_range2d`` support class template argument deduction for C++17. For example

.. code:: cpp

   tbb::blocked_range2d range(0, 100, size_t(0), size_t(50));

declares ``range`` as ``tbb::blocked_range<int, size_t>``.

Example
-------

The code that follows shows a serial matrix
multiply, and the corresponding parallel matrix multiply that uses a 
``blocked_range2d`` to specify the iteration space.

.. code:: cpp

   const size_t L = 150;
   const size_t M = 225;
   const size_t N = 300;
   
   void SerialMatrixMultiply( float c[M][N], float a[M][L], float b[L][N] ) {
       for( size_t i=0; i<M; ++i ) {
           for( size_t j=0; j<N; ++j ) {
               float sum = 0;
               for( size_t k=0; k<L; ++k )
                   sum += a[i][k]*b[k][j];
               c[i][j] = sum;
           }
       }
   }

.. code:: cpp

   #include "tbb/parallel_for.h"
   #include "tbb/blocked_range2d.h"
   
   using namespace tbb;
   
   const size_t L = 150;
   const size_t M = 225;
   const size_t N = 300;
   
   class MatrixMultiplyBody2D {
       float (*my_a)[L];
       float (*my_b)[N];
       float (*my_c)[N];
   public:
       void operator()( const blocked_range2d<size_t>& r ) const {
           float (*a)[L] = my_a;
           float (*b)[N] = my_b;
           float (*c)[N] = my_c;
           for( size_t i=r.rows().begin(); i!=r.rows().end(); ++i ){
               for( size_t j=r.cols().begin(); j!=r.cols().end(); ++j ) {
                   float sum = 0;
                   for( size_t k=0; k<L; ++k )
                       sum += a[i][k]*b[k][j];
                   c[i][j] = sum;
               }
           }
       }
       MatrixMultiplyBody2D( float c[M][N], float a[M][L], float b[L][N] ) :
           my_a(a), my_b(b), my_c(c)
       {}
   };
   
   void ParallelMatrixMultiply(float c[M][N], float a[M][L], float b[L][N]){
       parallel_for( blocked_range2d<size_t>(0, M, 16, 0, N, 32),     
                     MatrixMultiplyBody2D(c,a,b) );
   }

The ``blocked_range2d`` enables the
two outermost loops of the serial version to become parallel loops. The ``parallel_for`` recursively splits the 
``blocked_range2d`` until the pieces are no larger than 16x32. It invokes 
``MatrixMultiplyBody2D::operator()`` on each piece.


The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``row_range_type``
  \
  A 
  ``blocked_range<RowValue>``. That is, the
  type of the row values.
------------------------------------------------------------------------------------------
\ ``col_range_type``
  \
  A ``blocked_range<ColValue>``. That is, the type of the column values.
------------------------------------------------------------------------------------------
\ ``blocked_range2d<RowValue,ColValue>( RowValue row_begin, RowValue row_end, typename row_range_type::size_type row_grainsize, ColValue col_begin, ColValue col_end, typename col_range_type::size_type col_grainsize )``
  \
  **Effects:**  Constructs a 
  ``blocked_range2d`` representing a two-dimensional
  space of values. The space is the half-open Cartesian
  product ``[row_begin, row_end) x [col_begin, col_end)``, with
  the given grain sizes for the rows and columns.
  
  **Example:**  The statement 
  ``blocked_range2d<char,int> r('a', 'z'+1, 3, 0, 10, 2 );`` constructs a two-dimensional
  space that contains all value
  pairs of the form ``(i, j)``, where ``i`` ranges from ``'a'`` to 
  ``'z'`` with a grain size of 3, and ``j`` ranges from 0 to 9 with a grain size of 2.
------------------------------------------------------------------------------------------
\ ``blocked_range2d<RowValue,ColValue>( RowValue row_begin, RowValue row_end, ColValue col_begin, ColValue col_end )``
  \
  Same as
  ``blocked_range2d(row_begin,row_end,1,col_begin,col_end,1)``.
------------------------------------------------------------------------------------------
\ ``blocked_range2d<RowValue,ColValue> ( blocked_range2d& range, split )``
  \
  Basic splitting constructor.
  
  **Requirements**: ``is_divisible()`` is true.
  
  **Effects**: Partitions range into two subranges. The newly constructed ``blocked_range2d`` is
  approximately the second half of the original ``range``, and ``range`` is updated to
  be the remainder. Each subrange has the same grain size as the original ``range``. The split is
  either by rows or columns. The choice of which axis to split is intended to cause, after repeated splitting, the
  subranges to approach the aspect ratio of the respective row and column grain sizes. For example, if the
  ``row_grainsize`` is twice ``col_grainsize``, the subranges will tend towards having
  twice as many rows as columns.
------------------------------------------------------------------------------------------
\ ``blocked_range2d<RowValue,ColValue> ( blocked_range2d& range, proportional_split proportion )``
  \
  Proportional splitting constructor.
  
  **Requirements**: ``is_divisible()`` is true.
  
  **Effects**: Partitions ``range`` into two subranges in the given ``proportion``
  across one of its axes. The choice of which axis to split is made in the same way as for the basic splitting
  constructor; then, proportional splitting is done for the chosen axis. The second axis and the grain sizes for
  each subrange remain the same as in the original range.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Effects**: Determines if range is empty.
  
  **Returns:** ``rows().empty()||cols().empty()``
------------------------------------------------------------------------------------------
\ ``bool is_divisible() const``
  \
  **Effects**: Determines if range can be split into
  subranges.
  
  **Returns:** ``rows().is_divisible()||cols().is_divisible()``
------------------------------------------------------------------------------------------
\ ``const row_range_type& rows() const``
  \
  **Returns:**  Range containing the rows of the value space.
------------------------------------------------------------------------------------------
\ ``const col_range_type& cols() const``
  \
  **Returns:**  Range containing the columns of the value space.
------------------------------------------------------------------------------------------
= ========================================================================================
