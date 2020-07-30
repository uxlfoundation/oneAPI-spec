====================================
Mandatory/Optional APIs and Features
====================================

Disclaimer
----------

The specification implementer may implement any subset of the oneVPL specification.
The specification makes no claim that that any codec, encoder, decoder or VPP filter or their
underlying features are mandatory for the implementation.
The oneVPL API is designed in a way so that the implementation user has several options
to discover implementation capabilities:

1. Before session creation user can get implementation capabilities by using
   :cpp:func:`MFXEnumImplementations` function to discover supported encoders/decoders or
   VPP filters with their supported color format and memory types.
2. Once session is created, use can use **Query** functions to obtain low level
   implementation capabilities.

Functions must be exposed by any implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`Exported Functions/API Version table <export-func-version-table>` shows
the list of functions exported by any implementation with corresponding API version.
Implementation of all those functions is mandatory, while majority of them can return
:cpp:enumerator:`mfxStatus::MFX_ERR_NOT_IMPLEMENTED`.

.. _export-func-version-table:

.. table:: Exported Functions/API Version

   ================================= ===========
   Function                          API Version
   ================================= ===========
   MFXInit                           1.0
   MFXClose                          1.0
   MFXQueryIMPL                      1.0
   MFXQueryVersion                   1.0
   MFXJoinSession                    1.0
   MFXDisjoinSession                 1.0
   MFXCloneSession                   1.0
   MFXSetPriority                    1.0
   MFXGetPriority                    1.0
   MFXVideoCORE_SetFrameAllocator    1.0
   MFXVideoCORE_SetHandle            1.0
   MFXVideoCORE_GetHandle            1.0
   MFXVideoCORE_SyncOperation        1.0
   MFXVideoENCODE_Query              1.0
   MFXVideoENCODE_QueryIOSurf        1.0
   MFXVideoENCODE_Init               1.0
   MFXVideoENCODE_Reset              1.0
   MFXVideoENCODE_Close              1.0
   MFXVideoENCODE_GetVideoParam      1.0
   MFXVideoENCODE_GetEncodeStat      1.0
   MFXVideoENCODE_EncodeFrameAsync   1.0
   MFXVideoDECODE_Query              1.0
   MFXVideoDECODE_DecodeHeader       1.0
   MFXVideoDECODE_QueryIOSurf        1.0
   MFXVideoDECODE_Init               1.0
   MFXVideoDECODE_Reset              1.0
   MFXVideoDECODE_Close              1.0
   MFXVideoDECODE_GetVideoParam      1.0
   MFXVideoDECODE_GetDecodeStat      1.0
   MFXVideoDECODE_SetSkipMode        1.0
   MFXVideoDECODE_GetPayload         1.0
   MFXVideoDECODE_DecodeFrameAsync   1.0
   MFXVideoVPP_Query                 1.0
   MFXVideoVPP_QueryIOSurf           1.0
   MFXVideoVPP_Init                  1.0
   MFXVideoVPP_Reset                 1.0
   MFXVideoVPP_Close                 1.0
   MFXVideoVPP_GetVideoParam         1.0
   MFXVideoVPP_GetVPPStat            1.0
   MFXVideoVPP_RunFrameVPPAsync      1.0
   MFXVideoVPP_RunFrameVPPAsyncEx    1.10
   MFXInitEx                         1.14
   MFXVideoCORE_QueryPlatform        1.19
   MFXMemory_GetSurfaceForVPP        2.0
   MFXMemory_GetSurfaceForEncode     2.0
   MFXMemory_GetSurfaceForDecode     2.0
   MFXQueryImplsDescription          2.0
   MFXReleaseImplDescription         2.0
   ================================= ===========

Mandatory API for each implementation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each implementation must implement following functions:

1. Functions required for the dispatcher to create session: :cpp:func:`MFXInitEx`,
   :cpp:func:`MFXClose`.
2. Functions required for the dispatcher to return implementation capabilities:
   :cpp:func:`MFXQueryImplsDescription`, :cpp:func:`MFXReleaseImplDescription`.
3. If implementation implements any encoder, than those functions are mandatory
   for the implementation: :cpp:func:`MFXVideoENCODE_Init`, :cpp:func:`MFXVideoENCODE_Close`,
   :cpp:func:`MFXVideoENCODE_Query`, :cpp:func:`MFXVideoENCODE_EncodeFrameAsync`.
4. If implementation implements any decoder, than those functions are mandatory
   for the implementation: :cpp:func:`MFXVideoDECODE_Init`, :cpp:func:`MFXVideoDECODE_Close`,
   :cpp:func:`MFXVideoDECODE_Query`, :cpp:func:`MFXVideoDECODE_DecodeFrameAsync`.
5. If implementation implements any VPP filter, than those functions are mandatory
   for the implementation: :cpp:func:`MFXVideoVPP_Init`, :cpp:func:`MFXVideoVPP_Close`,
   :cpp:func:`MFXVideoVPP_Query`, :cpp:func:`MFXVideoVPP_RunFrameVPPAsync`.
6. Function required for the asynchronous operations synchronization
   :cpp:func:`MFXVideoCORE_SyncOperation` is mandatory for the implementation.
7. Any other functions or extension buffers are optional for the implementation.

If implementation implements either decoder or encoder or VPP filter, its capabilities
must be provided by using :cpp:struct:`mfxImplDescription` structure, which lists
mandatory capabilities of the implementation.

.. note:: Mandatory function must have implementation and must not return
          :cpp:enumerator:`MFX_ERR_NOT_IMPLEMENTED` status.
