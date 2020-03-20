/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
   * @brief C API for Intel® oneAPI Video Processing Library
   * @file vpl_video.h
*/

#ifndef VPL_VIDEO_H
#define VPL_VIDEO_H

#include "vpl_export.h"
#include "vpl_types.h"
#include <vplmemory/vplm.h>
#include "vpl_config.hpp"
#include "vpl_device.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Construct a workstream
VPL_EXPORT vplWorkstream vplCreateWorkStream(VplDeviceType device, vpl::VplParams *config);

/// @brief Set a workstream property
VPL_EXPORT vplStatus vplSetConfigProperty(vplWorkstream ws, VplWorkstreamProp prop, void* value, size_t size);

/// @brief Get a workstream property
VPL_EXPORT vplStatus vplGetConfigProperty(vplWorkstream workstream, VplWorkstreamProp prop, void* out_value, size_t * out_size);

/// @brief Destruct a workstream
VPL_EXPORT vplStatus vplDestroyWorkstream(vplWorkstream *ws);

/// @brief Get preconfigured default parameters
VPL_EXPORT vplStatus vplGetWorkstreamPreset(VplDeviceType device, VplWorkstreamType type, vplm_variant* config);

/// @brief Get workstream state
VPL_EXPORT vplWorkstreamState vplWorkstreamGetState(vplWorkstream ws);

/// @brief Decode workstream decodes a frame
VPL_EXPORT vplm_mem* vplDecodeFrame(vplWorkstream decode, const void *pbs, size_t size);

/// @brief Decode workstream decodes a frame with fused frame postprocessing
VPL_EXPORT vplm_mem* vplDecodeProcessFrame(vplWorkstream decode, const void *pbs, size_t size);

/// @brief ProcessFrame workstream runs frame processing operation(s) on a frame
VPL_EXPORT vplm_mem* vplProcessFrame(vplWorkstream procframe, vplm_mem* image);

// @brief Encode workstream encodes a frame with fused frame preprocessing
VPL_EXPORT size_t vplProcessEncodeFrame(vplWorkstream encode, vplm_mem* image, void *pbs_out);

// @brief Encode workstream encodes a frame
VPL_EXPORT size_t vplEncodeFrame(vplWorkstream encode, vplm_mem* image, void *pbs_out);

/// @brief Transcode workstream transcodes a frame
VPL_EXPORT size_t vplTranscodeFrame(vplWorkstream transcode, const void *pbs, size_t size, void *pbs_out);

/// @brief Construct a device
VPL_EXPORT vplDevice vplCreateDevice(VplDeviceType dtype);

/// @brief Destruct a device
VPL_EXPORT vplStatus vplDestroyDevice(vplDevice *dev);

/// @brief Get default preset configuration
VPL_EXPORT vpl::VplParams* vplGetPreset(vplDevice dev, VplWorkstreamType wstype, uint32_t id);

/// @brief Get device property
VPL_EXPORT vpl::VplDeviceProperty* vplGetDeviceProperty(vplDevice dev, uint32_t id);

/// @brief Get device count
VPL_EXPORT int vplGetDeviceCount(vplDevice dev);

VPL_EXPORT vplStatus vplSetPropertyPB(vplWorkstream ws, vpl::VplParams*);
VPL_EXPORT vplStatus vplGetPropertyPB(vplWorkstream ws, vpl::VplParams*);
VPL_EXPORT vplStatus vplPushBlob(vplWorkstream ws, void*, size_t size);

#ifdef __cplusplus
}
#endif

#endif // VPL_VIDEO_H
