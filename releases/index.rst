.. oneAPI Specification Versions documentation master file, created by
   sphinx-quickstart on Thu Apr  8 09:51:39 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

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


1.1
---

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `1.1 provisional rev 1`_
    - 2021-4-7
    - `HTML <https://spec.oneapi.com/versions/1.1-provisional-rev-1/>`__ `PDF <https://spec.oneapi.com/versions/1.1-provisional-rev-1/oneAPI-spec.pdf>`__


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
    - `HTML <https://spec.oneapi.com/versions/1.0-rev-2/>`__ `PDF <https://spec.oneapi.com/versions/1.0-rev-2/oneAPI-spec.pdf>`__
  * - `1.0 rev 1`_
    - 2020-9-14
    - `HTML <https://spec.oneapi.com/versions/1.0-rev-1/>`__ `PDF <https://spec.oneapi.com/versions/1.0-rev-1/oneAPI-spec.pdf>`__ 

Release Notes
-------------

1.1 provisional rev 1
~~~~~~~~~~~~~~~~~~~~~

1.0 rev 2
~~~~~~~~~

* Formatting fixes for PDF

1.0 rev 1
~~~~~~~~~

* Initial release

Advanced Ray Tracing
====================

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneART v0.5`_
    - 2021-2-18
    - `HTML <https://spec.oneapi.com/oneart/0.5-rev-1/index.html>`__


Release Notes
-------------

oneART v0.5
~~~~~~~~~~~

* Advanced ray tracing capabilities have been added to the oneAPI
  specification providing software developers across the industry the
  ability to “write once” for high-fidelity ray-traced computations
  across multiple vendors’ systems and accelerators. Standardizing
  these interfaces provides well-designed, tried and true APIs and
  options for a broad set of compute and rendering infrastructure
  development.

* The advanced ray tracing functionality is subdivided into several
  domains within the oneAPI Specification:

  * Geometric ray tracing computations
  * Volumetric computation and rendering
  * Image denoising
  * Scalable rendering and visualization infrastructure

* The set of Advanced Ray Tracing APIs include the following, which
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
  * - `oneDNN Graph v0.5`_
    - 2021-4-8
    - `HTML <https://spec.oneapi.com/onednn-graph/latest/index.html>`__

Release Notes
-------------

oneDNN Graph v0.5
~~~~~~~~~~~~~~~~~

oneVPL
======

.. list-table::
  :widths: 30 20 50
  :header-rows: 1

  * - Version
    - Date
    - View
  * - `oneVPL v2.3.1`_
    - 2021-4-8
    - `HTML <https://spec.oneapi.com/onevpl/2.3.1/index.html>`__

Release Notes
-------------

oneVPL v2.3.1
~~~~~~~~~~~~~

* Encoding in Hyper mode.
  
* New product names for platforms:
  
  * Code name Rocket Lake,
  * Code name Alder Lake S,
  * Code name Alder Lake P,
  * Code name Arctic Sound P.
    
* mfx.h header file is added which includes all header files.
* Added deprecation messages (deprecation macro) to the MFXInit and MFXInitEx functions definition.
