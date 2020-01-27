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
#include <vplmemory/vplm_vaapi.h>

#include <stdexcept>

namespace vplm
{

namespace vaapi
{

/** \brief VAAPI memory accessor. */
class memory: public vplm::memory
{
public:
    memory(VADisplay dpy, const vplm_mem* mem)
        : vplm::memory(mem)
        , dpy_(dpy)
    {}

    memory(VADisplay dpy, const vplm::memory& mem)
        : vplm::memory(mem)
        , dpy_(dpy)
    {}

    inline vplm_status getBufferId(VABufferID& id) noexcept {
        return vplm_va_get_buffer(object_, dpy_, &id);
    }

    inline vplm_status getSurfaceId(VASurfaceID& id) noexcept {
        return vplm_va_get_surface(object_, dpy_, &id);
    }

    inline VABufferID getBufferId() {
        VABufferID id;
        if (getBufferId(id) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get VA buffer");
        return id;
    }

    inline VASurfaceID getSurfaceId() {
        VASurfaceID id;
        if (getSurfaceId(id) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get VA surface");
        return id;
    }

private:
    VADisplay dpy_;
};

class image
{
public:
    image(VADisplay dpy, const vplm::memory& mem)
        : memory_(dpy, mem)
    {
        if (memory_.getSurfaceId(id_) != VPLM_SUCCESS) {
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to get VA surface");
        }
    }

    inline VASurfaceID id() const { return id_; }

private:
    vplm::vaapi::memory memory_;
    VASurfaceID id_;
};

inline vplm::vaapi::memory make_surface(VADisplay dpy, VASurfaceID id)
{
    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_from_va_surface(dpy, id, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create VA image");

    vplm::vaapi::memory ret(dpy, mem);
    vplm_unref(mem);
    return ret;
}

inline vplm::vaapi::memory make_buffer(VADisplay dpy, VABufferID id)
{
    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_from_va_buffer(dpy, id, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create VA buffer");

    vplm::vaapi::memory ret(dpy, mem);
    vplm_unref(mem);
    return ret;
}

}; // namespace vaapi

}; // namespace vplm
