============
Introduction
============
**[intro]**

This document specifies requirements for implementations of
oneAPI Threading Building Blocks (oneTBB).

oneAPI Threading Building Blocks is a programming model
for scalable parallel programming using standard ISO C++
code. A program uses oneTBB to specify logical parallelism in its
algorithms, while a oneTBB implementation maps that parallelism
onto execution threads.

oneTBB employs generic programming via C++ templates,
with most of its interfaces defined by requirements on types and not
specific types. Generic programming makes oneTBB flexible yet efficient,
through customizing APIs to specific needs of an application.

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
