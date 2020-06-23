Example 1 shows the pseudo code of the decoding procedure. The following describes a few key points:

- The application can use the :cpp:func:`MFXVideoDECODE_DecodeHeader` function to retrieve decoding initialization parameters
  from the bitstream. This step is optional if such parameters are retrievable from other sources such as an
  audio/video splitter.
- The application uses the :cpp:func:`MFXVideoDECODE_QueryIOSurf` function to obtain the number of working frame surfaces required
  to reorder output frames. This call is optional and required when application uses external allocation.
- The application calls the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function for a decoding operation, with the bitstream buffer (bits), and an unlocked working frame surface (work) as input parameters. 

.. attention:: Starting from API version 2.0 application can provide NULL as working frame surface what leads to internal memory allocation. 

If decoding output is not available, the function returns a status code requesting additional bitstream input or working frame surfaces as follows:

  - :cpp:enumerator:`MFX_ERR_MORE_DATA`: The function needs additional bitstream input. The existing buffer contains less than a frame worth of bitstream data.
  - :cpp:enumerator:`MFX_ERR_MORE_SURFACE`: The function needs one more frame surface to produce any output.
  - :cpp:enumerator:`MFX_ERR_REALLOC_SURFACE`: Dynamic resolution change case - the function needs bigger working frame surface (work).

- Upon successful decoding, the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function returns :cpp:enumerator:`MFX_ERR_NONE`. However, the decoded frame data
  (identified by the disp pointer) is not yet available because the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function is asynchronous.
  The application has to use the :cpp:func:`MFXVideoCORE_SyncOperation` or :cpp:struct:`mfxFrameSurfaceInterface` interface to synchronize the decoding operation before retrieving
  the decoded frame data.
- At the end of the bitstream, the application continuously calls the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function with a NULL
  bitstream pointer to drain any remaining frames cached within the SDK decoder, until the function returns :cpp:enumerator:`MFX_ERR_MORE_DATA`.

Example 2 below demonstrates simplified decoding procedure.

.. _simplified-decoding-procedure:

Starting for API version 2.0 new decoding approach has been introduced. For simple use cases, when user just wants to decode some elementary stream and 
don't want to set additional parameters, the simplified procedure of Decoder's initialization has been proposed. For such situations it is possible to skip 
explicit stages of stream's header decodeng and Decoder's initialization and perform it implicitly during decoding of first frame. 
This change also requires additional field in mfxBitstream object to indicate codec type. In that mode decoder allocates mfxFrameSurface1 internally, 
so users should set input surface to zero.   

Example 1: Decoding Pseudo Code

.. code-block:: c++

   MFXVideoDECODE_DecodeHeader(session, bitstream, &init_param);
   MFXVideoDECODE_QueryIOSurf(session, &init_param, &request);
   allocate_pool_of_frame_surfaces(request.NumFrameSuggested);
   MFXVideoDECODE_Init(session, &init_param);
   sts=MFX_ERR_MORE_DATA;
   for (;;) {
      if (sts==MFX_ERR_MORE_DATA && !end_of_stream())
         append_more_bitstream(bitstream);
      find_unlocked_surface_from_the_pool(&work);
      bits=(end_of_stream())?NULL:bitstream;
      sts=MFXVideoDECODE_DecodeFrameAsync(session,bits,work,&disp,&syncp);
      if (sts==MFX_ERR_MORE_SURFACE) continue;
      if (end_of_bitstream() && sts==MFX_ERR_MORE_DATA) break;
      if (sts==MFX_ERR_REALLOC_SURFACE) {
         MFXVideoDECODE_GetVideoParam(session, &param);
         realloc_surface(work, param.mfx.FrameInfo);
         continue;
      }
      // skipped other error handling
      if (sts==MFX_ERR_NONE) {
         MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
         do_something_with_decoded_frame(disp);
      }
   }
   MFXVideoDECODE_Close();
   free_pool_of_frame_surfaces();

Example 2: Simplified decoding procedure

