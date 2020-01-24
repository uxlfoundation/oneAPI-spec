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

#ifndef __VPLM_DMABUF_H__
#define __VPLM_DMABUF_H__

#ifdef __linux__

#include <vplmemory/vplm.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief DMABUF image representation. */
typedef struct {
    /** \brief Private data assigned to the object by VPL Memory library.
     *
     * Do not modify this field. Otherwise library behavior is undefined.
     */
    uintptr_t priv;

    /** \brief Memory handle from which this representation was derived. */
    vplm_mem* memory;

    /** \brief File descriptor representing the whole image. Can be -1.
      *
      * File descriptor will be equal to -1 if image can't be represented
      * as a single object (i.e. planes are managed by separate independent
      * objects). In this case, use file descriptor of each plane defined below.
      */
    int fd;

    /** \brief Size of the buffer holding the whole image. Can be 0.
      *
      * Size will be equal to 0 if image can't be represented as a single object
      * (file descriptor will be equal to -1).
      */
    size_t size;

    /** \brief Number of planes composing the image. */
    size_t num_planes;

    /** \brief Per-plane description. */
    struct {
        /** \brief Offset from the beginning of the object data containing the plane. */
        size_t offset;

        /** \brief Stride (pitch) of this plane. */
        uint32_t stride;

#if 0
        /** \brief File descriptor of the object containing this plane.  */
        int fd;

        /** \brief Size of the buffer holding this plane.
          *
          * Pay attention that this is not a plane size, but object size. Plane data starts
          * with the offset specified above from the beginning of the object data.
          */
        size_t size;
#endif
    } planes[VPLM_IMAGE_MAX_PLANES];
} vplm_dmabuf_image;

typedef struct _vplm_dmabuf_vtable {
    vplm_status (*get_image)(const vplm_mem* mem, vplm_dmabuf_image* image);
    vplm_status (*close_image)(vplm_dmabuf_image* image);
} vplm_dmabuf_vtable;

/** \brief Returns dmabuf handle for the memory object.
 *
 * User is responsible to close dmabuf handle when it won't be needed anymore. Library
 * provides the helper function #vplm_dmabuf_close_image to do that. However, there are
 * cases (like with XCB library) when downstream component closes the dmabuf on its own.
 * For this reason #vplm_dmabuf_close_image is not mandatory and it does not have any
 * side effects on the memory object from which dmabuf was exported.
 */
static inline vplm_status vplm_dmabuf_get_image(const vplm_mem* memory, vplm_dmabuf_image* image)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->dmabuf->get_image(memory, image);
}

/** \brief Returns dmabuf handle for the memory object.
 *
 * Closes dmabuf handles previously returned by #vplm_dmabuf_get_image. This function call
 * is optional. It does not have side effects on the memory object from which dmabuf was
 * exported.
 */
static inline vplm_status vplm_dmabuf_close_image(vplm_dmabuf_image* image)
{
    if (!image || !image->memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return image->memory->dmabuf->close_image(image);
}

#ifdef __cplusplus
}
#endif

#endif // __linux
#endif // __VPLM_DMABUF_H__
