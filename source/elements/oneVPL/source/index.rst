..
  Copyright 2020 Intel Corporation

.. _oneVPL-section:


******
oneVPL
******

The |vpl_full_name| is a programming interface for video decoding,
encoding, and processing to build portable media pipelines on CPU's,
GPU's, and other accelerators.  It provides API primitives for
zero-copy buffer sharing, device discovery and selection in media
centric and video analytics workloads. oneVPL's backwards and
cross-architecture compatibility ensures optimal execution on current
and next generation hardware without source code changes.

See `oneVPL API Reference`_ for the detailed API description.

oneVPL for |msdk_full_name| Users
=================================

oneVPL is source compatible with |msdk_full_name| (MSDK), allowing
applications to use MSDK to target older hardware and oneVPL to target
everthing else. oneVPL offers improved usability over MSDK. Some
obsolete features of MSDK have been omitted from oneVPL.


oneVPL Usability Enhancements
-----------------------------

1. Smart dispatcher with implementations capabilities
   discovery. Explore `SDK Session`_ for more details.
2. Simplified decoder initialization. Expore `Decoding Procedures`_
   for more details.
3. New memory management and components (session)
   interoperability. Explore `Internal memory managment`_ and
   `Decoding Procedures`_ for more details.
4. Improved internal threading and internal task scheduling.

Obsolete MSDK Features omitted from oneVPL
------------------------------------------

The following MSDKt features are not
included in oneVPL:

Audio Support
   oneVPL is for video processing, and removes audio APIs that
   duplicate functionality from other audio libraries like
   `Sound Open Firmware <https://github.com/thesofproject>`__

ENC and PAK interfaces
   Available as part of Flexible Encode Infrastructure (FEI) and
   plugin interfaces.  FEI is the Intel Graphic specific feature
   designed for AVC and HEVC encoders, not widely used by customers.

User plugins architecture
   oneVPL enables robust video acceleration through API
   implementations of many different video processing frameworks,
   making support of its own user plugin framework obsolete.

External Buffer memory managment
   A set of callback functions to replace internal memory allocation
   is obsolete.

Video Processing extended runtime functionality
   Video processing function MFXVideoVPP_RunFrameVPPAsyncEx is
   used for plugins only and is obsolete.

External threading
   New threading model makes MFXDoWork function obsolete

The following behaviors occur when attempting to use a MSDK API that is not supported by oneVPL:

Code compilation
   Code compiled with the oneVPL API headers will generate a compile
   and/or link error when attempting to use a removed API.

Code previously compiled with MSDK and used with a oneVPL runtime
   Code previously compiled with MSDK and executing using a oneVPL
   runtime will generate an :cpp:enumerator:`MFX_ERR_UNSUPPORTED`
   error when calling a removed function.

MSDK API's not present in oneVPL
--------------------------------

Audio related functions::

  MFXAudioCORE_SyncOperation(mfxSession session, mfxSyncPoint syncp, mfxU32 wait)
  MFXAudioDECODE_Close(mfxSession session)
  MFXAudioDECODE_DecodeFrameAsync(mfxSession session, mfxBitstream *bs,
                                  mfxAudioFrame *frame_out, mfxSyncPoint *syncp)
  MFXAudioDECODE_DecodeHeader(mfxSession session, mfxBitstream *bs, mfxAudioParam *par)
  MFXAudioDECODE_GetAudioParam(mfxSession session, mfxAudioParam *par)
  MFXAudioDECODE_Init(mfxSession session, mfxAudioParam *par)
  MFXAudioDECODE_Query(mfxSession session, mfxAudioParam *in, mfxAudioParam *out)
  MFXAudioDECODE_QueryIOSize(mfxSession session, mfxAudioParam *par, mfxAudioAllocRequest *request)
  MFXAudioDECODE_Reset(mfxSession session, mfxAudioParam *par)
  MFXAudioENCODE_Close(mfxSession session)
  MFXAudioENCODE_EncodeFrameAsync(mfxSession session, mfxAudioFrame *frame,
                                  mfxBitstream *buffer_out, mfxSyncPoint *syncp)
  MFXAudioENCODE_GetAudioParam(mfxSession session, mfxAudioParam *par)
  MFXAudioENCODE_Init(mfxSession session, mfxAudioParam *par)
  MFXAudioENCODE_Query(mfxSession session, mfxAudioParam *in, mfxAudioParam *out)
  MFXAudioENCODE_QueryIOSize(mfxSession session, mfxAudioParam *par, mfxAudioAllocRequest *request)
  MFXAudioENCODE_Reset(mfxSession session, mfxAudioParam *par)

Flexible encode infrastructure functions::
   
  MFXVideoENC_Close(mfxSession session)
  MFXVideoENC_GetVideoParam(mfxSession session, mfxVideoParam *par)
  MFXVideoENC_Init(mfxSession session, mfxVideoParam *par)
  MFXVideoENC_ProcessFrameAsync (mfxSession session, mfxENCInput *in,
                                 mfxENCOutput *out, mfxSyncPoint *syncp)
  MFXVideoENC_Query(mfxSession session, mfxVideoParam *in, mfxVideoParam *out)
  MFXVideoENC_QueryIOSurf(mfxSession session, mfxVideoParam *par,
                          mfxFrameAllocRequest *request)
  MFXVideoENC_Reset(mfxSession session, mfxVideoParam *par)
  MFXVideoPAK_Close(mfxSession session)
  MFXVideoPAK_GetVideoParam(mfxSession session, mfxVideoParam *par)
  MFXVideoPAK_Init(mfxSession session, mfxVideoParam *par)
  MFXVideoPAK_ProcessFrameAsync(mfxSession session, mfxPAKInput *in,
                                mfxPAKOutput *out, mfxSyncPoint *syncp)
  MFXVideoPAK_Query(mfxSession session, mfxVideoParam *in, mfxVideoParam *out)
  MFXVideoPAK_QueryIOSurf(mfxSession session, mfxVideoParam *par,
                          mfxFrameAllocRequest *request)
  MFXVideoPAK_Reset(mfxSession session, mfxVideoParam *par)

