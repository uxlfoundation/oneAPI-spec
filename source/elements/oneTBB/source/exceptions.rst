==========
Exceptions
==========

oneAPI Threading Building Blocks propagates exceptions along logical paths in a tree of tasks. Because these paths cross between thread stacks, support for moving an exception between stacks is necessary.

When an exception is thrown out of a task, it is caught inside the TBB run-time and handled as follows:

* If the cancellation group for the task has already been cancelled, the exception is ignored.
* Otherwise the exception or an approximation of it is captured and the group is cancelled.
* The captured exception is rethrown from the root of the cancellation group after all tasks in the group have completed or have been successfully cancelled.

The exact exception is captured when both of the following conditions are true:

* The task's ``task_group_context`` was created in a translation unit compiled with ``TBB_USE_CAPTURED_EXCEPTION=0``.
* The TBB library was built with a compiler that supports the ``std::exception_ptr`` feature of C++11.

Otherwise an approximation of the original exception *x* is captured as follows:

* If ``x`` is a ``tbb_exception``, it
  is captured by ``x.move()``.
* If ``x`` is a ``std::exception``, it is captured as
  a
  ``tbb::captured_exception(typeid(x).name(),x.what())``.
* Otherwise ``x`` is captured as a ``tbb::captured_exception``
  with implementation-specified value for ``name()`` and
  ``what()``.

.. toctree::

   exceptions/specific_exceptions.rst
