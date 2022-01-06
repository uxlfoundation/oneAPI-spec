.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===============================
 oneAPI Specification Releases
===============================


This document lists releases of oneAPI specifications.

In addition to be published as part of the oneAPI spefication, some of
the components publish specifications independent from the oneAPI
specification. Typically, a oneAPI specification includes a snapshot
of the latest approved release of the component. This page lists
releases of the oneAPI specification and releases of component
specifications.  Releases of collections of oneAPI components
(e.g. Intel oneAPI Basekit) identify the version of the oneAPI
specification that it supports.


oneAPI Specification
====================

The latest approved specification is 1.0. The 1.1 specification is
under development and is labeled *provisional* until it is approved.
Releases are listed below. See GitHub_ for the latest build.

.. _GitHub: https://github.com/oneapi-src/oneapi-spec


1.1
---

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `1.1 rev 1`_
    - 2021-11-12
    - `HTML <https://spec.oneapi.io/versions/1.1-rev-1/>`__ `PDF <https://spec.oneapi.io/versions/1.1-rev-1/oneAPI-spec.pdf>`__
  * - `1.1 provisional rev 2`_
    - 2021-7-19
    - `HTML <https://spec.oneapi.io/versions/1.1-provisional-rev-2/>`__ `PDF <https://spec.oneapi.io/versions/1.1-provisional-rev-2/oneAPI-spec.pdf>`__
  * - `1.1 provisional rev 1`_
    - 2021-4-7
    - `HTML <https://spec.oneapi.io/versions/1.1-provisional-rev-1/>`__ `PDF <https://spec.oneapi.io/versions/1.1-provisional-rev-1/oneAPI-spec.pdf>`__


1.0
---

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `1.0 rev 2`_
    - 2020-10-21
    - `HTML <https://spec.oneapi.io/versions/1.0-rev-2/>`__ `PDF <https://spec.oneapi.io/versions/1.0-rev-2/oneAPI-spec.pdf>`__
  * - `1.0 rev 1`_
    - 2020-9-14
    - `HTML <https://spec.oneapi.io/versions/1.0-rev-1/>`__ `PDF <https://spec.oneapi.io/versions/1.0-rev-1/oneAPI-spec.pdf>`__

Release Notes
-------------

1.1 rev 1
~~~~~~~~~

Changes since 1.0

* Ray Tracing: Added

  * Ray tracing capabilities have been added to the oneAPI
    specification providing software developers across the industry
    the ability to “write once” for high-fidelity ray-traced
    computations across multiple vendors’ systems and
    accelerators. Standardizing these interfaces provides
    well-designed, tried and true APIs and options for a broad set of
    compute and rendering infrastructure development.

  * The ray tracing functionality is subdivided into several
    domains within the oneAPI Specification:

    * Geometric ray tracing computations
    * Volumetric computation and rendering
    * Image denoising
    * Scalable rendering and visualization infrastructure

  * The set of Ray Tracing APIs include the following, which
    are in active use via the Intel® oneAPI Rendering Toolkit:

    * Embree
    * Open Volume Kernel Library
    * Open Image Denoise
    * OSPRay

* oneMKL:

  Introduces additional batched APIs for dense linear algebra. Sparse
  matrix-dense matrix product has been extended to support both row
  and column major layout for the dense matrix. The input USM pointers
  in the vector math APIs are now const qualified. To align with
  changes in SYCL 2020, all oneMKL USM APIs were updated to take an
  (optional) std::vector of input events instead of
  sycl::vector_class. Other changes include minor clarifications and
  bug fixes.

* DPC++

  The new extensions listed as part of oneAPI 1.1 include simplified
  device selection through text-based filtering, a default context for
  each platform to simplify common coding patterns, interoperability
  with devices that use Level Zero as a backend, an easier to use
  kernel-scope local memory allocation mechanism, GPU-specific
  information queries, FPGA-specific performance tuning controls, and
  a sub-group mask feature.

  DPC++ features that were incorporated into the SYCL 2020 spec were
  removed from this document.

* oneVPL

  New AV1 encode features. Enabled support for planar I422, I210, and
  BGR formats. Added surface pool interface for surface management.

