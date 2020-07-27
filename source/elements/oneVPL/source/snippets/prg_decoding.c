/*############################################################################
  # Copyright (C) 2020 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#include <stdlib.h>
#include <stdio.h>

#include "mfxdefs.h"
#include "mfxvideo.h"
#include "mfxmvc.h"

/* these macro requires code complilation*/
#define INFINITE 0

mfxSession session;
mfxBitstream *bitstream, *bits;
mfxVideoParam init_param, param;
mfxFrameAllocRequest request;
mfxStatus sts;
mfxFrameSurface1* work, *disp;
mfxSyncPoint syncp;


static void allocate_pool_of_frame_surfaces(int nFrames)
{
    return;
}

static int end_of_stream()
{
    return 1;
}

static void append_more_bitstream(mfxBitstream *bs)
{
    return;
}

static void find_unlocked_surface_from_the_pool(mfxFrameSurface1 **pool)
{
    return;
}

static void realloc_surface(mfxFrameSurface1* work, mfxFrameInfo FrameInfo)
{
    return;
}

static void do_something_with_decoded_frame(mfxFrameSurface1* disp)
{
    return;
}

static void free_pool_of_frame_surfaces()
{
    return;
}

static void release_surface(mfxFrameSurface1* surf)
{
    return;
}
/* end of internal stuff */


static void prg_decoding1 () {
/*beg1*/
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
   if (end_of_stream() && sts==MFX_ERR_MORE_DATA) break;
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
MFXVideoDECODE_Close(session);
free_pool_of_frame_surfaces();
/*end1*/
}

static void prg_decoding2 () {
/*beg2*/
sts=MFX_ERR_MORE_DATA;
for (;;) {
   if (sts==MFX_ERR_MORE_DATA && !end_of_stream())
      append_more_bitstream(bitstream);
   bits=(end_of_stream())?NULL:bitstream;
   sts=MFXVideoDECODE_DecodeFrameAsync(session,bits,NULL,&disp,&syncp);
   if (sts==MFX_ERR_MORE_SURFACE) continue;
   if (end_of_stream() && sts==MFX_ERR_MORE_DATA) break;
   // skipped other error handling
   if (sts==MFX_ERR_NONE) {
      MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
      do_something_with_decoded_frame(disp);
      release_surface(disp);
   }
}
/*end2*/
}

static void prg_decoding3 () {
/*beg3*/
mfxExtBuffer *eb[2];
mfxExtMVCSeqDesc  seq_desc;
mfxVideoParam init_param;

init_param.ExtParam=(mfxExtBuffer **)&eb;
init_param.NumExtParam=1;
eb[0]=(mfxExtBuffer *)&seq_desc;
MFXVideoDECODE_DecodeHeader(session, bitstream, &init_param);

/* select views to decode */
mfxExtMVCTargetViews tv;
init_param.NumExtParam=2;
eb[1]=(mfxExtBuffer *)&tv;

/* initialize decoder */
MFXVideoDECODE_Init(session, &init_param);

/* perform decoding */
for (;;) {
    MFXVideoDECODE_DecodeFrameAsync(session, bits, work, &disp, &syncp);
    MFXVideoCORE_SyncOperation(session, syncp, INFINITE);
}

/* close decoder */
MFXVideoDECODE_Close(session);
/*end3*/
}