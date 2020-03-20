/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief C++ API for Intel® oneAPI Video Processing Library
 * @file vpl_device.hpp
 */

#ifndef VPL_DEVICE_HPP
#define VPL_DEVICE_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "vpl/vpl.h"
#include "vpl/vpl_utils.h" 

using namespace vpl;

namespace vpl {

/** \brief VPL device API
 *
 * Device discovery and property query interface:
 * the number of SDKs and handles to the SDKs, 
 * the number of devices and handles to devices,
 * and the device properties.
 * 
 * It also includes device capability queries and 
 * predefined device settings for Decode, VPP, Infer and Encode workstream.

*/

/** \brief VPL maximum device name length
 */
#define VPL_MAX_DEVICE_NAME 512

/** \brief VPL device property structure
 */
struct VplDeviceProperty {
  VplDeviceType type;
  uint32_t vendorId;
  uint32_t deviceId;
//  VplDeviceUUID uuid;
  uint32_t subdeviceId;
  uint32_t coreClockRate;
  uint32_t maxCmdEngines;
  bool unifiedMemorySupported;
  bool eccMemorySupported;
  uint32_t numUnits;  // number of tiles, cores
  char name[VPL_MAX_DEVICE_NAME];
};

/** \brief VPL device instance
 */
class VPL_EXPORT DeviceInstance {
public:
  VplDeviceType m_dtype;
  uint32_t m_id;
  DeviceInstance(VplDeviceType dtype, uint32_t id):m_dtype(dtype),m_id(id) {}
};

class VPL_EXPORT DeviceInfo {
public:

  /** \brief Get device count 
   * 
   * \param[in] dtype device type
   * \return number of devices found for the device type
  */
  int GetDeviceCount(VplDeviceType dtype);

  /** \brief Get device property
   * 
   * \param[in] dtype device type
   * \param[in] id device ID
   * \return device property
   * 
   */
  VplDeviceProperty* GetDeviceProperty(VplDeviceType dtype, uint32_t id);

  /** \brief Get prefered device
   * 
   * \param[in] wstypes a bit mask of workstream types
   * \return preferred device instance for the workstream type
   * 
   */
  DeviceInstance* GetPreferredDevice(uint32_t wstypes);

  /** \brief Get device preset to setup a workstream
   * 
   * \param[in] dtype device type
   * \param[in] wstype workstream type
   * \param[in] id device id
   * \return config preset for the device and wstype
   * 
   */
  VplParams* GetPreset(VplDeviceType dtype, VplWorkstreamType wstype, uint32_t id = 0);
  
  DeviceInfo();
  ~DeviceInfo();

protected:
  vplDevice GetDeviceHandle(VplDeviceType dtype);

  vplDevice m_device[VPL_DEVICE_COUNT]; /**< Dispatch handle*/
};

} // namespace vpl

#endif // VPL_DEVICE_HPP
