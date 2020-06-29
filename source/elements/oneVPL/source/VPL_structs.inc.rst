
mfxRange32U
~~~~~~~~~~~
.. doxygenstruct:: mfxRange32U
   :project: oneVPL
   :members:
   :protected-members:

mfxI16Pair
~~~~~~~~~~
.. doxygenstruct:: mfxI16Pair
   :project: oneVPL
   :members:
   :protected-members:

mfxHDLPair
~~~~~~~~~~
.. doxygenstruct:: mfxHDLPair
   :project: oneVPL
   :members:
   :protected-members:

mfxVersion
~~~~~~~~~~
.. doxygenunion:: mfxVersion
   :project: oneVPL

mfxStructVersion
~~~~~~~~~~~~~~~~
.. doxygenunion:: mfxStructVersion
   :project: oneVPL

mfxPlatform
~~~~~~~~~~~
.. doxygenstruct:: mfxPlatform
   :project: oneVPL
   :members:
   :protected-members:

mfxInitParam
~~~~~~~~~~~~
.. doxygenstruct:: mfxInitParam
   :project: oneVPL
   :members:
   :protected-members:

mfxInfoMFX
~~~~~~~~~~
.. doxygenstruct:: mfxInfoMFX
   :project: oneVPL
   :members:
   :protected-members:

.. note::

   The :cpp:member:`mfxInfoMFX::InitialDelayInKB`, :cpp:member:`mfxInfoMFX::TargetKbps`, :cpp:member:`mfxInfoMFX::MaxKbps` parameters are for the constant bitrate (CBR), variable bitrate control (VBR) and CQP HRD algorithms.

   The SDK encoders follow the Hypothetical Reference Decoding (HRD) model. The HRD model assumes that data flows into a buffer
   of the fixed size BufferSizeInKB with a constant bitrate TargetKbps. (Estimate the targeted frame size by dividing the framerate
   by the bitrate.)

   The decoder starts decoding after the buffer reaches the initial size InitialDelayInKB, which is equivalent to reaching an initial
   delay of InitialDelayInKB*8000/TargetKbpsms. Note: In this context, KB is 1000 bytes and Kbps is 1000 bps.

   If InitialDelayInKB or BufferSizeInKB is equal to zero, the value is calculated using bitrate, frame rate, profile, level, and so on.

   TargetKbps must be specified for encoding initialization.

   For variable bitrate control, the MaxKbps parameter specifies the maximum bitrate at which the encoded data enters the
   Video Buffering Verifier (VBV) buffer. If MaxKbps is equal to zero, the value is calculated from bitrate, frame rate, profile,
   level, and so on.

.. note::

   The :cpp:member:`mfxInfoMFX::TargetKbps`, :cpp:member:`mfxInfoMFX::Accuracy`, :cpp:member:`mfxInfoMFX::Convergence` parameters are for the average variable bitrate control (AVBR) algorithm.
   The algorithm focuses on overall encoding quality while meeting the specified bitrate, TargetKbps, within the accuracy range Accuracy,
   after a Convergence period. This method does not follow HRD and the instant bitrate is not capped or padded.

mfxFrameInfo
~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameInfo
   :project: oneVPL
   :members:
   :protected-members:

.. note::

   Data alignment for Shift = 0
   
   .. graphviz::
   
     digraph {
         abc [shape=none, margin=0, label=<
         <TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" CELLPADDING="4">
          <TR><TD>Bit</TD><TD>15</TD><TD>14</TD><TD>13</TD><TD>12</TD><TD>11</TD><TD>10</TD><TD>9</TD><TD>8</TD>
              <TD>7</TD><TD>6</TD><TD>5</TD><TD>4</TD><TD>3</TD><TD>2</TD><TD>1</TD><TD>0</TD>
          </TR>
          <TR><TD>Value</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD COLSPAN="10">Valid data</TD>
          </TR>
            </TABLE>>];
     }
   
   
   Data alignment for Shift != 0
   
   .. graphviz::
   
     digraph {
         abc [shape=none, margin=0, label=<
         <TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0" CELLPADDING="4">
          <TR><TD>Bit</TD><TD>15</TD><TD>14</TD><TD>13</TD><TD>12</TD><TD>11</TD><TD>10</TD><TD>9</TD><TD>8</TD>
              <TD>7</TD><TD>6</TD><TD>5</TD><TD>4</TD><TD>3</TD><TD>2</TD><TD>1</TD><TD>0</TD>
          </TR>
          <TR><TD>Value</TD><TD COLSPAN="10">Valid data</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD><TD>0</TD>
          </TR>
            </TABLE>>];
     }

