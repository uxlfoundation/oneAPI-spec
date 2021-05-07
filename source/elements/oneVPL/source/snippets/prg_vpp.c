/*############################################################################
  # Copyright (C) 2020 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "va/va.h"

#include "mfxdefs.h"
#include "mfxvideo.h"
#include "mfxmvc.h"

/* These macro required for code compilation. */
#define INFINITE 0x7FFFFFFF
#define UNUSED_PARAM(x) (void)(x)

mfxSession session;
mfxVideoParam init_param;
mfxFrameAllocRequest response[2];
mfxStatus sts;
mfxFrameSurface1 **in_pool, **out_pool;
mfxSyncPoint syncp;

mfxFrameSurface1 *in, *out;


static void allocate_pool_of_surfaces(mfxFrameSurface1 **pool, int nFrames)
{
    UNUSED_PARAM(pool);
    UNUSED_PARAM(nFrames);
    return;
}

static mfxFrameSurface1* find_unlocked_surface_and_fill_content(mfxFrameSurface1 **pool)
{
    UNUSED_PARAM(pool);
    return pool[0];
}

static mfxFrameSurface1* find_unlocked_surface_from_the_pool(mfxFrameSurface1 **pool)
{
    UNUSED_PARAM(pool);
    return pool[0];
}

static void process_output_frame(mfxFrameSurface1 *surf)
{
    UNUSED_PARAM(surf);
    return;
}

static void fill_content_for_video_processing(mfxFrameSurface1 *surf)
{
    UNUSED_PARAM(surf);
    return;
}

static int end_of_stream()
{
    return 1;
}

static void free_pool_of_surfaces(mfxFrameSurface1 **in_pool)
{
    UNUSED_PARAM(in_pool);
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

static void prg_vpp4 () {
/*beg4*/
VADisplay va_dpy = 0;
VASurfaceID surface_id = 0;

vaInitialize(va_dpy, NULL, NULL);

// MFX_3DLUT_MEMORY_LAYOUT_INTEL_65LUT indicate 65*65*128*8bytes.
mfxU32 seg_size = 65, mul_size = 128;
mfxMemId memId = 0;

// create 3DLUT surface (MFX_3DLUT_MEMORY_LAYOUT_INTEL_65LUT)
VASurfaceAttrib    surface_attrib = {};
surface_attrib.type =  VASurfaceAttribPixelFormat;
surface_attrib.flags = VA_SURFACE_ATTRIB_SETTABLE;
surface_attrib.value.type = VAGenericValueTypeInteger;
surface_attrib.value.value.i = VA_FOURCC_RGBA;

vaCreateSurfaces(va_dpy,
                 VA_RT_FORMAT_RGB32,   // 4 bytes
                 seg_size * mul_size,  // 65*128
                 seg_size * 2,         // 65*2
                 &surface_id,
                 1,
                 &surface_attrib,
                 1);

*((VASurfaceID*)memId) = surface_id;

// configure 3DLUT parameters
mfxExtVPP3DLut lut3DConfig;
memset(&lut3DConfig, 0, sizeof(lut3DConfig));
lut3DConfig.Header.BufferId         = MFX_EXTBUFF_VPP_3DLUT;
lut3DConfig.Header.BufferSz         = sizeof(mfxExtVPP3DLut);
lut3DConfig.ChannelMapping          = MFX_3DLUT_CHANNEL_MAPPING_RGB_RGB;    
lut3DConfig.BufferType              = MFX_RESOURCE_VA_SURFACE;
lut3DConfig.VideoBuffer.DataType    = MFX_DATA_TYPE_U16;
lut3DConfig.VideoBuffer.MemLayout   = MFX_3DLUT_MEMORY_LAYOUT_INTEL_65LUT;
lut3DConfig.VideoBuffer.MemId       = memId;

// release 3DLUT surface
vaDestroySurfaces(va_dpy, &surface_id, 1);
/*end4*/
}

static void prg_vpp5 () {
/*beg5*/

// 64 size 3DLUT
mfxU8 dataR[64], dataG[64], dataB[64];
mfxChannel channelR, channelG, channelB;
channelR.DataType = MFX_DATA_TYPE_U8;
channelR.Size = 64;
channelR.Data = dataR;
channelG.DataType = MFX_DATA_TYPE_U8;
channelG.Size = 64;
channelG.Data = dataG;
channelB.DataType = MFX_DATA_TYPE_U8;
channelB.Size = 64;
channelB.Data = dataB;

// configure 3DLUT parameters
mfxExtVPP3DLut lut3DConfig;
memset(&lut3DConfig, 0, sizeof(lut3DConfig));
lut3DConfig.Header.BufferId         = MFX_EXTBUFF_VPP_3DLUT;
lut3DConfig.Header.BufferSz         = sizeof(mfxExtVPP3DLut);
lut3DConfig.ChannelMapping          = MFX_3DLUT_CHANNEL_MAPPING_RGB_RGB;    
lut3DConfig.BufferType              = MFX_RESOURCE_SYSTEM_SURFACE;
lut3DConfig.SystemBuffer.Channel[0] = channelR;
lut3DConfig.SystemBuffer.Channel[1] = channelG;
lut3DConfig.SystemBuffer.Channel[2] = channelB;

/*end5*/
}
