/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/
/// @file vpl_types.h
/// Implements non implementation specific workstream functionality
/// such as logging and get/set parameters.
#ifndef VPL_TYPES_H
#define VPL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define VPL_MAKEFOURCC(A, B, C, D) \
    ((((uint32_t)A)) + (((uint32_t)B) << 8) + (((uint32_t)C) << 16) + (((uint32_t)D) << 24))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _vplWorkstream *vplWorkstream;

/// @brief status codes
typedef enum{
    VPL_OK = 0,
    VPL_ERR_NOT_SUPPORTED    = -1,
    VPL_ERR_NULL_POINTER     = -2,
    VPL_ERR_NOT_FOUND        = -3,
    VPL_ERR_HW_UNAVALIBLE    = -4,
    VPL_ERR_INVALID_FRAME    = -5,
    VPL_ERR_OUT_OF_RESOURCES = -6,
    VPL_ERR_INTERNAL_ERROR   = -7,
    VPL_ERR_INVALID_SIZE     = -8,
    VPL_ERR_INVALID_PROPERTY = -9
}vplStatus; 

/// @brief workstream state communicates next steps to the application
typedef enum{
    // special decoder's state
    /
    VPL_STATE_READ_INPUT                = 1000, ///< Decoder needs additional input bitstream data to decode.
    VPL_STATE_CLOSED_TO_INPUT           = 1001,
    VPL_STATE_ERROR                     = 1002, ///< Decoder has encountered an error and entered error state.
    VPL_STATE_INPUT_BUFFER_FULL         = 1003, ///< Decoder internal input buffer is full. Caller must retrieve the decoded frames before supplying new bitstream data.
    VPL_STATE_INPUT_EXCEEDS_BUFFER_SIZE = 1004, ///< The input data exceeds the capacity of the input buffer
    VPL_STATE_END_OF_OPERATION          = 1005  ///< All decoded frames have been retrieved by the caller. Decoder workstream ends.

}vplWorkstreamState;

/// @brief workstream type
typedef enum  {
    VPL_WORKSTREAM_DECODE = 0,  // decode with raw frame postprocessing
    VPL_WORKSTREAM_ENCODE,      // encode with raw frame preprocessing
    VPL_WORKSTREAM_TRANSCODE,   // decode -> frame processing -> encode
} VplWorkstreamType;

/// @brief Target device specifies which extension will be loaded
typedef enum {
    VPL_TARGET_DEVICE_DEFAULT,  // Let the runtime determine the best target 
    VPL_TARGET_DEVICE_CPU,      // Run on CPU
    VPL_TARGET_DEVICE_GPU_GEN,  // Run on Gen graphics GPU
    VPL_TARGET_DEVICE_GPU_VSI,  // Run on VSI GPU
    VPL_TARGET_DEVICE_FPGA      // Run on FPGA
} VplTargetDevice;

/// @brief Settable/Gettable properties for workstreams
typedef enum {
    VPL_PROP_WORKSTREAM_TYPE,
    VPL_PROP_VERSION,
    VPL_PROP_VERSION_STRING, 

    //special decoded configs
    VPL_PROP_DECODED_BUFFER_SIZE,
    VPL_MAX_NUMBER_OF_DECODED_IMAGES,

    // special encode config
    VPL_PROP_ENCODE_BITRATE,
    VPL_PROP_ENCODE_SCENARIO,
    VPL_PROP_ENCODE_TARGETUSAGE,

    // common configs
    VPL_PROP_SRC_FORMAT,    // fourCC for input bitstream/frame
    VPL_PROP_DST_FORMAT,    // destination fourCC for bitstream/frame
    VPL_PROP_INPUT_FRAMERATE,   
    VPL_PROP_OUTPUT_FRAMERATE,  
    VPL_PROP_INPUT_RESOLUTION,
    VPL_PROP_OUTPUT_RESOLUTION,
    VPL_PROP_INPUT_CROPS,
    VPL_PROP_OUTPUT_CROPS,
    VPL_PROP_INPUT_ASPECTRATIO,
    VPL_PROP_OUTPUT_ASPECTRATIO,        
    VPL_PROP_INPUT_PICSTRUCT,
    VPL_PROP_OUTPUT_PICSTRUCT,
    
    // status callback configurations
    VPL_PROP_STATUS_CALLBACK,
    VPL_PROP_STATUS_CALLBACK_DATA,
    VPL_PROP_STATUS_LEVEL,
} VplWorkstreamProp;

