===============================
parallel_sort Template Function
===============================


Summary
-------
Sort a sequence.

Header
------

.. code:: cpp

   #include "tbb/parallel_sort.h"


Syntax
------

.. code:: cpp

   template<typename RandomAccessIterator>
   void parallel_sort( RandomAccessIterator begin, RandomAccessIterator end );
   
   template<typename RandomAccessIterator, typename Compare>
   void parallel_sort( RandomAccessIterator begin, RandomAccessIterator end,
                       const Compare& comp );
   
   template<typename Container>
   void parallel_sort( Container c );
   
   template<typename Container>
   void parallel_sort( Container c, const Compare& comp );


Description
-----------

Sorts a sequence or a container. The sort is neither stable nor deterministic: relative
ordering of elements with equal keys is not preserved and not guaranteed to repeat if the same
sequence is sorted again.  The requirements on the iterator and sequence are the same as for
``std::sort``. Specifically, ``RandomAccessIterator`` must be a
random access iterator, and its value type *T* must model the requirements in the table
below.

= ========================================================================================
\ Requirements on the iterator type It and its value type T for parallel_sort: Pseudo-Signature, Semantics
==========================================================================================
\ ``void iter_swap( It a, It b )``
  \
  Swaps the values of the elements the iterators ``a`` and
  ``b`` are pointing to.
------------------------------------------------------------------------------------------
\ ``bool Compare::operator()(const T& x, const T& y)``
  \
  ``true`` if ``x`` comes before ``y`` and
  ``false`` otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================

A call ``parallel_sort( begin, end, comp )`` sorts the sequence *[begin, end)* using the argument ``comp`` to determine relative orderings.  If
``comp( x, y )`` returns ``true`` then *x* appears before
*y* in the sorted sequence.

A call ``parallel_sort( begin, end )`` is equivalent to ``parallel_sort( begin, end, std::less<T> )``.

A call ``parallel_sort( c[, comp] )`` is equivalent to ``parallel_sort( std::begin(c), std::end(c)[, comp] )``.

**Complexity**

``parallel_sort`` is comparison sort with an average time complexity of
*O(N×log(N))*, where *N* is the number of elements in the sequence. When worker
threads are available, ``parallel_sort`` creates subtasks that may be executed
concurrently, leading to improved execution times.

Example
-------

The following example shows various forms of ``parallel_sort``. Arrays
``a`` and ``c`` are sorted using the default comparison, which
sorts in ascending order. Arrays ``b`` and ``d`` are sorted in
descending order by using ``std::greater<float>`` for comparison.

.. code:: cpp

   #include "tbb/parallel_sort.h"
   #include <math.h>
   
   using namespace tbb;
   
   const int N = 100000;
   float a[N], b[N], c[N], d[N];
   
   int main() {
       for( int i = 0; i < N; i++ ) {
           a[i] = sin((double)i);
           b[i] = cos((double)i);
           c[i] = 1/sin((double)i);
           d[i] = 1/cos((double)i);
       }
       parallel_sort(a, a + N);
       parallel_sort(b, b + N, std::greater<float>());
       parallel_sort(c);
       parallel_sort(d, std::greater<float>());
       return 0;
   }

