===========
Task Groups
===========

 

This section covers the high-level interface to the
task scheduler. The Task Scheduler section covers the low-level interface. The
high-level interface lets you easily create groups of potentially parallel
tasks from functors or lambda expressions. The low-level interface permits more
detailed control, such as control over exception propagation and affinity.

Summary
-------

High-level interface for running functions in parallel.

Syntax
------

.. code:: cpp

   template<typename Func> task_handle;
   template<typename Func> task_handle<Func> make_task( const Func& f );
   enum task_group_status;
   class task_group;
   class structured_task_group;
   bool is_current_task_group_canceling();


Header
------

.. code:: cpp

   #include "tbb/task_group.h"

**Requirements**

Functor arguments for various methods in this
section should meet the requirements in the table below.

= ========================================================================================
\ Requirements on functor arguments: Pseudo-Signature, Semantics
==========================================================================================
\ ``Func::Func (const Func&)``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``Func::~Func ()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void Func::operator()() const;``
  \
  Evaluate functor.
------------------------------------------------------------------------------------------
= ========================================================================================


.. toctree::

   task_groups/task_group_cls.rst
   task_groups/task_group_status_enum.rst
   task_groups/task_handle_cls.rst
   task_groups/make_task_func.rst
   task_groups/is_current_task_group_canceling_func.rst
