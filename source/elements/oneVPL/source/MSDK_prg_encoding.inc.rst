Encoding procedure
~~~~~~~~~~~~~~~~~~

There are two ways of  allocation and handling in SDK for shared memory: external and internal.

Example below shows the pseudo code of the encoding procedure with external memory  (legacy mode).

.. code-block:: c++

   MFXVideoENCODE_QueryIOSurf(session, &init_param, &request);
   allocate_pool_of_frame_surfaces(request.NumFrameSuggested);
   MFXVideoENCODE_Init(session, &init_param);
   sts=MFX_ERR_MORE_DATA;
   for (;;) {
      if (sts==MFX_ERR_MORE_DATA && !end_of_stream()) {
         find_unlocked_surface_from_the_pool(&surface);
         fill_content_for_encoding(surface);
      }
      surface2=end_of_stream()?NULL:surface;
      sts=MFXVideoENCODE_EncodeFrameAsync(session,NULL,surface2,bits,&syncp);
      if (end_of_stream() && sts==MFX_ERR_MORE_DATA) break;
      // Skipped other error handling
      if (sts==MFX_ERR_NONE) {
         MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
         do_something_with_encoded_bits(bits);
      }
   }
   MFXVideoENCODE_Close();
   free_pool_of_frame_surfaces();

The following describes a few key points:

- The application uses the MFXVideoENCODE_QueryIOSurf function to obtain the number of working frame surfaces
  required for reordering input frames.
- The application calls the MFXVideoENCODE_EncodeFrameAsync function for the encoding operation. The input frame
  must be in an unlocked frame surface from the frame surface pool. If the encoding output is not available,
  the function returns the status code MFX_ERR_MORE_DATA to request additional input frames.
- Upon successful encoding, the MFXVideoENCODE_EncodeFrameAsync function returns MFX_ERR_NONE. However,
  the encoded bitstream is not yet available because the MFXVideoENCODE_EncodeFrameAsync function is asynchronous.
  The application must use the MFXVideoCORE_SyncOperation function to synchronize the encoding operation
  before retrieving the encoded bitstream.
- At the end of the stream, the application continuously calls the MFXVideoENCODE_EncodeFrameAsync function
  with NULL surface pointer to drain any remaining bitstreams cached within the SDK encoder, until the function
  returns MFX_ERR_MORE_DATA.

.. note:: It is the application's responsibility to fill pixels outside of crop window when it is smaller than
   frame to be encoded. Especially in cases when crops are not aligned to minimum coding block size (16 for AVC,
   8 for HEVC and VP9).

Another approach is when SDK allocates memory for shared objects internally. 

.. code-block:: c++

   MFXVideoENCODE_Init(session, &init_param);
   sts=MFX_ERR_MORE_DATA;
   for (;;) {
      if (sts==MFX_ERR_MORE_DATA && !end_of_stream()) {
         MFXMemory_GetSurfaceForEncode(&surface);
         fill_content_for_encoding(surface);
      }
      surface2=end_of_stream()?NULL:surface;
      sts=MFXVideoENCODE_EncodeFrameAsync(session,NULL,surface2,bits,&syncp);
      if (surface2) surface->FrameInterface->(*Release)(surface2);
      if (end_of_stream() && sts==MFX_ERR_MORE_DATA) break;
      // Skipped other error handling
      if (sts==MFX_ERR_NONE) {
         MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
         do_something_with_encoded_bits(bits);
      }
   }
   MFXVideoENCODE_Close();

There are several key points which are different from legacy mode:

- The application doesn't need to call MFXVideoENCODE_QueryIOSurf function to obtain the number of working frame surfaces since allocation is done by SDK
- The application calls the MFXMemory_GetSurfaceForEncode function to get free surface for the following encode operation.
- The application needs to call the FrameInterface->(\*Release) function to decrement reference counter of the obtained surface after MFXVideoENCODE_EncodeFrameAsync call.


Configuration Change
~~~~~~~~~~~~~~~~~~~~

The application changes configuration during encoding by calling MFXVideoENCODE_Reset function. Depending on
difference in configuration parameters before and after change, the SDK encoder either continues current sequence
or starts a new one. If the SDK encoder starts a new sequence it completely resets internal state and begins a new
sequence with IDR frame.

