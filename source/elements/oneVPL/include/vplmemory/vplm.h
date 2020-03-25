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

#ifndef __VPLM_H__
#define __VPLM_H__

#include <stdint.h>
#include <uchar.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VPLM_API
#ifdef _WIN32
#ifdef VPLM_EXPORT
#define VPLM_API __declspec(dllexport)
#else
#define VPLM_API __declspec(dllimport)
#endif
#else
#define VPLM_API
#endif
#endif

/** \brief VPL Memory success status and error codes. See _vplm_status. */
typedef int32_t vplm_status;

/** \brief Major VPL Memory object handle. */
typedef struct _vplm_vtable vplm_mem;

/** \brief VPL Memory success status and error codes */
enum _vplm_status {
    /** \brief Operation completed successfully */
    VPLM_SUCCESS                              = 0,

    /** \brief Operation is not supported */
    VPLM_ERROR_UNSUPPORTED                    = -1,

    /** \brief Some parameter passed to function is invalid
     *
     * Typically, function returns an object in the location specified
     * by the pointer which is NULL. However, this status may also mean
     * that some other parameter(s) are invalid.
     */
    VPLM_ERROR_INVALID_PARAMETER              = -2,

    /** \brief vplm_mem which was passed is invalid */
    VPLM_ERROR_INVALID_MEMORY_OBJECT          = -3,

    /** \brief vplm_buffer_info which was passed is invalid */
    VPLM_ERROR_INVALID_BUFFER_DESCRIPTION     = -4,

    /** \brief Passed object represents invalid buffer */
    VPLM_ERROR_INVALID_BUFFER                 = -5,

    /** \brief vplm_image_info which was passed is invalid */
    VPLM_ERROR_INVALID_IMAGE_DESCRIPTION      = -6,

    /** \brief Passed object represents invalid image */
    VPLM_ERROR_INVALID_IMAGE                  = -7,

    /** \brief Memory allocation failed */
    VPLM_ERROR_ALLOCATION_FAILED              = -8,

    /** \brief Memory object does not have the requested property */
    VPLM_ERROR_NO_PROPERTY                    = -9,

    /** \brief Operation is not supported for the specified device */
    VPLM_ERROR_UNSUPPORTED_DEVICE             = -10,

    /** \brief Image representation returned by framework is not supported.
     *
     * Framework (VAAPI or OPENCL, etc. driver) returned object
     * representation which is not supported by vpl memory library.
     */
    VPLM_ERROR_UNSUPPORTED_REPRESENTATION     = -11,

    /** \brief Some system operation failed. */
    VPLM_ERROR_OPERATION_FAILED               = -12,

    /** \brief Some VAAPI issued call failed. */
    VPLM_ERROR_VAAPI_OPERATION_FAILED         = -13,

    /** \brief Some OpenCL issued call failed. */
    VPLM_ERROR_OPENCL_OPERATION_FAILED        = -14,
} /*vplm_status*/;

typedef struct {
    uint32_t w;
    uint32_t h;
} vplm_size;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} vplm_rect;

typedef enum {
    VPLM_VARIANT_TYPE_INT32 = 1,      /**< 32-bit signed integer */
    VPLM_VARIANT_TYPE_INT64,          /**< 64-bit signed integer */
    VPLM_VARIANT_TYPE_DOUBLE,         /**< double */
    VPLM_VARIANT_TYPE_SIZE,           /**< vplm_size */
    VPLM_VARIANT_TYPE_RECT,           /**< vplm_rect */
    VPLM_VARIANT_TYPE_POINTER,        /**< Generic pointer type */
} vplm_variantype;

/** \brief Generic value. */
typedef struct {
    /** \brief Value type. */
    vplm_variantype  type;
    /** \brief Value holder. */
    union {
        int32_t     int32;
        int64_t     int64;
        double      dbl;
        vplm_size     size;
        vplm_rect     rect;
        void*       ptr;
    };
} vplm_variant;

