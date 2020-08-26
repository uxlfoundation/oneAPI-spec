============================
Mandatory APIs and Functions
============================

----------
Disclaimer
----------

The specification implementer may implement any subset of the oneVPL specification.
The specification makes no claim that that any codec, encoder, decoder, or VPP
filter, or their underlying features, are mandatory for the implementation.
The oneVPL API is designed such that the implementation user has several options
to discover implementation capabilities:

#. Before session creation, the user can get implementation capabilities by using
   the :cpp:func:`MFXEnumImplementations` function to discover supported
   encoders, decoders, or VPP filters with their supported color format and
   memory types.
#. Once the session is created, the user can use **Query** functions to obtain
   low level implementation capabilities.

-------------------
Mandatory Functions
-------------------

The :ref:`Exported Functions/API Version table <export-func-version-table>` shows
the list of functions that must be exposed by any implementation, with the
corresponding API version. Implementation of all listed functions is mandatory.
The majority of the functions can return :cpp:enumerator:`mfxStatus::MFX_ERR_NOT_IMPLEMENTED`.

.. _export-func-version-table:

.. list-table:: Exported Functions/API Version
   :header-rows: 1
   :widths: 70 30

   * - **Function**
     - **API Version**
   * - :cpp:func:`MFXInit`
     - 1.0
   * - :cpp:func:`MFXClose`
     - 1.0
   * - :cpp:func:`MFXQueryIMPL`
     - 1.0
   * - :cpp:func:`MFXQueryVersion`
     - 1.0
   * - :cpp:func:`MFXJoinSession`
     - 1.0
   * - :cpp:func:`MFXDisjoinSession`
     - 1.0
   * - :cpp:func:`MFXCloneSession`
     - 1.0
   * - :cpp:func:`MFXSetPriority`
     - 1.0
   * - :cpp:func:`MFXGetPriority`
     - 1.0
   * - :cpp:func:`MFXVideoCORE_SetFrameAllocator`
     - 1.0
   * - :cpp:func:`MFXVideoCORE_SetHandle`
     - 1.0
   * - :cpp:func:`MFXVideoCORE_GetHandle`
     - 1.0
   * - :cpp:func:`MFXVideoCORE_SyncOperation`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_Query`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_QueryIOSurf`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_Init`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_Reset`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_Close`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_GetVideoParam`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_GetEncodeStat`
     - 1.0
   * - :cpp:func:`MFXVideoENCODE_EncodeFrameAsync`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_Query`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_DecodeHeader`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_QueryIOSurf`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_Init`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_Reset`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_Close`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_GetVideoParam`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_GetDecodeStat`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_SetSkipMode`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_GetPayload`
     - 1.0
   * - :cpp:func:`MFXVideoDECODE_DecodeFrameAsync`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_Query`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_QueryIOSurf`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_Init`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_Reset`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_Close`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_GetVideoParam`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_GetVPPStat`
     - 1.0
   * - :cpp:func:`MFXVideoVPP_RunFrameVPPAsync`
     - 1.0
   * - :cpp:func:`MFXInitEx`
     - 1.14
   * - :cpp:func:`MFXVideoCORE_QueryPlatform`
     - 1.19
   * - :cpp:func:`MFXMemory_GetSurfaceForVPP`
     - 2.0
   * - :cpp:func:`MFXMemory_GetSurfaceForEncode`
     - 2.0
   * - :cpp:func:`MFXMemory_GetSurfaceForDecode`
     - 2.0
   * - :cpp:func:`MFXQueryImplsDescription`
     - 2.0
   * - :cpp:func:`MFXReleaseImplDescription`
     - 2.0


--------------
Mandatory APIs
--------------

Each implementation must implement the APIs listed below.

.. _mandatory-apis-table:

.. list-table:: Mandatory APIs
   :header-rows: 1
   :widths: 50 50

   * - **Functions**
     - **Description**
   * - | :cpp:func:`MFXInitEx`
       | :cpp:func:`MFXClose`
     - Functions required for the dispatcher to create session.
   * - | :cpp:func:`MFXQueryImplsDescription`
       | :cpp:func:`MFXReleaseImplDescription`
     - Functions required for the dispatcher to return implementation capabilities.
   * - | :cpp:func:`MFXVideoENCODE_Init`
       | :cpp:func:`MFXVideoENCODE_Close`
       | :cpp:func:`MFXVideoENCODE_Query`
       | :cpp:func:`MFXVideoENCODE_EncodeFrameAsync`
     - Encoder functions, required if the implementation implements any encoder.
   * - | :cpp:func:`MFXVideoDECODE_Init`
       | :cpp:func:`MFXVideoDECODE_Close`
       | :cpp:func:`MFXVideoDECODE_Query`
       | :cpp:func:`MFXVideoDECODE_DecodeFrameAsync`
     - Decoder functions, required if the implementation implements any decoder.
   * - | :cpp:func:`MFXVideoVPP_Init`
       | :cpp:func:`MFXVideoVPP_Close`
       | :cpp:func:`MFXVideoVPP_Query`
       | :cpp:func:`MFXVideoVPP_RunFrameVPPAsync`
     - VPP functions, required if the implementation implements any VPP filter.
   * - :cpp:func:`MFXVideoCORE_SyncOperation`
     - Function required for synchronization of asynchronous operations.
   * - :cpp:struct:`mfxImplDescription`
     - Decoder, encoder, or VPP capabilities information, required if the implementation implements a decoder, encoder, or VPP filter. Structure lists mandatory capabilities of the implementation.

Any other functions or extension buffers are optional for the implementation.

.. note:: Mandatory functions must have an implementation and must not return the
          :cpp:enumerator:`MFX_ERR_NOT_IMPLEMENTED` status.
