.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=======================
oneVPL Experimental API
=======================

All API entries defined under the ONEVPL_EXPERIMENTAL macro are considered as
expiremental. Backward compatibility is not guaranteed for these features.
Future presense is not guaranteed as well.

By default, experimental API is turned off in the header files. To enable
it, need to define ONEVPL_EXPERIMENTAL macro during the application
compilation stage.

The following is a list of experimental interfaces, starting from API version
2.6.


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
     -
     -
   * - Extended enum for :cpp:member:`mfxExtDecodeErrorReport::ErrorTypes`
     - 2.6
     -
     -
   * - :cpp:enumerator:`mfxHandleType::MFX_HANDLE_PXP_CONTEXT`
     - 2.6
     -
     -
