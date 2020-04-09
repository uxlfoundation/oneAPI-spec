==============================
parallel_for Template Function
==============================


Summary
-------

Template function that performs parallel iteration over a range of values.

Header
------

.. code:: cpp

    #include "tbb/parallel_for.h"


Syntax
------

.. code:: cpp

   template<typename Index, typename Func>
   Func parallel_for( Index first, Index_type last, const Func& f
                      [, partitioner[, task_group_context& group]] );
   
   template<typename Index, typename Func>
   Func parallel_for( Index first, Index_type last, 
                      Index step, const Func& f
                      [, partitioner[, task_group_context& group]] );
   
   template<typename Range, typename Body> 
   void parallel_for( const Range& range, const Body& body, 
                      [, partitioner[, task_group_context& group]] );


Description
-----------

A ``parallel_for(first,last,step,f)`` represents parallel execution of the
loop:

.. code:: cpp

   for( auto i=first; i<last; i+=step ) f(i);

The index type must be an integral type. The loop must not wrap around. The step value must be
positive. If omitted, it is implicitly 1. There is no guarantee that the iterations
run in parallel. Deadlock may occur if a lesser iteration waits for a greater
iteration. The partitioning strategy is
``auto_partitioner`` when the parameter is not specified.

A ``parallel_for(range,body,partitioner)`` provides a more general form of parallel
iteration. It represents parallel execution of ``body`` over each value
in range. The optional ``partitioner`` specifies a partitioning
strategy. Type ``Range`` must model the Range concept . The body must
model the requirements in the following table.

