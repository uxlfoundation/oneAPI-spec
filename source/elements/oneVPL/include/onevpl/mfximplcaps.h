// Copyright (c) 2020 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "mfxdefs.h"

#ifndef __MFXIMPLCAPS_H__
#define __MFXIMPLCAPS_H__

#include "mfxstructures.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if (MFX_VERSION >= 2000)
/*!
   @brief
      This function delivers implementation capabilities in the requested format according to the format value.

   @param[in] format   Format in which capabilities must be delivered. See mfxImplCapsDeliveryFormat for more details.

   @return
      Handle to the capability report or NULL in case of unsupported format.
*/
mfxHDL MFX_CDECL MFXQueryImplDescription(mfxImplCapsDeliveryFormat format);

/*!
   @brief
      This function destoys handle allocated by MFXQueryImplCapabilities function.

   @param[in] hdl   Handle to destroy. Can be equal to NULL.

   @return
      MFX_ERR_NONE The function completed successfully.
*/
mfxStatus MFX_CDECL MFXReleaseImplDescription(mfxHDL hdl);
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MFXIMPLCAPS_H__