The application controls encoder behavior during parameter change by attaching mfxExtEncoderResetOption to
mfxVideoParam structure during reset. By using this structure, the application instructs encoder to start or not
to start a new sequence after reset. In some cases request to continue current sequence cannot be satisfied and
encoder fails during reset. To avoid such cases the application may query reset outcome before actual reset
by calling MFXVideoENCODE_Query function with mfxExtEncoderResetOption attached to mfxVideoParam structure.

The application uses the following procedure to change encoding configurations:

- The application retrieves any cached frames in the SDK encoder by calling the MFXVideoENCODE_EncodeFrameAsync
  function with a NULL input frame pointer until the function returns MFX_ERR_MORE_DATA.

.. note:: The application must set the initial encoding configuration flag EndOfStream of the mfxExtCodingOption
   structure to OFF to avoid inserting an End of Stream (EOS) marker into the bitstream. An EOS marker causes
   the bitstream to terminate before encoding is complete.

- The application calls the MFXVideoENCODE_Reset function with the new configuration:

   - If the function successfully set the configuration, the application can continue encoding as usual.
   - If the new configuration requires a new memory allocation, the function returns MFX_ERR_INCOMPATIBLE_VIDEO_PARAM.
     The application must close the SDK encoder and reinitialize the encoding procedure with the new configuration.

External Bit Rate Control
~~~~~~~~~~~~~~~~~~~~~~~~~

The application can make encoder use external BRC instead of native one. In order to do that it should attach
to mfxVideoParam structure mfxExtCodingOption2 with ExtBRC = MFX_CODINGOPTION_ON and callback structure mfxExtBRC
during encoder initialization. Callbacks Init, Reset and Close will be invoked inside MFXVideoENCODE_Init,
MFXVideoENCODE_Reset and MFXVideoENCODE_Close correspondingly. Figure below illustrates asynchronous encoding flow
with external BRC (usage of GetFrameCtrl and Update):

.. image:: images/extbrc_async.png
   :alt: asynchronous encoding flow with external BRC

.. note:: **IntAsyncDepth** is the SDK max internal asynchronous encoding queue size;
   it is always less than or equal to mfxVideoParam::AsyncDepth.

External BRC Pseudo Code:

.. code-block:: c++

   #include "mfxvideo.h"
   #include "mfxbrc.h"

   typedef struct {
      mfxU32 EncodedOrder;
      mfxI32 QP;
      mfxU32 MaxSize;
      mfxU32 MinSize;
      mfxU16 Status;
      mfxU64 StartTime;
      // ... skipped
   } MyBrcFrame;

   typedef struct {
      MyBrcFrame* frame_queue;
      mfxU32 frame_queue_size;
      mfxU32 frame_queue_max_size;
      mfxI32 max_qp[3]; //I,P,B
      mfxI32 min_qp[3]; //I,P,B
      // ... skipped
   } MyBrcContext;

   mfxStatus MyBrcInit(mfxHDL pthis, mfxVideoParam* par) {
      MyBrcContext* ctx = (MyBrcContext*)pthis;
      mfxI32 QpBdOffset;
      mfxExtCodingOption2* co2;

      if (!pthis || !par)
         return MFX_ERR_NULL_PTR;

      if (!IsParametersSupported(par))
         return MFX_ERR_UNSUPPORTED;

      frame_queue_max_size = par->AsyncDepth;
      frame_queue = (MyBrcFrame*)malloc(sizeof(MyBrcFrame) * frame_queue_max_size);

      if (!frame_queue)
         return MFX_ERR_MEMORY_ALLOC;

      co2 = (mfxExtCodingOption2*)GetExtBuffer(par->ExtParam, par->NumExtParam, MFX_EXTBUFF_CODING_OPTION2);
      QpBdOffset = (par->BitDepthLuma > 8) : (6 * (par->BitDepthLuma - 8)) : 0;

      for (<X = I,P,B>) {
         ctx->max_qp[X] = (co2 && co2->MaxQPX) ? (co2->MaxQPX - QpBdOffset) : <Default>;
         ctx->min_qp[X] = (co2 && co2->MinQPX) ? (co2->MinQPX - QpBdOffset) : <Default>;
      }

      // skipped initialization of other other BRC parameters

      frame_queue_size = 0;

      return MFX_ERR_NONE;
   }

   mfxStatus MyBrcReset(mfxHDL pthis, mfxVideoParam* par) {
      MyBrcContext* ctx = (MyBrcContext*)pthis;

      if (!pthis || !par)
         return MFX_ERR_NULL_PTR;

      if (!IsParametersSupported(par))
         return MFX_ERR_UNSUPPORTED;

      if (!IsResetPossible(ctx, par))
         return MFX_ERR_INCOMPATIBLE_VIDEO_PARAM;

      // reset here BRC parameters if required

      return MFX_ERR_NONE;
   }

   mfxStatus MyBrcClose(mfxHDL pthis) {
      MyBrcContext* ctx = (MyBrcContext*)pthis;

      if (!pthis)
         return MFX_ERR_NULL_PTR;

      if (ctx->frame_queue) {
         free(ctx->frame_queue);
         ctx->frame_queue = NULL;
         ctx->frame_queue_max_size = 0;
         ctx->frame_queue_size = 0;
      }

      return MFX_ERR_NONE;
   }

   mfxStatus MyBrcGetFrameCtrl(mfxHDL pthis, mfxBRCFrameParam* par, mfxBRCFrameCtrl* ctrl) {
      MyBrcContext* ctx = (MyBrcContext*)pthis;
      MyBrcFrame* frame = NULL;
      mfxU32 cost;

      if (!pthis || !par || !ctrl)
         return MFX_ERR_NULL_PTR;

      if (par->NumRecode > 0)
         frame = GetFrame(ctx->frame_queue, ctx->frame_queue_size, par->EncodedOrder);
      else if (ctx->frame_queue_size < ctx->frame_queue_max_size)
         frame = ctx->frame_queue[ctx->frame_queue_size++];

      if (!frame)
         return MFX_ERR_UNDEFINED_BEHAVIOR;

      if (par->NumRecode == 0) {
         frame->EncodedOrder = par->EncodedOrder;
         cost = GetFrameCost(par->FrameType, par->PyramidLayer);
         frame->MinSize = GetMinSize(ctx, cost);
         frame->MaxSize = GetMaxSize(ctx, cost);
         frame->QP = GetInitQP(ctx, frame->MinSize, frame->MaxSize, cost); // from QP/size stat
         frame->StartTime = GetTime();
      }

      ctrl->QpY = frame->QP;

      return MFX_ERR_NONE;
   }

   mfxStatus MyBrcUpdate(mfxHDL pthis, mfxBRCFrameParam* par, mfxBRCFrameCtrl* ctrl, mfxBRCFrameStatus* status) {
      MyBrcContext* ctx = (MyBrcContext*)pthis;
      MyBrcFrame* frame = NULL;
      bool panic = false;

      if (!pthis || !par || !ctrl || !status)
         return MFX_ERR_NULL_PTR;

      frame = GetFrame(ctx->frame_queue, ctx->frame_queue_size, par->EncodedOrder);
      if (!frame)
         return MFX_ERR_UNDEFINED_BEHAVIOR;

      // update QP/size stat here

      if (   frame->Status == MFX_BRC_PANIC_BIG_FRAME
        || frame->Status == MFX_BRC_PANIC_SMALL_FRAME_FRAME)
         panic = true;

      if (panic || (par->CodedFrameSize >= frame->MinSize && par->CodedFrameSize <= frame->MaxSize)) {
         UpdateBRCState(par->CodedFrameSize, ctx);
         RemoveFromQueue(ctx->frame_queue, ctx->frame_queue_size, frame);
         ctx->frame_queue_size--;
         status->BRCStatus = MFX_BRC_OK;

         // Here update Min/MaxSize for all queued frames

         return MFX_ERR_NONE;
      }

      panic = ((GetTime() - frame->StartTime) >= GetMaxFrameEncodingTime(ctx));

      if (par->CodedFrameSize > frame->MaxSize) {
         if (panic || (frame->QP >= ctx->max_qp[X])) {
            frame->Status = MFX_BRC_PANIC_BIG_FRAME;
         } else {
            frame->Status = MFX_BRC_BIG_FRAME;
            frame->QP = <increase QP>;
         }
      }

      if (par->CodedFrameSize < frame->MinSize) {
         if (panic || (frame->QP <= ctx->min_qp[X])) {
            frame->Status = MFX_BRC_PANIC_SMALL_FRAME;
            status->MinFrameSize = frame->MinSize;
         } else {
            frame->Status = MFX_BRC_SMALL_FRAME;
            frame->QP = <decrease QP>;
         }
      }

      status->BRCStatus = frame->Status;

      return MFX_ERR_NONE;
   }

   //initialize encoder
   MyBrcContext brc_ctx;
   mfxExtBRC ext_brc;
   mfxExtCodingOption2 co2;
   mfxExtBuffer* ext_buf[2] = {&co2.Header, &ext_brc.Header};

   memset(&brc_ctx, 0, sizeof(MyBrcContext));
   memset(&ext_brc, 0, sizeof(mfxExtBRC));
   memset(&co2, 0, sizeof(mfxExtCodingOption2));

   vpar.ExtParam = ext_buf;
   vpar.NumExtParam = sizeof(ext_buf) / sizeof(ext_buf[0]);

   co2.Header.BufferId = MFX_EXTBUFF_CODING_OPTION2;
   co2.Header.BufferSz = sizeof(mfxExtCodingOption2);
   co2.ExtBRC = MFX_CODINGOPTION_ON;

   ext_brc.Header.BufferId = MFX_EXTBUFF_BRC;
   ext_brc.Header.BufferSz = sizeof(mfxExtBRC);
   ext_brc.pthis           = &brc_ctx;
   ext_brc.Init            = MyBrcInit;
   ext_brc.Reset           = MyBrcReset;
   ext_brc.Close           = MyBrcClose;
   ext_brc.GetFrameCtrl    = MyBrcGetFrameCtrl;
   ext_brc.Update          = MyBrcUpdate;

   status = MFXVideoENCODE_Query(session, &vpar, &vpar);
   if (status == MFX_ERR_UNSUPPOERTED || co2.ExtBRC != MFX_CODINGOPTION_ON)
      // unsupported case
   else
      status = MFXVideoENCODE_Init(session, &vpar);

