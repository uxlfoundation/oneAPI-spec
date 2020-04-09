=============================
parallel_do Template Function
=============================


Summary
-------

Template function that processes work items in parallel.

Header
------


.. code:: cpp

    #include "tbb/parallel_do.h"


Syntax
------

.. code:: cpp

   template<typename InputIterator, typename Body> 
   void parallel_do( InputIterator first, InputIterator last,
                     Body body[, task_group_context& group] );
   
   template<typename Container, typename Body>
   void parallel_do( Container c, Body body[, task_group_context& group] );
                   


Description
-----------

The ``parallel_do`` template has two forms.

The sequence form  
``parallel_do(first,last,body)`` applies a function object
``body`` over a sequence [``first,last``). Items may be
processed in parallel. Additional work items can be added by ``body``
if it has a second argument of type ``parallel_do_feeder``. The function
terminates when ``body(x)`` returns for all items ``x``
that were in the input sequence or added by method ``parallel_do_feeder::add``.

The container form ``parallel_do(c,body)`` is equivalent to
``parallel_do(std::begin(c),std::end(c),body)``.

The requirements for input iterators are specified in Chapter 24 of the ISO C++ standard.
The table below shows the requirements on type ``Body``.

= ========================================================================================
\ Requirements for parallel_do Body and its argument type T: Pseudo-Signature, Semantics
==========================================================================================
\ 
  .. code:: cpp

      Body::operator()(
        cv-qualifiersopt T referenceopt item,
        parallel_do_feeder<T>& feeder
      ) const
     OR
      Body::operator()(
        cv-qualifiersopt T referenceopt item
      ) const
     				  
  
  \
  Process a work item. ``parallel_do`` may
  concurrently invoke ``operator()`` for the same 
  body object but different items.
  
  The operator may accept ``item`` by value or by reference,
  including rvalue reference.
  
  The signature with ``feeder`` permits additional work items to be added.
  
  .. caution::

     Defining both the one-argument and two-argument forms of 
     ``operator()`` is not permitted.
  
------------------------------------------------------------------------------------------
\ ``T( const T& )``
  \
  Optional since C++11. Copy a work item.
------------------------------------------------------------------------------------------
\ ``T( T&& )``
  \
  Supported since C++11; optional. Move a work item.
------------------------------------------------------------------------------------------
\ ``~T::T()``
  \
  Destroy a work item.
------------------------------------------------------------------------------------------
= ========================================================================================

.. note::

   The argument type ``T`` should be either copy constructible,
   move constructible, or both. If the type is not copy constructible, there are
   additional usage restrictions:
   
   * If ``Body::operator()`` accepts its argument by value, or if the
     ``InputIterator`` type does not also satisfy the requirements
     of a forward iterator, then dereferencing an ``InputIterator``
     must produce an rvalue reference.
   * Additional work items should be passed to the feeder as rvalues,
     for example via the ``std::move`` function.
   

The algorithm can be passed a ``task_group_context`` object
so that its tasks are executed in this group. By default the algorithm
is executed in a bound group of its own.

.. tip::

   For good performance, execution of ``Body::operator()``
   should take at least ~100,000 clock cycles. If it is less,
   overhead of ``parallel_do`` may outweigh performance benefits.
   
   The parallelism in ``parallel_do`` is not scalable if all of the items
   come from an input stream that does not have random access.
   To achieve scaling, do one of the following:
   
   * Use random access iterators to specify the input stream. 
     Also, consider using ``parallel_for`` in this case.
   * Design your algorithm such that the body often adds more than
     one piece of work.
   


Example
-------

The following code sketches a body with the
two-argument form of ``operator()``.

.. code:: cpp

   struct MyBody {
       void operator()(item_t item, 
                       parallel_do_feeder<item_t>& feeder ) {
           for each new piece of work implied by item do {
               item_t new_item = initializer;
               feeder.add(new_item);
           }
       } 
   };
   		


See also:

* :doc:`Bound groups (task_group_context Class) <../../task_scheduler/task_group_context>`

.. toctree::

   parallel_do_func/parallel_do_feeder_cls.rst
