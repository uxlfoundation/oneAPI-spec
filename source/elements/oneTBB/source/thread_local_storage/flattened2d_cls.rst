==========================
flattened2d Template Class
==========================


Summary
-------

Adaptor that provides a flattened view of a container of containers.

Syntax
------

.. code:: cpp

       template<typename Container>
       class flattened2;
        
       template <typename Container>
       flattened2d<Container> flatten2d(const Container &c); 
        
       template <typename Container>
       flattened2d<Container> flatten2d(
           const Container &c, 
           const typename Container::const_iterator b, 
           const typename Container::const_iterator e); 


Header
------

.. code:: cpp

   #include "tbb/enumerable_thread_specific.h"


Description
-----------

A ``flattened2d`` provides a flattened view of a container of containers. Iterating from ``begin()`` to ``end()``visits all of the elements in the inner containers. This can be useful when traversing an ``enumerable_thread_specific`` whose elements are containers.

The utility function ``flatten2d`` creates a ``flattened2d`` object from a container.

Example
-------

The following code shows a simple example usage of ``flatten2d`` and ``flattened2d``. Each thread collects the values of ``i`` that are evenly divisible by ``K`` in a thread-local vector. In main, the results are printed by using a ``flattened2d`` to simplify the traversal of all of the elements in all of the local vectors.

.. code:: cpp

       
   #include <iostream>
   #include <utility>
   #include <vector>
    
   #include "tbb/task_scheduler_init.h"
   #include "tbb/enumerable_thread_specific.h"
   #include "tbb/parallel_for.h"
   #include "tbb/blocked_range.h"
    
   // A VecType has a separate std::vector<int> per thread
   typedef tbb::enumerable_thread_specific< std::vector<int> > VecType;
   VecType MyVectors; 
   int K = 1000000;
    
   struct Func {
       void operator()(const tbb::blocked_range<int>& r) const {
           VecType::reference v = MyVectors.local();
           for (int i=r.begin(); i!=r.end(); ++i) 
               if( i%k==0 ) 
                   v.push_back(i);
       } 
   };
    
   int main() {
       tbb::parallel_for(tbb::blocked_range<int>(0, 100000000), Func());
    
       tbb::flattened2d<VecType> flat_view = tbb::flatten2d( MyVectors );
       for( tbb::flattened2d<VecType>::const_iterator 
            i = flat_view.begin(); i != flat_view.end(); ++i) 
           cout << *i << endl;
       return 0;
   }


Members
-------

.. code:: cpp

   namespace tbb {
       template<typename Container>
       class flattened2d {
    
       public:
           // Basic types
           typedef implementation-dependent size_type;
           typedef implementation-dependent difference_type;
           typedef implementation-dependent allocator_type;
           typedef implementation-dependent value_type;
           typedef implementation-dependent reference;
           typedef implementation-dependent const_reference;
           typedef implementation-dependent pointer;
           typedef implementation-dependent const_pointer;
    
           typedef implementation-dependent iterator;
           typedef implementation-dependent const_iterator;
    
           explicit flattened2d( const Container& c );
    
           flattened2d( const Container& c, 
                        typename Container::const_iterator first,
                       typename Container::const_iterator last );
    
           iterator begin();
           iterator end();
           const_iterator begin() const;
           const_iterator end() const;
    
           size_type size() const;
       };
    
       template <typename Container>
       flattened2d<Container> flatten2d(const Container &c);
    
       template <typename Container>
       flattened2d<Container> flatten2d(
           const Container &c, 
           const typename Container::const_iterator first, 
           const typename Container::const_iterator last);
   }

.. toctree::

   flattened2d_cls/whole_container_operations_2d_cls.rst
   flattened2d_cls/concurrent_operations.rst
   flattened2d_cls/iterators_2d_cls.rst
   flattened2d_cls/utility_funcs.rst
