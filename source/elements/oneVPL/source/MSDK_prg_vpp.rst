Example below shows the pseudo code of the video processing procedure.

.. code-block:: c++

   MFXVideoVPP_QueryIOSurf(session, &init_param, response);
   allocate_pool_of_surfaces(in_pool, response[0].NumFrameSuggested);
   allocate_pool_of_surfaces(out_pool, response[1].NumFrameSuggested);
   MFXVideoVPP_Init(session, &init_param);
   in=find_unlocked_surface_and_fill_content(in_pool);
   out=find_unlocked_surface_from_the_pool(out_pool);
   for (;;) {
      sts=MFXVideoVPP_RunFrameVPPAsync(session,in,out,aux,&syncp);
      if (sts==MFX_ERR_MORE_SURFACE || sts==MFX_ERR_NONE) {
         MFXVideoCore_SyncOperation(session,syncp,INFINITE);
         process_output_frame(out);
         out=find_unlocked_surface_from_the_pool(out_pool);
      }
      if (sts==MFX_ERR_MORE_DATA && in==NULL)
         break;
      if (sts==MFX_ERR_NONE || sts==MFX_ERR_MORE_DATA) {
         in=find_unlocked_surface(in_pool);
         fill_content_for_video_processing(in);
         if (end_of_input_sequence())
            in=NULL;
      }
   }
   MFXVideoVPP_Close(session);
   free_pool_of_surfaces(in_pool);
   free_pool_of_surfaces(out_pool);

The following describes a few key points:

- The application uses the MFXVideoVPP_QueryIOSurf function to obtain the number of frame surfaces needed for input
  and output. The application must allocate two frame surface pools, one for the input and the other for the output.
- The video processing function MFXVideoVPP_RunFrameVPPAsync is asynchronous. The application must synchronize to make
  the output result ready, through the MFXVideoCORE_SyncOperation function.
- The body of the video processing procedures covers three scenarios as follows:
- If the number of frames consumed at input is equal to the number of frames generated at output, **VPP** returns
  MFX_ERR_NONE when an output is ready. The application must process the output frame after synchronization,
  as the MFXVideoVPP_RunFrameVPPAsync function is asynchronous. At the end of a sequence, the application must
  provide a NULL input to drain any remaining frames.
- If the number of frames consumed at input is more than the number of frames generated at output, **VPP** returns
  MFX_ERR_MORE_DATA for additional input until an output is ready. When the output is ready, **VPP** returns MFX_ERR_NONE.
  The application must process the output frame after synchronization and provide a NULL input at the end of sequence to drain any remaining frames.
- If the number of frames consumed at input is less than the number of frames generated at output, **VPP** returns
  either MFX_ERR_MORE_SURFACE (when more than one output is ready), or MFX_ERR_NONE (when one output is ready
  and **VPP** expects new input). In both cases, the application must process the output frame after synchronization
  and provide a NULL input at the end of sequence to drain any remaining frames.

Configuration
~~~~~~~~~~~~~

The SDK configures the video processing pipeline operation based on the difference between the input and output
formats, specified in the mfxVideoParam structure. A few examples follow:

- When the input color format is YUY2 and the output color format is NV12, the SDK enables color conversion from YUY2 to NV12.
- When the input is interleaved and the output is progressive, the SDK enables de-interlacing.
- When the input is single field and the output is interlaced or progressive, the SDK enables field weaving,
  optionally with deinterlacing.
- When the input is interlaced and the output is single field, the SDK enables field splitting.

In addition to specifying the input and output formats, the application can provide hints to fine-tune the video processing
pipeline operation. The application can disable filters in pipeline by using mfxExtVPPDoNotUse structure; enable them
by using mfxExtVPPDoUse structure and configure them by using dedicated configuration structures. See Table 4 for complete
list of configurable video processing filters, their IDs and configuration structures. See the ExtendedBufferID enumerator
for more details.

The SDK ensures that all filters necessary to convert input format to output one are included in pipeline. However,
the SDK can skip some optional filters even if they are explicitly requested by the application, for example,
due to limitation of underlying hardware. To notify application about this skip, the SDK returns warning MFX_WRN_FILTER_SKIPPED.
The application can retrieve list of active filters by attaching mfxExtVPPDoUse structure to mfxVideoParam structure and
calling MFXVideoVPP_GetVideoParam function. The application must allocate enough memory for filter list.

Configurable VPP filters:

