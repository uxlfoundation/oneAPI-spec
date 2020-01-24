/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief C++ API for Intel(R) Video Processing Library
 * @file vpl.hpp
*/

#ifndef VPL_HPP
#define VPL_HPP

#include <stdexcept>
#include <vector>
#include <string>

#include "vpl/vpl.h"
#include "vpl/vpl_utils.h"

namespace vpl {

/** \brief Decode + frame processing workstream

*/
class Decode {
 public:

  /** \brief Constructor for decode workstream
    *
    * \param[in] src_format VplFourCC codec the workstream will decode
    * \param[in] (optional) target device
  */
  Decode(VplFourCC src_format, VplTargetDevice device = VPL_TARGET_DEVICE_DEFAULT ) : m_workstream(NULL) {
    m_workstream=vplCreateWorkStream(VPL_WORKSTREAM_DECODE,device );

    if ((!m_workstream) ) {
      throw std::logic_error(
          std::string(__FILE__) + ":" +
          std::to_string(__LINE__) + ":" +
          std::string(__FUNCTION__) +
          ": Unable to create decoder");
    }

    vplSetConfigProperty(m_workstream, VPL_PROP_SRC_FORMAT, &src_format, sizeof(src_format));
    VplFourCC dst_format=VPL_FOURCC_NV12;
    vplSetConfigProperty(m_workstream, VPL_PROP_DST_FORMAT, &dst_format, sizeof(dst_format));
  }

  /** \brief Destructor for decode workstream */
  virtual ~Decode(void) { vplDestroyWorkstream(&m_workstream); }

  /** \brief Constructor for decode workstream
    *
    * \param[in] *pbs bitstream input data
    * \param[in] size size of input data in bytes
  */
  vplm_mem* DecodeFrame(const void* pbs, size_t size) {
    return vplDecodeFrame(m_workstream, pbs, size);
  }

  /** \brief Cast operator for C++/C API interoperability */
  operator vplWorkstream() { return m_workstream; }

  /** \brief Get workstream state */
  vplWorkstreamState GetState() { return vplWorkstreamGetState(m_workstream); };

  /** \brief Set workstream parameter */
  template<typename T>
  vplStatus SetConfig(VplWorkstreamProp prop, T val) {
    return vplSetConfigProperty(m_workstream, prop, &val, sizeof(T));
  }

  /** \brief Get workstream parameter value */
  template<typename T>
  vplStatus GetConfig(VplWorkstreamProp prop, T &val) {
    size_t out_size;
    return vplGetConfigProperty(m_workstream, prop, &val, &out_size);
  }

 protected:
  vplWorkstream m_workstream;

 private:
  Decode(const Decode& copy);
  Decode& operator=(const Decode& decode);
};
}  // namespace vpl

#endif  // VPL_HPP
