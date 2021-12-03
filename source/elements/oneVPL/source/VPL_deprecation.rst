.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==============
Deprecated API
==============

The following is a list of deprecated interfaces, starting from API version 2.0.


.. list-table:: Deprecated API
   :header-rows: 1
   :widths: auto

   * - **API**
     - **Deprecated in API Version**
     - **Removed in API Version**
     - **Alternatives**
     - **Behaviour change of deprecated API**
   * - :cpp:func:`MFXInit`
     - 2.3
     -
     - :cpp:func:`MFXLoad` + :cpp:func:`MFXCreateSession`
     - API may return :cpp:enumerator:`MFX_ERR_NOT_IMPLEMENTED` status
   * - :cpp:func:`MFXInitEx`
     - 2.3
     -
     - :cpp:func:`MFXLoad` + :cpp:func:`MFXCreateSession`
     - API may return :cpp:enumerator:`MFX_ERR_NOT_IMPLEMENTED` status
   * - :cpp:struct:`mfxExtVPPDenoise`
     - 2.5
     -
     - Use :cpp:struct:`mfxExtVPPDenoise2`
     - No change
   * - :cpp:enumerator:`MFX_FOURCC_RGB3`
     - 2.0
     -
     - Use :cpp:enumerator:`MFX_FOURCC_RGB4`
     - No change
   * - :cpp:member:`mfxExtCodingOption::EndOfSequence`
     - 2.0
     -
     - Flag is ignored
     - No change
   * - :cpp:member:`mfxExtCodingOption::EndOfStream`
     - 2.0
     -
     - Flag is ignored
     - No change
   * - :cpp:member:`mfxExtCodingOption3::ExtBrcAdaptiveLTR`
     - 2.4
     -
     - Use :cpp:member:`mfxExtCodingOption3::AdaptiveLTR`
     - No change
   * - :cpp:enumerator:`MFX_EXTBUFF_VPP_SCENE_CHANGE`
     - 2.0
     -
     - Ignored
     - No change
   * - :cpp:member:`mfxExtVppAuxData::SpatialComplexity`
     - 2.0
     -
     - Field is not filled by the library
     - No change
   * - :cpp:member:`mfxExtVppAuxData::TemporalComplexity`
     - 2.0
     -
     - Field is not filled by the library
     - No change
   * - :cpp:member:`mfxExtVppAuxData::SceneChangeRate`
     - 2.0
     -
     - Field is not filled by the library
     - No change
   * - :cpp:member:`mfxExtVppAuxData::RepeatedFrame`
     - 2.0
     -
     - Field is not filled by the library
     - No change