* Level Zero

  Updates included significantly improved image processing
  functionality, better interoperability with other APIs and operating
  systems, new extensions for floating-point atomics and additional
  subgroup operations, and extensions to tune and optimize the way
  memory is allocated and kernels are scheduled on specific devices.

1.1 provisional rev 2
~~~~~~~~~~~~~~~~~~~~~

* oneVPL: Updated to 2.4.0
* oneDAL: Updated some APIs
* oneMKL: bug fixes

1.1 provisional rev 1
~~~~~~~~~~~~~~~~~~~~~

* Ray Tracing: added to oneAPI specification
* VPL: Updated to 2.3.1
* Level Zero: Updated to 1.1.2
* oneDNN: Added graph API

1.0 rev 2
~~~~~~~~~

* Formatting fixes for PDF

1.0 rev 1
~~~~~~~~~

* Initial release

oneIPL
======

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneIPL v0.5`_
    - 2021-10-8
    - `HTML <https://spec.oneapi.io/oneipl/latest/index.html>`__


Release Notes
-------------

oneIPL v0.5
~~~~~~~~~~~

Initial release


oneDTL
======

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneDTL v0.5`_
    - 2021-11-10
    - `HTML <https://spec.oneapi.io/onedtl/latest/index.html>`__


Release Notes
-------------

oneDTL v0.5
~~~~~~~~~~~

Initial release


Ray Tracing
===========

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `Ray Tracing v0.5`_
    - 2021-2-18
    - `HTML <https://spec.oneapi.io/oneart/0.5-rev-1/index.html>`__


Release Notes
-------------

Ray Tracing v0.5
~~~~~~~~~~~~~~~~

* Ray tracing capabilities have been added to the oneAPI
  specification providing software developers across the industry the
  ability to “write once” for high-fidelity ray-traced computations
  across multiple vendors’ systems and accelerators. Standardizing
  these interfaces provides well-designed, tried and true APIs and
  options for a broad set of compute and rendering infrastructure
  development.

* The ray tracing functionality is subdivided into several
  domains within the oneAPI Specification:

  * Geometric ray tracing computations
  * Volumetric computation and rendering
  * Image denoising
  * Scalable rendering and visualization infrastructure

* The set of Ray Tracing APIs include the following, which
  are in active use via the Intel® oneAPI Rendering Toolkit:

  * Embree
  * Open Volume Kernel Library
  * Open Image Denoise
  * OSPRay


oneDNN Graph
============

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneDNN Graph v0.9`_
    - 2021-12-28
    - `HTML <https://spec.oneapi.io/onednn-graph/latest/index.html>`__
  * - `oneDNN Graph v0.8`_
    - 2021-11-8
    - `HTML <https://spec.oneapi.io/onednn-graph/latest/index.html>`__
  * - `oneDNN Graph v0.5`_
    - 2021-4-8
    - `HTML <https://spec.oneapi.io/onednn-graph/latest/index.html>`__

Release Notes
-------------

oneDNN Graph v0.9
~~~~~~~~~~~~~~~~~

- Introduced bf16 inference support.
- Introduced multi-head attention (MHA) fusion supported by oneDNN Graph
  compiler with optimized code generation (experimental).

oneDNN Graph v0.8
~~~~~~~~~~~~~~~~~

Introduces int8 inference support.


oneDNN Graph v0.5
~~~~~~~~~~~~~~~~~

Provides more optimization and improves the programming
experience. The main changes are as follows:

- Support in-place optimization to reduce memory footprint and provide
  better data locality
- Support using the partition vector directly for compilation and
  execution without maintaining a computation graph
- Provide a special End op to express the multiple uses of a logical
  tensor, typically for indicating the output tensors of the graph

oneVPL
======

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneVPL v2.6.0`_
    - 2021-12-3
    - `HTML <https://spec.oneapi.io/onevpl/2.6.0/index.html>`__
  * - `oneVPL v2.5.0`_
    - 2021-8-30
    - `HTML <https://spec.oneapi.io/onevpl/2.5.0/index.html>`__
  * - `oneVPL v2.4.0`_
    - 2021-5-12
    - `HTML <https://spec.oneapi.io/onevpl/2.4.0/index.html>`__
  * - `oneVPL v2.3.1`_
    - 2021-4-8
    - `HTML <https://spec.oneapi.io/onevpl/2.3.1/index.html>`__

