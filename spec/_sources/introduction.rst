.. SPDX-FileCopyrightText: 2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==============
 Introduction
==============

oneAPI simplifies software development by providing the same languages
and programming models across accelerator architectures. In this
section, we introduce the programming model.

Parallel application development is a combination of *API
programming*, where the parallel algorithm is hidden behind an API
provided by the system, and *direct programming*, where the
application programmer writes the parallel algorithm.

When using API programming, a developer implements performance
critical sections of the program with library calls.  Well-defined and
mature problem domains have high-performance solutions packaged as
libraries. oneAPI defines a set of APIs for the most used data
parallel domains, and oneAPI platforms provide library implementations
across a variety of accelerators.  Where possible, the API is based on
established standards like BLAS. API programming enables a programmer
to attain high performance across a diverse set of accelerators with
minimal coding & tuning.

Some problem domains are not well suited to API programming because no
standard solution exists or because solutions require a level of
customization that cannot be easily implemented in a library. In this
case, a developer uses direct programming and must explicitly code the
parallel algorithm. oneAPI's programming model is based on data
parallelism, where the same computation is performed on each data
element, and parallelism of the application scales as the data
scales. By allowing the programmer to directly express parallelism,
data parallel algorithms make it possible to productively create
highly efficient algorithms for parallel architectures.

Data parallel algorithms are used for many of the most computationally
demanding problems including scientific computing, artificial
intelligence, and visualization.  Data parallel algorithms can be
efficiently mapped to a diverse set of architectures: multi-core CPUs,
GPUs, systolic arrays, and FPGAs.

Target Audience
===============

The expected audience for this specification includes: application
developers, middleware developers, system software providers, and
hardware providers. As a *contributor* to this specification, you will
shape the accelerator software ecosystem. A productive and high
performing system must take into account the constraints at all levels
of the software stack. As a *user* of this document, you can ensure
that your components will inter-operate with applications and system
software for the oneAPI platform.

Goals of the Specification
==========================

oneAPI seeks to provide:

  - *Source-level compatibility*: oneAPI applications and middleware
    port to a conformant oneAPI platform through recompilation and
    re-tuning.

  - *Performance transparency*: API's and language construct allow the
    programmer enough control over the mapping to hardware to create
    an efficient solution

  - *Software stack portability*: Platform providers can port a oneAPI
    software stack by implementing the oneAPI Level Zero interface.

Definitions
===========

This specification uses the definition of must, must not, required,
and so on specified in `RFC 2119`_.

Contribution Guidelines
=======================

See Contributing_.

.. [*]: Other names and brands may be claimed as the property of others.
.. _`RFC 2119`: https://tools.ietf.org/html/rfc2119
.. _Contributing: https://github.com/uxlfoundation/CONTRIBUTING.rst
