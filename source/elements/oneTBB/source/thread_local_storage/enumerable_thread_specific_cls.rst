=========================================
enumerable_thread_specific Template Class
=========================================


Summary
-------

Template class for
thread local storage.

Syntax
------


.. code:: cpp

   enum ets_key_usage_type {
       ets_key_per_instance,
       ets_no_key
   };
   
   template <typename T,
       typename Allocator=cache_aligned_allocator<T>,
       ets_key_usage_type ETS_key_type=ets_no_key>
   class enumerable_thread_specific;


Header
------


.. code:: cpp

   #include "tbb/enumerable_thread_specific.h"


Description
-----------

An
``enumerable_thread_specific`` provides thread local storage (TLS)
for elements of type ``T``. An ``enumerable_thread_specific``
acts as a container by providing iterators and ranges across all of the thread-local
elements.

The thread-local elements are created lazily. A freshly constructed
``enumerable_thread_specific`` has no elements.  When a thread
requests access to an ``enumerable_thread_specific``, it creates an
element corresponding to that thread.  The number of elements is equal to the number
of distinct threads that have accessed the
``enumerable_thread_specific`` and not necessarily the number of
threads in use by the application. Clearing an ``enumerable_thread_specific``
removes all its elements.

The ``ETS_key_usage_type`` parameter can be
used to select between an implementation that consumes no native TLS keys and a
specialization that offers higher performance but consumes 1 native TLS key per
``enumerable_thread_specific`` instance. If no ``ETS_key_usage_type``
parameter is provided, ``ets_no_key`` is used by default.

.. caution::

   The number of native TLS keys is limited and can be fairly small, for example 64
   or 128. Therefore it is recommended to restrict the use of the
   ``ets_key_per_instance`` specialization to only the most
   performance critical cases.

.. caution::

   ``enumerable_thread_specific`` uses the OS-specific value returned
   by ``tbb::this_tbb_thread::get_id()`` to identify threads. This
   value is not guaranteed to be unique except for the life of the thread.
   A newly created thread may get an OS-specific ID equal to that of an already
   destroyed thread.  The number of elements of the
   ``enumerable_thread_specific`` may therefore be less than the
   number of actual distinct threads that have called ``local()``,
   and the element returned by the first reference by a thread to the
   ``enumerable_thread_specific`` may not be newly-constructed.


Example
-------

The following code shows a simple example usage of
``enumerable_thread_specific``. The number of calls to
``null_parallel_for_body::operator()`` and total number of iterations executed are
counted by each thread that participates in the ``parallel_for``, and these counts are
printed at the end of main.

.. code:: cpp

   #include <cstdio>
   #include <utility>
   
   #include "tbb/task_scheduler_init.h"
   #include "tbb/enumerable_thread_specific.h"
   #include "tbb/parallel_for.h"
   #include "tbb/blocked_range.h"
   
   typedef tbb::enumerable_thread_specific< std::pair<int,int> > CounterType;
   CounterType MyCounters (std::make_pair(0,0));
   
   struct Body {
        void operator()(const tbb::blocked_range<int> &r) const {
             CounterType::reference my_counter = MyCounters.local();
             ++my_counter.first;
             for (int i = r.begin(); i != r.end(); ++i)
                 ++my_counter.second;
        }
   };
   
   int main() {
        tbb::parallel_for( tbb::blocked_range<int>(0, 100000000), Body());
   
        for (CounterType::const_iterator i = MyCounters.begin();
             i != MyCounters.end(); ++i)
        {
               printf("Thread stats:\n");
               printf("     calls to operator(): %d", i->first);
               printf("     total # of iterations executed: %d\n\n",
                      i->second);
       }
   }


Example with Lambda Expressions
-------------------------------

Class
``enumerable_thread_specific`` has a method
``combine(f)`` that does a reduction using binary functor
``f``, which can be written using a lambda expression.
For example, the previous example can be extended to sum the thread-local values by
adding the following lines to the end of function
``main``:

.. code:: cpp

   std::pair<int,int> sum =
       MyCounters.combine([](std::pair<int,int> x,
                             std::pair<int,int> y) {
           return std::make_pair(x.first+y.first,
                                 x.second+y.second);
       });
   printf("Total calls to operator() = %d, "
            "total iterations = %d\n", sum.first, sum.second);


Members
-------

.. code:: cpp

   namespace tbb {
       template <typename T,
           typename Allocator=cache_aligned_allocator<T>,
           ets_key_usage_type ETS_key_type=ets_no_key >
       class enumerable_thread_specific {
       public:
           // Basic types
           typedef Allocator allocator_type;
           typedef T value_type;
           typedef T& reference;
           typedef const T& const_reference;
           typedef T* pointer;
           typedef implementation-dependent size_type;
           typedef implementation-dependent difference_type;
   
           // Iterator types
           typedef implementation-dependent iterator;
           typedef implementation-dependent const_iterator;
   
           // Parallel range types
           typedef implementation-dependent range_type;
           typedef implementation-dependent const_range_type;
   
           // Construction and destruction
           enumerable_thread_specific();
           template <typename Finit>
           explicit enumerable_thread_specific( Finit finit );
           explicit enumerable_thread_specific( const T& exemplar );
           // Supported since C++11
           explicit enumerable_thread_specific( T&& exemplar );
           template <typename... Args>
           enumerable_thread_specific( Args&&... args );
           ~enumerable_thread_specific();
   
           // Copying constructors and assignments
           enumerable_thread_specific(
               const enumerable_thread_specific& other
           );
           template<typename Alloc, ets_key_usage_type Cachetype>
           enumerable_thread_specific(
               const enumerable_thread_specific<T, Alloc, Cachetype>& other
           );
           enumerable_thread_specific& 
           operator=( const enumerable_thread_specific& other );
           template<typename Alloc, ets_key_usage_type Cachetype>
           enumerable_thread_specific&
           operator=( const enumerable_thread_specific<T, Alloc, Cachetype>& other );
   
           // Moving constructors and assignments supported since C++11.
           enumerable_thread_specific(
               enumerable_thread_specific&& other
           );
           template<typename Alloc, ets_key_usage_type Cachetype>
           enumerable_thread_specific(
               enumerable_thread_specific<T, Alloc, Cachetype>&& other
           );
           enumerable_thread_specific&
           operator=( enumerable_thread_specific&& other );
           template<typename Alloc, ets_key_usage_type Cachetype>
           enumerable_thread_specific&
           operator=( enumerable_thread_specific<T, Alloc, Cachetype>&& other );
   
           // Other whole container operations
           void clear();
   
           // Concurrent operations
           reference local();
           reference local( bool& exists );
           size_type size() const;
           bool empty() const;
   
           // Combining
           template<typename BinaryFunc> T combine( BinaryFunc f );
           template<typename UnaryFunc> void combine_each( UnaryFunc f );
   
           // Parallel iteration
           range_type range( size_t grainsize=1 );
           const_range_type range( size_t grainsize=1 ) const;
   
           // Iterators
           iterator begin();
           iterator end();
           const_iterator begin() const;
           const_iterator end() const;
       };
   }

.. toctree::

   enumerable_thread_specific_cls/whole_container_operations_specific_cls.rst
   enumerable_thread_specific_cls/concurrent_operations1.rst
   enumerable_thread_specific_cls/combining.rst
   enumerable_thread_specific_cls/parallel_literation_specific_cls.rst
   enumerable_thread_specific_cls/iterators_specific_cls.rst
