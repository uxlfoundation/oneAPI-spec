..
  Copyright 2020 Intel Corporation

.. _oneVPL-section:

======
oneVPL
======

The |vpl_full_name| (oneVPL) is a programming interface for video decoding,
encoding, and processing to build portable media pipelines on CPUs,
GPUs, and other accelerators. It provides device discovery and selection in
media centric and video analytics workloads and API primitives for zero-copy
buffer sharing. oneVPL is backwards and cross-architecture compatible to ensure
optimal execution on current and next generation hardware without source code
changes.

---------------------
oneVPL API versioning
---------------------

oneVPL is the successor to |msdk_full_name|. oneVPL API versioning starts from
2.0. There is a correspondent version of |msdk_full_name| API which is used as a basis
for oneVPL and defined as ``MFX_LEGACY_VERSION`` macro.

Experimental APIs in oneVPL are protected with the following macro::

   #if (MFX_VERSION >= MFX_VERSION_NEXT)

To use the API, define the ``MFX_VERSION_USE_LATEST`` macro.

.. toctree::
   :hidden:

   MSDK_architecture
   MSDK_prg
   VPL_summary
   VPL_apnds
   MSDK_acronyms
   VPL_api_ref