======================================  =============================
Filter ID                               Configuration structure
======================================  =============================
MFX_EXTBUFF_VPP_DENOISE                 mfxExtVPPDenoise
MFX_EXTBUFF_VPP_MCTF                    mfxExtVppMctf
MFX_EXTBUFF_VPP_DETAIL                  mfxExtVPPDetail
MFX_EXTBUFF_VPP_FRAME_RATE_CONVERSION   mfxExtVPPFrameRateConversion
MFX_EXTBUFF_VPP_IMAGE_STABILIZATION     mfxExtVPPImageStab
MFX_EXTBUFF_VPP_PICSTRUCT_DETECTION     none
MFX_EXTBUFF_VPP_PROCAMP                 mfxExtVPPProcAmp
MFX_EXTBUFF_VPP_FIELD_PROCESSING        mfxExtVPPFieldProcessing
======================================  =============================

Example of Video Processing configuration:

.. code-block:: c++

   /* enable image stabilization filter with default settings */
   mfxExtVPPDoUse du;
   mfxU32 al=MFX_EXTBUFF_VPP_IMAGE_STABILIZATION;

   du.Header.BufferId=MFX_EXTBUFF_VPP_DOUSE;
   du.Header.BufferSz=sizeof(mfxExtVPPDoUse);
   du.NumAlg=1;
   du.AlgList=&al;

   /* configure the mfxVideoParam structure */
   mfxVideoParam conf;
   mfxExtBuffer *eb=&du;

   memset(&conf,0,sizeof(conf));
   conf.IOPattern=MFX_IOPATTERN_IN_SYSTEM_MEMORY | MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
   conf.NumExtParam=1;
   conf.ExtParam=&eb;
 
   conf.vpp.In.FourCC=MFX_FOURCC_YV12;
   conf.vpp.Out.FourCC=MFX_FOURCC_NV12;
   conf.vpp.In.Width=conf.vpp.Out.Width=1920;
   conf.vpp.In.Height=conf.vpp.Out.Height=1088;

   /* video processing initialization */
   MFXVideoVPP_Init(session, &conf);

Region of Interest
~~~~~~~~~~~~~~~~~~

During video processing operations, the application can specify a region of interest for each frame, as illustrated below:

VPP Region of Interest Operation:

.. image:: images/vpp_region_of_interest_operation.png
   :alt: VPP Region of Interest Operation

Specifying a region of interest guides the resizing function to achieve special effects such as resizing
from 16:9 to 4:3 while keeping the aspect ratio intact. Use the CropX, CropY, CropW and CropH parameters
in the mfxVideoParam structure to specify a region of interest.

Examples of VPP Operations on Region of Interest:

================================================== ============ ========================== ============ ==========================
Operation                                          VPP Input    VPP Input                  VPP Output   VPP Output
                                                   Width/Height CropX, CropY, CropW, CropH Width/Height CropX, CropY, CropW, CropH
================================================== ============ ========================== ============ ==========================
Cropping                                           720x480      16,16,688,448              720x480      16,16,688,448
Resizing                                           720x480      0,0,720,480                1440x960     0,0,1440,960
Horizontal stretching                              720x480      0,0,720,480                640x480      0,0,640,480
16:9 4:3 with letter boxing at the top and bottom  1920x1088    0,0,1920,1088              720x480      0,36,720,408
4:3 16:9 with pillar boxing at the left and right  720x480      0,0,720,480                1920x1088    144,0,1632,1088
================================================== ============ ========================== ============ ==========================

Multi-view video processing
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK video processing supports processing multiple views. For video processing initialization, the application needs to attach the mfxExtMVCSeqDesc structure to 
the mfxVideoParam structure and call the MFXVideoVPP_Init function. The function saves the view identifiers. During video processing, the SDK processes each view independently,
one view at a time. The SDK refers to the FrameID field of the mfxFrameInfo structure to configure each view according to its processing pipeline. 
The application needs to fill the the FrameID field before calling the MFXVideoVPP_RunFrameVPPAsync function, if the video processing source frame is not the output from the SDK MVC decoder.
The following pseudo code illustrates it:

.. code-block:: c++

    mfxExtBuffer *eb;
    mfxExtMVCSeqDesc  seq_desc;
    mfxVideoParam init_param;

    init_param.ExtParam = &eb;
    init_param.NumExtParam=1;
    eb=&seq_desc;

    /* init VPP */
    MFXVideoVPP_Init(session, &init_param);

    /* perform processing */
    for (;;) {
        MFXVideoVPP_RunFrameVPPAsync(session,in,out,aux,&syncp);
        MFXVideoCORE_SyncOperation(session,syncp,INFINITE);
    }

    /* close VPP */
    MFXVideoVPP_Close(session);