JPEG
~~~~

The application can use the same encoding procedures for JPEG/motion JPEG encoding, as illustrated by the pseudo code:

.. code-block:: c++

   // encoder initialization
   MFXVideoENCODE_Init (...);
   // single frame/picture encoding
   MFXVideoENCODE_EncodeFrameAsync (...);
   MFXVideoCORE_SyncOperation(...);
   // close down
   MFXVideoENCODE_Close(...);

**ENCODE** supports JPEG baseline profile encoding as follows:

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

The application may specify Huffman and quantization tables during encoder initialization by attaching :cpp:struct:`mfxExtJPEGQuantTables` and
:cpp:struct:`mfxExtJPEGHuffmanTables` buffers to :cpp:struct:`mfxVideoParam` structure. If the application does not define tables then the SDK
encoder uses tables recommended in ITU-T* Recommendation T.81. If the application does not define quantization table it has to specify Quality
parameter in :cpp:struct:`mfxInfoMFX` structure. In this case, the SDK encoder scales default quantization table according to specified Quality
parameter.

The application should properly configured chroma sampling format and color format. FourCC and ChromaFormat fields in :cpp:struct:`mfxFrameInfo`
structure are used for this. For example, to encode 4:2:2 vertically sampled YCbCr picture, the application should set FourCC to
:cpp:enumerator:`MFX_FOURCC_YUY2` and ChromaFormat to :cpp:enumerator:`MFX_CHROMAFORMAT_YUV422V`. To encode 4:4:4 sampled RGB picture, the application
should set FourCC to :cpp:enumerator:`MFX_FOURCC_RGB4` and ChromaFormat to :cpp:enumerator:`MFX_CHROMAFORMAT_YUV444`.