typedef enum {
    /** 8-bit 4:2:0 color formats */
    VPLM_PIXEL_FORMAT_NV12 = 0x3231564E,
    VPLM_PIXEL_FORMAT_YV12 = 0x32315659,
    VPLM_PIXEL_FORMAT_I420 = 0x30323449,

    /** 10-bit YUV 4:2:0 color formats */
    VPLM_PIXEL_FORMAT_P010 = 0x30313050,

    /** 8-bit YUV 4:2:2 color formats */
    VPLM_PIXEL_FORMAT_YUY2 = 0x32595559,
    VPLM_PIXEL_FORMAT_UYVY = 0x59565955,

    /** 10-bit YUV 4:2:2 color formats*/
    VPLM_PIXEL_FORMAT_Y210 = 0x30313259,

    /** 8-bit YUVA 4:4:4 color formats */
    VPLM_PIXEL_FORMAT_AYUV = 0x56555941,

    /** 10-bit YUVA 4:4:4 color formats */
    VPLM_PIXEL_FORMAT_Y410 = 0x30313459,

    /** 8-bit RGB */
    VPLM_PIXEL_FORMAT_RGBP = 0x50424752,

    /** 8-bit RGBA color formats */
    VPLM_PIXEL_FORMAT_ARGB = 0x42475241,
    VPLM_PIXEL_FORMAT_ABGR = 0x52474241,
    VPLM_PIXEL_FORMAT_RGBA = 0x41424752,
} vplm_pixel_format;

typedef enum {
    VPLM_DATA_TYPE_U8 = 0,  /**< Buffer contains uint8_t data. */
    VPLM_DATA_TYPE_VAAPI,   /**< Buffer contains some custom VAAPI data. */
} vplm_data_type;

/** \brief VPL Memory Buffer description. */
typedef struct {
    vplm_data_type data_type;
    size_t size;
    uint64_t reserved[32];
} vplm_buffer_info;

/** \brief VPL Memory CPU (HOST) buffer representation. */
typedef struct {
    /** \brief Private data assigned to the object by VPL Memory library.
     *
     * Do not modify this field. Otherwise library behavior is undefined.
     */
    uintptr_t priv;

    vplm_buffer_info info;

    /** \brief Memory handle from which this representation was derived. */
    vplm_mem* memory;

    uint8_t* data;
    size_t size;
} vplm_cpu_buffer;

#define VPLM_IMAGE_MAX_PLANES  4

/** \brief VPL Memory Image description. */
typedef struct {
    vplm_pixel_format format;
    /** \brief Width of the image containing valid data. */
    uint32_t width;

    /** \brief Width of the image containing valid data. */
    uint32_t height;

    /** \brief Padded width of the image.
     *
     * Should be greater or equal to #width or equal to 0. In the latter case,
     * vpl memory library decides on alignment during memory allocation.
     *
     * Padded area might not contain valid data. Moreover, padded area might
     * or might not be initialized depending on implementation.
     */
    uint32_t aligned_width;

    /** \brief Padded height of the image.
     *
     * Should be greater or equal to #height or equal to 0. In the latter case,
     * vpl memory library decides on alignment during memory allocation.
     *
     * Padded area might not contain valid data. Moreover, padded area might
     * or might not be initialized depending on implementation.
     */
    uint32_t aligned_height;

    uint64_t reserved[32];
} vplm_image_info;

/** \brief VPL Memory CPU (HOST) image representation. */
typedef struct {
    /** \brief Private data assigned to the object by VPL Memory library.
     *
     * Do not modify this field. Otherwise library behavior is undefined.
     */
    uintptr_t priv;

    /** \brief Image info. */
    vplm_image_info info;

    /** \brief Memory handle from which this representation was derived. */
    vplm_mem* memory;

    /** \brief Pointer to the buffer holding the whole image. Can be NULL.
     *
     * Will be NULL if image can't be represented by the single buffer. Use
     * per-plane pointers in this case.
     */
    uint8_t* buffer;

    /** \brief Size of the buffer holding the whole image. Can be 0.
     *
     * Will be 0 if image can't be represented by the single buffer.
     */
    size_t buffer_size;

    /** \brief Number of planes composing the image. */
    size_t num_planes;

    struct {
        /** \brief Pointer to the plane data. */
        uint8_t* data;
        /** \brief Stride (pitch) of this plane. */
        uint32_t stride;
    } planes[VPLM_IMAGE_MAX_PLANES];
} vplm_cpu_image;

