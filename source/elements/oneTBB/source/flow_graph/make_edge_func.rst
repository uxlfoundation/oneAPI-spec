===========================
make_edge Template Function
===========================


Summary
-------

A template function that adds an edge between a ``sender<T>`` and a ``receiver<T>.``

Syntax
------

.. code:: cpp

   template< typename T >
   inline void make_edge( sender<T> &p, receiver<T> &s );
   
   //Overloads
   
   //Makes an edge from port 0 of a multi-output predecessor to port 0 of a multi-input successor
   template< typename T, typename V >
   inline void make_edge( T& output, V& input)
   
   //Makes an edge from port 0 of a multi-output predecessor to a receiver.
   template< typename T, typename R >
   inline void make_edge( T& output, receiver<R> input) 
   
   //Makes an edge from a sender to port 0 of a multi-input successor.
   template<typename S,  typename V>
   inline void make_edge( sender<S> output, V& input) 
   

.. note::

   The overloads require C++11 support.


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"
