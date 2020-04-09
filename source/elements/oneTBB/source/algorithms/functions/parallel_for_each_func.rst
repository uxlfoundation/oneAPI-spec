===================================
parallel_for_each Template Function
===================================


Summary
-------

Parallel variant of ``std::for_each``.

Header
------

.. code:: cpp

   #include "tbb/parallel_for_each.h"


Syntax
------

.. code:: cpp

   template<typename InputIterator, typename Func> 
   void parallel_for_each( InputIterator first, InputIterator last, 
                           const Func& f[, task_group_context& group] );
   
   template<typename Container, typename Func>
   void parallel_for_each( Container c,
                           const Func& f[, task_group_context& group] );


Description
-----------

The ``parallel_for_each`` template function applies a function object
``f`` to each element in a sequence [*first,last*)
or a container *c*, possibly in parallel.

The requirements for input iterators are specified in Chapter 24 of
the ISO C++ standard. The table below shows the requirements on type Body.

= ========================================================================================
\ parallel_for_each Requirements for Body B and its Argument Type T: Pseudo-Signature, Semantics
==========================================================================================
\ ``B::operator()( cv-qualifiers T& item ) const``
  \
  Process an item. ``parallel_for_each`` may
  concurrently invoke ``operator()`` for the same 
  body object but different ``item``.
------------------------------------------------------------------------------------------
\ ``T( const T& )``
  \
  Copy a work item.
------------------------------------------------------------------------------------------
\ ``~T::T()``
  \
  Destroy a work item.
------------------------------------------------------------------------------------------
= ========================================================================================

.. tip::

   For good performance with input streams that do not have random access,
   execution of ``B::operator()`` should take at least ~100,000 clock cycles.
   If it is less, overhead of ``parallel_for_each`` may outweigh performance benefits.
   
   For smaller overheads and good scalability, use random access iterators to specify the input stream.

If the ``group`` argument is specified, the algorithm's tasks are executed in this
group. By default, the algorithm is executed in a bound group of its own.