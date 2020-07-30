.. _decoding-proc:

===================
Decoding Procedures
===================

The following pseudo code shows the decoding procedure:

.. literalinclude:: snippets/prg_decoding.c
   :language: c++
   :start-after: /*beg1*/
   :end-before: /*end1*/
   :lineno-start: 1

Note the following key points about the example:

- The application can use the :cpp:func:`MFXVideoDECODE_DecodeHeader` function
  to retrieve decoding initialization parameters from the bitstream. This step
  is optional if the data is retrievable from other sources such as an
  audio/video splitter.
- The application can use the :cpp:func:`MFXVideoDECODE_QueryIOSurf` function to
  obtain the number of working frame surfaces required to reorder output frames.
  This step is required if the application is responsible for memory allocation.
  Use of this function is not required if the SDK is responsible for memory
  allocation.
- The application calls the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function
  for a decoding operation with the bitstream buffer (bits) and an unlocked
  working frame surface (work) as input parameters.

  .. attention:: Starting with API version 2.0, the application can provide NULL
                 as the working frame surface what leads to internal memory
                 allocation.

- If decoding output is not available, the function returns a status code
  requesting additional bitstream input or working frame surfaces as follows:

  - :cpp:enumerator:`mfxStatus::MFX_ERR_MORE_DATA`: The function needs additional
    bitstream input. The existing buffer contains less than a frame's worth of
    bitstream data.
  - :cpp:enumerator:`mfxStatus::MFX_ERR_MORE_SURFACE`: The function needs one
    more frame surface to produce any output.
  - :cpp:enumerator:`mfxStatus::MFX_ERR_REALLOC_SURFACE`: Dynamic resolution
    change case - the function needs bigger working frame surface (work).

