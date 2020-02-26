=============================
remove_edge Template Function
=============================


Summary
-------

A template function that removes an edge between a ``sender<T>`` and a ``receiver<T>.``

Syntax
------

.. code:: cpp

   template< typename T >
   void remove_edge( sender<T> &p, receiver<T> &s );
   
   //Overloads
   
   //Removes an edge between port 0 of a multi-output predecessor and port 0 of a multi-input successor.
   template< typename T, typename V >
   inline void remove_edge( T& output, V& input)
   
   //Removes an edge between port 0 of a multi-output predecessor and a receiver.
   template< typename T, typename R >
   inline void remove_edge( T& output, receiver<R> input)
   
   //Removes an edge between a sender and port 0 of a multi-input successor.
   template<typename S,  typename V>
   inline void remove_edge( sender<S> output, V& input)
   

.. note::

   The overloads require C++11 support.


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"
