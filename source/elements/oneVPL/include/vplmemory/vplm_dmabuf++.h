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

#ifdef __linux__

#include <vplmemory/vplm.h>
#include <vplmemory/vplm_dmabuf.h>

#include <stdexcept>
#include <vector>
#include <string>

namespace vplm
{

class dmabuf_image: public vplm::wrapper<vplm_dmabuf_image>
{
public:
    inline int fd()
    {
        return object_.fd;
    }

    inline size_t size()
    {
        return object_.size;
    }

    inline size_t offset(size_t index)
    {
        if (index >= object_.num_planes)
            throw std::logic_error(std::string(__FUNCTION__) + ": Plane index out of range");
        return object_.planes[index].offset;
    }

    inline std::vector<size_t> offsets()
    {
        __VPLMCPP_RETURN_AS_VECTOR(object_.planes, offset, object_.num_planes);
    }

    inline uint32_t stride(size_t index)
    {
        if (index >= object_.num_planes)
            throw std::logic_error(std::string(__FUNCTION__) + ": Plane index out of range");
        return object_.planes[index].stride;
    }

    inline std::vector<uint32_t> strides()
    {
        __VPLMCPP_RETURN_AS_VECTOR(object_.planes, stride, object_.num_planes);
    }
};

namespace dmabuf
{

class memory: public vplm::memory
{
public:
    memory(const vplm_mem* mem)
        : vplm::memory(mem)
    {}

    memory(const vplm::memory& mem)
        : vplm::memory(mem)
    {}

    inline vplm_status get(vplm::dmabuf_image& image) noexcept {
        return vplm_dmabuf_get_image(object_, &image);
    }

    inline vplm::dmabuf_image get() {
        vplm::dmabuf_image image;
        if (get(image) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get DMABUF object");
        return image;
    }
};

class image: public vplm::dmabuf_image
{
public:
    image(const vplm::memory& mem)
        : memory_(mem)
    {
        if (memory_.get(*this) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to map CPU image");
    }

    ~image()
    {
        vplm_dmabuf_close_image(&object_);
    }

private:
    vplm::dmabuf::memory memory_;
};

}; // namespace dmabuf

}; // namespace vplm

#endif // __linux__
