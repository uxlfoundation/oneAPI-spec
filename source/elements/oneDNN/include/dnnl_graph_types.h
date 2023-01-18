// Copyright 2022 Intel Corporation
// SPDX-FileCopyrightText: 2022 Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

/// @file
/// oneDNN types specific to Graph extension

#ifndef DNNL_GRAPH_TYPES_H
#define DNNL_GRAPH_TYPES_H

#include "dnnl_common_types.h"

/// @addtogroup dnnl_graph_api
/// @{


/// Allocation call-back function interface for host.
typedef void *(*dnnl_graph_host_allocate_f)(size_t size, size_t alignment);

/// Deallocation call-back function interface for host.
typedef void (*dnnl_graph_host_deallocate_f)(void *);

/// @addtogroup dnnl_graph_api_sycl_interop
/// @{

/// Allocation call-back function interface for SYCL. SYCL allocator
/// should be used for SYCL devices. The call-back should return a USM
/// device memory pointer.
typedef void *(*dnnl_graph_sycl_allocate_f)(
        size_t size, size_t alignment, const void *dev, const void *context);

/// Deallocation call-back function interface for SYCL. SYCL allocator
/// should be used for SYCL devices. The call-back should deallocate a
/// USM device memory returned by #dnnl_graph_sycl_allocate_f.
typedef void (*dnnl_graph_sycl_deallocate_f)(
        void *buf, const void *dev, const void *context, void *event);

/// @} dnnl_graph_api_sycl_interop

/// A wildcard value for number of dimensions which is unknown at a tensor or
/// operation creation time.
#define DNNL_GRAPH_UNKNOWN_NDIMS -1

/// A wildcard value for dimensions that are unknown at a tensor or operation
/// creation time.
#define DNNL_GRAPH_UNKNOWN_DIM INT64_MIN

/// @} dnnl_graph_api

#endif