/** \brief Access modes to acquire access to images or buffers. */
typedef enum {
    /** \brief Read access to the memory.
     *
     * Object is being access for reading which allows independent parallel read access,
     * but does not allow parallel write access.
     */
    VPLM_ACCESS_MODE_READ = 0x1,
    /** \brief Write access to the memory.
     *
     * Object is being access for writing which implies unique single access. Any parallel
     * access, being that read or write, is not allowed.
     */
    VPLM_ACCESS_MODE_WRITE = 0x2,
    /** \brief Read and write access to the memory. */
    VPLM_ACCESS_MODE_READWRITE = VPLM_ACCESS_MODE_READ | VPLM_ACCESS_MODE_WRITE,
} vplm_access_flags;

/** \brief Specifies user-defined on destroy callback.
 *
 * User-defined callback function (see vplm_on_destroy_cb for prototype) will be called
 * once object reference counter will reach 0, but before object will actually will be
 * destroyed. In this way user can intersect with the object destruction and "save" it
 * increasing reference counter and placing it in some pool. Library will check object
 * reference counter once more upon the exit from the user callback function. If the
 * counter will be 0 object will be destroyed, if not it will be kept alive. User must
 * let the counter reach 0 for the object to be really destroyed.
 */
#define VPLM_PROPERTY_CALLBACK_ON_DESTROY 0x1000
/** \brief On destroy callback function prototype. */
typedef void (*vplm_on_destroy_cb)(const vplm_mem* mem);

/** \brief User defined custom properties start key.
 *
 * Keys range < than this key is reserved for VPL Memory Library implementation.
 */
#define VPLM_PROPERTY_CUSTOM     0x100000

/* CPU support */

/** \brief Allocates buffer in system memory and returns vpl memory handle */
VPLM_API vplm_status vplm_create_cpu_buffer(const vplm_buffer_info* info, vplm_mem** memory);

/** \brief Allocates image in system memory and returns vpl memory handle
 *
 * Memory will be allocated according to provided info description. If vplm_image_info.aligned_width
 * and/or info->aligned_height are equal to 0, library will select alignment for vplm_image_info.width
 * and/or vplm_image_info.height on its own. If these values are not zero they will be respected.
 * However, library may still additionally align them to the higher values. If application needs to
 * strictly specify image padding, then it should allocate image on its own and pass it to
 * vplm_create_from_cpu_image.
 */
VPLM_API vplm_status vplm_create_cpu_image(const vplm_image_info* info, vplm_mem** memory);

VPLM_API vplm_status vplm_create_from_cpu_buffer(const vplm_cpu_buffer* buffer, vplm_mem** memory);
VPLM_API vplm_status vplm_create_from_cpu_image(const vplm_cpu_image* image, vplm_mem** memory);

/* Function table */
typedef struct _vplm_va_vtable vplm_va_vtable;
typedef struct _vplm_cl_vtable vplm_cl_vtable;
typedef struct _vplm_dx11_vtable vplm_dx11_vtable;
typedef struct _vplm_dmabuf_vtable vplm_dmabuf_vtable;

