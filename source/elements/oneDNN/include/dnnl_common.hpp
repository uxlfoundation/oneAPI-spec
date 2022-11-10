// Copyright 2022 Intel Corporation
// SPDX-FileCopyrightText: 2022 Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

/// @file
/// oneDNN common API between primitive and graph extension

#ifndef DNNL_COMMON_HPP
#define DNNL_COMMON_HPP

/// @cond DO_NOT_DOCUMENT_THIS
#include <algorithm>
#include <iterator>
#include <memory>

/// @endcond

/// @addtogroup dnnl_api oneDNN API
/// @{

/// oneDNN namespace
namespace dnnl {

/// @addtogroup dnnl_api_common Common API
/// @{

/// @addtogroup dnnl_api_utils Utilities
/// Utility types and definitions.
/// @{

/// oneDNN exception class.
///
/// This class captures the status returned by a failed function call
  struct error : public std::exception {};

/// @} dnnl_api_utils

/// @addtogroup dnnl_api_engine Engine
///
/// An abstraction of a computational device: a CPU, a specific GPU
/// card in the system, etc. Most primitives are created to execute
/// computations on one specific engine. The only exceptions are reorder
/// primitives that transfer data between two different engines.
///
/// @{

/// An execution engine.
  struct engine {
    /// Kinds of engines.
    enum class kind {
        /// An unspecified engine
        any,
        /// CPU engine
        cpu,
        /// GPU engine
        gpu,
    };

    /// Constructs an empty engine. An empty engine cannot be used in any
    /// operations.
    engine() = default;

    /// Returns the number of engines of a certain kind.
    ///
    /// @param akind The kind of engines to count.
    /// @returns The number of engines of the specified kind.
    static size_t get_count(kind akind);

    /// Constructs an engine.
    ///
    /// @param akind The kind of engine to construct.
    /// @param index The index of the engine. Must be less than the value
    ///     returned by #get_count() for this particular kind of engine.
    engine(kind akind, size_t index);

    /// Returns the kind of the engine.
    /// @returns The kind of the engine.
    kind get_kind() const;
};

/// @} dnnl_api_engine

/// @addtogroup dnnl_api_stream Stream
///
/// An encapsulation of execution context tied to a particular engine.
///
/// @{


/// An execution stream.
struct stream {
    /// Stream flags. Can be combined using the bitwise OR operator.
    enum class flags : unsigned {
        /// In-order execution.
        in_order,
        /// Out-of-order execution.
        out_of_order,
        /// Default stream configuration.
        default_flags,
    };

    /// Constructs an empty stream. An empty stream cannot be used in any
    /// operations.
    stream();

    /// Constructs a stream for the specified engine and with behavior
    /// controlled by the specified flags.
    ///
    /// @param aengine Engine to create the stream on.
    /// @param aflags Flags controlling stream behavior.
    stream(const engine &aengine, flags aflags = flags::default_flags);

    /// @returns The associated engine.
    engine get_engine() const;

    /// Waits for all primitives executing in the stream to finish.
    /// @returns The stream itself.
    stream &wait();

};

/// @} dnnl_api_stream

/// @addtogroup dnnl_api_fpmath_mode Floating-point Math Mode
/// @{

/// Floating-point math mode
enum class fpmath_mode {
    /// Default behavior, no downconversions allowed
    strict,
    /// Implicit f32->bf16 conversions allowed
    bf16,
    /// Implicit f32->f16 conversions allowed
    f16,
    /// Implicit f32->tf32 conversions allowed
    tf32,
    /// Implicit f32->f16 or f32->bf16 conversions allowed
    any
};

/// @} dnnl_api_fpmath_mode

/// @} dnnl_api_common

} // namespace dnnl

/// @} dnnl_api

#endif