User Plugin functions::

  MFXAudioUSER_ProcessFrameAsync(mfxSession session, const mfxHDL *in,
                                 mfxU32 in_num, const mfxHDL *out,
				 mfxU32 out_num, mfxSyncPointx *syncp)
  MFXAudioUSER_Register(mfxSession session, mfxU32 type, const mfxPlugin *par)
  MFXAudioUSER_Unregister(mfxSession session, mfxU32 type)
  MFXVideoUSER_GetPlugin(mfxSession session, mfxU32 type, mfxPlugin *par)
  MFXVideoUSER_ProcessFrameAsync(mfxSession session, const mfxHDL *in, mfxU32 in_num,
                                 const mfxHDL *out, mfxU32 out_num, mfxSyncPoint *syncp)
  MFXVideoUSER_Register(mfxSession session, mfxU32 type, const mfxPlugin *par)
  MFXVideoUSER_Unregister(mfxSession session, mfxU32 type)
  MFXVideoUSER_Load(mfxSession session, const mfxPluginUID *uid, mfxU32 version)
  MFXVideoUSER_LoadByPath(mfxSession session, const mfxPluginUID *uid, mfxU32 version,
                          const mfxChar *path, mfxU32 len)
  MFXVideoUSER_UnLoad(mfxSession session, const mfxPluginUID *uid)
  MFXDoWork(mfxSession session)

Memory functions::

  MFXVideoCORE_SetBufferAllocator(mfxSession session, mfxBufferAllocator *allocator)

Video processing functions::

  MFXVideoVPP_RunFrameVPPAsyncEx(mfxSession session, mfxFrameSurface1 *in,
                                 mfxFrameSurface1 *surface_work, mfxFrameSurface1 **surface_out,
				 mfxSyncPoint *syncp)

.. important:: Corresponding extension buffers are also removed.

oneVPL API's not present in MSDK
--------------------------------

oneVPL dispatcher functions:

| :cpp:func:`MFXLoad`
| :cpp:func:`MFXUnload`
| :cpp:func:`MFXCreateConfig`
| :cpp:func:`MFXSetConfigFilterProperty`
| :cpp:func:`MFXEnumImplementations`
| :cpp:func:`MFXCreateSession`
| :cpp:func:`MFXDispReleaseImplDescription`

Memory management functions:

| :cpp:func:`MFXMemory_GetSurfaceForVPP`
| :cpp:func:`MFXMemory_GetSurfaceForEncode`
| :cpp:func:`MFXMemory_GetSurfaceForDecode`

Implementation capabilities retrieval functions:

| :cpp:func:`MFXQueryImplDescription`
| :cpp:func:`MFXReleaseImplDescription`

oneVPL API versioning
=====================

As a successor of MSDKt oneVPL API version starts from 2.0.

Experimental API's in oneVPL are protected with the following macro::

   #if (MFX_VERSION >= MFX_VERSION_NEXT)

To use the API, define the ``MFX_VERSION_USE_LATEST`` macro.

Acronyms and Abbreviations
==========================
.. include:: MSDK_acronyms.inc.rst

Architecture
============
.. include:: MSDK_architecture.inc.rst

Video Decoding
--------------
.. include:: MSDK_decoding.inc.rst

Video Encoding
--------------
.. include:: MSDK_encoding.inc.rst

Video Processing
----------------
.. include:: MSDK_processing.inc.rst

Programming Guide
=================
.. include:: MSDK_prg.inc.rst

Summary Tables
==============
.. include:: VPL_summary.inc.rst

Appendicies
===========
.. include:: VPL_apnds.inc.rst


oneVPL API Reference
====================

Basic Types
-----------
.. doxygentypedef:: mfxU8
   :project: oneVPL

.. doxygentypedef:: mfxI8
   :project: oneVPL

.. doxygentypedef:: mfxU16
   :project: oneVPL

.. doxygentypedef:: mfxI16
   :project: oneVPL

.. doxygentypedef:: mfxU32
   :project: oneVPL

.. doxygentypedef:: mfxI32
   :project: oneVPL

.. doxygentypedef:: mfxUL32
   :project: oneVPL

.. doxygentypedef:: mfxL32
   :project: oneVPL

.. doxygentypedef:: mfxU64
   :project: oneVPL

.. doxygentypedef:: mfxI64
   :project: oneVPL

.. doxygentypedef:: mfxF32
   :project: oneVPL

.. doxygentypedef:: mfxF64
   :project: oneVPL

.. doxygentypedef:: mfxHDL
   :project: oneVPL

.. doxygentypedef:: mfxMemId
   :project: oneVPL

.. doxygentypedef:: mfxThreadTask
   :project: oneVPL

.. doxygentypedef:: mfxChar
   :project: oneVPL

Typedefs
--------

.. doxygentypedef:: mfxSession
   :project: oneVPL 

.. doxygentypedef:: mfxSyncPoint
   :project: oneVPL

.. doxygentypedef:: mfxLoader
   :project: oneVPL 

.. doxygentypedef:: mfxConfig
   :project: oneVPL

oneVPL Dispatcher API
---------------------

.. include:: VPL_disp_api.inc.rst

Enums
-----

.. include:: VPL_enums.inc.rst

Structs
-------

.. include:: VPL_structs.inc.rst

Functions
---------------

.. include:: VPL_functions.inc.rst

