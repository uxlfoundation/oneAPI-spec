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

#ifndef __VPLM_SYCL_H__
#define __VPLM_SYCL_H__

#include <CL/sycl.hpp>
#include <sycl/accessor.hpp>
#include <vplmemory/vplm++.h>
#include <vplmemory/vplm_opencl++.h>

namespace vplm
{
namespace sycl
{
class memory
{
public:
    memory(const vplm_mem* vpl_mem) : mem_(vpl_mem), cpu_image_(), cl_image_()
    {
    }

    memory(const ::vplm::memory& vpl_mem) : mem_(vpl_mem()), cpu_image_(), cl_image_()
    {
    }

    cl::sycl::image<2> acquire_image(const cl::sycl::queue& sycl_queue, cl::sycl::access::mode access_mode)
    {
        vplm_access_flags mode = access_mode_sycl2vpl(access_mode);

        auto sycl_device = sycl_queue.get_device();

#ifdef SYCL_OPENCL_INTEROP
        if (!sycl_device.is_cpu() && !sycl_device.is_host()) {
            if (vplm_cl_get_image(mem_, sycl_queue.get(), &cl_image_) == VPLM_SUCCESS) {
                return cl::sycl::image<2>(cl_image_.planes[0].clmem, sycl_queue.get_context());
            }
        }
#endif
        if (vplm_map_image(mem_, mode, &cpu_image_) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Error mapping to CPU image");
        vplm_image_info info;
        vplm_get_image_info(mem_, &info);
        cl::sycl::image_channel_order format = vplFormat2SYCL(info.format);
        cl::sycl::image_channel_type data_type = cl::sycl::image_channel_type::unsigned_int8; // fp32
        cl::sycl::range<2> range(info.width, info.height);
        return cl::sycl::image<2>(cpu_image_.planes[0].data, format, data_type, range);
    }

    void release_image()
    {
        release_handle();
    }

    ~memory()
    {
        release_handle();
    }

protected:
    const vplm_mem* mem_;
    vplm_cpu_image cpu_image_;
    vplm_cl_image cl_image_;

    void release_handle()
    {
        if (cpu_image_.num_planes != 0) {
            vplm_unmap_image(&cpu_image_);
            cpu_image_ = {};
        }
#ifdef SYCL_OPENCL_INTEROP
        if (cl_image_.num_planes != 0) {
            vplm_cl_end_image_access(&cl_image_);
            cl_image_ = {};
        }
#endif
    }

    inline cl::sycl::image_channel_order vplFormat2SYCL(int32_t format)
    {
        switch (format) {
        case VPLM_PIXEL_FORMAT_NV12:
            return (cl::sycl::image_channel_order) -1;
        case VPLM_PIXEL_FORMAT_RGBA:
            return cl::sycl::image_channel_order::rgba;
        case VPLM_PIXEL_FORMAT_RGBP:
            return (cl::sycl::image_channel_order) -1;
        case VPLM_PIXEL_FORMAT_I420:
            return (cl::sycl::image_channel_order) -1;
        }
        return (cl::sycl::image_channel_order) -1;
    }

    inline vplm_access_flags access_mode_sycl2vpl(cl::sycl::access::mode access_mode)
    {
        switch (access_mode) {
        case cl::sycl::access::mode::read:
            return VPLM_ACCESS_MODE_READ;
        case cl::sycl::access::mode::write:
            return VPLM_ACCESS_MODE_WRITE;
        case cl::sycl::access::mode::read_write:
            return VPLM_ACCESS_MODE_READWRITE;
        default:
            return VPLM_ACCESS_MODE_READWRITE;
        }
    }
};
}
}

#endif // __VPLM_SYCL_H__
