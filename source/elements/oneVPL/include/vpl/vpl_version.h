/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/
/// @file vpl_version.h VPL version information
#ifndef VPL_VERSION_H
#define VPL_VERSION_H

#include <string.h>

#include "config.h"

#define STRING2(a) #a
#define STRING(a) STRING2(a)

// version is defined in top-level CMakeLists.txt
//
// oneAPI version schema:
// <major>.<major_update>[-phase<phase_update>]
//
// Examples:
//   2021.1           (gold, initial release)
//   2021.1-beta02    (beta, update 1)

#if (VPL_VERSION_PHASE == 0)
#define VPL_VERSION_PHASE_STR "alpha"
#elif (VPL_VERSION_PHASE == 1)
#define VPL_VERSION_PHASE_STR "beta"
#elif (VPL_VERSION_PHASE == 99)
#define VPL_VERSION_PHASE_STR "gold"
#endif

const char *vplVersionString = 
  STRING(VPL_VERSION_MAJOR) "."
  STRING(VPL_VERSION_MAJOR_UPDATE)
#if (VPL_VERSION_PHASE < 99)
   "-" VPL_VERSION_PHASE_STR
#if (VPL_VERSION_PHASE < 10)
  "0"
#endif
  STRING(VPL_VERSION_PHASE_UPDATE)
#endif
;

#endif // VPL_VERSION_H

