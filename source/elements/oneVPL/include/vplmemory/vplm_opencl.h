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

#ifndef __VPLM_OPENCL_H__
#define __VPLM_OPENCL_H__

#include <vplmemory/vplm.h>
#include <CL/cl.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief OpenCL image representation. */
typedef struct {
    /** \brief Private data assigned to the object by VPL Memory library.
     *
     * Do not modify this field. Otherwise library behavior is undefined.
     */
    uintptr_t priv;

    /** \brief Memory handle from which this CL representation was derived. */
    vplm_mem* memory;

    /** \brief Number of planes composing CL representation. */
    size_t num_planes;

    /** \brief Per-plane description. */
    struct {
        cl_mem clmem;
    } planes[VPLM_IMAGE_MAX_PLANES];
} vplm_cl_image;

VPLM_API vplm_status vplm_create_cl_image(cl_command_queue queue, const vplm_image_info* info, vplm_mem** memory);
VPLM_API vplm_status vplm_create_from_cl_image(cl_command_queue queue, const vplm_cl_image* image, vplm_mem** memory);

typedef struct _vplm_cl_vtable {
    size_t (*query_queues)(const vplm_mem* mem, cl_command_queue* queues, size_t num_queues);

    vplm_status (*get_image)(const vplm_mem* mem, cl_command_queue queue, vplm_cl_image* clmem);

    vplm_status (*begin_image_access)(
        const vplm_cl_image* image,
        cl_uint num_events_in_wait_list,
        const cl_event *event_wait_list,
        cl_event *event);

    vplm_status (*end_image_access)(
        const vplm_cl_image* image,
        cl_uint num_events_in_wait_list,
        const cl_event *event_wait_list,
        cl_event *event);
} vplm_cl_vtable;

/** \brief Returns OpenCL queues for which the library manages OpenCL representation.
 *
 * If function is called with queues=NULL or with num_queues=0, then function returns number
 * of OpenCL queues for which the library tracks object representation.
 *
 * If function is called with queues!=NULL and num_queues!=0, then function fills queues
 * array with the valid queues for which the library tracks object representation and returns
 * number of valid items in queues array.
 *
 * @param[in] memory Memory object to query.
 * @param[in,out] queues User supplied array where library should return OpenCL queues for which
 *   memory object has valid representations.
 * @param[in] num_queues Size of queues array.
 *
 * @returns Number of valid items in user supplied queues array.
 * @returns If queues=NULL or num_queues=0 - number of valid queues for which the library
 * tracks object representation
 */
static inline size_t vplm_cl_query_queues(const vplm_mem* memory, cl_command_queue* queues, size_t num_queues)
{
    if (!memory || !memory->cl)
        return 0;
    return memory->cl->query_queues(memory, queues, num_queues);
}

/** \brief Returns memory object representation as OpenCL image.
 *
 * If memory object does not have OpenCL representation yet, it will be generated or
 * an error returned if that's not possible for some reason. Under the hood VPL Memory
 * library uses one of OpenCL memory sharing APIs unless memory object wasn't initially
 * created as an OpenCL object. #vplm_cl_begin_image_access and #vplm_cl_end_image_access
 * functions should further be used to mark access period to the OpenCL object in the
 * OpenCL queue(s).
 */
static inline vplm_status vplm_cl_get_image(const vplm_mem* memory, cl_command_queue queue, vplm_cl_image* image)
{
    if (!memory || !memory->cl)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->cl->get_image(memory, queue, image);
}

/** \brief Begins access to OpenCL object representation. */
static inline vplm_status vplm_cl_begin_image_access(
    const vplm_cl_image* image,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event)
{
    if (!image || !image->memory || !image->memory->cl)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return image->memory->cl->begin_image_access(image, num_events_in_wait_list, event_wait_list, event);
}

/** \brief Ends access to OpenCL object representation. */
static inline vplm_status vplm_cl_end_image_access(
    const vplm_cl_image* image,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event)
{
    if (!image || !image->memory || !image->memory->cl)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return image->memory->cl->end_image_access(image, num_events_in_wait_list, event_wait_list, event);
}

#ifdef __cplusplus
}
#endif

#endif // __VPLM_OPENCL_H__
