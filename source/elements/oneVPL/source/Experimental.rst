.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=======================
oneVPL Experimental API
=======================

All API entries defined under the ONEVPL_EXPERIMENTAL macro are considered as
experimental. Backward compatibility is not guaranteed for these features.
Future presence is not guaranteed as well.

By default, experimental API is turned off in the header files. To enable
it, need to define ONEVPL_EXPERIMENTAL macro during the application
compilation stage.

The following is a list of experimental interfaces, starting from API version
2.6.

.. _experimental-api-table:

.. list-table:: Experimental API
   :header-rows: 1
   :widths: auto

   * - **Experimental API**
     - **Added in API Version**
     - **Removed in API Version**
     - **Removal Reason**
   * - :cpp:struct:`mfxExtendedDeviceId`
     - 2.6
     -
     -
   * - :cpp:member:`mfxExtCodingOption3::CPUEncToolsProcessing`
     - 2.6
     -
     -
   * - :cpp:type:`mfxExtRefListCtrl`
     - 2.6
     - 2.8
     - Moved to production
   * - :cpp:enumerator:`MFX_EXTBUFF_UNIVERSAL_REFLIST_CTRL`
     - 2.6
     - 2.8
     - Moved to production
   * - Extended enum for :cpp:member:`mfxExtDecodeErrorReport::ErrorTypes`
     - 2.6
     - 2.7
     - Moved to production
   * - :cpp:enumerator:`mfxHandleType::MFX_HANDLE_PXP_CONTEXT`
     - 2.6
     - 2.7
     - Moved to production
   * - :cpp:struct:`mfxRefInterface`
     - 2.7
     -
     -
   * - All definitions in mfxencodestats.h
     - 2.7
     -
     -
   * - :cpp:enumerator:`MFX_FOURCC_ABGR16F` FourCC definition
     - 2.8
     -
     -
   * - :cpp:enumerator:`MFX_CONTENT_NOISY_VIDEO` ContentInfo definition
     - 2.8
     -
     -
   * - Camera Processing API for RAW acceleration
     - 2.8
     -
     -
   * - Hint to disable external video frames caching for GPU copy
     - 2.8
     -
     -
   * - :cpp:member:`mfxExtMBQP::Pitch`
     - 2.8
     -
     -
   * - :cpp:struct:`mfxExtSyncSubmission`
     - 2.9
     -
     -
   * - :cpp:struct:`mfxExtVPPPercEncPrefilter`
     - 2.9
     -
     -
   * - :cpp:member:`mfxExtendedDeviceId::RevisionID`
     - 2.9
     -
     -
   * - :cpp:struct:`extDeviceUUID`
     - 2.9
     -
     -
   * - :cpp:struct:`mfxExtTuneEncodeQuality`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_DEFAULT`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_PSNR`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_SSIM`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_MS_SSIM`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_VMAF`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_PERCEPTUAL`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_EXTBUFF_TUNE_ENCODE_QUALITY`
     - 2.9
     -
     -
   * - :cpp:struct:`mfxAutoSelectImplDeviceHandle`
     - 2.9
     -
     -
   * - :cpp:type:`mfxAutoSelectImplType`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_AUTO_SELECT_IMPL_TYPE_UNKNOWN`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_AUTO_SELECT_IMPL_TYPE_DEVICE_HANDLE`
     - 2.9
     -
     -
