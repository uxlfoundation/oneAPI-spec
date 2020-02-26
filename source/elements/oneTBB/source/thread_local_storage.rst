====================
Thread Local Storage
====================

oneAPI Threading Building Blocks
provides two template classes for thread local storage. Both provide a
thread-local element per thread. Both lazily create the elements on demand.
They differ in their intended use models:

``combinable`` provides thread-local
storage for holding per-thread subcomputations that will later be reduced to a
single result. It is PPL compatible.

``enumerable_thread_specific``
provides thread-local storage that acts like an STL container with one element
per thread. The container permits iterating over the elements using the usual
STL iteration idioms.

This section also describes template class 
``flatten2d``, which assists a common idiom where an 
``enumerable_thread_specific`` represents a container
partitioner across threads.

.. toctree::

   thread_local_storage/combinable_cls.rst
   thread_local_storage/enumerable_thread_specific_cls.rst
   thread_local_storage/flattened2d_cls.rst
