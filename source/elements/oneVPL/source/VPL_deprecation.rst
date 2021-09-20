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