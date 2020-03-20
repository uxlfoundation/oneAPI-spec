/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief C++ API for Intel® oneAPI Video Processing Library
 * @file vpl_context.hpp
 */

#ifndef VPL_CONTEXT_HPP
#define VPL_CONTEXT_HPP

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

#include "vpl/vpl_device.hpp"

namespace vpl {

/** \brief VPL device context API
 *
 * Device context is an abstraction to represent the command queue to submit the workstream operations
 * 
*/

class Workstream;

class VPL_EXPORT DeviceContext {
public:
  /** \brief DeviceContext constructor
   *
   * \param[in] dev device instance to run the workstream operations
   * 
   */
  DeviceContext(const DeviceInstance &dev): m_device(dev) {}

  /** \brief Get Device Instance
   * 
   * \result Device instance
   * 
   */
  DeviceInstance* GetDevice() { return &m_device; }


  /** \brief Add workstream to context users
   * 
   * \param[in] ws workstream
   * 
   */
  void AddWorkstream(Workstream *ws) { m_workstreams.push_back(ws); }

  /** \brief Remove workstream from context users 
   * 
   * \param[in] ws workstream
   * 
   */
  void RemoveWorkstream(Workstream *ws) {
    auto it = find(m_workstreams.begin(), m_workstreams.end(), ws);
    if (it != m_workstreams.end()) {
      m_workstreams.erase(it);
    }
  }

  /** \brief DeviceContext destructor
   * 
   */
  ~DeviceContext();

protected:
  DeviceInstance m_device;                /**< running device */
  std::vector<Workstream*> m_workstreams; /**< workstreams sharing the context */
};

} // namespace vpl

#endif // VPL_CONTEXT_HPP
