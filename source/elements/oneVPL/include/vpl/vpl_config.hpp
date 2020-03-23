/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief C++ API for Intel® oneAPI Video Processing Library
 * @file vpl_device.hpp
 */

#ifndef VPL_CONFIG_HPP
#define VPL_CONFIG_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "vpl/vpl_types.h"
#include "vpl/vpl_export.h"

namespace vpl {

/** \brief VPL config API
 *
 * Workstream configuration interface:
 * per session and per frame settings for Decode, VideoProcess, Encode and Infer workstreams
 * It is usually initialized by DeviceInfo::GetPreset() and can be modified by application
*/

class VPL_EXPORT VplParams {
public:

  /** \brief Get Input Format 
   * 
   * \return Input image raw format
  */
  VplFourCC GetInputFormat() { return m_iformat; }
  void      SetInputFormat(VplFourCC format) { m_iformat = format; }

  VplFourCC GetOutputFormat() { return m_oformat; }
  void      SetOutputFormat(VplFourCC format) { m_oformat = format; }

  VplFrameRate &GetInputFrameRate() { return m_iframerate; }
  void      SetInputFrameRate(VplFrameRate &fr) { m_iframerate = fr; }

  VplFrameRate &GetOutputFrameRate() { return m_oframerate; }
  void      SetOutputFrameRate(VplFrameRate &fr) { m_oframerate = fr; }

  VplVideoSurfaceResolution &GetInputResolution() { return m_iresolution; }
  void      SetInputResolution(VplVideoSurfaceResolution &res) { m_iresolution = res; }

  VplVideoSurfaceResolution &GetOutputResolution() { return m_oresolution; }
  void      SetOutputResolution(VplVideoSurfaceResolution &res) { m_oresolution = res; }

  VplCrop &GetInputCrop() { return m_icrop; }
  void      SetInputCrop(VplCrop &crop) { m_icrop = crop; }

  VplCrop &GetOutputCrop() { return m_ocrop; }
  void      SetOutputCrop(VplCrop &crop) { m_icrop = crop; }

  VplAspectRatio &GetInputAspectRatio() { return m_iaspect; }
  void      SetInputAspectRatio(VplAspectRatio &ratio) { m_iaspect = ratio; }

  VplAspectRatio &GetOutputAspectRatio() { return m_oaspect; }
  void      SetOutputAspectRatio(VplAspectRatio &ratio) { m_oaspect = ratio; }

  uint16_t  GetPictStruct() { return m_picstruct; }
  void      SetPictStruct(uint16_t ps) { m_picstruct = ps; } 

  VplParams();
  ~VplParams() {}

protected:
  VplFourCC                 m_iformat;
  VplFourCC                 m_oformat;
  VplFrameRate              m_iframerate;
  VplFrameRate              m_oframerate;
  VplVideoSurfaceResolution m_iresolution;
  VplVideoSurfaceResolution m_oresolution;
  VplCrop                   m_icrop;
  VplCrop                   m_ocrop;
  VplAspectRatio            m_iaspect;
  VplAspectRatio            m_oaspect;
  uint16_t                  m_picstruct;
};

class VPL_EXPORT VplParamsDecode: public VplParams {
public:
  VplCodecType GetCodecType() { return m_codec; }
  void         SetCodecType(VplCodecType codec) { m_codec = codec; }

  uint32_t GetDecodeBufferSize() { return m_buffersz; }
  void     SetDecodeBufferSize(uint32_t s) { m_buffersz = s; }

  uint32_t GetMaxNumBuffers() { return m_maxnumbuffers; }
  void SetMaxNumBuffers(uint32_t m)  { m_maxnumbuffers = m; }

  VplParamsDecode();
  ~VplParamsDecode() {}
protected:
  VplCodecType m_codec;
  uint32_t     m_buffersz;
  uint32_t     m_maxnumbuffers;
};

class VPL_EXPORT VplParamsEncode: public VplParams {
public:
  VplCodecType GetCodecType() { return m_codec; }
  void         SetCodecType(VplCodecType codec) { m_codec = codec; }

  uint32_t GetBitRateKps() { return m_bitratekbps; }
  void     SetBitRateKps(uint32_t r) { m_bitratekbps = r; }

  uint32_t GetIFrameInterval() { return m_iframeinterval; }
  void     SetIFrameInterval(uint32_t il) { m_iframeinterval = il; }

  uint32_t GetBFrameInterval() { return m_bframeinterval; }
  void     SetBFrameInterval(uint32_t il) { m_bframeinterval = il; }

  uint32_t GetFrameRateNumerator() { return m_fr_num; }
  void     SetFrameRateNumerator(uint32_t n)  { m_fr_num = n; }
  
  uint32_t GetFrameRateDenominator() { return m_fr_denom; }
  void     SetFrameRateDenominator(uint32_t d) { m_fr_denom = d; }

  VplEncodePreset GetEncodePreset() { return m_encodepreset; }
  void     SetEncodePreset(VplEncodePreset ps) { m_encodepreset = ps; }

  VplRateControl GetRateControl() { return m_ratecontrol; }
  void     SetRateControl(VplRateControl rc) { m_ratecontrol = rc; }

  VplBRC   GetBRC() { return m_brc; }
  void     SetBRC(VplBRC brc) { m_brc = brc; }
  VplParamsEncode();
  ~VplParamsEncode() {}

protected:
  VplCodecType      m_codec;
  uint32_t          m_bitratekbps;
  uint32_t          m_iframeinterval;
  uint32_t          m_bframeinterval;
  uint32_t          m_fr_num;
  uint32_t          m_fr_denom;
  VplEncodePreset   m_encodepreset;
  VplRateControl    m_ratecontrol;
  VplEncodeScenario m_scenario;
  VplBRC            m_brc;
};

} // namespace vpl

#endif // VPL_CONFIG_HPP
