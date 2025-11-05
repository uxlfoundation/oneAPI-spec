.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _oneDPL-section:

======
oneDPL
======

The |dpl_full_name| (oneDPL) provides the functionality
specified in the `C++ standard`_, with extensions to support data parallelism
and offloading to devices, and with extensions to simplify its usage for 
implementing data parallel algorithms.

The library is comprised of the following components:

- :doc:`Parallel API <parallel_api>`:

  * Parallel algorithms, complemented with execution
    policies and companion APIs for running on oneAPI devices.

  * An additional set of library classes and functions that
    are known to be useful in practice but are not yet included into
    C++ or SYCL specifications. 

- :doc:`SYCL Kernels API <sycl_kernels_api>`:

  * A subset of the `C++ standard`_ library which can be used with
    buffers and data parallel kernels.

  * Support of random number generation including engines and distributions.

  * Various utilities in addition to C++ standard functionality.

.. toctree::

   common.rst
   parallel_api.rst
   sycl_kernels_api.rst

.. _`C++ Standard`: https://isocpp.org/std/the-standard
