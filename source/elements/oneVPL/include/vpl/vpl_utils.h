/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
     * @brief Utility functions for file I/O
     * @file vpl_utils.h
*/
#ifndef VPL_UTILS_H
#define VPL_UTILS_H

#include "vpl_export.h"
#include "vpl_video.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief file handle
typedef struct VplFile VplFile;

/// @brief Open a file
VPL_EXPORT VplFile* vplOpenFile(const char* filename, const char* mode);

/// @brief Close a file
VPL_EXPORT vplStatus vplCloseFile(VplFile* fFile);

/// @brief write a vplm_mem* image to file
VPL_EXPORT vplStatus vplWriteData(VplFile* fOutput, vplm_mem* mem);

/// @brief read a vplm_mem* image from file
VPL_EXPORT vplStatus vplReadData(VplFile* fInput, vplm_mem* mem);

#ifdef __cplusplus
}
#endif
#endif
