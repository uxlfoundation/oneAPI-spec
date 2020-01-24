/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/
/// @file vpl.h Top level C header for VPL

#ifndef LIBVPL_INCLUDE_VPL_VPL_H_
#define LIBVPL_INCLUDE_VPL_VPL_H_

// enabling this macro will for the entire stack to use VPL image as intended
// in production. One memory doesn't support creating a new
// image from existing driver-centric allocations, so we roll back to buffer mode

#define USE_VPL_IMAGE

#include "vpl/vpl_video.h"
#include "vpl/vpl_utils.h"

#endif  // LIBVPL_INCLUDE_VPL_VPL_H_
