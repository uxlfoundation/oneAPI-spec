/*############################################################################
  # Copyright (C) 2020 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mfxdefs.h"
#include "mfxvideo.h"

/* these macro requires code complilation*/
#define INFINITE 0

mfxSession session;
mfxBitstream *bitstream;
mfxFrameSurface1 *surface_work, *surface_disp;
mfxSyncPoint syncp;
/* end of internal stuff */


static void prg_err () {
/*beg1*/
mfxStatus sts=MFX_ERR_NONE;
for (;;) {
   // do something
   sts=MFXVideoDECODE_DecodeFrameAsync(session, bitstream,  surface_work, &surface_disp, &syncp);
   if (sts == MFX_WRN_DEVICE_BUSY) sleep(5);
}
/*end1*/
}