Release Notes
-------------

oneVPL v2.6.0
~~~~~~~~~~~~~

New in this release:

* New development practice to treat some new API features as
  experimental was introduced.
  All new experimental API is wrapped with ONE_EXPERIMENTAL macro.
* Experimental API: introduced MFX_HANDLE_PXP_CONTEXT to support
  protected content.
* Experimental API: introduced CPUEncToolsProcessing hint to run
  adaptive encoding tools on CPU.
* Experimental API: extended device ID reporting to cover
  multi-adapter cases.
* Experimental API: introduced common alias for mfxExtAVCRefListCtrl
* Experimental API: mfxExtDecodeErrorReport ErrorTypes enum extended
  with new JPEG/MJPEG decode error report.
* Clarified LowPower flag meaning.
* Described that mfxExtThreadsParam can be attached to
  mfxInitializationParam during session initialization.
* Refined description of the MFXVideoDECODE_VPP_DecodeFrameAsync
  function.
* New dispatcher's config filter property: MediaAdapterType.
* Marked all deprecated fields as MFX_DEPRECATED.
* Introduced priority loading option for custom libraries.
* Clarified AV1 encoder behavior about writing of IVF headers.
* Removed outdated note about loading priority of Intel Media Software
  Development Kit
* Spelled out mfxVariant type usage for strings.
* New product names for platforms:

    * Code name DG2,
    * Code name ATS-M.

oneVPL v2.5.0
~~~~~~~~~~~~~

New in this release:

* Added mfxMediaAdapterType to capability reporting.
* Added surface pool interface.
* Helper macro definition to simplify filter properties set up process
  for dispatcher.
* Added mfxExtAV1BitstreamParam, mfxExtAV1ResolutionParam and
  mfxExtAV1TileParam for AV1e.
* Added MFX_RESOURCE_VA_SURFACE_PTR and MFX_RESOURCE_VA_BUFFER_PTR
  enumerators.
* Clarified HEVC Main 10 Still Picture Profile configuration.
* External Buffer ID of mfxExtVideoSignalInfo and
  mfxExtMasteringDisplayColourVolume for video processing.
* New MFX_WRN_ALLOC_TIMEOUT_EXPIRED return status. Indicates that all
  surfaces are currently in use and timeout set by
  mfxExtAllocationHints for allocation of new surfaces through
  functions GetSurfaceForXXX expired.
* Introduced universal temporal layering structure.
* Added MFX_RESOURCE_VA_SURFACE_PTR and MFX_RESOURCE_VA_BUFFER_PTR
  enumerators.
* Introduced segmentation interface for AV1e, including ext-buffers
  and enums.
* Introduced planar I422 and I210 FourCC codes.

Bug Fixes:

* Dispatcher: Removed /etc/ld.so.cache from oneVPL search order.
* mfxSurfaceArray: CDECL attribute added to the member-functions.

Deprecated:

* mfxExtVPPDenoise extension buffer.

oneVPL v2.4.0
~~~~~~~~~~~~~

* Added ability to retrieve path to the shared library with the implementation.
* Added 3DLUT (Three-Dimensional Look Up Table) filter in VPP.
* Added mfxGUID structure to specify Globally Unique Identifiers (GUIDs).
* Added QueryInterface function to mfxFrameSurfaceInterface.
* Added AdaptiveRef and alias for ExtBrcAdaptiveLTR.
* Added MFX_FOURCC_BGRP FourCC for Planar BGR format.
* Environmental variables to control dispatcher's logger.

oneVPL v2.3.1
~~~~~~~~~~~~~

* Encoding in Hyper mode.

* New product names for platforms:

  * Code name Rocket Lake,
  * Code name Alder Lake S,
  * Code name Alder Lake P,
  * Code name Arctic Sound P.

* mfx.h header file is added which includes all header files.
* Added deprecation messages (deprecation macro) to the MFXInit and
  MFXInitEx functions definition.
