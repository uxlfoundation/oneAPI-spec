/*############################################################################
  # Copyright (C) 2020 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

/**
 * @brief C++ API for Intel® oneAPI Video Processing Library
 * @file vpl.hpp
 */

#ifndef VPL_HPP
#define VPL_HPP

#include <stdexcept>
#include <string>
#include <vector>
#include <queue>

#include "vpl/vpl.h"
#include "vpl/vpl_utils.h"
#include "vpl_context.hpp"

namespace vpl {

enum VplBlobType {
  VPL_BLOB_BS   = 0,
  VPL_BLOB_VPLM = 1, 
};

class VPL_EXPORT VplBlob {
public:
  VplBlob(VplBlobType btype, size_t size, void *data)
   : m_type(btype), m_data(data), m_size(size) {}

  ~VplBlob() {
    if (m_type == VPL_BLOB_BS) {
      delete (char*) m_data;
    } else {
      delete (vplm_mem*) m_data;
    }
  }
  VplBlobType m_type;
  size_t      m_size;
  void       *m_data;
};

class VPL_EXPORT DataQueue {
public:
  DataQueue(int limit = 1) : m_limit(limit) {}
  ~DataQueue();

  bool     IsFull()            { return m_blobs.size() == m_limit; } 
  bool     IsEmpty()           { return m_blobs.empty(); }
  VplBlob* GetFront()          { return m_blobs.front(); }
  void     Push(VplBlob *blob) { m_blobs.push(blob); }
  void     Pop()               { m_blobs.pop(); }
  int      GetLimit()          { return m_limit; }

protected:
  int                  m_limit;
  std::queue<VplBlob*> m_blobs;
};

/** \brief Video processing workstream
 *
 * Workstreams are the core of VPL.  A workstream implements a consistent
 * interface for decode, frame processing, and encode across multiple
 * accelerator types.  It also provides consistent parameter handling and
 * logging.

*/
class VPL_EXPORT Workstream {
public:   

   /** \brief Workstream constructor
   *
   * \param[in] config workstream settings
   * \param[in] dev device instance to create a context
   * \param[in] wstype workstream type
   */
  Workstream(VplParams *config, DeviceInstance &dev, VplWorkstreamType wstype);

  /** \brief Workstream constructor
   *
   * \param[in] config workstream settings
   * \param[in] dcontext workstream device context
   * \param[in] wstype workstream type
   */
  Workstream(VplParams *config, DeviceContext *dcontext, VplWorkstreamType wstype);

  /** \brief Get workstream device context
   * 
   * \return workstream device context 
   */
  DeviceContext *GetContext() { return m_context; }

  /** \brief Returns workstream state
   *
   * GetState returns workstream state, which can be
   *   - VPL_STATE_READ_INPUT                Can read more input
   *   - VPL_STATE_ERROR                     Error during operation
   *   - VPL_STATE_INPUT_BUFFER_FULL         Input buffer is at capacity, drain to make space
   *   - VPL_STATE_INPUT_EXCEEDS_BUFFER_SIZE Input size>buffer size
   *   - VPL_STATE_END_OF_OPERATION          No more operations to do
   *
   * \return workstream state
   */
  vplWorkstreamState GetState() { return vplWorkstreamGetState(m_workstream); }

  //---------------------------------------------------------
  // Workstream settings
  //---------------------------------------------------------
  /** \brief Get workstream configuration setting
   *
   * \return workstream configuration setting message
   */
  vpl::VplParams *GetConfig() { return m_config; }

  /** \brief Set workstream configuration setting
   * 
   * \param[in] config workstream setting 
   *
   * \return configuration setting message
   */
  void SetConfig(vpl::VplParams *config) { m_config = config; }


  /** \brief Propagate the workstream settings to the device
   *
   * \return status
   */
  vplStatus UpdateDeviceConfig();

#if 0
  //--------------------------------------------------------------
  // Workstream pipeline interface
  //--------------------------------------------------------------
  /** \brief Add successor workstream
   * 
   * \param[in] succ successor workstream
   * \param[in] dataqueue data queue
   * \param[in] oport output port number
   * \param[in] iport successor workstream input port number
   * \return workstream state
   */  
  vplStatus AddSuccessor(Workstream *succ, DataQueue *dataqueue, int oport = 0, int iport = 0);

  /** \brief Add data queue to buffer output
   * 
   * \param[in] sink data queue
   * \param[in] oport output port
   * \return status
   */  
  vplStatus AddDataSink(DataQueue *sink, int oport = 0); 

  /** \brief Add data queue to buffer input
   * 
   * \param[in] src input buffer queue
   * \param[in] iport input port
   * \return status
   */  
  vplStatus AddDataSource(DataQueue *src, int iport = 0); 

  /** \brief Run workstream and queue its outputs
   * 
   * \return status
   */  
  vplStatus Run(); 

  //---------------------------------------------------------------------
  // Obsoleted parameter setting interface 
  //---------------------------------------------------------------------
  /** \brief Set a workstream parameter
   *
   * Sets a parameter.  Parameters are in the VplWorstreamProp enum.
   *
   * \param[in] prop workstream property to set
   * \param[in] val value to set
   * \return status
   */
  template <typename T> vplStatus SetConfig(VplWorkstreamProp prop, T val);

