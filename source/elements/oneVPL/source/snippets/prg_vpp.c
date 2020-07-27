
/*############################################################################
  # Copyright (C) 2020 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mfxdefs.h"
#include "mfxvideo.h"
#include "mfxmvc.h"

/* these macro requires code complilation*/
#define INFINITE 0

mfxSession session;
mfxVideoParam init_param;
mfxFrameAllocRequest response[2];
mfxStatus sts;
mfxFrameSurface1 **in_pool, **out_pool;
mfxSyncPoint syncp;

mfxFrameSurface1 *in, *out;


static void allocate_pool_of_surfaces(mfxFrameSurface1 **pool, int nFrames)
{
    return;
}

static mfxFrameSurface1* find_unlocked_surface_and_fill_content(mfxFrameSurface1 **pool)
{
    return pool[0];
}

static mfxFrameSurface1* find_unlocked_surface_from_the_pool(mfxFrameSurface1 **pool)
{
    return pool[0];
}

static void process_output_frame(mfxFrameSurface1 *surf)
{
    return;
}

static void fill_content_for_video_processing(mfxFrameSurface1 *surf)
{
    return;
}

static int end_of_stream()
{
    return 1;
}

static void free_pool_of_surfaces()
{
    return;
}
/* end of internal stuff */


static void prg_vpp1 () {
/*beg1*/
MFXVideoVPP_QueryIOSurf(session, &init_param, response);
allocate_pool_of_surfaces(in_pool, response[0].NumFrameSuggested);
allocate_pool_of_surfaces(out_pool, response[1].NumFrameSuggested);
MFXVideoVPP_Init(session, &init_param);
mfxFrameSurface1 *in=find_unlocked_surface_and_fill_content(in_pool);
mfxFrameSurface1 *out=find_unlocked_surface_from_the_pool(out_pool);
for (;;) {
   sts=MFXVideoVPP_RunFrameVPPAsync(session,in,out,NULL,&syncp);
   if (sts==MFX_ERR_MORE_SURFACE || sts==MFX_ERR_NONE) {
      MFXVideoCORE_SyncOperation(session,syncp,INFINITE);
      process_output_frame(out);
      out=find_unlocked_surface_from_the_pool(out_pool);
   }
   if (sts==MFX_ERR_MORE_DATA && in==NULL)
      break;
   if (sts==MFX_ERR_NONE || sts==MFX_ERR_MORE_DATA) {
      in=find_unlocked_surface_from_the_pool(in_pool);
      fill_content_for_video_processing(in);
      if (end_of_stream())
         in=NULL;
   }
}
MFXVideoVPP_Close(session);
free_pool_of_surfaces(in_pool);
free_pool_of_surfaces(out_pool);
/*end1*/
}

static void prg_vpp2 () {
/*beg2*/
/* enable image stabilization filter with default settings */
mfxExtVPPDoUse du;
mfxU32 al=MFX_EXTBUFF_VPP_IMAGE_STABILIZATION;

du.Header.BufferId=MFX_EXTBUFF_VPP_DOUSE;
du.Header.BufferSz=sizeof(mfxExtVPPDoUse);
du.NumAlg=1;
du.AlgList=&al;

/* configure the mfxVideoParam structure */
mfxVideoParam conf;
mfxExtBuffer *eb=(mfxExtBuffer *)&du;

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
/*end2*/
}

static void prg_vpp3 () {
/*beg3*/
mfxExtBuffer *eb;
mfxExtMVCSeqDesc  seq_desc;
mfxVideoParam init_param;

init_param.ExtParam = &eb;
init_param.NumExtParam=1;
eb=(mfxExtBuffer *)&seq_desc;

/* init VPP */
MFXVideoVPP_Init(session, &init_param);

/* perform processing */
for (;;) {
    MFXVideoVPP_RunFrameVPPAsync(session,in,out,NULL,&syncp);
    MFXVideoCORE_SyncOperation(session,syncp,INFINITE);
}

/* close VPP */
MFXVideoVPP_Close(session);
/*end3*/
}