= ========================================================================================
\ Requirements for parallel_for Body: Pseudo-Signature, Semantics
==========================================================================================
\ ``Body::Body( const Body& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``Body::~Body()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void Body::operator()( Range& range ) const``
  \
  Apply body to range.
------------------------------------------------------------------------------------------
= ========================================================================================

A ``parallel_for`` recursively splits the range into subranges to the
point such that ``is_divisible()`` is false for each subrange, and
makes copies of the body for each of these subranges. For each such body/subrange
pair, it invokes ``Body::operator()``. The invocations are
interleaved with the recursive splitting, in order to minimize space overhead and
efficiently use cache.

Some of the copies of the range and body may be destroyed after
``parallel_for`` returns. This late destruction is not an issue in
typical usage, but is something to be aware of when looking at execution traces or
writing range or body objects with complex side effects.

When worker threads are available, ``parallel_for`` executes
iterations in non-deterministic order. Do not rely upon any particular execution
order for correctness. However, for efficiency, do expect
``parallel_for`` to tend towards operating on consecutive runs of
values.

When no worker threads are available, ``parallel_for`` executes
iterations from left to right in the following sense. Imagine drawing a binary
tree that represents the recursive splitting. Each non-leaf node represents
splitting a subrange ``r`` by invoking one of the splitting
constructors of ``Range``. The left child represents the updated value of
``r``. The right child represents the newly constructed object. Each
leaf in the tree represents an indivisible subrange.  The method
``Body::operator()`` is invoked on each leaf subrange, from left to
right.

All overloads can be passed a ``task_group_context`` object so that
the algorithm’s tasks are executed in this group. By default the algorithm is
executed in a bound group of its own.

**Complexity**

If the range and body take O(1) space, and the range splits into nearly equal
pieces, then the space complexity is O(P log(N)), where N is the size of the range
and P is the number of threads.

Example
-------

This example defines a routine ``ParallelAverage`` that sets
``output[i]`` to the average of ``input[i-1]``,
``input[i]``, and ``input[i+1]``, for 1 <= i< n.


.. code:: cpp

   #include "tbb/parallel_for.h"
   #include "tbb/blocked_range.h"
   
   using namespace tbb;
   
   struct Average {
       const float* input;
       float* output;
       void operator()( const blocked_range<int>& range ) const {
           for( int i=range.begin(); i!=range.end(); ++i )
               output[i] = (input[i-1]+input[i]+input[i+1])*(1/3.f);
       }
   };
   
   // Note: Reads input[0..n] and writes output[1..n-1]. 
   void ParallelAverage( float* output, const float* input, size_t n ) {
       Average avg;
       avg.input = input;
       avg.output = output;
       parallel_for( blocked_range<int>( 1, n ), avg );
       }


Example
-------

This example is more complex and requires familiarity with STL. It shows the power of
``parallel_for`` beyond flat iteration spaces. The code performs a parallel
merge of two sorted sequences. It works for any sequence with a random-access
iterator. The algorithm (Akl 1987) works recursively as follows:

* If the sequences are too short for effective use of parallelism, do a sequential merge. Otherwise perform steps 2-6.
* Swap the sequences if necessary, so that the first sequence [begin1,end1) is at least as long as the second sequence [begin2,end2).
* Set m1 to the middle position in [begin1,end1). Call the item at that location key.
* Set m2 to where *key* would fall in [begin2,end2).
* Merge [begin1,m1) and [begin2,m2) to create the first part of the merged sequence.
* Merge [m1,end1) and [m2,end2) to create the second part of the merged sequence.

The oneAPI Threading Building Blocks implementation of this algorithm uses the range object to
perform most of the steps. Predicate ``is_divisible`` performs the test
in step 1, and step 2. The splitting constructor does steps 3-6. The body object
does the sequential merges.


.. code:: cpp

   #include "tbb/parallel_for.h"
   #include <algorithm>
   
   using namespace tbb;
   
   template<typename Iterator>
   struct ParallelMergeRange {
       static size_t grainsize;
       Iterator begin1, end1; // [begin1,end1) is 1st sequence to be merged
       Iterator begin2, end2; // [begin2,end2) is 2nd sequence to be merged
       Iterator out;               // where to put merged sequence    
       bool empty()   const {return (end1-begin1)+(end2-begin2)==0;}
       bool is_divisible() const {
           return std::min( end1-begin1, end2-begin2 ) > grainsize;
       }
       ParallelMergeRange( ParallelMergeRange& r, split ) {
           if( r.end1-r.begin1 < r.end2-r.begin2 ) {
               std::swap(r.begin1,r.begin2);
               std::swap(r.end1,r.end2);
           }
           Iterator m1 = r.begin1 + (r.end1-r.begin1)/2;
           Iterator m2 = std::lower_bound( r.begin2, r.end2, *m1 );
           begin1 = m1;
           begin2 = m2;
           end1 = r.end1;
           end2 = r.end2;
           out = r.out + (m1-r.begin1) + (m2-r.begin2);
           r.end1 = m1;
           r.end2 = m2;
       }
       ParallelMergeRange( Iterator begin1_, Iterator end1_, 
                           Iterator begin2_, Iterator end2_, 
                           Iterator out_ ) :
           begin1(begin1_), end1(end1_), 
           begin2(begin2_), end2(end2_), out(out_)
       {}
   };
   
   template<typename Iterator>
   size_t ParallelMergeRange<Iterator>::grainsize = 1000;
   
   template<typename Iterator>
   struct ParallelMergeBody {
       void operator()( ParallelMergeRange<Iterator>& r ) const {
           std::merge( r.begin1, r.end1, r.begin2, r.end2, r.out );
       }
   };
   
   template<typename Iterator>
   void ParallelMerge( Iterator begin1, Iterator end1, Iterator begin2, Iterator end2, Iterator out ) {
       parallel_for(     
          ParallelMergeRange<Iterator>(begin1,end1,begin2,end2,out),
          ParallelMergeBody<Iterator>(),
          simple_partitioner() 
       );
   }


Because the algorithm moves many locations, it tends to be bandwidth limited. Speedup varies, depending upon the system.

See also:

* :doc:`Range Concept <../../general/named_requirements/range>`
* :doc:`Bound groups (task_group_context Class) <../../task_scheduler/task_group_context>`
