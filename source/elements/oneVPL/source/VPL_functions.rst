=========
Functions
=========

---------------------------
Implementation Capabilities
---------------------------

.. doxygenfunction:: MFXQueryImplsDescription
   :project: oneVPL

.. important:: Function :cpp:func:`MFXQueryImplsDescription` is mandatory for any implementation.

.. doxygenfunction:: MFXReleaseImplDescription
   :project: oneVPL

.. important:: Function :cpp:func:`MFXReleaseImplDescription` is mandatory for any implementation.


------------------
Session Management
------------------

.. doxygenfunction:: MFXInit
   :project: oneVPL

.. doxygenfunction:: MFXInitEx
   :project: oneVPL

.. important:: Function :cpp:func:`MFXInitEx` is mandatory for any implementation.

.. doxygenfunction:: MFXClose
   :project: oneVPL

.. important:: Function :cpp:func:`MFXClose` is mandatory for any implementation.

.. doxygenfunction:: MFXQueryIMPL
   :project: oneVPL

.. doxygenfunction:: MFXQueryVersion
   :project: oneVPL

.. doxygenfunction:: MFXJoinSession
   :project: oneVPL

.. doxygenfunction:: MFXDisjoinSession
   :project: oneVPL

.. doxygenfunction:: MFXCloneSession
   :project: oneVPL

.. doxygenfunction:: MFXSetPriority
   :project: oneVPL

.. doxygenfunction:: MFXGetPriority
   :project: oneVPL

---------
VideoCORE
---------

.. doxygenfunction:: MFXVideoCORE_SetFrameAllocator
   :project: oneVPL

.. doxygenfunction:: MFXVideoCORE_SetHandle
   :project: oneVPL

.. doxygenfunction:: MFXVideoCORE_GetHandle
   :project: oneVPL

.. doxygenfunction:: MFXVideoCORE_QueryPlatform
   :project: oneVPL

.. doxygenfunction:: MFXVideoCORE_SyncOperation
   :project: oneVPL

.. important:: Function :cpp:func:`MFXVideoCORE_SyncOperation` is mandatory for
   any implementation.

------
Memory
------

.. doxygenfunction:: MFXMemory_GetSurfaceForVPP
   :project: oneVPL

.. doxygenfunction:: MFXMemory_GetSurfaceForEncode
   :project: oneVPL

.. doxygenfunction:: MFXMemory_GetSurfaceForDecode
   :project: oneVPL


-----------
VideoENCODE
-----------

.. doxygenfunction:: MFXVideoENCODE_Query
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoENCODE_Query` function is mandatory when
   implementing an encoder.

.. doxygenfunction:: MFXVideoENCODE_QueryIOSurf
   :project: oneVPL

.. doxygenfunction:: MFXVideoENCODE_Init
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoENCODE_Init` function is mandatory when
               implementing an encoder.

.. doxygenfunction:: MFXVideoENCODE_Reset
   :project: oneVPL

.. doxygenfunction:: MFXVideoENCODE_Close
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoENCODE_Close` function is mandatory when
               implementing an encoder.

.. doxygenfunction:: MFXVideoENCODE_GetVideoParam
   :project: oneVPL

.. doxygenfunction:: MFXVideoENCODE_GetEncodeStat
   :project: oneVPL

.. doxygenfunction:: MFXVideoENCODE_EncodeFrameAsync
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoENCODE_EncodeFrameAsync` function is mandatory when
               implementing an encoder.

-----------
VideoDECODE
-----------

.. doxygenfunction:: MFXVideoDECODE_Query
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoDECODE_Query` is mandatory when implementing a decoder.

.. doxygenfunction:: MFXVideoDECODE_DecodeHeader
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_QueryIOSurf
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_Init
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoDECODE_Init` is mandatory when implementing a decoder.

.. doxygenfunction:: MFXVideoDECODE_Reset
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_Close
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoDECODE_Close` is mandatory when implementing a decoder.

.. doxygenfunction:: MFXVideoDECODE_GetVideoParam
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_GetDecodeStat
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_SetSkipMode
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_GetPayload
   :project: oneVPL

.. doxygenfunction:: MFXVideoDECODE_DecodeFrameAsync
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` is mandatory when implementing a decoder.

--------
VideoVPP
--------

.. doxygenfunction:: MFXVideoVPP_Query
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoVPP_Query` function is mandatory when implementing a VPP filter.

.. doxygenfunction:: MFXVideoVPP_QueryIOSurf
   :project: oneVPL

.. doxygenfunction:: MFXVideoVPP_Init
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoVPP_Init` function is mandatory when implementing a VPP filter.

.. doxygenfunction:: MFXVideoVPP_Reset
   :project: oneVPL

.. doxygenfunction:: MFXVideoVPP_Close
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoVPP_Close` function is mandatory when implementing a VPP filter.

.. doxygenfunction:: MFXVideoVPP_GetVideoParam
   :project: oneVPL

.. doxygenfunction:: MFXVideoVPP_GetVPPStat
   :project: oneVPL

.. doxygenfunction:: MFXVideoVPP_RunFrameVPPAsync
   :project: oneVPL

.. important:: The :cpp:func:`MFXVideoVPP_RunFrameVPPAsync` function is mandatory when implementing a VPP filter.

--------
Adapters
--------

.. doxygenfunction:: MFXQueryAdapters
   :project: oneVPL

.. doxygenfunction:: MFXQueryAdaptersDecode
   :project: oneVPL

.. doxygenfunction:: MFXQueryAdaptersNumber
   :project: oneVPL