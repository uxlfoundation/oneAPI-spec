===================
General Information
===================

C++11 is the minimal version of the C++ standard required by oneTBB.
An implementation of oneTBB shall not require newer versions of the standard
except where explicitly specified; also it shall not require any non-standard
language extensions.

An implementation may use platform-specific APIs if those are compatible
with the C++ execution and memory models. For example, a platform-specific
implementation of threads may be used if that implementation provides
the same execution guarantees as C++ threads.

An implementation of oneTBB shall support execution on single core and multi-core CPUs,
including those that provide simultaneous multithreading capabilities.

On CPU, an implementation shall support nested parallelism, so that one
can build larger parallel components from smaller parallel components. 

.. toctree::

   general/terminology.rst
   general/notation.rst
   general/identifiers.rst
   general/thread_safety.rst
