===============
task Allocation
===============

Always allocate memory for 
``task`` objects using one of the special overloaded new
operators. The allocation methods do not construct the 
``task``. Instead, they return a proxy object that can be
used as an argument to an overloaded version of operator new provided by the
library.

In general, the allocation methods must be called
before any of the tasks allocated are spawned. The exception to this rule is 
``allocate_additional_child_of(t)``, which can be called
even if 
``task````t`` is already running. The proxy types are
defined by the implementation. The only guarantee is that the phrase
"new(proxy) T(...)" allocates and constructs a task of type 
*T*.

.. tip::

   Allocating tasks larger than 216 bytes might be
   significantly slower than allocating smaller tasks. In general, task objects
   should be small lightweight entities.

Because these methods are used idiomatically, the
members in the following table show the idiom, not the declaration. The
argument 
``this`` is typically implicit, but shown explicitly in
the headings to distinguish instance methods from static methods.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``new( task::allocate_root( task_group_context& group ) ) T``
  \
  Allocate a 
  ``task`` of type 
  *T* with the specified cancellation group. The figure below
  summarizes the state transition.
  
  .. figure:: ../../Resources/06000008.png

     Effect of task::allocate_root()

  Use method 
  ``spawn_root_and_wait`` to execute the 
  ``task``.
------------------------------------------------------------------------------------------
\ ``new( task::allocate_root() ) T``
  \
  Like 
  ``new(task::allocate_root(task_group_context&))``
  except that cancellation group is the current innermost cancellation group.
------------------------------------------------------------------------------------------
\ ``new( x.allocate_continuation() ) T``
  \
  Allocates and constructs a task of type 
  ``T``, and transfers the 
  *successor* from 
  ``x`` to the new task. No reference
  counts change. The figure below summarizes the state transition.
  
  .. figure:: ../../Resources/06000009.png

     Effect of allocate_continuation()

------------------------------------------------------------------------------------------
\ ``new( x.allocate_child() ) T``
  \
  Allocates a 
  ``task`` with 
  ``this`` as its 
  *successor*. The figure below summarizes the state
  transition.
  
  .. figure:: ../../Resources/0600000A.png
     
     Effect of allocate_child()

  If using explicit continuation passing,
  then the continuation, not the 
  ``successor``, should call the allocation
  method, so that successor is set correctly.
  
  If the number of tasks is not a small
  fixed number, consider building a 
  ``task_list`` of the predecessors first, and
  spawning them with a single call to ``task::spawn``. If a 
  ``task`` must spawn some predecessors before all
  are constructed, it should use 
  ``task::allocate_additional_child_of(*this)``
  instead, because that method atomically increments 
  ``refcount``, so that the additional
  predecessor is properly accounted. However, if doing so, the task must protect
  against premature zeroing of 
  ``refcount`` by using a blocking-style
  task pattern.
------------------------------------------------------------------------------------------
\ ``new(task::allocate_additional_child_of( y )) T``
  \
  Allocates a 
  ``task`` as a predecessor of another 
  ``task y``. Task 
  ``y`` may be already running or have other
  predecessors running. The figure below summarizes the state transition.
  
  .. figure:: ../../Resources/0600000B.png

     Effect of allocate_additional_child_of(successor)

  Because 
  ``y`` may already have running
  predecessors, the increment of 
  ``y``.``refcount`` is
  atomic (unlike the other allocation methods, where the increment is not
  atomic). When adding a predecessor to a task with other predecessors running,
  it is up to the programmer to ensure that the successor's 
  ``refcount`` does not prematurely reach 0
  and trigger execution of the successor before the new predecessor is added.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`task_list Class <../task_list_cls>`
* :doc:`Synchronization <synchronization_task>`
