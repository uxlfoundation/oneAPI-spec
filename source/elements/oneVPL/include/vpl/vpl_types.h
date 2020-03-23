/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief Structs, enums, etc. used by VPL
 * @file vpl_types.h
*/

#ifndef VPL_TYPES_H
#define VPL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#define VPL_MAKEFOURCC(A, B, C, D) \
    ((((uint32_t)A)) + (((uint32_t)B) << 8) + (((uint32_t)C) << 16) + (((uint32_t)D) << 24))

#ifdef __cplusplus
extern "C" {
#endif

typedef class _vplWorkstream *vplWorkstream;
typedef class _vplDeviceInfo *vplDevice;

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
    VPL_STATE_READ_INPUT                = 1000, // decoder is ready to read input bitstream buffer
    VPL_STATE_CLOSED_TO_INPUT           = 1001,
    VPL_STATE_ERROR                     = 1002,
    VPL_STATE_INPUT_BUFFER_FULL         = 1003, // The input buffer is at capacity, frames must be drain to make space
    VPL_STATE_INPUT_EXCEEDS_BUFFER_SIZE = 1004, // The input data exceeds the capacity of the input buffer
    VPL_STATE_END_OF_OPERATION          = 1005, // End of operations
    VPL_STATE_OK                        = 1006
}vplWorkstreamState;

/// @brief workstream type
typedef enum  {
    VPL_WORKSTREAM_DECODE    = 0x01,  // decode
    VPL_WORKSTREAM_VIDEOPROC = 0x02,  // video processing
    VPL_WORKSTREAM_ENCODE    = 0x04,  // encode
    VPL_WORKSTREAM_INFER     = 0x08,  // DL inference
} VplWorkstreamType;

/// @brief Specifies which device extension is available and will be loaded
typedef enum {
    VPL_DEVICE_CPU = 0,
    VPL_DEVICE_GEN,
    VPL_DEVICE_HDDL,
    VPL_DEVICE_FPGA,
    VPL_DEVICE_COUNT
} VplDeviceType;

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
    VPL_PROP_ENCODE_BRC_ALGORITHM,
    VPL_PROP_ENCODE_FRAMERATE_NUMERATOR,
    VPL_PROP_ENCODE_FRAMERATE_DENOMINATOR,
    VPL_PROP_ENCODE_PERFQUALITY_PRESET,
    VPL_PROP_ENCODE_SCENARIO,
    VPL_PROP_ENCODE_IFRAME_INTERVAL,
    VPL_PROP_ENCODE_BFRAME_INTERVAL,

    // common configs
    VPL_PROP_SRC_BITSTREAM_FORMAT,
    VPL_PROP_SRC_RAW_FORMAT,    
    VPL_PROP_DST_BITSTREAM_FORMAT,
    VPL_PROP_DST_RAW_FORMAT,    
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
    VPL_PROP_STATUS_LOGLEVEL,

    // always last property
    VPL_PROP_NUMPROPS
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
}VplEncodeScenario;

typedef enum {
    VPL_BRC_CBR   = 0,
    VPL_BRC_VBR   = 1,
    VPL_BRC_CQP   = 2,
    VPL_BRC_AVBR  = 3,
    VPL_BRC_COUNT = 4,
}VplBRC;

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
    //VPL_FOURCC_YV12 = VPL_MAKEFOURCC('Y', 'V', '1', '2'),
    VPL_FOURCC_RGB4 = VPL_MAKEFOURCC('R', 'G', 'B', '4'),
    //VPL_FOURCC_YUY2 = VPL_MAKEFOURCC('Y', 'U', 'Y', '2'),
    //VPL_FOURCC_P210 = VPL_MAKEFOURCC('P', '2', '1', '0'),
    //VPL_FOURCC_BGR4 = VPL_MAKEFOURCC('B', 'G', 'R', '4'),      /* ABGR in that order, A channel is 8 MSBs */
    //VPL_FOURCC_A2RGB10 = VPL_MAKEFOURCC('R', 'G', '1', '0'),   /* ARGB in that order, A channel is two MSBs */
    //VPL_FOURCC_AYUV = VPL_MAKEFOURCC('A', 'Y', 'U', 'V'),      /* YUV 4:4:4, AYUV in that order, A channel is 8 MSBs */
    //VPL_FOURCC_UYVY = VPL_MAKEFOURCC('U', 'Y', 'V', 'Y'),
    //VPL_FOURCC_Y210 = VPL_MAKEFOURCC('Y', '2', '1', '0'),
    //VPL_FOURCC_Y410 = VPL_MAKEFOURCC('Y', '4', '1', '0'),
    //VPL_FOURCC_Y216 = VPL_MAKEFOURCC('Y', '2', '1', '6'),
    //VPL_FOURCC_Y416 = VPL_MAKEFOURCC('Y', '4', '1', '6'),
    VPL_FOURCC_I420 = VPL_MAKEFOURCC('I', '4', '2', '0'),
    VPL_FOURCC_BGRA = VPL_MAKEFOURCC('B', 'G', 'R', 'A'),
    VPL_FOURCC_I010 = VPL_MAKEFOURCC('I', '0', '1', '0'),
} VplFourCC;

/// @brief bitstream codec types
typedef enum {
    // Bitstream codec formats
    VPL_CODEC_H264  = 0,
    VPL_CODEC_H265  = 1,
    VPL_CODEC_MPEG2 = 2,
    VPL_CODEC_VC1   = 3,
    VPL_CODEC_VP9   = 4,
    VPL_CODEC_AV1   = 5,
    VPL_CODEC_COUNT = 6,
} VplCodecType;

typedef enum {
    VPL_BALANCED                   = 0,
    VPL_MAX_QUALITY                = 1,
    VPL_HIGH_QUALITY               = 2,
    VPL_QUALITY                    = 3,
    VPL_SPEED                      = 4,
    VPL_HIGH_SPEED                 = 5,
    VPL_MAX_SPEED                  = 6,
    VPL_LOW_LATENCY_MAX_QUALITY    = 7,
    VPL_LOW_LATENCY_MAX_SPEED      = 8,
    VPL_LOWEST_LATENCY_MAX_QUALITY = 9,
    VPL_LOWEST_LATENCY_MAX_SPEED   = 10,
    VPL_EP_COUNT = 11,
} VplEncodePreset;

typedef struct {
    uint32_t crop_x;
    uint32_t crop_y;
    uint32_t crop_w;
    uint32_t crop_h;
} VplCrop;

typedef struct {
    uint32_t ratio_w;
    uint32_t ratio_h;
} VplAspectRatio;

typedef struct {
  uint32_t major;
  uint32_t major_update;
  uint32_t phase;
  uint32_t phase_update;
} VplVersion;



typedef struct {
  uint32_t width;
  uint32_t height;
} VplVideoSurfaceResolution;


typedef struct {
  uint16_t BitDepthLuma;
  uint16_t BitDepthChroma;
  uint32_t Shift;
  uint32_t FourCC;
  uint16_t Width;  //VPL memory info aligned_width
  uint16_t Height; //VPL memory info aligned_height
  uint16_t CropX;
  uint16_t CropY;
  uint16_t CropW;  //VPL memory info width
  uint16_t CropH;  //VPL memory info height

  uint32_t FrameRateExtN;
  uint32_t FrameRateExtD;

  uint16_t AspectRatioW;
  uint16_t AspectRatioH;

  uint16_t PicStruct;
  uint16_t ChromaFormat;
  uint64_t reserved[8];
} VPLFrameInfo;




#ifdef __cplusplus
}
#endif

#endif // VPL_TYPES_H
