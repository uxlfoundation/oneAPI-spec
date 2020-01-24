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

#include <stdexcept>
#include <vector>
#include <string>

namespace vplm
{

/**
 * \brief Intends to wrap vpl memory C-API structures.
 *
 * To access underlying C structure, use operator(). For example:
 *   wrapper<vplm_image_info> info;
 *   vplm_image_info& c_info = info();
 */
template<class T>
class wrapper
{
public:
    wrapper()
        : object_()
    {}

    wrapper(const T& other)
        : object_(other)
    {}

    wrapper<T>& operator=(const T& other)
    {
        object_ = other;
        return *this;
    }

    T& operator()()
    {
        return object_;
    }

    const T& operator()() const
    {
        return object_;
    }

    T* operator&()
    {
        return &object_;
    }

    const T* operator&() const
    {
        return &object_;
    }

protected:
    T object_;
};

class variant : public vplm::wrapper<vplm_variant>
{
public:
    variant(vplm_variant v) : vplm::wrapper<vplm_variant>(v)
    {
    }

    // constructors
    variant(int32_t v)
    {
        object_.type = VPLM_VARIANT_TYPE_INT32;
        object_.int32 = v;
    }

    variant(int64_t v)
    {
        object_.type = VPLM_VARIANT_TYPE_INT64;
        object_.int64 = v;
    }

    variant(double v)
    {
        object_.type = VPLM_VARIANT_TYPE_DOUBLE;
        object_.dbl = v;
    }

    variant(vplm_size v)
    {
        object_.type = VPLM_VARIANT_TYPE_SIZE;
        object_.size = v;
    }

    variant(vplm_rect v)
    {
        object_.type = VPLM_VARIANT_TYPE_RECT;
        object_.rect = v;
    }

    template<typename T>
    variant(T* v)
    {
        object_.type = VPLM_VARIANT_TYPE_POINTER;
        object_.ptr = v;
    }

    template<typename T>
    variant(T v)   // For enum stored as int32_t
    {
        object_.type = VPLM_VARIANT_TYPE_INT32;
        object_.int32 = static_cast<int32_t>(v);
    }

    // getters
    operator int32_t()
    {
        if (object_.type == VPLM_VARIANT_TYPE_INT32) return object_.int32;
        throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
    }

    operator int64_t()
    {
        if (object_.type == VPLM_VARIANT_TYPE_INT32) return object_.int32;
        if (object_.type == VPLM_VARIANT_TYPE_INT64) return object_.int64;
        throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
    }

    operator double()
    {
        if (object_.type == VPLM_VARIANT_TYPE_INT32) return object_.int32;
        if (object_.type == VPLM_VARIANT_TYPE_DOUBLE) return object_.dbl;
        throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
    }

    operator vplm_size()
    {
        if (object_.type == VPLM_VARIANT_TYPE_SIZE) return object_.size;
        throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
    }

    operator vplm_rect()
    {
        if (object_.type == VPLM_VARIANT_TYPE_RECT) return object_.rect;
        throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
    }

    template<typename T>
    operator T* ()
    {
        if (object_.type != VPLM_VARIANT_TYPE_POINTER)
            throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
        return (T*)object_.ptr;
    }

    template<typename T>
    operator T()   // For enum stored as int32_t
    {
        if (object_.type != VPLM_VARIANT_TYPE_INT32)
            throw std::logic_error(std::string(__FUNCTION__) + ": Invalid type");
        return (T)object_.int32;
    }
};

/** \brief Base C++ VPL Memory object.
 *
 * This class wraps C memory handle and provides access to generic
 * VPL Memory API calls independent from the HW frameworks like
 * getting/setting properties.
 *
 * To access underlying memory object within some framework (like
 * Opencl or VAAPI), VPL Memory C++ API defines framework specific
 * memory handlers inherited from this base class. The key thing
 * to note is that end user can construct framework handler from
 * the base memory object. For example:
 * \code
    #include <vplmemory/vplm++.h>
    #include <vplmemory/vplm_vaapi++.h>

    vplm::memory mem = get_from_somewhere();
    vplm::vaapi::memory va_mem(mem);

    printf(">>> VASurfaceID=%d\n", va_mem.getSurfaceId());
    \endcode
 */
class memory : public wrapper<const vplm_mem*>
{
public:
    memory()
    {
    }

    memory(const vplm_mem* mem)
    {
        object_ = mem;
        ref();
    }

    memory(const memory& mem)
        : wrapper<const vplm_mem*>()
    {
        object_ = mem();
        ref();
    }

    ~memory()
    {
        unref();
    }

    memory& operator=(const memory& mem)
    {
        unref();
        object_ = mem();
        ref();
        return *this;
    }

