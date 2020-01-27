/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
   * @brief C API for Intel(R) Video Processing Library
   * @file vpl_video.h
*/

#ifndef VPL_VIDEO_H
#define VPL_VIDEO_H

#include "vpl_export.h"
#include "vpl_types.h"
#include <vplmemory/vplm.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Opaque handle for workstreams
typedef struct _vplWorkstream *vplWorkstream;

/// @brief Construct a workstream
VPL_EXPORT vplWorkstream vplCreateWorkStream(VplWorkstreamType type, VplTargetDevice device);

/// @brief Destruct a workstream
VPL_EXPORT vplStatus vplDestroyWorkstream(vplWorkstream *ws);

/// @brief Set a workstream property
VPL_EXPORT vplStatus vplSetConfigProperty(vplWorkstream ws, VplWorkstreamProp prop, void* value, size_t size);

/// @brief Get a workstream property
VPL_EXPORT vplStatus vplGetConfigProperty(vplWorkstream workstream, VplWorkstreamProp prop, void* out_value, size_t * out_size);

/// @brief Get workstream state
VPL_EXPORT vplWorkstreamState vplWorkstreamGetState(vplWorkstream ws);

/// @brief Decode workstream decodes a frame
VPL_EXPORT vplm_mem* vplDecodeFrame(vplWorkstream decode, const void *pbs, size_t size);


VPL_EXPORT vplm_mem* vplEncodeFrame(vplWorkstream encode, vplm_mem* image, uint8_t eos);

#ifdef __cplusplus
}
#endif

#endif // VPL_VIDEO_H
