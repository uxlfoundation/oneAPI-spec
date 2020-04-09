==========================
affinity_partitioner Class
==========================


Summary
-------

Hint that loop iterations should be assigned to threads in a way that
optimizes for cache affinity.

Header
------

.. code:: cpp

   #include "tbb/partitioner.h"


Syntax
------

.. code:: cpp

   class affinity_partitioner;


Description
-----------

An ``affinity_partitioner`` hints that execution of a loop
template should use the same task affinity pattern for splitting the
work as used by previous execution of the loop (or another loop) with
the same ``affinity_partitioner`` object.

Unlike the other partitioners, it is important that the same
``affinity_partitioner`` object be passed to the loop
templates to be optimized for affinity. The Tutorial section on
"Bandwidth and Cache Affinity" discusses affinity effects in detail.

.. tip::

   The affinity_partitioner generally improves performance only when:
   
   * The computation does a few operations per data access.
   * The data acted upon by the loop fits in cache.
   * The loop, or a similar loop, is re-executed over the same data.
   * There are more than two hardware threads available.
   


Members
-------

.. code:: cpp

   namespace tbb {
       class affinity_partitioner {
       public:
           affinity_partitioner();
           ~affinity_partitioner();
       };
   }
         


Example
-------

The following example can benefit from cache affinity. The example
simulates a one-dimensional additive automaton.


.. code:: cpp

   #include "tbb/blocked_range.h"
   #include "tbb/parallel_for.h"
   #include "tbb/partitioner.h"
   
   using namespace tbb;
   
   const int N = 1000000;
   typedef unsigned char Cell;
   Cell Array[2][N];
   int FlipFlop;
   
   struct TimeStepOverSubrange {
       void operator()( const blocked_range<int>& r ) const {
           int j = r.end();
           const Cell* x = Array[FlipFlop];
           Cell* y = Array[!FlipFlop];
           for( int i=r.begin(); i!=j; ++i )
               y[i] = x[i]^x[i+1];
       }
   };
   
   void DoAllTimeSteps( int m ) {
       affinity_partitioner ap;
       for( int k=0; k<m; ++k ) {
           parallel_for( blocked_range<int>(0,N-1),
                         TimeStepOverSubrange(),
                         ap );
           FlipFlop ^= 1;
       }
   }
           


For each time step, the old state of the automaton is read from
``Array[FlipFlop]``, and the new state is written into
``Array[!FlipFlop]``. Then ``FlipFlop`` flips
to make the new state become the old state. The aggregate size of both
states is about 2 MByte, which fits in most modern processors'
cache. Improvements ranging from 50%-200% have been observed for this
example on 8 core machines, compared with using an
``auto_partitioner`` instead.

The ``affinity_partitioner`` must live between loop
iterations. The example accomplishes this by declaring it outside the
loop that executes all iterations. An alternative would be to declare
the ``affinity partitioner`` at the file scope, which works
as long as ``DoAllTimeSteps`` itself is not invoked
concurrently. The same instance of ``affinity_partitioner``
should not be passed to two parallel algorithm templates that are
invoked concurrently. Use separate instances instead.

The following table provides additional information on the members of
this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``affinity_partitioner()``
  \
  Construct an ``affinity_partitioner``.
------------------------------------------------------------------------------------------
\ ``~affinity_partitioner()``
  \
  Destroy this ``affinity_partitioner``.
------------------------------------------------------------------------------------------
= ========================================================================================


