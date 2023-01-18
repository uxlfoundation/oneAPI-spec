// Copyright 2022 Intel Corporation
// SPDX-FileCopyrightText: 2022 Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

#ifndef DNNL_GRAPH_SYCL_HPP
#define DNNL_GRAPH_SYCL_HPP

#include <vector>

#include <CL/sycl.hpp>

#include "dnnl_graph.hpp"

/// @addtogroup dnnl_graph_api
/// @{

namespace dnnl {
namespace graph {

/// @addtogroup dnnl_graph_api_interop Runtime interoperability API
/// API extensions to interact with the underlying run-time.
/// @{

/// @addtogroup dnnl_graph_api_sycl_interop SYCL interoperability API
/// API extensions to interact with the underlying SYCL run-time.
///
/// @{

/// SYCL interoperability namespace
namespace sycl_interop {

/// Constructs an allocator from SYCL malloc and free function pointer. SYCL
/// allocator  should be used for SYCL runtime and host allocator should be used
/// for non-SYCL. Currently, only device USM allocator is supported.
///
/// @param sycl_malloc The pointer to SYCL malloc function
/// @param sycl_free The pointer to SYCL free function
/// @returns Created allocator
inline allocator make_allocator(dnnl_graph_sycl_allocate_f sycl_malloc,
				dnnl_graph_sycl_deallocate_f sycl_free);

inline dnnl::engine make_engine_with_allocator(const sycl::device &adevice,
					       const sycl::context &acontext, const allocator &alloc);

/// Executes a compiled partition in a specified stream and returns a SYCL
/// event.
///
/// @param c_partition Compiled partition to execute.
/// @param astream Stream object to run over
/// @param inputs Arguments map.
/// @param outputs Arguments map.
/// @param deps Optional vector with `sycl::event` dependencies.
/// @returns Output event.
inline sycl::event execute(compiled_partition &c_partition, stream &astream,
        const std::vector<tensor> &inputs, std::vector<tensor> &outputs,
			   const std::vector<sycl::event> &deps = {});

} // namespace sycl_interop

/// @} dnnl_graph_api_sycl_interop

/// @} dnnl_graph_api_interop

} // namespace graph
} // namespace dnnl

/// @} dnnl_graph_api

#endif