  /** \brief Get a workstream parameter
   *
   * Retrieves a workstream parameter
   *
   * \param[in] prop workstream property to set
   * \param[in] val value to get
   * \return status
   */
  template <typename T> vplStatus GetConfig(VplWorkstreamProp prop, T &val);
#endif

  operator vplWorkstream() { return m_workstream; }

  /** \brief Workstream destructor */
  ~Workstream();


protected:
  vpl::DeviceContext *m_context;   /**< Running device context */
  VplParams  *m_config;    /**< Workstream setting */
  VplWorkstreamType   m_wstype;    /**< Workstream type */
  
  vplWorkstream       m_workstream;/**< Dispatch handle */
};

class VPL_EXPORT Decode: public Workstream {
public:
  //-------------------------------------------------------------
  // Constructor and Destructor
  //-------------------------------------------------------------

   /** \brief Decode constructor
   *
   * \param[in] config decode settings
   * \param[in] dcontext decode context
   */
  Decode(VplParams *config, DeviceContext *dcontext)
    :Workstream(config, dcontext, VPL_WORKSTREAM_DECODE) {}

   /** \brief Workstream constructor
   *
   * \param[in] config workstream settings
   * \param[in] dev device instance to create a context
   */
  Decode(VplParams *config, DeviceInstance &dev)
    :Workstream(config, dev, VPL_WORKSTREAM_DECODE) {}

  /** \brief Get Decode workstream parameter protobuf message
   *
   * Retrieve the Decode workstream setting protobuf message
   * 
   * \return configuration setting protobuf message
   */
  vpl::VplParams *GetConfig();

  /** \brief Update Decode workstream parameter to device
   * 
   * Propagate the Decode workstream settings to the device
   *
   * \return status
   */
  vplStatus UpdateDeviceConfig();  

  /** \brief Decode a video frame
   *
   * The DecodeFrame operation decodes a single frame of video
   * when sufficient bitstream data is provided.  Bitstream input
   * does not need to be provided at frame boundaries.  If a frame 
   * cannot be parsed a null frame is returned. 
   *
   * \param[in] *pbs bitstream input data
   * \param[in] size size of input data in bytes
   * \return decoded frame (can be a null pointer)
   */
  vplm_mem *DecodeFrame(const void *pbs, size_t size);

  ~Decode();

};

class VPL_EXPORT Encode: public Workstream {
public:
  //-------------------------------------------------------------
  // Constructor and Destructor
  //-------------------------------------------------------------

   /** \brief Encode constructor
   *
   * \param[in] config encode settings
   * \param[in] dcontext encode context
   */
  Encode(VplParams *config, DeviceContext *dcontext)
    :Workstream(config, dcontext, VPL_WORKSTREAM_ENCODE) {}

   /** \brief Encode constructor
   *
   * \param[in] config workstream settings
   * \param[in] dev device instance to create a context
   */
  Encode(VplParams *config, DeviceInstance &dev)
    :Workstream(config, dev, VPL_WORKSTREAM_ENCODE) {}

  /** \brief Get Encode workstream parameter protobuf message
   *
   * Retrieve the Encode workstream setting protobuf message
   *
   * \return configuration setting protobuf message
   */
  vpl::VplParams *GetConfig();

  /** \brief Update Encode workstream parameter to device
   * 
   * Propagate the Encode workstream settings to the device
   *
   * \return status
   */
  vplStatus UpdateDeviceConfig();  

  /** \brief Encode a video frame
   *
   * Encodes a raw frame of video to compressed bitstream.
   * If a frame cannot be output this iteration returns output size 0.
   * 
   * \param[in] image raw frame to encode
   * \param[out] pbs_out 
   * \return # of bytes in encoded bitstream output
   */
  size_t EncodeFrame(vplm_mem *image, void *pbs_out);
  
  ~Encode();

};

class VPL_EXPORT VideoProcess: public Workstream {
public:
  //-------------------------------------------------------------
  // Constructor and Destructor
  //-------------------------------------------------------------

   /** \brief Process constructor
   *
   * \param[in] config video processing settings
   * \param[in] dcontext video processing context
   */
  VideoProcess(VplParams *config, DeviceContext *dcontext)
    :Workstream(config, dcontext, VPL_WORKSTREAM_VIDEOPROC) {}

   /** \brief Process constructor
   *
   * \param[in] config workstream settings
   * \param[in] dev device instance to create a context
   */
  VideoProcess(VplParams *config, DeviceInstance &dev)
    :Workstream(config, dev, VPL_WORKSTREAM_VIDEOPROC) {}

   /** \brief Get VideoProcess workstream settings
   *
   * Retrieve the VideoProcess workstream setting message 
   *
   * \return configuration setting protobuf message
   */
  vpl::VplParams *GetConfig();

  /** \brief Update VideoProcess workstream parameter to device driver
   * 
   * Propagate the VideoProcess workstream settings to the device driver
   *
   * \return status
   */
  vplStatus UpdateDeviceConfig();   

  /** \brief Process a video frame
   *
   * Process a raw frame of video to create an output raw frame 
   * 
   * \param[in] in raw frame to process
   * \return output raw frame output 
   */
  vplm_mem* ProcessFrame(vplm_mem *in); 
  
  ~VideoProcess();

};

} // namespace vpl

#endif // VPL_HPP
