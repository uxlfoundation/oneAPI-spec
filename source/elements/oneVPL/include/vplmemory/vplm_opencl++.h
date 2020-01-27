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

#pragma once

#include <vplmemory/vplm.h>
#include <vplmemory/vplm_opencl.h>

#include <stdexcept>
#include <vector>
#include <string>

namespace vplm
{

class cl_image: public vplm::wrapper<vplm_cl_image>
{
public:
    cl_mem operator[](size_t index)
    {
        if (index >= object_.num_planes)
            throw std::logic_error(std::string(__FUNCTION__) + ": Plane index out of range");
        return object_.planes[index].clmem;
    }

    inline std::vector<cl_mem> mem()
    {
        __VPLMCPP_RETURN_AS_VECTOR(object_.planes, clmem, object_.num_planes);
    }
};

namespace opencl
{

/** \brief OpenCL memory accessor. */
class memory: public vplm::memory
{
public:
    memory(cl_command_queue queue, const vplm_mem* mem)
        : vplm::memory(mem)
        , queue_(queue)
    {
    }

    memory(cl_command_queue queue, const vplm::memory& mem)
        : vplm::memory(mem)
        , queue_(queue)
    {
    }

    inline vplm_status get(vplm::cl_image& image) noexcept {
        return vplm_cl_get_image(object_, queue_, &image());
    }

    inline vplm::cl_image get() {
        vplm::cl_image image;
        if (get(image) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get CL image");
        return image;
    }

    inline vplm_status begin_access(
        const vplm::cl_image& clmem,
        cl_uint num_events_in_wait_list,
        const cl_event *event_wait_list,
        cl_event *event)
    {
        return vplm_cl_begin_image_access(&clmem, num_events_in_wait_list, event_wait_list, event);
    }

    inline vplm_status end_access(
        const vplm::cl_image& clmem,
        cl_uint num_events_in_wait_list,
        const cl_event *event_wait_list,
        cl_event *event)
    {
        return vplm_cl_end_image_access(&clmem, num_events_in_wait_list, event_wait_list, event);
    }

private:
    cl_command_queue queue_;
};

/** \brief OpenCL image accessor.
 *
 * Helper class which gets access to the memory object as OpenCL image in constructor
 * and releases access in destructor. Example:
 *
 * \code
    #include <vplmemory/vplm++.h>
    #include <vplmemory/vplm_opencl++.h>

    vplm::memory mem = get_from_somewhere();

    {
        vplm::opencl::image image(mem, VPLM_ACCESS_MODE_READ);

        printf(">>> first plane cl_mem: %p\n", image[0]);
    }
    \endcode
 */
class image: public vplm::cl_image
{
public:
    image(cl_command_queue queue, const vplm::memory& mem)
        : memory_(queue, mem)
    {
        if (memory_.get(*this) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get CL image");

        if (memory_.begin_access(*this, 0, nullptr, nullptr) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to start access to CL image");
    }

    ~image()
    {
        memory_.end_access(*this, 0, nullptr, nullptr);
    }

private:
    vplm::opencl::memory memory_;
};

inline vplm::opencl::memory make_memory(cl_command_queue queue, vplm::cl_image& image)
{
    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_from_cl_image(queue, &image, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create CL image");

    vplm::opencl::memory ret(queue, mem);
    vplm_unref(mem);
    return ret;
}
#

}; // namespace opencl

}; // namespace vplm