The SDK encoder supports different sets of chroma sampling and color formats on different platforms. The application has to call
:cpp:func:`MFXVideoENCODE_Query` function to check if required color format is supported on given platform and then initialize encoder with
proper values of FourCC and ChromaFormat in :cpp:struct:`mfxFrameInfo` structure.

The application should not define number of scans and number of components. They are derived by the SDK encoder from Interleaved flag in
:cpp:struct:`mfxInfoMFX` structure and from chroma type. If interleaved coding is specified then one scan is encoded that contains all image
components. Otherwise, number of scans is equal to number of components. The SDK encoder uses next component IDs - “1” for luma (Y),
“2” for chroma Cb (U) and “3” for chroma Cr (V).

The application should allocate big enough buffer to hold encoded picture. Roughly, its upper limit may be calculated using next equation:

.. code-block:: c++

   BufferSizeInKB = 4 + (Width * Height * BytesPerPx + 1023) / 1024;

where Width and Height are weight and height of the picture in pixel, BytesPerPx is number of byte for one pixel. It equals to 1 for monochrome
picture, 1.5 for NV12 and YV12 color formats, 2 for YUY2 color format, and 3 for RGB32 color format (alpha channel is not encoded).

Multi-view video encoding
~~~~~~~~~~~~~~~~~~~~~~~~~

Similar to the decoding and video processing initialization procedures, the application attaches the mfxExtMVCSeqDesc structure to the mfxVideoParam structure for encoding 
initialization. The mfxExtMVCSeqDesc structure configures the SDK MVC encoder to work in three modes:

- Default dependency mode: the application specifies NumView` and all other fields zero. The SDK encoder creates a single operation point with all views 
  (view identifier 0 : NumView-1) as target views. The first view (view identifier 0) is the base view. Other views depend on the base view.
  
- Explicit dependency mode: the application specifies NumView and the View dependency array, and sets all other fields to zero. The SDK encoder creates a single operation point
  with all views (view identifier View[0 : NumView-1].ViewId) as target views. The first view (view identifier View[0].ViewId) is the base view. 
  The view dependencies follow the View dependency structures.
  
- Complete mode: the application fully specifies the views and their dependencies. The SDK encoder generates a bitstream with corresponding stream structures.

The SDK MVC encoder does not support importing sequence and picture headers via the mfxExtCodingOptionSPSPPS structure, or configuring reference frame list via the mfxExtRefListCtrl structure.

During encoding, the SDK encoding function MFXVideoENCODE_EncodeFrameAsync accumulates input frames until encoding of a picture is possible. 
The function returns MFX_ERR_MORE_DATA for more data at input or MFX_ERR_NONE if having successfully accumulated enough data for encoding of a picture. 
The generated bitstream contains the complete picture (multiple views).
The application can change this behavior and instruct encoder to output each view in a separate bitstream buffer. 
To do so the application has to turn on the ViewOutput flag in the mfxExtCodingOption structure. In this case, encoder returns MFX_ERR_MORE_BITSTREAM 
if it needs more bitstream buffers at output and MFX_ERR_NONE when processing of picture (multiple views) has been finished. 
It is recommended that the application provides a new input frame each time the SDK encoder requests new bitstream buffer.
The application must submit views data for encoding in the order they are described in the mfxExtMVCSeqDesc structure. 
Particular view data can be submitted for encoding only when all views that it depends upon have already been submitted.

The following pseudo code shows the encoding procedure pseudo code.

.. code-block:: c++

    mfxExtBuffer *eb;
    mfxExtMVCSeqDesc  seq_desc;
    mfxVideoParam init_param;

    init_param.ExtParam=&eb;
    init_param.NumExtParam=1;
    eb=&seq_desc;

    /* init encoder */
    MFXVideoENCODE_Init(session, &init_param);

    /* perform encoding */
    for (;;) {
        MFXVideoENCODE_EncodeFrameAsync(session, NULL, surface2, bits,
                                        &syncp);
        MFXVideoCORE_SyncOperation(session,syncp,INFINITE);
    }

    /* close encoder */
    MFXVideoENCODE_Close();
    