/** \brief VPL Memory object, aka vplm_mem.*/
typedef struct _vplm_vtable {
    uintptr_t priv;

    uint32_t (*ref)(const vplm_mem* mem);
    uint32_t (*unref)(const vplm_mem* mem);

    vplm_status (*set_property)(const vplm_mem* mem, int32_t key, vplm_variant value);
    vplm_status (*get_property)(const vplm_mem* mem, int32_t key, vplm_variant* value);
    vplm_status (*clear_properties)(const vplm_mem* mem);
    vplm_status (*get_image_info)(const vplm_mem* mem, vplm_image_info* info);
    vplm_status (*get_buffer_info)(const vplm_mem* mem, vplm_buffer_info* info);

    vplm_status (*map_buffer)(const vplm_mem* mem, uint64_t flags, vplm_cpu_buffer* buffer);
    vplm_status (*unmap_buffer)(vplm_cpu_buffer* buffer);

    vplm_status (*map_image)(const vplm_mem* mem, uint64_t flags, vplm_cpu_image* image);
    vplm_status (*unmap_image)(vplm_cpu_image* image);

    vplm_va_vtable* va;
    vplm_cl_vtable* cl;
    vplm_dx11_vtable* dx11;
    vplm_dmabuf_vtable* dmabuf;
} vplm_vtable;

/* General API */

/** \brief Increases referece counter of the memory object.
 *
 * This function call effectively marks one more user of the object making
 * sure object won't be deleted while this user won't decrease refence counter
 * by vplm_unref.
 */
static inline uint32_t vplm_ref(const vplm_mem* memory)
{
    if (!memory)
        return 0;
    return memory->ref(memory);
}

/** \brief Decreases reference counter of the memory object.
 *
 * Once reference counter will reach 0 object will be destroyed. However,
 * user might install VPLM_PROPERTY_CALLBACK_ON_DESTROY to intersect object
 * release procedure and effectively "save" the object and reuse it via some
 * objects pool.
 */
static inline uint32_t vplm_unref(const vplm_mem* memory)
{
    if (!memory)
        return 0;
    return memory->unref(memory);
}

/** \brief Sets object property. */
static inline vplm_status vplm_set_property(const vplm_mem* memory, int32_t key, vplm_variant value)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->set_property(memory, key, value);
}

/** \brief Returns object property. */
static inline vplm_status vplm_get_property(const vplm_mem* memory, int32_t key, vplm_variant* value)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->get_property(memory, key, value);
}

/** \brief Removes all properties from the object. */
static inline vplm_status vplm_clear_properties(const vplm_mem* memory)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->clear_properties(memory);
}

/** \brief Returns generic object info in a buffer representation. */
static inline vplm_status vplm_get_buffer_info(const vplm_mem* memory, vplm_buffer_info* info)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->get_buffer_info(memory, info);
}

/** \brief Returns generic object info in an image representation. */
static inline vplm_status vplm_get_image_info(const vplm_mem* memory, vplm_image_info* info)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->get_image_info(memory, info);
}

/* CPU support */
/** \brief Maps object to be accessed on CPU (HOST) as a buffer. */
static inline vplm_status vplm_map_buffer(const vplm_mem* memory, uint64_t flags, vplm_cpu_buffer* buffer)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->map_buffer(memory, flags, buffer);
}

/** \brief Unmaps object from the CPU (HOST).
 *
 * On the exit of this function object representation previously returned in #vplm_cpu_buffer
 * becomes invalid and should not be accessed.
 */
static inline vplm_status vplm_unmap_buffer(vplm_cpu_buffer* buffer)
{
    if (!buffer || !buffer->memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return buffer->memory->unmap_buffer(buffer);
}

/** \brief Maps object to be accessed on CPU (HOST) as an image. */
static inline vplm_status vplm_map_image(const vplm_mem* memory, uint64_t flags, vplm_cpu_image* image)
{
    if (!memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return memory->map_image(memory, flags, image);
}

/** \brief Unmaps object from the CPU (HOST).
 *
 * On the exit of this function object representation previously returned in #vplm_cpu_image
 * becomes invalid and should not be accessed.
 */
static inline vplm_status vplm_unmap_image(vplm_cpu_image* image)
{
    if (!image || !image->memory)
        return VPLM_ERROR_INVALID_MEMORY_OBJECT;
    return image->memory->unmap_image(image);
}

#ifdef __cplusplus
}
#endif

#endif // __VPLM_H__
