/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DNNL_SYCL_HPP
#define DNNL_SYCL_HPP

#include <CL/sycl.hpp>

#include "dnnl.hpp"

/// @addtogroup dnnl_sycl_interop_api
///
/// oneDNN API with SYCL interoperability.
///
/// @{

/// oneDNN namespace
namespace dnnl {

/// SYCL interoperability namespace
namespace sycl_interop {

/// Memory allocation kinds.
enum class memory_kind {
    /// Device memory allocation kind. Such memory allocation is accessible by
    /// the device, and is not accessible by the host.
    usm_device,
    /// Shared memory allocation kind. Such memory allocation is accessible by
    /// both the host and the device.
    usm_shared,
    /// Buffer memory allocation kind. Such memory allocation is accessible in
    /// global address space.
    buffer,
};

/// @addtogroup dnnl_sycl_interop_api_engine
///
/// oneDNN engine API with SYCL interoperability.
///
/// @{

/// Creates an engine object using a specified SYCL device and SYCL context
/// objects.
///
/// @param adevice SYCL device.
/// @param acontext SYCL context.
/// @returns Engine object for the @p adevice SYCL device, within the
///     specified @p acontext SYCL context.
engine make_engine(
        const cl::sycl::device &adevice, const cl::sycl::context &acontext);

/// Returns the SYCL device underlying a specified engine object.
///
/// @param aengine Engine object.
/// @returns SYCL device object underlying the @p aengine engine
///     object.
cl::sycl::device get_device(const engine &aengine);

/// Returns the SYCL context underlying a specified engine object.
///
/// @param aengine Engine object.
/// @returns SYCL context object underlying the @p aengine engine object.
cl::sycl::context get_context(const engine &aengine);

/// @} dnnl_sycl_interop_api_engine

/// @addtogroup dnnl_sycl_interop_api_stream
///
/// oneDNN stream API with SYCL interoperability.
///
/// @{

/// Creates a stream for a specified engine and SYCL queue objects.
///
/// @param aengine Engine object to use for the stream.
/// @param aqueue SYCL queue to use for the stream.
/// @returns Stream object for the @p aengine engine object, which holds the @p
///     aqueue SYCL queue object.
stream make_stream(const engine &aengine, cl::sycl::queue &aqueue);

/// Returns the SYCL queue underlying a specified stream object.
///
/// @param astream Stream object.
/// @returns SYCL queue underlying the @p astream stream object.
cl::sycl::queue get_queue(const stream &astream);

/// @} dnnl_sycl_interop_api_stream

/// @addtogroup dnnl_sycl_interop_api_memory
///
/// oneDNN memory API with SYCL interoperability.
///
/// @{

/// Creates a memory object of a specified description and of a specified memory
/// allocation kind, for a specified engine.
///
/// @param adesc Memory descriptor that describes the data.
/// @param aengine Engine to store the data on.
/// @param akind Memory allocation kind.
/// @param ahandle Handle of the memory data to use. This parameter is optional.
///     By default, the underlying memory buffer is allocated internally, its
///     memory allocation kind is #dnnl::sycl_interop::memory_kind::usm_device,
///     and the library owns the buffer. If @p handle is provided, the library
///     does not own the buffer.
///
/// @note
///     If @p handle is provided, and @p akind is
///     #dnnl::sycl_interop::memory_kind::buffer, an exception is thrown.
///
/// @returns Memory object described by @p adesc memory descriptor, which is
///     stored on the @p aengine engine object, and is of @p akind memory
///     allocation kind.
memory make_memory(const memory::desc &adesc, const engine &aengine,
        memory_kind akind, void *ahandle = DNNL_MEMORY_ALLOCATE);

/// Creates a memory object of a specified description and of a specified memory
/// allocation kind, for a specified stream.
///
/// @param adesc Memory descriptor that describes the data.
/// @param astream Stream object where the data is used.
/// @param akind Memory allocation kind.
/// @param ahandle Handle of the memory data to use. This parameter is optional.
///     By default, the underlying memory buffer is allocated internally, its
///     memory allocation kind is #dnnl::sycl_interop::memory_kind::usm_device,
///     and the library owns the buffer. If @p handle is provided, the library
///     does not own the buffer.
///
/// @note
///     If @p handle is provided, and @p akind is
///     #dnnl::sycl_interop::memory_kind::buffer, an exception is thrown.
///
/// @returns Memory object described by @p adesc memory descriptor, is in the @p
///     astream stream, and is of @p akind memory allocation kind.
memory make_memory(const memory::desc &adesc, const stream &astream,
        memory_kind akind, void *ahandle = DNNL_MEMORY_ALLOCATE);

/// Creates a memory object using a specified SYCL buffer.
///
/// @note
///     When such memory object is created, it is implied that its memory
///     allocation kind is #dnnl::sycl_interop::memory_kind::buffer.
///
/// @tparam T Data type of the specified SYCL buffer.
/// @tparam ndims Number of dimensions of the specified SYCL buffer.
/// @param adesc Memory descriptor that describes the data within the specified
///     buffer.
/// @param aengine Engine to store the data on.
/// @param abuffer SYCL buffer.
/// @param astream Stream object where the data is used.
/// @returns Memory object which holds a @p abuffer SYCL buffer described by the
/// @p adesc memory descriptor, stored on the @p aengine engine and used within
///     the @p astream stream.
template <typename T, int ndims>
memory make_memory(const memory::desc &adesc, const engine &aengine,
        cl::sycl::buffer<T, ndims> abuffer, stream &astream);

/// Returns the memory allocation kind of a specified memory object.
///
/// @note
///     The memory allocation kind of a memory object could be changed during
///     its lifetime, by setting the USM handle or SYCL buffer of said memory
///     object.
///
/// @param amemory Memory object.
/// @returns Memory allocation kind of the @p amemory memory object.
memory_kind get_memory_kind(const memory &amemory);

/// Sets the SYCL buffer underlying a specified memory object.
///
/// @note
///     By setting the SYCL buffer of a memory object its memory allocation kind
///     will be changed to #dnnl::sycl_interop::memory_kind::buffer.
///
/// @tparam T Data type of the specified SYCL buffer.
/// @tparam ndims Number of dimensions of the specified SYCL buffer.
/// @param amemory Memory object that will store the @p abuffer SYCL buffer.
/// @param abuffer SYCL buffer to be stored in the @p amemory memory object.
template <typename T, int ndims>
void set_buffer(memory &amemory, cl::sycl::buffer<T, ndims> abuffer);

/// Sets the SYCL buffer underlying a specified memory object in a specified
/// stream.
///
/// @tparam T Data type of the specified SYCL buffer.
/// @tparam ndims Number of dimensions of the specified SYCL buffer.
/// @param amemory Memory object that will store the @p abuffer SYCL buffer.
/// @param abuffer SYCL buffer to be stored in the @p amemory memory object and
///     used in the @p astream stream.
/// @param astream Stream object within which the @p amemory memory object is
///     used.
template <typename T, int ndims>
void set_buffer(
        memory &amemory, cl::sycl::buffer<T, ndims> abuffer, stream &astream);

/// Returns the SYCL buffer underlying a specified memory object.
///
/// @tparam T Data type of the specified SYCL buffer.
/// @tparam ndims Number of dimensions of the specified buffer.
/// @param amemory Memory object.
/// @return SYCL buffer of type @p T with @p ndims dimensions, underlying the @p
///     amemory memory object.
template <typename T, int ndims = 1>
cl::sycl::buffer<T, ndims> get_buffer(const memory &amemory);

/// @}

/// @addtogroup dnnl_sycl_interop_api_primitives
///
/// oneDNN primitive API with SYCL interoperability.
///
/// @{

/// Executes computations using a specified primitive object in a specified
/// stream.
///
/// Arguments are passed via an arguments map containing <index, memory object>
/// pairs. The index must be one of the `DNNL_ARG_*` values such as
/// `DNNL_ARG_SRC`, and the memory must have a memory descriptor matching the
/// one returned by #dnnl::primitive_desc_base::query_md(#query::exec_arg_md,
/// index) unless using dynamic shapes (see #DNNL_RUNTIME_DIM_VAL).
///
/// @param aprimitive Primitive to be executed.
/// @param astream Stream object. The stream must belong to the same engine as
///     the primitive.
/// @param args Arguments map.
/// @param dependencies Vector of SYCL events that the execution depends on.
/// @returns SYCL event object for the specified primitive execution.
cl::sycl::event execute(const primitive &aprimitive, const stream &astream,
        const std::unordered_map<int, memory> &args,
        const std::vector<cl::sycl::event> &dependencies = {});

/// @} dnnl_sycl_interop_api_primitives

} // namespace sycl_interop
} // namespace dnnl

/// @} dnnl_sycl_interop_api

#endif
