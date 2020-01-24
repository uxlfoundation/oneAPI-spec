/*
 * Copyright (c) 2019 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __VPLM_VAAPI_H__
#define __VPLM_VAAPI_H__

#include <vplmemory/vplm.h>
#include <va/va.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Wraps given VAAPI surface into VPL Memory object.
 *
 * @param[in] dpy Valid VA display which was used to create the surface.
 * @param[in] id Valid VA surface id created on the specified VA display.
 * @param[out] memory Output vpl memory handle wrapping VA surface.
 */
VPLM_API vplm_status vplm_create_from_va_surface(VADisplay dpy, VASurfaceID id, vplm_mem** memory);

/** \brief Wraps given VAAPI buffer into VPL Memory object.
 *
 * @param[in] dpy Valid VA display which was used to create the buffer.
 * @param[in] id Valid VA buffer id created on the specified VA display.
 * @param[out] memory Output vpl memory handle wrapping VA buffer.
 */
VPLM_API vplm_status vplm_create_from_va_buffer(VADisplay dpy, VABufferID id, vplm_mem** memory);

typedef struct _vplm_va_vtable {
    size_t (*query_displays)(const vplm_mem* mem, VADisplay* displays, size_t num_displays);

    vplm_status (*get_surface)(const vplm_mem* memory, VADisplay dpy, VASurfaceID* image);
    vplm_status (*get_buffer)(const vplm_mem* memory, VADisplay dpy, VABufferID* buffer);
} vplm_va_vtable;

/** \brief Returns OpenCL memory object representation as an image.
 *
 * If memory object does not have OpenCL representation yet, it will be generated or
 * an error returned if that's not possible for some reason. Under the hood VPL Memory
 * library uses one of OpenCL memory sharing APIs unless memory object wasn't initially
 * created as an OpenCL object. #vplm_cl_begin_image_access and #vplm_cl_end_image_access
 * functions should further be used to mark access period to the OpenCL object in the
 * OpenCL queue(s).
 */
static inline size_t vplm_va_query_displays(const vplm_mem* memory, VADisplay* displays, size_t num_displays)
{
    if (!memory || !memory->va)
        return 0;
    return memory->va->query_displays(memory, displays, num_displays);
}

/** \brief Returns memory object representation as VA surface.
 *
 * If memory object does not have VA representation yet, it will be generated or
 * an error returned if that's not possible for some reason.
 */
static inline vplm_status vplm_va_get_surface(const vplm_mem* memory, VADisplay dpy, VASurfaceID* image)
{
    if (!memory || !memory->va)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->va->get_surface(memory, dpy, image);
}

/** \brief Returns memory object representation as VA buffer.
 *
 * If memory object does not have VA representation yet, it will be generated or
 * an error returned if that's not possible for some reason.
 */
static inline vplm_status vplm_va_get_buffer(const vplm_mem* memory, VADisplay dpy, VABufferID* buffer)
{
    if (!memory || !memory->va)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->va->get_buffer(memory, dpy, buffer);
}

#ifdef __cplusplus
}
#endif

#endif // __VPLM_VAAPI_H__
