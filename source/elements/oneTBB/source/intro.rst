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