/// @brief logging level
typedef enum {
    LOG_NONE     = 0x0,
    LOG_INFO     = 0x1,
    LOG_WARNING  = 0x2,
    LOG_ERROR    = 0x4,
    LOG_CRITICAL = 0x8,
    LOG_ALL      = 0xFFFF,
}vplLogLevel;

typedef enum {
    GAME_STREAMING,
    CLOUD_GAMING,
    VIDEO_CONFERENCING,
    LIVE_STREAMING,
    LIVE_STREAMING_LD,
    RECORDING,
    SURVEILLANCE,
    REMOTE_DISPLAY,
}vplEncodeScenario;

typedef enum {
    VPL_BEST_QUALITY = 1,
    VPL_BALANCED,
    VPL_BEST_SPEED
}vplTargetUsage;

typedef struct
{
    uint32_t FrameRateExtN;
    uint32_t FrameRateExtD;
}VplFrameRate;


/// @brief bitstream and raw frame format FourCC codes
typedef enum {
    // Bitstream formats
    VPL_FOURCC_H264 = VPL_MAKEFOURCC('H', '2', '6', '4'),
    VPL_FOURCC_H265 = VPL_MAKEFOURCC('H', '2', '6', '5'),

    // Raw frame formats
    VPL_FOURCC_NV12 = VPL_MAKEFOURCC('N', 'V', '1', '2'),
    VPL_FOURCC_YV12 = VPL_MAKEFOURCC('Y', 'V', '1', '2'),
    VPL_FOURCC_RGB4 = VPL_MAKEFOURCC('R', 'G', 'B', '4'),
    VPL_FOURCC_YUY2 = VPL_MAKEFOURCC('Y', 'U', 'Y', '2'),
    VPL_FOURCC_P210 = VPL_MAKEFOURCC('P', '2', '1', '0'),
    VPL_FOURCC_BGR4 = VPL_MAKEFOURCC('B', 'G', 'R', '4'),      /* ABGR in that order, A channel is 8 MSBs */
    VPL_FOURCC_A2RGB10 = VPL_MAKEFOURCC('R', 'G', '1', '0'),   /* ARGB in that order, A channel is two MSBs */
    VPL_FOURCC_AYUV = VPL_MAKEFOURCC('A', 'Y', 'U', 'V'),      /* YUV 4:4:4, AYUV in that order, A channel is 8 MSBs */
    VPL_FOURCC_UYVY = VPL_MAKEFOURCC('U', 'Y', 'V', 'Y'),
    VPL_FOURCC_Y210 = VPL_MAKEFOURCC('Y', '2', '1', '0'),
    VPL_FOURCC_Y410 = VPL_MAKEFOURCC('Y', '4', '1', '0'),
    VPL_FOURCC_Y216 = VPL_MAKEFOURCC('Y', '2', '1', '6'),
    VPL_FOURCC_Y416 = VPL_MAKEFOURCC('Y', '4', '1', '6'),
    VPL_FOURCC_I420 = VPL_MAKEFOURCC('I', '4', '2', '0'),
    VPL_FOURCC_RGBA = VPL_MAKEFOURCC('R', 'G', 'B', 'A'),
} VplFourCC;

/// @brief Version information
typedef struct {
  uint32_t major;
  uint32_t major_update;
  uint32_t phase;
  uint32_t phase_update;
} VplVersion;


/// @brief raw frame resolution
typedef struct {
  uint32_t width;
  uint32_t height;
} VplVideoSurfaceResolution;

#ifdef __cplusplus
}
#endif

#endif // VPL_TYPES_H