.. code-block:: c++

   sts=MFX_ERR_MORE_DATA;
   for (;;) {
      if (sts==MFX_ERR_MORE_DATA && !end_of_stream())
         append_more_bitstream(bitstream);
      bits=(end_of_stream())?NULL:bitstream;
      sts=MFXVideoDECODE_DecodeFrameAsync(session,bits,NULL,&disp,&syncp);
      if (sts==MFX_ERR_MORE_SURFACE) continue;
      if (end_of_bitstream() && sts==MFX_ERR_MORE_DATA) break;
      // skipped other error handling
      if (sts==MFX_ERR_NONE) {
         MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
         do_something_with_decoded_frame(disp);
         release_surface(disp);
      }
   }

Bitstream Repositioning
~~~~~~~~~~~~~~~~~~~~~~~

The application can use the following procedure for bitstream reposition during decoding:

- Use the :cpp:func:`MFXVideoDECODE_Reset` function to reset the SDK decoder.
- Optionally, if the application maintains a sequence header that decodes correctly the bitstream at the new position,
  the application may insert the sequence header to the bitstream buffer.
- Append the bitstream from the new location to the bitstream buffer.
- Resume the decoding procedure. If the sequence header is not inserted in the above steps, the SDK decoder searches
  for a new sequence header before starting decoding.
  
Broken Streams Handling
~~~~~~~~~~~~~~~~~~~~~~~

Robustness and capability to handle broken input stream is important part of the decoder.

First of all, start code prefix (ITU-T H.264 3.148 and ITU-T H.265 3.142) is used to separate NAL units.
Then all syntax elements in bitstream are parsed and verified. If any of elements violate the specification then input
bitstream is considered as invalid and decoder tries to re-sync (find next start code). The further decoder’s behavior
is depend on which syntax element is broken:

* SPS header – return :cpp:enumerator:`MFX_ERR_INCOMPATIBLE_VIDEO_PARAM` (HEVC decoder only, AVC decoder uses last valid)
* PPS header – re-sync, use last valid PPS for decoding
* Slice header – skip this slice, re-sync
* Slice data - Corruption flags are set on output surface

.. note:: Some requirements are relaxed because there are a lot of streams which violate the letter of standard
   but can be decoded without errors.

* Many streams have IDR frames with frame_num != 0 while specification says that “If the current picture is an IDR picture,
  frame_num shall be equal to 0.” (ITU-T H.265 7.4.3)
* VUI is also validated, but errors doesn’t invalidate the whole SPS, decoder either doesn’t use corrupted VUI (AVC)
  or resets incorrect values to default (HEVC).

The corruption at reference frame is spread over all inter-coded pictures which use this reference for prediction. To cope
with this problem you either have to periodically insert I-frames (intra-coded) or use ‘intra refresh’ technique. The latter
allows to recover corruptions within a pre-defined time interval. The main point of ‘intra refresh’ is to insert cyclic
intra-coded pattern (usually row) of macroblocks into the inter-coded pictures, restricting motion vectors accordingly.
Intra-refresh is often used in combination with Recovery point SEI, where recovery_frame_cnt is derived from intra-refresh
interval. Recovery point SEI message is well described at ITU-T H.264 D.2.7 and ITU-T H.265 D.2.8. This message can be used
by the decoder to understand from which picture all subsequent (in display order) pictures contain no errors, if we start
decoding from AU associated with this SEI message. In opposite to IDR, recovery point message doesn’t mark reference pictures
as "unused for reference".

Besides validation of syntax elements and theirs constrains, decoder also uses various hints to handle broken streams.

* If there are no valid slices for current frame – the whole frame is skipped.
* The slices which violate slice segment header semantics (ITU-T H.265 7.4.7.1) are skipped. Only
  slice_temporal_mvp_enabled_flag is checked for now.
* Since LTR (Long Term Reference) stays at DPB until it will be explicitly cleared by IDR or MMCO, the incorrect
  LTR could cause long standing visual artifacts. AVC decoder uses the following approaches to care about this:

  * When we have DPB overflow in case incorrect MMCO command which marks reference picture as LT, we rollback this operation
  * An IDR frame with frame_num != 0 can’t be LTR

