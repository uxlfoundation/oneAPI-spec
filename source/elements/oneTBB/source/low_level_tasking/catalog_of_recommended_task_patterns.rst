====================================
Catalog of Recommended task Patterns
====================================

This section catalogues recommended task patterns. In each pattern, class T is assumed to derive from class ``task``. Subtasks are labeled t\ :sub:`1`, t\ :sub:`2`, ... t\ :sub:`k`. The subscripts indicate the order in which the subtasks execute if no parallelism is available. If parallelism is available, the subtask execution order is non-deterministic, except that t\ :sub:`1` is guaranteed to be executed by the spawning thread.

Recursive task patterns are recommended for efficient scalable parallelism, because they allow the task scheduler to unfold potential parallelism to match available parallelism. A recursive task pattern begins by creating a root task t\ :sub:`0` and running it as follows.

.. code:: cpp

    T& t0 = *new(allocate_root()) T(...);
    task::spawn_root_and_wait(t0);

The root task's method ``execute()`` recursively
creates more tasks as described in subsequent subsections.

Blocking Style With k Children
------------------------------

The following shows the recommended style for a recursive task
of type *T* where each level spawns *k* children.

.. code:: cpp

    task* T::execute() {
        if( not recursing any further ) {
            ...
        } else {
            set_ref_count(k+1);
            task& tk = *new(allocate_child()) T(...);  spawn(tk);
            task& tk-1= *new(allocate_child()) T(...);  spawn(tk-1);
            ...
            task& t1= *new(allocate_child()) T(...);
            spawn_and_wait_for_all(t1);
        }
        return NULL;
    }

Child construction and spawning may be reordered if convenient, as long as a task is constructed before it is spawned.

The key points of the pattern are:

* The call to ``set_ref_count`` uses *k*\ +1 as its argument. The extra 1 is critical.
* Each task is allocated by ``allocate_child``.
* The call ``spawn_and_wait_for_all`` combines spawning and waiting. A more uniform but slightly less efficient alternative is to spawn all tasks with spawn and wait by calling ``wait_for_all``.


Continuation-Passing Style With k Children
------------------------------------------

There are two recommended styles. They differ in whether it is more convenient to recycle the parent as the continuation or as a child. The decision should be based upon whether the continuation or child acts more like the parent.

Optionally, as shown in the following examples, the code can return a pointer to one of the children instead of spawning it. Doing so causes the child to execute immediately after the parent returns. This option often improves efficiency because it skips pointless overhead of putting the task into the task pool and taking it back out.

Recycling Parent as Continuation
--------------------------------

This style is useful when the continuation needs to inherit much of the state of the parent and the child does not need the state. The continuation must have the same type as the parent.

.. code:: cpp

    task* T::execute() {
        if( not recursing any further ) {
            ...
            return NULL;
        } else {
            set_ref_count(k);
            recycle_as_continuation();
            task& tk  = *new(allocate_child()) T(...); spawn(tk);
            task& tk-1 = *new(allocate_child()) T(...); spawn(tk-1);
            ...
            // Return pointer to first child instead of spawning it,
            // to remove unnecessary overhead.
            task& t1 = *new(allocate_child()) T(...);
            return &t1;
        }
    }

The key points of the pattern are:

* The call to ``set_ref_count`` uses *k* as its argument. There is no extra +1 as there is in blocking style discussed in Section Blocking Style With k Children.
* Each child task is allocated by ``allocate_child``.
* The continuation is recycled from the parent, and hence gets the parent's state without doing copy operations.


Recycling Parent as a Child
---------------------------

This style is useful when the child inherits much of its
state from a parent and the continuation does not need the state of the parent. The
child must have the same type as the parent. In the example, C is the type of the
continuation, and must derive from class ``task``. If C does nothing
except wait for all children to complete, then C can be the class
``empty_task``.

.. code:: cpp

    task* T::execute() {
        if( not recursing any further ) {
            ...
            return NULL;
        } else {
            // Construct continuation
            C& c = allocate_continuation();
            c.set_ref_count(k);
            // Recycle self as first child
            task& tk = *new(c.allocate_child()) T(...); spawn(tk);
            task& tk-1 = *new(c.allocate_child()) T(...); spawn(tk-1);
            ...
            task& t2 = *new(c.allocate_child()) T(...);  spawn(t2);
            // task t1 is our recycled self.
            recycle_as_child_of(c);
            update fields of *this to subproblem to be solved by t1
            return this;
        }
    }

The key points of the pattern are:

* The call to ``set_ref_count`` uses *k* as its argument. There is no extra 1 as there is in blocking style discussed in Section Blocking Style With k Children .
* Each child task except for t\ :sub:`1` is allocated by c.``allocate_child``. It is critical to use ``c.allocate_child``, and not ``(*this).allocate_child;`` otherwise the task graph will be wrong.
* Task t\ :sub:`1` is recycled from the parent, and hence gets the parent's state without performing copy operations. Do not forget to update the state to represent a child subproblem; otherwise infinite recursion will occur.


Letting Main Thread Work While Child Tasks Run
----------------------------------------------

Sometimes it is desirable to have the main thread continue execution while child tasks
are running. The following pattern does this by using a dummy
``empty_task``.

.. code:: cpp

    task* dummy = new( task::allocate_root() ) empty_task;
    dummy->set_ref_count(k+1);
    task& tk = *new( dummy->allocate_child() ) T;  dummy->spawn(tk);
    task& tk-1 = *new( dummy->allocate_child() ) T;  dummy->spawn(tk-1);
    ...
    task& t1 = *new( dummy->allocate_child() ) T;  dummy->spawn(t1);
    ...do any other work...
    dummy->wait_for_all();
    dummy->destroy(*dummy);

The key points of the pattern are:

* The dummy task is a placeholder and never runs.
* The call to ``set_ref_count`` uses *k*\ +1 as its argument.
* The dummy task must be explicitly destroyed.


See also:

* :doc:`empty_task Class <empty_task_cls>`