mfxVideoParam
~~~~~~~~~~~~~
.. doxygenstruct:: mfxVideoParam
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameData
~~~~~~~~~~~~
.. doxygenstruct:: mfxY410
   :project: oneVPL
   :members:
   :protected-members:

.. doxygenstruct:: mfxA2RGB10
   :project: oneVPL
   :members:
   :protected-members:

.. doxygenstruct:: mfxFrameData
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameSurfaceInterface
~~~~~~~~~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameSurfaceInterface
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameSurface1
~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameSurface1
   :project: oneVPL
   :members:
   :protected-members:

mfxBitstream
~~~~~~~~~~~~
.. doxygenstruct:: mfxBitstream
   :project: oneVPL
   :members:
   :protected-members:

mfxEncodeStat
~~~~~~~~~~~~~
.. doxygenstruct:: mfxEncodeStat
   :project: oneVPL
   :members:
   :protected-members:

mfxDecodeStat
~~~~~~~~~~~~~
.. doxygenstruct:: mfxDecodeStat
   :project: oneVPL
   :members:
   :protected-members:

mfxPayload
~~~~~~~~~~
.. doxygenstruct:: mfxPayload
   :project: oneVPL
   :members:
   :protected-members:

+-----------+-------------------------------------------+
| **Codec** | **Supported Types**                       |
+===========+===========================================+
| MPEG2     | 0x01B2 //User Data                        |
+-----------+-------------------------------------------+
| AVC       | 02 //pan_scan_rect                        |
|           |                                           |
|           | 03 //filler_payload                       |
|           |                                           |
|           | 04 //user_data_registered_itu_t_t35       |
|           |                                           |
|           | 05 //user_data_unregistered               |
|           |                                           |
|           | 06 //recovery_point                       |
|           |                                           |
|           | 09 //scene_info                           |
|           |                                           |
|           | 13 //full_frame_freeze                    |
|           |                                           |
|           | 14 //full_frame_freeze_release            |
|           |                                           |
|           | 15 //full_frame_snapshot                  |
|           |                                           |
|           | 16 //progressive_refinement_segment_start |
|           |                                           |
|           | 17 //progressive_refinement_segment_end   |
|           |                                           |
|           | 19 //film_grain_characteristics           |
|           |                                           |
|           | 20 //deblocking_filter_display_preference |
|           |                                           |
|           | 21 //stereo_video_info                    |
|           |                                           |
|           | 45 //frame_packing_arrangement            |
+-----------+-------------------------------------------+
| HEVC      | All                                       |
+-----------+-------------------------------------------+

mfxEncodeCtrl
~~~~~~~~~~~~~
.. doxygenstruct:: mfxEncodeCtrl
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameAllocRequest
~~~~~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameAllocRequest
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameAllocResponse
~~~~~~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameAllocResponse
   :project: oneVPL
   :members:
   :protected-members:

mfxFrameAllocator
~~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxFrameAllocator
   :project: oneVPL
   :members:
   :protected-members:

mfxComponentInfo
~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxComponentInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxAdapterInfo
~~~~~~~~~~~~~~
.. doxygenstruct:: mfxAdapterInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxAdaptersInfo
~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxAdaptersInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxQPandMode
~~~~~~~~~~~~
.. doxygenstruct:: mfxQPandMode
   :project: oneVPL
   :members:
   :protected-members:

VPP Structures
~~~~~~~~~~~~~~

mfxInfoVPP
**********
.. doxygenstruct:: mfxInfoVPP
   :project: oneVPL
   :members:
   :protected-members:

mfxVPPStat
**********
.. doxygenstruct:: mfxVPPStat
   :project: oneVPL
   :members:
   :protected-members:

Extension buffers structures
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