- Upon successful decoding, the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync`
  function returns :cpp:enumerator:`mfxStatus::MFX_ERR_NONE`. However, the
  decoded frame data (identified by the surface_out pointer) is not yet available
  because the :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function is asynchronous.
  The application must use the :cpp:func:`MFXVideoCORE_SyncOperation` or
  :cpp:struct:`mfxFrameSurfaceInterface` interface to synchronize the decoding
  operation before retrieving the decoded frame data.
- At the end of the bitstream, the application continuously calls the
  :cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function with a NULL bitstream
  pointer to drain any remaining frames cached within the SDK decoder, until the
  function returns :cpp:enumerator:`mfxStatus::MFX_ERR_MORE_DATA`.

The following example shows the simplified decoding procedure:

.. literalinclude:: snippets/prg_decoding.c
   :language: c++
   :start-after: /*beg2*/
   :end-before: /*end2*/
   :lineno-start: 1

.. _simplified-decoding-procedure:

API version 2.0 introduces a new decoding approach. For simple use cases, when
the user wants to decode a stream and doesn't want to set additional
parameters, the simplified procedure for the decoder's initialization has been
proposed. For such situations it is possible to skip explicit stages of a
stream's header decoding and the decoder's initialization and instead to perform
it implicitly during decoding of the first frame. This change also requires
additional field in the :cpp:struct:`mfxBitstream` object to indicate codec type.
In that mode the decoder allocates :cpp:struct:`mfxFrameSurface1` internally, so
users should set input surface to zero.

-----------------------
Bitstream Repositioning
-----------------------

The application can use the following procedure for bitstream reposition during
decoding:

#. Use the :cpp:func:`MFXVideoDECODE_Reset` function to reset the SDK decoder.
#. Optional: If the application maintains a sequence header that correctly
   decodes the bitstream at the new position, the application may insert the
   sequence header to the bitstream buffer.
#. Append the bitstream from the new location to the bitstream buffer.
#. Resume the decoding procedure. If the sequence header is not inserted in the
   previous steps, the SDK decoder searches for a new sequence header before
   starting decoding.

-----------------------
Broken Streams Handling
-----------------------

Robustness and the capability to handle broken input stream is an important part
of the decoder.

First, the start code prefix (ITU-T\* H.264 3.148 and ITU-T H.265 3.142) is
used to separate NAL units. Then all syntax elements in the bitstream are parsed
and verified. If any of the elements violate the specification, the input
bitstream is considered invalid and the decoder tries to re-sync (find the next
start code). Subsequent decoder behavior is dependent on which syntax element is
broken:

* SPS header – return :cpp:enumerator:`mfxStatus::MFX_ERR_INCOMPATIBLE_VIDEO_PARAM`
  (HEVC decoder only, AVC decoder uses last valid)
* PPS header – re-sync, use last valid PPS for decoding
* Slice header – skip this slice, re-sync
* Slice data - Corruption flags are set on output surface

.. note:: Some requirements are relaxed because there are many streams which
          violate the strict standard but can be decoded without errors.

* Many streams have IDR frames with frame_num != 0 while the specification says
  that “If the current picture is an IDR picture, frame_num shall be equal to 0”
  (ITU-T H.265 7.4.3).
* VUI is also validated, but errors do not invalidate the whole SPS. The decoder
  either does not use the corrupted VUI (AVC) or resets incorrect values to
  default (HEVC).

Corruption at the reference frame is spread over all inter-coded pictures that
use the reference frame for prediction. To cope with this problem you must either
periodically insert I-frames (intra-coded) or use the ‘intra-refresh’ technique.
The 'intra refresh' technique allows the recovery from corruptions within a
predefined time interval. The main point of intra-refresh is to insert a cyclic
intra-coded pattern (usually a row) of macroblocks into the inter-coded pictures,
restricting motion vectors accordingly. Intra-refresh is often used in combination
with recovery point SEI, where the recovery_frame_cnt is derived from the
intra-refresh interval. The recovery point SEI message is well described at
ITU-T H.264 D.2.7 and ITU-T H.265 D.2.8. If decoding starts from AU associated
with this SEI message, then the message can be used by the decoder to determine
from which picture all subsequent pictures have no errors. In comparison to IDR,
the recovery point message does not mark reference pictures as 'unused for
reference'.

Besides validation of syntax elements and their constraints, the decoder also uses
various hints to handle broken streams:

* If there are no valid slices for the current frame, then the whole frame is skipped.
* The slices which violate slice segment header semantics (ITU-T H.265 7.4.7.1)
  are skipped. Only slice_temporal_mvp_enabled_flag is checked for now.
* Since LTR (Long Term Reference) stays at DPB until it is explicitly
  cleared by IDR or MMCO, the incorrect LTR could cause long standing visual
  artifacts. AVC decoder uses the following approaches to handle this:

  * When there is a DPB overflow in the case of an incorrect MMCO command that
    marks the reference picture as LT, the operation is rolled back.
  * An IDR frame with frame_num != 0 can’t be LTR.

* If the decoder detects frame gapping, it inserts ‘fake’ (marked as non-existing)
  frames, updates FrameNumWrap (ITU-T H.264 8.2.4.1) for reference frames, and
  applies the Sliding Window (ITU-T H.264 8.2.5.3) marking process. ‘Fake’ frames
  are marked as reference, but since they are marked as non-existing, they are
  not used for inter-prediction.

--------------------
VP8 Specific Details
--------------------

Unlike other supported by SDK decoders, VP8 can accept only a complete frame as
input. The application should provide the complete frame accompanied by the
:cpp:enumerator:`MFX_BITSTREAM_COMPLETE_FRAME` flag. This is the single specific
difference.

----
JPEG
----

The application can use the same decoding procedures for JPEG/motion JPEG decoding,
as shown in the pseudo code below:

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


:term:`DECODE` supports JPEG baseline profile decoding as follows:

- DCT-based process
- Source image: 8-bit samples within each component
- Sequential
- Huffman coding: 2 AC and 2 DC tables
- 3 loadable quantization matrices
- Interleaved and non-interleaved scans
- Single and multiple scans

   - Chroma sub-sampling ratios:

     - Chroma 4:0:0 (grey image)
     - Chroma 4:1:1
     - Chroma 4:2:0
     - Chroma horizontal 4:2:2
     - Chroma vertical 4:2:2
     - Chroma 4:4:4

- 3 channel images

The :cpp:func:`MFXVideoDECODE_Query` function will return
:cpp:enumerator:`mfxStatus::MFX_ERR_UNSUPPORTED` if the input bitstream contains
unsupported features.

For still picture JPEG decoding, the input can be any JPEG bitstreams that
conform to the ITU-T Recommendation T.81 with an EXIF or JFIF header. For
motion JPEG decoding, the input can be any JPEG bitstreams that conform to the
ITU-T Recommendation T.81.

Unlike other SDK decoders, JPEG decoding supports three different output color
formats: :term:`NV12`, :term:`YUY2`, and :term:`RGB32`. This support sometimes
requires internal color conversion and more complicated initialization. The color
format of the input bitstream is described by the
``JPEGChromaFormat`` and ``JPEGColorFormat`` fields in the :cpp:struct:`mfxInfoMFX`
structure. The :cpp:func:`MFXVideoDECODE_DecodeHeader` function usually fills
them in. If the JPEG bitstream does not contains color format information, the
application should provide it. Output color format is described by general SDK
parameters: the ``FourCC`` and ``ChromaFormat`` fields in the
:cpp:struct:`mfxFrameInfo` structure.

Motion JPEG supports interlaced content by compressing each field (a half-height
frame) individually. This behavior is incompatible with the rest of the SDK
transcoding pipeline, where the SDK requires fields to be in odd and even lines
of the same frame surface. The decoding procedure is modified as follows:

- The application calls the :cpp:func:`MFXVideoDECODE_DecodeHeader` function
  with the first field JPEG bitstream to retrieve initialization parameters.
- The application initializes the SDK JPEG decoder with the following settings:

  - The ``PicStruct`` field of the :cpp:struct:`mfxVideoParam` structure set to the
    correct interlaced type, :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF` or
    :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`, from the motion JPEG header.
  - Double the ``Height`` field in the :cpp:struct:`mfxVideoParam` structure as the
    value returned by the :cpp:func:`MFXVideoDECODE_DecodeHeader` function
    describes only the first field. The actual frame surface should contain both
    fields.

- During decoding, the application sends both fields for decoding in the
  same :cpp:struct:`mfxBitstream`. The application should also set ``DataFlag``
  in the :cpp:struct:`mfxBitstream` structure to
  :cpp:enumerator:`MFX_BITSTREAM_COMPLETE_FRAME`. The SDK decodes both fields
  and combines them into odd and even lines according to the SDK convention.

The SDK supports JPEG picture rotation, in multiple of 90 degrees, as part of the
decoding operation. By default, the :cpp:func:`MFXVideoDECODE_DecodeHeader`
function returns the Rotation parameter so that after rotation, the pixel at the
first row and first column is at the top left. The application can overwrite the
default rotation before calling :cpp:func:`MFXVideoDECODE_Init`.

The application may specify Huffman and quantization tables during decoder
initialization by attaching :cpp:struct:`mfxExtJPEGQuantTables` and
:cpp:struct:`mfxExtJPEGHuffmanTables` buffers to the :cpp:struct:`mfxVideoParam`
structure. In this case, the decoder ignores tables from bitstream and uses
the tables specified by the application. The application can also retrieve these
tables by attaching the same buffers to :cpp:struct:`mfxVideoParam` and calling
:cpp:func:`MFXVideoDECODE_GetVideoParam` or :cpp:func:`MFXVideoDECODE_DecodeHeader`
functions.

-------------------------
Multi-view Video Decoding
-------------------------

The SDK MVC decoder operates on complete MVC streams that contain all
view and temporal configurations. The application can configure the SDK decoder
to generate a subset at the decoding output. To do this, the application must
understand the stream structure and use the stream information to configure the
SDK decoder for target views.

The decoder initialization procedure is as follows:

#. The application calls the :cpp:func:`MFXVideoDECODE_DecodeHeader` function to
   obtain the stream structural information. This is done in two steps:

   #. The application calls the :cpp:func:`MFXVideoDECODE_DecodeHeader` function
      with the :cpp:struct:`mfxExtMVCSeqDesc` structure attached to the
      :cpp:struct:`mfxVideoParam` structure. At this point, do not allocate
      memory for the arrays in the :cpp:struct:`mfxExtMVCSeqDesc` structure. Set
      the ``View``, ``ViewId``, and ``OP`` pointers to NULL and set
      ``NumViewAlloc``, ``NumViewIdAlloc``, and ``NumOPAlloc`` to zero. The
      function parses the bitstream and returns
      :cpp:enumerator:`mfxStatus::MFX_ERR_NOT_ENOUGH_BUFFER` with the correct
      values for NumView, NumViewId, and NumOP. This step can be skipped if the
      application is able to obtain the NumView, NumViewId, and NumOP values from
      other sources.
   #. The application allocates memory for the View, ViewId, and OP arrays and
      calls the :cpp:func:`MFXVideoDECODE_DecodeHeader` function again. The
      function returns the MVC structural information in the allocated arrays.

#. The application fills the :cpp:struct:`mfxExtMVCTargetViews` structure to
   choose the target views, based on information described in the
   :cpp:struct:`mfxExtMVCSeqDesc` structure.
#. The application initializes the SDK decoder using the
   :cpp:func:`MFXVideoDECODE_Init` function. The application must attach both the
   :cpp:struct:`mfxExtMVCSeqDesc` structure and the :cpp:struct:`mfxExtMVCTargetViews`
   structure to the :cpp:struct:`mfxVideoParam` structure.

In the above steps, do not modify the values of the :cpp:struct:`mfxExtMVCSeqDesc`
structure after the :cpp:func:`MFXVideoDECODE_DecodeHeader` function, as the SDK
decoder uses the values in the structure for internal memory allocation. Once the
application configures the SDK decoder, the rest of the decoding procedure remains
unchanged. As shown in the pseudo code below, the application calls the
:cpp:func:`MFXVideoDECODE_DecodeFrameAsync` function multiple times to obtain all
target views of the current frame picture, one target view at a time. The target
view is identified by the ``FrameID`` field of the
:cpp:struct:`mfxFrameInfo` structure.

.. literalinclude:: snippets/prg_decoding.c
   :language: c++
   :start-after: /*beg3*/
   :end-before: /*end3*/
   :lineno-start: 1