* If decoder detects frame gapping, it inserts ‘fake’ (marked as non-existing) frames, updates FrameNumWrap
  (ITU-T H.264 8.2.4.1) for reference frames and applies Sliding Window (ITU-T H.264 8.2.5.3) marking process.
  ‘Fake’ frames are marked as reference, but since they are marked as non-existing they are not really used for inter-prediction.

VP8 Specific Details
~~~~~~~~~~~~~~~~~~~~

Unlike other supported by SDK decoders, VP8 can accept only complete frame as input and application should provide it accompanied by
:cpp:enumerator:`MFX_BITSTREAM_COMPLETE_FRAME` flag. This is the single specific difference.

JPEG
~~~~

The application can use the same decoding procedures for JPEG/motion JPEG decoding, as illustrated in pseudo code below:

.. code-block:: c++

   // optional; retrieve initialization parameters
   MFXVideoDECODE_DecodeHeader(...);
   // decoder initialization
   MFXVideoDECODE_Init(...);
   // single frame/picture decoding
   MFXVideoDECODE_DecodeFrameAsync(...);
   MFXVideoCORE_SyncOperation(...);
   // optional; retrieve meta-data
   MFXVideoDECODE_GetUserData(...);
   // close
   MFXVideoDECODE_Close(...);


**DECODE** supports JPEG baseline profile decoding as follows:

- DCT-based process
- Source image: 8-bit samples within each component
- Sequential
- Huffman coding: 2 AC and 2 DC tables
- 3 loadable quantization matrixes
- Interleaved and non-interleaved scans
- Single and multiple scans

   - chroma subsampling ratios:
   - Chroma 4:0:0 (grey image)
   - Chroma 4:1:1
   - Chroma 4:2:0
   - Chroma horizontal 4:2:2
   - Chroma vertical 4:2:2
   - Chroma 4:4:4

- 3 channels images

The :cpp:func:`MFXVideoDECODE_Query` function will return :cpp:enumerator:`MFX_ERR_UNSUPPORTED` if the input bitstream contains unsupported features.

For still picture JPEG decoding, the input can be any JPEG bitstreams that conform to the ITU-T* Recommendation T.81, with an EXIF* or JFIF* header.
For motion JPEG decoding, the input can be any JPEG bitstreams that conform to the ITU-T Recommendation T.81.

Unlike other SDK decoders, JPEG one supports three different output color formats - NV12, YUY2 and RGB32. This support sometimes requires internal
color conversion and more complicated initialization. The color format of input bitstream is described by JPEGChromaFormat and JPEGColorFormat
fields in :cpp:struct:`mfxInfoMFX` structure. The :cpp:func:`MFXVideoDECODE_DecodeHeader` function usually fills them in. But if JPEG bitstream does not contains color format
information, application should provide it. Output color format is described by general SDK parameters - FourCC and ChromaFormat fields in
:cpp:struct:`mfxFrameInfo` structure.

Motion JPEG supports interlaced content by compressing each field (a half-height frame) individually. This behavior is incompatible with the rest
SDK transcoding pipeline, where SDK requires that fields be in odd and even lines of the same frame surface.) The decoding procedure is modified as
follows:

- The application calls the :cpp:func:`MFXVideoDECODE_DecodeHeader` function, with the first field JPEG bitstream, to retrieve initialization parameters.
- The application initializes the SDK JPEG decoder with the following settings:

  - Set the PicStruct field of the :cpp:struct:`mfxVideoParam` structure with proper interlaced type, :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF` or
    :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`, from motion JPEG header.
  - Double the Height field of the :cpp:struct:`mfxVideoParam` structure as the value returned by the :cpp:func:`MFXVideoDECODE_DecodeHeader` function describes only the
    first field. The actual frame surface should contain both fields.

- During decoding, application sends both fields for decoding together in the same :cpp:struct:`mfxBitstream`. Application also should set DataFlag
  in :cpp:struct:`mfxBitstream` structure to :cpp:enumerator:`MFX_BITSTREAM_COMPLETE_FRAME`. The SDK decodes both fields and combines them into odd and
  even lines as in the SDK convention.

