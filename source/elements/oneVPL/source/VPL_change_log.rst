.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==========
Change Log
==========

This section describes the API evolution from version to version.

.. contents::
   :local:
   :depth: 1

-----------
Version 2.6
-----------

New in this release:

* New development practice to treat some new API features as experimental was introduced.
  All new experimental API is wrapped with ONE_EXPERIMENTAL macro.
* Experimental API: introduced MFX_HANDLE_PXP_CONTEXT to support protected content.
* Experimental API: introduced CPUEncToolsProcessing hint to run adaptive encoding tools on CPU.
* Experimental API: extended device ID reporting to cover multi-adapter cases.
* Experimental API: introduced common alias for mfxExtAVCRefListCtrl
* Experimental API: mfxExtDecodeErrorReport ErrorTypes enum extended with new JPEG/MJPEG decode error report.
* Clarified LowPower flag meaning.
* Described that mfxExtThreadsParam can be attached to mfxInitializationParam during session initialization.
* Refined description of the MFXVideoDECODE_VPP_DecodeFrameAsync function.
* New dispatcher's config filter property: MediaAdapterType.
* Marked all deprecated fields as MFX_DEPRECATED.
* Introduced priority loading option for custom libraries. 
* Clarified AV1 encoder behavior about writing of IVF headers.
* Removed outdated note about loading priority of |msdk_full_name|. For loading details see 
  :ref:`onevpl_coexistense`.
* Spelled out mfxVariant type usage for strings.
* New product names for platforms:

    * Code name DG2,
    * Code name ATS-M.

-----------
Version 2.5
-----------

New in this release:

* Added mfxMediaAdapterType to capability reporting.
* Added surface pool interface.
* Helper macro definition to simplify filter properties set up process
  for dispatcher.
* Added mfxExtAV1BitstreamParam, mfxExtAV1ResolutionParam and mfxExtAV1TileParam for AV1e.
* Added MFX_RESOURCE_VA_SURFACE_PTR and MFX_RESOURCE_VA_BUFFER_PTR enumerators.
* Clarified HEVC Main 10 Still Picture Profile configuration.
* External Buffer ID of mfxExtVideoSignalInfo and mfxExtMasteringDisplayColourVolume for video processing.
* New MFX_WRN_ALLOC_TIMEOUT_EXPIRED return status. Indicates that all surfaces are currently
  in use and timeout set by mfxExtAllocationHints for allocation of new surfaces through
  functions GetSurfaceForXXX expired.
* Introduced universal temporal layering structure.
* Added MFX_RESOURCE_VA_SURFACE_PTR and MFX_RESOURCE_VA_BUFFER_PTR enumerators. 
* Introduced segmentation interface for AV1e, including ext-buffers and enums.
* Introduced planar I422 and I210 FourCC codes.

Bug Fixes:

* Dispatcher: Removed /etc/ld.so.cache from oneVPL search order.
* mfxSurfaceArray: CDECL attribute added to the member-functions.

Deprecated:

* mfxExtVPPDenoise extension buffer.


-----------
Version 2.4
-----------

* Added ability to retrieve path to the shared library with the implementation.
* Added 3DLUT (Three-Dimensional Look Up Table) filter in VPP.
* Added mfxGUID structure to specify Globally Unique Identifiers (GUIDs).
* Added QueryInterface function to mfxFrameSurfaceInterface.
* Added AdaptiveRef and alias for ExtBrcAdaptiveLTR.
* Added MFX_FOURCC_BGRP FourCC for Planar BGR format.
* Enviromental variables to control dispatcher's logger.

-----------
Version 2.3
-----------

* Encoding in Hyper mode.
* New product names for platforms:

    * Code name Rocket Lake,
    * Code name Alder Lake S,
    * Code name Alder Lake P,
    * Code name for Arctic Sound P.
    * For spec version 2.3.1 MFX_PLATFORM_XEHP_SDV alias was added

* mfx.h header file is added which includes all header files.
* Added deprecation messages (deprecation macro) to the functions MFXInit and
  MFXInitEx functions definition.