    inline vplm_status setProperty(int32_t key, vplm::variant value)
    {
        return vplm_set_property(object_, key, value());
    }

    inline vplm::variant getProperty(int32_t key)
    {
        vplm_variant val;
        vplm_status err = vplm_get_property(object_, key, &val);
        if (err != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + " key=" + std::to_string(key));
        return vplm::variant(val);
    }

    inline vplm_status clearProperties()
    {
        return vplm_clear_properties(object_);
    }
    
protected:
    inline void ref()
    {
        if (object_ != nullptr)
            vplm_ref(object_);
    }

    inline void unref()
    {
        if (object_ != nullptr)
            vplm_unref(object_);
        object_ = nullptr;
    }
};

/** \cond PRIVATE */
#define __VPLMCPP_RETURN_AS_VECTOR(object, field, num_elements) \
{ \
    std::vector<decltype((object)[0].field)> ret(num_elements); \
    for (size_t i = 0; i < (num_elements); ++i) { \
        ret[i] = (object)[i].field; \
    } \
    return ret; \
}
/** \endcond */

///////////////////////////////////////////////////////////////////////////////
// CPU

class cpu_image : public vplm::wrapper<vplm_cpu_image>
{
public:
    inline uint8_t* buffer()
    {
        return object_.buffer;
    };

    inline size_t buffer_size()
    {
        return object_.buffer_size;
    };

    inline uint8_t* data(size_t index)
    {
        if (index >= object_.num_planes)
            throw std::logic_error(std::string(__FUNCTION__) + ": Plane index out of range");
        return object_.planes[index].data;
    };

    inline std::vector<uint8_t*> data()
    {
        __VPLMCPP_RETURN_AS_VECTOR(object_.planes, data, object_.num_planes);
    }

    inline uint32_t stride(size_t index)
    {
        if (index >= object_.num_planes)
            throw std::logic_error(std::string(__FUNCTION__) + ": Plane index out of range");
        return object_.planes[index].stride;
    };

    inline std::vector<uint32_t> strides()
    {
        __VPLMCPP_RETURN_AS_VECTOR(object_.planes, stride, object_.num_planes);
    };
};

namespace cpu
{

/** \brief CPU (HOST) memory accessor. */
class memory: public vplm::memory
{
public:
    memory(const vplm_mem* mem)
        : vplm::memory(mem)
    {}

    memory(const vplm::memory& mem)
        : vplm::memory(mem)
    {}

    inline vplm_status map(uint64_t flags, vplm::cpu_image& image) {
        return vplm_map_image(object_, flags, &image);
    }

    inline vplm_status unmap(vplm::cpu_image& image) {
        return vplm_unmap_image(&image);
    }
};

/** \brief CPU (HOST) image accessor.
 *
 * Helper class which maps memory object for CPU (HOST) access in constructor
 * and unmaps in destructor. Example:
 *
 * \code
    #include <vplmemory/vplm++.h>

    vplm::memory mem = get_from_somewhere();

    {
        vplm::cpu::image image(mem, VPLM_ACCESS_MODE_READ);

        printf(">>> first plane stride is: %d\n", image.stride(0));
    }
    \endcode
 */
class image: public vplm::cpu_image
{
public:
    image(const vplm::memory& mem, uint64_t flags)
        : memory_(mem)
    {
        if (memory_.map(flags, *this) != VPLM_SUCCESS)
            throw std::logic_error(std::string(__FUNCTION__) + ": Failed to map CPU image");
    }

    ~image()
    {
        memory_.unmap(*this);
    }

private:
    vplm::cpu::memory memory_;
};

inline vplm::cpu::memory make_memory(const vplm::cpu_image& image)
{
    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_from_cpu_image(&image, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create CPU image");

    vplm::cpu::memory ret(mem);
    vplm_unref(mem);
    return ret;
}

/** \brief Creates image in system (HOST) memory. */
inline vplm::cpu::memory make_memory(const vplm_image_info& info)
{
    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_cpu_image(&info, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create CPU image");

    vplm::cpu::memory ret(mem);
    vplm_unref(mem);
    return ret;
}

/** \brief Creates image in system (HOST) memory. */
inline vplm::cpu::memory make_memory(uint32_t width, uint32_t height, vplm_pixel_format format)
{
    vplm_image_info info{};
    info.width  = width;
    info.height = height;
    info.format = format;

    vplm_mem* mem = nullptr;
    vplm_status sts = vplm_create_cpu_image(&info, &mem);

    if (sts != VPLM_SUCCESS)
        throw std::logic_error(std::string(__FUNCTION__) + ": Failed to create CPU image");

    vplm::cpu::memory ret(mem);
    vplm_unref(mem);
    return ret;
}

}; // namespace cpu

}; // namespace vplm