SDK supports JPEG picture rotation, in multiple of 90 degrees, as part of the decoding operation. By default, the :cpp:func:`MFXVideoDECODE_DecodeHeader`
function returns the Rotation parameter so that after rotation, the pixel at the first row and first column is at the top left.
The application can overwrite the default rotation before calling :cpp:func:`MFXVideoDECODE_Init`.

The application may specify Huffman and quantization tables during decoder initialization by attaching :cpp:struct:`mfxExtJPEGQuantTables`
and :cpp:struct:`mfxExtJPEGHuffmanTables` buffers to :cpp:struct:`mfxVideoParam` structure. In this case, decoder ignores tables from bitstream
and uses specified by application. The application can also retrieve these tables by attaching the same buffers to mfxVideoParam and calling
:cpp:func:`MFXVideoDECODE_GetVideoParam` or :cpp:func:`MFXVideoDECODE_DecodeHeader` functions.

Multi-view video decoding
~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK MVC decoder operates on complete MVC streams that contain all view/temporal configurations. The application can configure the SDK decoder to generate a subset at the decoding output. 
To do this, the application needs to understand the stream structure and based on such information configure the SDK decoder for target views.

The decoder initialization procedure is as follows:

* The application calls the MFXVideoDECODE_DecodeHeader function to obtain the stream structural information. This is actually done in two sub-steps:

  * The application calls the MFXVideoDECODE_DecodeHeader function with the mfxExtMVCSeqDesc structure attached to the mfxVideoParam structure. 
     Do not allocate memory for the arrays in the mfxExtMVCSeqDesc structure just yet. Set the View, ViewId and OP pointers to NULL and set NumViewAlloc, 
     NumViewIdAlloc and NumOPAlloc to zero. The function parses the bitstream and returns MFX_ERR_NOT_ENOUGH_BUFFER with the correct values NumView, NumViewId and NumOP. 
     This step can be skipped if the application is able to obtain the NumView, NumViewId and NumOP values from other sources.
  * The application allocates memory for the View, ViewId and OP arrays and calls the MFXVideoDECODE_DecodeHeader function again. 
     The function returns the MVC structural information in the allocated arrays.
* The application fills the mfxExtMvcTargetViews structure to choose the target views, based on information described in the mfxExtMVCSeqDesc structure.
* The application initializes the SDK decoder using the MFXVideoDECODE_Init function. The application must attach both the mfxExtMVCSeqDesc structure and 
   the mfxExtMvcTargetViews structure to the mfxVideoParam structure.

In the above steps, do not modify the values of the mfxExtMVCSeqDesc structure after the MFXVideoDECODE_DecodeHeader function, as 
the SDK decoder uses the values in the structure for internal memory allocation. Once the application configures the SDK decoder, the rest decoding procedure remains unchanged. 
As illustrated in the pseudo code below, the application calls the MFXVideoDECODE_DecodeFrameAsync function multiple times to obtain all target views of the current frame
picture, one target view at a time. The target view is identified by the FrameID field of the mfxFrameInfo structure. 

.. code-block:: c++

    mfxExtBuffer *eb[2];
    mfxExtMVCSeqDesc  seq_desc;
    mfxVideoParam init_param;

    init_param.ExtParam=&eb;
    init_param.NumExtParam=1;
    eb[0]=&seq_desc;
    MFXVideoDECODE_DecodeHeader(session, bitstream, &init_param);

    /* select views to decode */
    mfxExtMvcTargetViews tv;
    init_param.NumExtParam=2;
    eb[1]=&tv;

    /* initialize decoder */
    MFXVideoDECODE_Init(session, &init_param);

    /* perform decoding */
    for (;;) {
        MFXVideoDECODE_DecodeFrameAsync(session, bits, work, &disp,
                                        &syncp);
        MFXVideoCORE_SyncOperation(session, &syncp, INFINITE);
    }

    /* close decoder */
    MFXVideoDECODE_Close();