mfxExtBuffer
************
.. doxygenstruct:: mfxExtBuffer
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtCodingOption
******************
.. doxygenstruct:: mfxExtCodingOption
   :project: oneVPL
   :members:
   :protected-members:

mfxExtCodingOption2
*******************
.. doxygenstruct:: mfxExtCodingOption2
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtCodingOption3
*******************
.. doxygenstruct:: mfxExtCodingOption3
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtCodingOptionSPSPPS
************************
.. doxygenstruct:: mfxExtCodingOptionSPSPPS
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtInsertHeaders
*******************
.. doxygenstruct:: mfxExtInsertHeaders
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtCodingOptionVPS
*********************
.. doxygenstruct:: mfxExtCodingOptionVPS
   :project: oneVPL
   :members:
   :protected-members:

mfxExtThreadsParam
******************
.. doxygenstruct:: mfxExtThreadsParam
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVideoSignalInfo
*********************
.. doxygenstruct:: mfxExtVideoSignalInfo
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtAVCRefListCtrl
********************
.. doxygenstruct:: mfxExtAVCRefListCtrl
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMasteringDisplayColourVolume
**********************************
.. doxygenstruct:: mfxExtMasteringDisplayColourVolume
   :project: oneVPL
   :members:
   :protected-members:

mfxExtContentLightLevelInfo
***************************
.. doxygenstruct:: mfxExtContentLightLevelInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtPictureTimingSEI
**********************
.. doxygenstruct:: mfxExtPictureTimingSEI
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtAvcTemporalLayers
***********************
.. doxygenstruct:: mfxExtAvcTemporalLayers
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncoderCapability
***********************
.. doxygenstruct:: mfxExtEncoderCapability
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncoderResetOption
************************
.. doxygenstruct:: mfxExtEncoderResetOption
   :project: oneVPL
   :members:
   :protected-members:

mfxExtAVCEncodedFrameInfo
*************************
.. doxygenstruct:: mfxExtAVCEncodedFrameInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncoderROI
****************
.. doxygenstruct:: mfxExtEncoderROI
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncoderIPCMArea
*********************
.. doxygenstruct:: mfxExtEncoderIPCMArea
   :project: oneVPL
   :members:
   :protected-members:

mfxExtAVCRefLists
*****************
.. doxygenstruct:: mfxExtAVCRefLists
   :project: oneVPL
   :members:
   :protected-members:

mfxExtChromaLocInfo
*******************
.. doxygenstruct:: mfxExtChromaLocInfo
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtMBForceIntra
******************
.. doxygenstruct:: mfxExtMBForceIntra
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMBQP
**********
.. doxygenstruct:: mfxExtMBQP
   :project: oneVPL
   :members:
   :protected-members:

mfxExtHEVCTiles
***************
.. doxygenstruct:: mfxExtHEVCTiles
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMBDisableSkipMap
**********************
.. doxygenstruct:: mfxExtMBDisableSkipMap
   :project: oneVPL
   :members:
   :protected-members:

mfxExtHEVCParam
***************
.. doxygenstruct:: mfxExtHEVCParam
   :project: oneVPL
   :members:
   :protected-members:

mfxExtDecodeErrorReport
***********************
.. doxygenstruct:: mfxExtDecodeErrorReport
   :project: oneVPL
   :members:
   :protected-members:

mfxExtDecodedFrameInfo
**********************
.. doxygenstruct:: mfxExtDecodedFrameInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtTimeCode
**************
.. doxygenstruct:: mfxExtTimeCode
   :project: oneVPL
   :members:
   :protected-members:

mfxExtHEVCRegion
****************
.. doxygenstruct:: mfxExtHEVCRegion
   :project: oneVPL
   :members:
   :protected-members:

mfxExtPredWeightTable
*********************
.. doxygenstruct:: mfxExtPredWeightTable
   :project: oneVPL
   :members:
   :protected-members:

mfxExtAVCRoundingOffset
***********************
.. doxygenstruct:: mfxExtAVCRoundingOffset
   :project: oneVPL
   :members:
   :protected-members:

mfxExtDirtyRect
***************
.. doxygenstruct:: mfxExtDirtyRect
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMoveRect
**************
.. doxygenstruct:: mfxExtMoveRect
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMVOverPicBoundaries
*************************
.. doxygenstruct:: mfxExtMVOverPicBoundaries
   :project: oneVPL
   :members:
   :protected-members:

mfxVP9SegmentParam
******************
.. doxygenstruct:: mfxVP9SegmentParam
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVP9Segmentation
*********************
.. doxygenstruct:: mfxExtVP9Segmentation
   :project: oneVPL
   :members:
   :protected-members:

mfxVP9TemporalLayer
*******************
.. doxygenstruct:: mfxVP9TemporalLayer
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVP9TemporalLayers
***********************
.. doxygenstruct:: mfxExtVP9TemporalLayers
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVP9Param
**************
.. doxygenstruct:: mfxExtVP9Param
   :project: oneVPL
   :members:
   :protected-members:

mfxEncodedUnitInfo
******************
.. doxygenstruct:: mfxEncodedUnitInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncodedUnitsInfo
**********************
.. doxygenstruct:: mfxExtEncodedUnitsInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtPartialBitstreamParam
***************************
.. doxygenstruct:: mfxExtPartialBitstreamParam
   :project: oneVPL
   :members:
   :protected-members:

VPP Extention buffers
~~~~~~~~~~~~~~~~~~~~~

mfxExtVPPDoNotUse
*****************
.. doxygenstruct:: mfxExtVPPDoNotUse
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVPPDoUse
**************
.. doxygenstruct:: mfxExtVPPDoUse
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVPPDenoise
~~~~~~~~~~~~~~~~
.. doxygenstruct:: mfxExtVPPDenoise
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVPPDetail
***************
.. doxygenstruct:: mfxExtVPPDetail
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVPPProcAmp
****************
.. doxygenstruct:: mfxExtVPPProcAmp
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtVPPDeinterlacing
**********************
.. doxygenstruct:: mfxExtVPPDeinterlacing
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

mfxExtEncodedSlicesInfo
***********************
.. doxygenstruct:: mfxExtEncodedSlicesInfo
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVppAuxData
****************
.. doxygenstruct:: mfxExtVppAuxData
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPFrameRateConversion
****************************
.. doxygenstruct:: mfxExtVPPFrameRateConversion
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPImageStab
******************
.. doxygenstruct:: mfxExtVPPImageStab
   :project: oneVPL
   :members:
   :protected-members:

mfxVPPCompInputStream
*********************
.. doxygenstruct:: mfxVPPCompInputStream
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPComposite
******************
.. doxygenstruct:: mfxExtVPPComposite
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPVideoSignalInfo
************************
.. doxygenstruct:: mfxExtVPPVideoSignalInfo
   :project: oneVPL
   :members:
   :protected-members:


mfxExtVPPFieldProcessing
************************
.. doxygenstruct:: mfxExtVPPFieldProcessing
   :project: oneVPL
   :members:
   :protected-members:

mfxExtDecVideoProcessing
************************
.. doxygenstruct:: mfxExtDecVideoProcessing
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPRotation
*****************
.. doxygenstruct:: mfxExtVPPRotation
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPScaling
****************
.. doxygenstruct:: mfxExtVPPScaling
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPMirroring
******************
.. doxygenstruct:: mfxExtVPPMirroring
   :project: oneVPL
   :members:
   :protected-members:

mfxExtVPPColorFill
******************
.. doxygenstruct:: mfxExtVPPColorFill
   :project: oneVPL
   :members:
   :protected-members:

mfxExtColorConversion
*********************
.. doxygenstruct:: mfxExtColorConversion
   :project: oneVPL
   :members:
   :protected-members:

ChromaSiting is applied on input or output surface depending on the scenario:

+-------------------------+-------------------------+--------------------------------------------------------------------------------+
| VPP Input               | VPP Output              | ChromaSiting indicates                                                         |
+=========================+=========================+================================================================================+
| MFX_CHROMAFORMAT_YUV420 | MFX_CHROMAFORMAT_YUV444 | The input chroma location                                                      |
|                         |                         |                                                                                |
| MFX_CHROMAFORMAT_YUV422 |                         |                                                                                |
+-------------------------+-------------------------+--------------------------------------------------------------------------------+
| MFX_CHROMAFORMAT_YUV444 | MFX_CHROMAFORMAT_YUV420 | The output chroma location                                                     |
|                         |                         |                                                                                |
|                         | MFX_CHROMAFORMAT_YUV422 |                                                                                |
+-------------------------+-------------------------+--------------------------------------------------------------------------------+
| MFX_CHROMAFORMAT_YUV420 | MFX_CHROMAFORMAT_YUV420 | Chroma location for both input and output                                      |
+-------------------------+-------------------------+--------------------------------------------------------------------------------+
| MFX_CHROMAFORMAT_YUV420 | MFX_CHROMAFORMAT_YUV422 | horizontal location for both input and output, and vertical location for input |
+-------------------------+-------------------------+--------------------------------------------------------------------------------+

mfxExtVppMctf
*************
.. doxygenstruct:: mfxExtVppMctf
   :project: oneVPL
   :members:
   :protected-members:

Bit Rate Control Extension Buffers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

mfxBRCFrameParam
****************
.. doxygenstruct:: mfxBRCFrameParam
   :project: oneVPL
   :members:
   :protected-members:

Frame spatial complexity calculated according to this formula:

.. image:: images/frame_cmplx.png
   :alt: Frame spatial complexity

mfxBRCFrameCtrl
***************
.. doxygenstruct:: mfxBRCFrameCtrl
   :project: oneVPL
   :members:
   :protected-members:

mfxBRCFrameStatus
*****************
.. doxygenstruct:: mfxBRCFrameStatus
   :project: oneVPL
   :members:
   :protected-members:

mfxExtBRC
*********
.. doxygenstruct:: mfxExtBRC
   :project: oneVPL
   :members:
   :protected-members:

VP8 Extenrion Buffers
~~~~~~~~~~~~~~~~~~~~~

mfxExtVP8CodingOption
*********************
.. doxygenstruct:: mfxExtVP8CodingOption
   :project: oneVPL
   :members:
   :protected-members:

JPEG Extension Buffers
~~~~~~~~~~~~~~~~~~~~~~

mfxExtJPEGQuantTables
*********************
.. doxygenstruct:: mfxExtJPEGQuantTables
   :project: oneVPL
   :members:
   :protected-members:

+------------------+---------+------+---+
| Table ID         | 0       | 1    | 2 |
+------------------+---------+------+---+
| Number of tables |         |      |   |
+==================+=========+======+===+
| 0                | Y, U, V |      |   |
+------------------+---------+------+---+
| 1                | Y       | U, V |   |
+------------------+---------+------+---+
| 2                | Y       | U    | V |
+------------------+---------+------+---+

mfxExtJPEGHuffmanTables
***********************
.. doxygenstruct:: mfxExtJPEGHuffmanTables
   :project: oneVPL
   :members:
   :protected-members:

+------------------+---------+------+
| Table ID         | 0       | 1    |
+------------------+---------+------+
| Number of tables |         |      |
+==================+=========+======+
| 0                | Y, U, V |      |
+------------------+---------+------+
| 1                | Y       | U, V |
+------------------+---------+------+

MVC Extension Buffers
~~~~~~~~~~~~~~~~~~~~~

mfxMVCViewDependency
********************
.. doxygenstruct:: mfxMVCViewDependency
   :project: oneVPL
   :members:
   :protected-members:

mfxMVCOperationPoint
********************
.. doxygenstruct:: mfxMVCOperationPoint
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMVCSeqDesc
****************
.. doxygenstruct:: mfxExtMVCSeqDesc
   :project: oneVPL
   :members:
   :protected-members:

mfxExtMVCTargetViews
********************
.. doxygenstruct:: mfxExtMVCTargetViews
   :project: oneVPL
   :members:
   :protected-members:

mfxExtEncToolsConfig
********************
.. doxygenstruct:: mfxExtEncToolsConfig
   :project: oneVPL
   :members:
   :protected-members:

PCP Extension Buffers
~~~~~~~~~~~~~~~~~~~~~
.. doxygenstruct:: _mfxExtCencParam
   :project: oneVPL
   :members:
   :protected-members: