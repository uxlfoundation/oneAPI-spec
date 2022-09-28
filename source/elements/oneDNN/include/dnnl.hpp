// Copyright 2016-2020 Intel Corporation
// SPDX-FileCopyrightText: 2016-2020 Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

/// @file
/// oneDNN API

#ifndef DNNL_HPP
#define DNNL_HPP

/// @cond DO_NOT_DOCUMENT_THIS
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <vector>
#include <unordered_map>

/// @endcond

#include "dnnl.h"

/// @addtogroup dnnl_api oneDNN API
/// @{

/// oneDNN namespace
namespace dnnl {

/// @addtogroup dnnl_api_utils Utilities
/// Utility types and definitions.
/// @{

/// The exception class.
struct error : public std::exception {};

/// @} dnnl_api_utils

struct stream;
struct memory;
struct primitive_desc_base;

/// @addtogroup dnnl_api_primitives Primitives
/// Compute primitives
/// @{

/// @addtogroup dnnl_api_primitives_common Common
/// Common operations to create, destroy and inspect primitives
/// @{

/// Base class for all computational primitives.
struct primitive {
    /// Kinds of primitives supported by the library.
    enum class kind {
        /// Undefined primitive
        undef,
        /// A reorder primitive.
        reorder,
        /// A shuffle primitive.
        shuffle,
        /// A (out-of-place) tensor concatenation primitive.
        concat,
        /// A summation primitive.
        sum,
        /// A convolution primitive.
        convolution,
        /// A deconvolution primitive.
        deconvolution,
        /// An element-wise primitive.
        eltwise,
        /// A softmax primitive.
        softmax,
        /// A pooling primitive.
        pooling,
        /// A PReLU primitive.
        prelu,
        /// An LRN primitive.
        lrn,
        /// A batch normalization primitive.
        batch_normalization,
        /// A layer normalization primitive.
        layer_normalization,
        /// An inner product primitive.
        inner_product,
        /// An RNN primitive.
        rnn,
        /// A binary primitive.
        binary,
        /// A matmul (matrix multiplication) primitive.
        matmul,
        /// A resampling primitive.
        resampling,
    };

    /// Default constructor. Constructs an empty object.
    primitive();

    /// Constructs a primitive from a primitive descriptor.
    ///
    /// @param pd Primitive descriptor.
    primitive(const primitive_desc_base &pd);

    /// Returns the kind of the primitive.
    ///
    /// @returns The primitive kind.
    inline kind get_kind() const;

    /// Executes computations specified by the primitive in a specified stream.
    ///
    /// Arguments are passed via an arguments map containing <index, memory
    /// object> pairs. The index must be one of the `DNNL_ARG_*` values such
    /// as `DNNL_ARG_SRC`, and the memory must have a memory descriptor
    /// matching the one returned by
    /// #dnnl::primitive_desc_base::query_md(#query::exec_arg_md, index)
    /// unless using dynamic shapes (see #DNNL_RUNTIME_DIM_VAL).
    ///
    /// @param astream Stream object. The stream must belong to the same engine
    ///     as the primitive.
    /// @param args Arguments map.
    void execute(const stream &astream,
            const std::unordered_map<int, memory> &args) const;

    /// Assignment operator.
    primitive &operator=(const primitive &rhs);
};

/// @} dnnl_api_primitives_common

/// @addtogroup dnnl_api_attributes
///
/// A container for parameters that extend primitives behavior.
///
/// Attributes can also contain Post-ops, which are computations executed
/// after the primitive.
///
/// @{

/// Scratchpad mode.
enum class scratchpad_mode {
    /// The library manages the scratchpad allocation. There may be multiple
    /// implementation-specific policies that can be configured via mechanisms
    /// that fall outside of the scope of this specification.
    library,
    /// The user manages the scratchpad allocation by querying and providing
    /// the scratchpad memory to primitives. This mode is thread-safe as long
    /// as the scratchpad buffers are not used concurrently by two primitive
    /// executions.
    user,
};

/// Propagation kind.
enum class prop_kind {
    /// Undefined propagation kind.
    undef,
    /// Forward data propagation (training mode). In this mode, primitives
    /// perform computations necessary for subsequent backward propagation.
    forward_training,
    /// Forward data propagation (inference mode). In this mode, primitives
    /// perform only computations that are necessary for inference and omit
    /// computations that are necessary only for backward propagation.
    forward_inference,
    /// Forward data propagation,
    /// alias for #dnnl::prop_kind::forward_inference.
    forward_scoring,
    /// Forward data propagation,
    /// alias for #dnnl::prop_kind::forward_training.
    forward,
    /// Backward propagation (with respect to all parameters).
    backward,
    /// Backward data propagation.
    backward_data,
    /// Backward weights propagation.
    backward_weights,
    /// Backward bias propagation.
    backward_bias
};

/// Kinds of algorithms.
enum class algorithm {
    /// Undefined algorithm
    undef,
    /// Convolution algorithm that is chosen to be either direct or Winograd
    /// automatically
    convolution_auto,
    /// Direct convolution
    convolution_direct,
    /// Winograd convolution
    convolution_winograd,
    /// Direct deconvolution
    deconvolution_direct,
    /// Winograd deconvolution
    deconvolution_winograd,
    /// Elementwise: rectified linear unit (ReLU)
    eltwise_relu,
    /// Elementwise: hyperbolic tangent non-linearity (tanh)
    eltwise_tanh,
    /// Elementwise: exponential linear unit (ELU)
    eltwise_elu,
    /// Elementwise: square
    eltwise_square,
    /// Elementwise: abs
    eltwise_abs,
    /// Elementwise: square root
    eltwise_sqrt,
    /// Elementwise: swish (\f$x \cdot sigmoid(a \cdot x)\f$)
    eltwise_swish,
    /// Elementwise: linear
    eltwise_linear,
    /// Elementwise: bounded_relu
    eltwise_bounded_relu,
    /// Elementwise: soft_relu
    eltwise_soft_relu,
    /// Elementwise: logistic
    eltwise_logistic,
    /// Elementwise: exponent
    eltwise_exp,
    /// Elementwise: gelu
    /// alias for #dnnl::algorithm::eltwise_gelu_tanh
    eltwise_gelu,
    /// Elementwise: tanh-based gelu
    eltwise_gelu_tanh,
    /// Elementwise: erf-based gelu
    eltwise_gelu_erf,
    /// Elementwise: natural logarithm
    eltwise_log,
    /// Elementwise: clip
    eltwise_clip,
    /// Elementwise: pow
    eltwise_pow,
    /// Elementwise: round
    eltwise_round,
    /// Elementwise: rectified linear unit (ReLU) (dst for backward)
    eltwise_relu_use_dst_for_bwd,
    /// Elementwise: hyperbolic tangent non-linearity (tanh) (dst for backward)
    eltwise_tanh_use_dst_for_bwd,
    /// Elementwise: exponential linear unit (ELU) (dst for backward)
    eltwise_elu_use_dst_for_bwd,
    /// Elementwise: square root (dst for backward)
    eltwise_sqrt_use_dst_for_bwd,
    /// Elementwise: logistic (dst for backward)
    eltwise_logistic_use_dst_for_bwd,
    /// Elementwise: exponent (dst for backward)
    eltwise_exp_use_dst_for_bwd,
    /// Local response normalization (LRN) across multiple channels
    lrn_across_channels,
    /// LRN within a single channel
    lrn_within_channel,
    /// Max pooling
    pooling_max,
    /// Average pooling exclude padding,
    /// alias for #dnnl::algorithm::pooling_avg_include_padding
    pooling_avg,
    /// Average pooling include padding
    pooling_avg_include_padding,
    /// Average pooling exclude padding
    pooling_avg_exclude_padding,
    /// RNN cell
    vanilla_rnn,
    /// LSTM cell
    vanilla_lstm,
    /// GRU cell
    vanilla_gru,
    /// GRU cell with linear before reset. Differs from original GRU
    /// in how the new memory gate is calculated:
    /// \f$c_t = tanh(W_c*x_t + b_{c_x} + r_t*(U_c*h_{t-1}+b_{c_h})) \f$
    /// LRB GRU expects 4 bias tensors on input:
    /// \f$[b_{u}, b_{r}, b_{c_x}, b_{c_h}]\f$
    lbr_gru,
    /// Binary add
    binary_add,
    /// Binary mul
    binary_mul,
    /// Binary max
    binary_max,
    /// Binary min
    binary_min,
    /// Binary div
    binary_div,
    /// Binary sub
    binary_sub,
    /// Binary greater than or equal
    binary_ge,
    /// Binary greater than
    binary_gt,
    /// Binary less than or equal
    binary_le,
    /// Binary less than
    binary_lt,
    /// Binary equal
    binary_eq,
    /// Binary not equal
    binary_ne,
    /// Nearest Neighbor resampling method
    resampling_nearest,
    /// Linear (Bilinear, Trilinear) resampling method
    resampling_linear,
    /// Reduction using max operation
    reduction_max,
    /// Reduction using min operation
    reduction_min,
    /// Reduction using sum operation
    reduction_sum,
    /// Reduction using mul operation
    reduction_mul,
    /// Reduction using mean operation
    reduction_mean,
    /// Reduction using norm_lp_max operation
    reduction_norm_lp_max,
    /// Reduction using norm_lp_sum operation
    reduction_norm_lp_sum,
    /// Reduction using norm_lp_power_p_max operation
    reduction_norm_lp_power_p_max,
    /// Reduction using norm_lp_power_p_sum operation
    reduction_norm_lp_power_p_sum,
    /// Softmax, numerically stable
    softmax_accurate = dnnl_softmax_accurate,
    /// LogSoftmax, numerically stable
    softmax_log = dnnl_softmax_log,
};

/// @} dnnl_api_attributes

/// @addtogroup dnnl_api_primitives_common
/// @{

/// Flags for normalization primitives (can be combined via '|')
enum class normalization_flags : unsigned {
    /// Use no normalization flags. If specified, the library computes mean and
    /// variance on forward propagation for training and inference, outputs them
    /// on forward propagation for training, and computes the respective
    /// derivatives on backward propagation.
    none,

    /// Use global statistics. If specified, the library uses mean and
    /// variance provided by the user as an input on forward propagation and
    /// does not compute their derivatives on backward propagation. Otherwise,
    /// the library computes mean and variance on forward propagation for
    /// training and inference, outputs them on forward propagation for
    /// training, and computes the respective derivatives on backward
    /// propagation.
    use_global_stats,

    /// Use scale and shift parameters. If specified, the user is expected to
    /// pass scale and shift as inputs on forward propagation. On backward
    /// propagation of type #dnnl::prop_kind::backward, the library computes
    /// their derivatives. If not specified, the scale and shift parameters
    /// are not used by the library in any way.
    use_scale_shift,

    /// Fuse normalization with ReLU. On training, normalization will require
    /// the workspace to implement backward propagation. On inference, the
    /// workspace is not required and behavior is the same as when normalization
    /// is fused with ReLU using the post-ops API.
    fuse_norm_relu,
};

/// Bitwise OR operation for batch normalization flags.
normalization_flags operator|(normalization_flags lhs, normalization_flags rhs);

/// @} dnnl_api_primitives_common

/// @addtogroup dnnl_api_rnn
/// @{

/// RNN cell flags.
enum class rnn_flags : unsigned {
    /// Undefined RNN flags
    undef,
};

/// Bitwise OR operation for RNN cell flags.
rnn_flags operator|(rnn_flags lhs, rnn_flags rhs);

/// A direction of RNN primitive execution.
enum class rnn_direction {
    /// Unidirectional execution of RNN primitive from left to right.
    unidirectional_left2right,
    /// Unidirectional execution of RNN primitive from right to left.
    unidirectional_right2left,
    /// Bidirectional execution of RNN primitive with concatenation of the
    /// results.
    bidirectional_concat,
    /// Bidirectional execution of RNN primitive with summation of the
    /// results.
    bidirectional_sum,
    /// Alias for #dnnl::rnn_direction::unidirectional_left2right
    unidirectional = unidirectional_left2right,
};

/// @} dnnl_api_rnn

/// @addtogroup dnnl_api_primitives_common
/// @{

/// Primitive descriptor query specification.
enum class query {
    /// no query
    undef,

    /// memory required for scratchpad (bytes)
    memory_consumption_s64,

    /// implementation name
    impl_info_str,

    /// source memory desc
    src_md,
    /// source gradient (diff) memory desc
    diff_src_md,
    /// weights memory descriptor desc
    weights_md,
    /// weights gradient (diff) memory desc
    diff_weights_md,
    /// destination memory desc
    dst_md,
    /// destination gradient (diff) memory desc
    diff_dst_md,
    /// workspace memory desc
    workspace_md,
    /// scratchpad memory desc
    scratchpad_md,
    /// memory desc of an execute argument
    exec_arg_md,
};

/// @} dnnl_api_primitives_common

/// @} dnnl_api_primitives

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
    engine();

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

    /// Waits for all primitives executing in the stream to finish.
    /// @returns The stream itself.
    stream &wait();
};

/// @} dnnl_api_stream

/// @addtogroup dnnl_api_memory Memory
///
/// A container that describes and stores data. Memory objects can contain
/// data of various types and formats. There are two levels of abstraction:
///
/// 1. **Memory descriptor** -- engine-agnostic logical description of data
///     (number of dimensions, dimension sizes, and data type), and,
///     optionally, the information about the physical format of data in
///     memory. If this information is not known yet, a memory descriptor can
///     be created with #dnnl::memory::format_tag::any. This allows
///     compute-intensive primitives to choose the best format for
///     computation. The user is responsible for reordering the data into the
///     chosen format when formats do not match.
///
///     A memory descriptor can be initialized either by specifying dimensions
///     and a memory format tag or strides for each of them, or by
///     manipulating the dnnl_memory_desc_t structure directly.
///
///
///     The user can query the amount of memory required by a memory
///     descriptor using the #dnnl::memory::desc::get_size() function. The
///     size of data in general cannot be computed as the product of
///     dimensions multiplied by the size of the data type. So users are
///     required to use this function for better code portability.
///
///     Two memory descriptors can be compared using the equality and
///     inequality operators.  The comparison is especially useful when
///     checking whether it is necessary to reorder data from the user's data
///     format to a primitive's format.
///
/// 2. **Memory object** -- an engine-specific object that handles the memory
///     buffer and its description (a memory descriptor). For the CPU engine or
///     with USM, the memory buffer handle is simply a pointer to @c void. The
///     memory buffer can be queried using #dnnl::memory::get_data_handle() and
///     set using #dnnl::memory::set_data_handle(). The underlying SYCL buffer,
///     when used, can be queried using #dnnl::sycl_interop::get_buffer and set
///     using #dnnl::sycl_interop::set_buffer. A memory object can also be
///     queried for the underlying memory descriptor and for its engine using
///     #dnnl::memory::get_desc() and dnnl::memory::get_engine().
///
/// Along with ordinary memory descriptors with all dimensions being positive,
/// the library supports *zero-volume*  memory descriptors with one or more
/// dimensions set to zero. This is used to support the NumPy\* convention.
/// If a zero-volume memory is passed to a primitive, the primitive typically
/// does not perform any computations with this memory. For example:
///
/// - A concatenation primitive would ignore all memory object with zeroes in
///   the concat dimension / axis.
///
/// - A forward convolution with a source memory object with zero in the
///   minibatch dimension would always produce a destination memory object
///   with a zero in the minibatch dimension and perform no computations.
///
/// - However, a forward convolution with a zero in one of the weights
///   dimensions is ill-defined and is considered to be an error by the
///   library because there is no clear definition of what the output values
///   should be.
///
/// Memory buffer of a zero-volume memory is never accessed.
///
/// @{

/// Memory object.
///
/// A memory object encapsulates a handle to a memory buffer allocated on a
/// specific engine, tensor dimensions, data type, and memory format, which is
/// the way tensor indices map to offsets in linear memory space. Memory
/// objects are passed to primitives during execution.
struct memory {
    /// Integer type for representing dimension sizes and indices.
    using dim = int64_t;
    /// Vector of dimensions. Implementations are free to force a limit on the
    /// vector's length.
    using dims = std::vector<dim>;

    /// Data type specification.
    enum class data_type {
        /// Undefined data type (used for empty memory descriptors).
        undef,
        /// [16-bit/half-precision floating point](https://en.wikipedia.org/wiki/Half-precision_floating-point_format).
        f16,
        /// non-standard
        /// [16-bit floating point with 7-bit mantissa](https://en.wikipedia.org/wiki/Bfloat16_floating-point_format).
        bf16,
        /// [32-bit/single-precision floating point](https://en.wikipedia.org/wiki/Single-precision_floating-point_format).
        f32,
        /// 32-bit signed integer.
        s32,
        /// 8-bit signed integer.
        s8,
        /// 8-bit unsigned integer.
        u8,
    };

    /// Memory format tag specification.
    ///
    /// Memory format tags can be further divided into two categories:
    ///
    ///  - Domain-agnostic names, i.e. names that do not depend on the tensor
    ///    usage in the specific primitive. These names use letters from `a`
    ///    to `f` to denote logical dimensions and form the order in which the
    ///    dimensions are laid in memory. For example,
    ///    #dnnl::memory::format_tag::ab is used to denote a 2D tensor where the
    ///    second logical dimension (denoted as `b`) is the innermost, i.e.
    ///    has stride = 1, and the first logical dimension (`a`) is laid out in
    ///    memory with stride equal to the size of the second dimension. On the
    ///    other hand, #dnnl::memory::format_tag::ba is the transposed version
    ///    of the same tensor: the outermost dimension (`a`) becomes the
    ///    innermost one.
    ///
    ///  - Domain-specific names, i.e. names that make sense only in the
    ///    context of a certain domain, such as CNN. These names are
    ///    aliases to the corresponding domain-agnostic tags and used mostly
    ///    for convenience. For example, #dnnl::memory::format_tag::nc
    ///    is used to denote 2D CNN activations tensor memory format, where
    ///    the channels dimension is the innermost one and the batch dimension
    ///    is the outermost one. Moreover, #dnnl::memory::format_tag::nc is
    ///    an alias for #dnnl::memory::format_tag::ab, because for
    ///    CNN primitives the logical dimensions of activations tensors come
    ///    in order: batch, channels, spatial.  In other words, batch
    ///    corresponds to the first logical dimension (`a`), and channels
    ///    correspond to the second one (`b`).
    ///
    /// The following domain-specific notation applies to memory format tags:
    ///  - @c 'n' denotes the mini-batch dimension
    ///  - @c 'c' denotes a channels dimension
    ///  - When there are multiple channel dimensions (for example,
    ///    in convolution weights tensor), @c 'i' and @c 'o' denote dimensions
    ///    of input and output channels
    ///  - @c 'g' denotes a groups dimension for convolution weights
    ///  - @c 'd', @c 'h', and @c 'w' denote spatial depth, height, and width
    ///    respectively
    ///
    enum class format_tag {
        /// Undefined memory format tag
        undef,
        /// Placeholder memory format tag. Used to instruct the primitive to
        /// select a format automatically.
        any,

        /// plain 1D tensor
        a,

        /// plain 2D tensor
        ab,
        /// permuted 2D tensor
        ba,

        /// plain 3D tensor
        abc,
        /// permuted 3D tensor
        acb,
        /// permuted 3D tensor
        bac,
        /// permuted 3D tensor
        bca,
        /// permuted 3D tensor
        cba,

        /// plain 4D tensor
        abcd,
        /// permuted 4D tensor
        abdc,
        /// permuted 4D tensor
        acdb,
        /// permuted 4D tensor
        bacd,
        /// permuted 4D tensor
        bcda,
        /// permuted 4D tensor
        cdba,
        /// permuted 4D tensor
        dcab,

        /// plain 5D tensor
        abcde,
        /// permuted 5D tensor
        abdec,
        /// permuted 5D tensor
        acbde,
        /// permuted 5D tensor
        acdeb,
        /// permuted 5D tensor
        bacde,
        /// permuted 5D tensor
        bcdea,
        /// permuted 5D tensor
        cdeba,
        /// permuted 5D tensor
        decab,
        /// plain 6D tensor
        abcdef,
        /// plain 6D tensor
        acbdef,
        /// plain 6D tensor
        defcab,

        /// 1D tensor; an alias for #dnnl::memory::format_tag::a
        x = a,
        /// 2D CNN activations tensor; an alias for #dnnl::memory::format_tag::ab
        nc = ab,
        /// 2D CNN activations tensor; an alias for #dnnl::memory::format_tag::ba
        cn = ba,
        /// 2D RNN statistics tensor; an alias for #dnnl::memory::format_tag::ab
        tn = ab,
        /// 2D RNN statistics tensor; an alias for #dnnl::memory::format_tag::ba
        nt = ba,
        /// 3D CNN activations tensor; an alias for #dnnl::memory::format_tag::abc
        ncw = abc,
        /// 3D CNN activations tensor; an alias for #dnnl::memory::format_tag::acb
        nwc = acb,
        /// 4D CNN activations tensor; an alias for #dnnl::memory::format_tag::abcd
        nchw = abcd,
        /// 4D CNN activations tensor; an alias for #dnnl::memory::format_tag::acdb
        nhwc = acdb,
        /// 4D CNN activations tensor; an alias for #dnnl::memory::format_tag::bcda
        chwn = bcda,
        /// 5D CNN activations tensor; an alias for #dnnl::memory::format_tag::abcde
        ncdhw = abcde,
        /// 5D CNN activations tensor; an alias for #dnnl::memory::format_tag::acdeb
        ndhwc = acdeb,

        /// 2D CNN weights tensor; an alias for #dnnl::memory::format_tag::ab
        oi = ab,
        /// 2D CNN weights tensor; an alias for #dnnl::memory::format_tag::ba
        io = ba,
        /// 3D CNN weights tensor; an alias for #dnnl::memory::format_tag::abc
        oiw = abc,
        /// 3D CNN weights tensor; an alias for #dnnl::memory::format_tag::acb
        owi = acb,
        /// 3D CNN weights tensor; an alias for #dnnl::memory::format_tag::cba
        wio = cba,
        /// 3D CNN weights tensor; an alias for #dnnl::memory::format_tag::bca
        iwo = bca,
        /// 4D CNN weights tensor; an alias for #dnnl::memory::format_tag::abcd
        oihw = abcd,
        /// 4D CNN weights tensor; an alias for #dnnl::memory::format_tag::cdba
        hwio = cdba,
        /// 4D CNN weights tensor; an alias for #dnnl::memory::format_tag::acdb
        ohwi = acdb,
        /// 4D CNN weights tensor; an alias for #dnnl::memory::format_tag::bcda
        ihwo = bcda,
        /// 4D CNN weights tensor; an alias for #dnnl::memory::format_tag::bacd
        iohw = bacd,
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::abcde
        oidhw = abcde,
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::cdeba
        dhwio = cdeba,
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::acdeb
        odhwi = acdeb,
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::bacde
        iodhw = bacde,
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::bcdea
        idhwo = bcdea,

        /// 4D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcd
        goiw = abcd,
        /// 4D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::dcab
        wigo = dcab,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcde
        goihw = abcde,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::decab
        hwigo = decab,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::acbde
        giohw = acbde,
        /// 6D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcdef
        goidhw = abcdef,
        /// 6D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcdef
        giodhw = acbdef,
        /// 6D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::defcab
        dhwigo = defcab,

        /// 3D RNN data tensor in the format (seq_length, batch, input channels).
        tnc = abc,
        /// 3D RNN data tensor in the format (batch, seq_length, input channels).
        ntc = bac,
        /// 4D RNN states tensor in the format (num_layers, num_directions,
        /// batch, state channels).
        ldnc = abcd,
        /// 5D RNN weights tensor in the format (num_layers, num_directions,
        ///  input_channels, num_gates, output_channels).
        ///
        ///  - For LSTM cells, the gates order is input, forget, candidate
        ///    and output gate.
        ///  - For GRU cells, the gates order is update, reset and output gate.
        ldigo = abcde,
        /// 5D RNN weights tensor in the format (num_layers, num_directions,
        /// num_gates, output_channels, input_channels).
        ///
        ///  - For LSTM cells, the gates order is input, forget, candidate
        ///    and output gate.
        ///  - For GRU cells, the gates order is update, reset and output gate.
        ldgoi = abdec,
        /// 4D LSTM projection tensor in the format (num_layers, num_directions,
        /// num_channels_in_hidden_state, num_channels_in_recurrent_projection).
        ldio = abcd,
        /// 4D LSTM projection tensor in the format (num_layers, num_directions,
        /// num_channels_in_recurrent_projection, num_channels_in_hidden_state).
        ldoi = abdc,
        /// 4D RNN bias tensor in the format (num_layers, num_directions,
        /// num_gates, output_channels).
        ///
        ///  - For LSTM cells, the gates order is input, forget, candidate
        ///    and output gate.
        ///  - For GRU cells, the gates order is update, reset and output gate.
        ldgo = abcd,
    };

    /// A memory descriptor.
    struct desc {
        /// Constructs a zero (empty) memory descriptor. Such a memory
        /// descriptor can be used to indicate absence of an argument.
        desc();

        /// Constructs a memory descriptor.
        ///
        /// @note
        ///     The logical order of dimensions corresponds to the `abc...`
        ///     format tag, and the physical meaning of the dimensions depends
        ///     both on the primitive that would operate on this memory and
        ///     the operation context.
        ///
        /// @param adims Tensor dimensions.
        /// @param adata_type Data precision/type.
        /// @param aformat_tag Memory format tag.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case a
        ///     zero memory descriptor will be constructed. This flag is
        ///     optional and defaults to false.
        desc(const dims &adims, data_type adata_type, format_tag aformat_tag,
                bool allow_empty = false);

        /// Constructs a memory descriptor by strides.
        ///
        /// @note
        ///     The logical order of dimensions corresponds to the `abc...`
        ///     format tag, and the physical meaning of the dimensions depends
        ///     both on the primitive that would operate on this memory and
        ///     the operation context.
        ///
        /// @param adims Tensor dimensions.
        /// @param adata_type Data precision/type.
        /// @param strides Strides for each dimension.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case a
        ///     zero memory descriptor will be constructed. This flag is
        ///     optional and defaults to false.
        desc(const dims &adims, data_type adata_type, const dims &strides,
                bool allow_empty = false);

        /// Constructs a memory descriptor for a region inside an area
        /// described by this memory descriptor.
        //
        /// @param adims Sizes of the region.
        /// @param offsets Offsets to the region from the encompassing
        ///     memory object in each dimension.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case a
        ///     zero memory descriptor will be returned. This flag is optional
        ///     and defaults to false.
        /// @returns A memory descriptor for the region.
        desc submemory_desc(const dims &adims, const dims &offsets,
                bool allow_empty = false) const;

        /// Constructs a memory descriptor by reshaping an existing one. The
        /// new memory descriptor inherits the data type.
        ///
        /// The operation ensures that the transformation of the physical memory
        /// format corresponds to the transformation of the logical dimensions.
        /// If such transformation is impossible, the function either throws an
        /// exception (default) or returns a zero memory descriptor depending on
        /// the `allow_empty` flag.
        ///
        /// The reshape operation can be described as a combination of the
        /// following basic operations:
        /// 1. Add a dimension of size `1`. This is always possible.
        /// 2. Remove a dimension of size `1`.
        /// 3. Split a dimension into multiple ones. This is possible only if
        ///    the product of all tensor dimensions stays constant.
        /// 4. Join multiple consecutive dimensions into a single one.
        ///    This requires that the dimensions are dense in memory and have
        ///    the same order as their logical counterparts.
        ///    - Here, 'dense' means:
        ///      `stride for dim[i] == (stride for dim[i + 1]) * dim[i + 1]`;
        ///    - And 'same order' means:
        ///      `i < j` if and only if `stride for dim[j] <= stride for dim[i]`.
        ///
        /// @note
        ///     Reshape may fail for optimized memory formats.
        ///
        /// @param adims New dimensions. The product of dimensions must
        ///     remain constant.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case a
        ///     zero memory descriptor will be returned. This flag is optional
        ///     and defaults to false.
        /// @returns A new memory descriptor with new dimensions.
        desc reshape(const dims &adims, bool allow_empty = false) const;

        /// Constructs a memory descriptor by permuting axes in an existing
        /// one.
        ///
        /// The physical memory layout representation is adjusted accordingly
        /// to maintain the consistency between the logical and physical parts
        /// of the memory descriptor. The new memory descriptor inherits the
        /// data type.
        ///
        /// The logical axes will be permuted in the following manner:
        /// @code
        /// for (i = 0; i < ndims(); i++)
        ///     new_desc.dims()[permutation[i]] = dims()[i];
        /// @endcode
        ///
        /// Example:
        /// @code
        ///     std::vector<int> permutation = {1, 0}; // swap the first and
        ///                                            // the second axes
        ///     dnnl::memory::desc in_md(
        ///             {2, 3}, data_type, memory::format_tag::ab);
        ///     dnnl::memory::desc expect_out_md(
        ///             {3, 2}, data_type, memory::format_tag::ba);
        ///
        ///     assert(in_md.permute_axes(permutation) == expect_out_md);
        /// @endcode
        ///
        /// @param permutation Axes permutation.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case a
        ///     zero memory descriptor will be returned. This flag is optional
        ///     and defaults to false.
        /// @returns A new memory descriptor with new dimensions.
        desc permute_axes(const std::vector<int> &permutation,
                bool allow_empty = false) const;

        /// Returns dimensions of the memory descriptor.
        ///
        /// Potentially expensive due to the data copy involved.
        /// @returns A copy of the dimensions vector.
        memory::dims dims() const;

        /// Returns the data type of the memory descriptor.
        /// @returns The data type.
        memory::data_type data_type() const;

        /// Returns size of the memory descriptor in bytes.
        /// @returns The number of bytes required to allocate a memory buffer
        ///     for the memory object described by this memory descriptor.
        size_t get_size() const;

        /// Checks whether the memory descriptor is zero (empty).
        /// @returns @c true if the memory descriptor describes an empty
        ///     memory and @c false otherwise.
        bool is_zero() const;

        /// An equality operator.
        /// @param other Another memory descriptor.
        /// @returns Whether this and the other memory descriptors have
        ///     the same format tag, dimensions, strides, etc.
        bool operator==(const desc &other) const;

        /// An inequality operator.
        /// @param other Another memory descriptor.
        /// @returns Whether this and the other memory descriptors describe
        ///     different memory.
        bool operator!=(const desc &other) const;
    };

    /// Default constructor.
    ///
    /// Constructs an empty memory object, which can be used to indicate
    /// absence of a parameter.
    memory();

    /// Constructs a memory object.
    ///
    /// Unless @p handle is equal to #DNNL_MEMORY_NONE, the constructed memory
    /// object will have the underlying buffer set. In this case, the buffer
    /// will be initialized as if #dnnl::memory::set_data_handle() has been
    /// called.
    ///
    /// @sa memory::set_data_handle()
    ///
    /// @param md Memory descriptor.
    /// @param aengine Engine to store the data on.
    /// @param handle Handle of the memory buffer to use.
    ///     - A pointer to the user-allocated buffer. In this case the library
    ///       doesn't own the buffer.
    ///     - The #DNNL_MEMORY_ALLOCATE special value. Instructs the library to
    ///       allocate the buffer for the memory object. In this case the
    ///       library owns the buffer and the memory allocation kind of the
    ///       underlying buffer is
    ///       #dnnl::sycl_interop::memory_kind::usm.
    ///     - #DNNL_MEMORY_NONE to create dnnl::memory without an underlying
    ///       buffer.
    memory(const desc &md, const engine &aengine, void *handle);

    /// Constructs a memory object.
    ///
    /// The underlying buffer for the memory will be allocated by the library.
    /// The memory allocation kind of the underlying buffer is
    /// #dnnl::sycl_interop::memory_kind::usm.
    ///
    /// @param md Memory descriptor.
    /// @param aengine Engine to store the data on.
    memory(const desc &md, const engine &aengine);

    /// Returns the associated memory descriptor.
    desc get_desc() const;

    /// Returns the associated engine.
    engine get_engine() const;

    /// Returns the underlying memory buffer.
    ///
    /// On the CPU engine, or when using USM, this is a pointer to the
    /// allocated memory.
    void *get_data_handle() const;

    /// Sets the underlying memory buffer.
    ///
    /// This function may write zero values to the memory specified by the @p
    /// handle if the memory object has a zero padding area. This may be time
    /// consuming and happens each time this function is called. The
    /// operation is always blocking and the stream parameter is a hint.
    ///
    /// @note
    ///     Even when the memory object is used to hold values that stay
    ///     constant during the execution of the program (pre-packed weights
    ///     during inference, for example), the function will still write
    ///     zeroes to the padding area if it exists. Hence, the @p handle
    ///     parameter cannot and does not have a const qualifier.
    ///
    /// @param handle Memory buffer to use. On the CPU engine or when USM is
    ///     used, the memory buffer is a pointer to the actual data. It must
    ///     have at least #dnnl::memory::desc::get_size() bytes allocated.
    /// @param astream Stream to use to execute padding in.
    void set_data_handle(void *handle, const stream &astream) const;

    /// Sets the underlying memory buffer.
    ///
    /// See documentation for
    /// #dnnl::memory::set_data_handle(void *, const stream &) const
    /// for more information.
    ///
    /// @param handle Memory buffer to use. For the CPU engine, the memory
    ///     buffer is a pointer to the actual data. It must have at least
    ///     #dnnl::memory::desc::get_size() bytes allocated.
    void set_data_handle(void *handle) const;

    /// Maps a memory object and returns a host-side pointer to a memory
    /// buffer with a copy of its contents.
    ///
    /// Mapping enables read/write directly from/to the memory contents for
    /// engines that do not support direct memory access.
    ///
    /// Mapping is an exclusive operation - a memory object cannot be used in
    /// other operations until it is unmapped via #dnnl::memory::unmap_data()
    /// call.
    ///
    /// @note
    ///     Any primitives working with the memory should be completed before
    ///     the memory is mapped. Use #dnnl::stream::wait() to synchronize the
    ///     corresponding execution stream.
    ///
    /// @note
    ///     The map_data and unmap_data functions are provided mainly for
    ///     debug and testing purposes and their performance may be suboptimal.
    ///
    /// @tparam T Data type to return a pointer to.
    /// @returns Pointer to the mapped memory.
    template <typename T = void>
    T *map_data() const;

    /// Unmaps a memory object and writes back any changes made to the
    /// previously mapped memory buffer.
    ///
    /// @note
    ///     The map_data and unmap_data functions are provided mainly for
    ///     debug and testing purposes and their performance may be
    ///     suboptimal.
    ///
    /// @param mapped_ptr A pointer previously returned by
    ///     #dnnl::memory::map_data().
    void unmap_data(void *mapped_ptr) const;
};

/// @} dnnl_api_memory

/// @addtogroup dnnl_api_primitives
/// @{
/// @addtogroup dnnl_api_attributes Attributes
///
/// A container for parameters that extend primitives behavior.
///
/// @{

/// Post-ops.
///
/// Post-ops are computations executed after the main primitive computations
/// and are attached to the primitive via primitive attributes.
///
struct post_ops {
    /// Constructs an empty sequence of post-ops.
    post_ops();

    /// Returns the number of post-ops entries.
    int len() const;

    /// Returns the primitive kind of post-op at entry with a certain index.
    /// @param index Index of the post-op to return the kind for.
    /// @returns Primitive kind of the post-op at the specified index.
    primitive::kind kind(int index) const;

    /// Appends an accumulation (sum) post-op. Prior to accumulating the
    /// result, the previous value would be multiplied by a scaling factor
    /// @p scale provided as execution argument.
    ///
    /// The kind of this post-op is #dnnl::primitive::kind::sum.
    ///
    /// This feature may improve performance for cases like residual learning
    /// blocks, where the result of convolution is accumulated to the
    /// previously computed activations. The parameter @p scale may be used
    /// for the integer-based computations when the result and previous
    /// activations have different logical scaling factors.
    ///
    /// In the simplest case when the accumulation is the only post-op,
    /// the computations would be `dst[:] := scale * dst[:] + op(...)`
    /// instead of `dst[:] := op(...)`.
    ///
    /// If @p data_type is specified, the original dst tensor will be
    /// reinterpreted as a tensor with the provided data type. Because it is a
    /// reinterpretation, data_type and dst data type should have the same size.
    /// As a result, computations would be `dst[:] <- scale *
    /// as_data_type(dst[:]) + op(...)` instead of `dst[:] <- op(...)`.
    ///
    /// @note
    ///     This post-op executes in-place and does not change the
    ///     destination layout.
    ///
    /// @param data_type Data type.
    void append_sum(memory::data_type data_type = memory::data_type::undef);

    /// Returns the parameters of an accumulation (sum) post-op.
    ///
    /// @param index Index of the sum post-op.
    /// @param scale Scaling factor of the sum post-op.
    void get_params_sum(int index, float &scale) const;

    /// Returns the parameters of an accumulation (sum) post-op.
    ///
    /// @param index Index of the sum post-op.
    /// @param scale Scaling factor of the sum post-op.
    /// @param data_type Data type of the sum post-op.
    void get_params_sum(
            int index, float &scale, memory::data_type &data_type) const;

    /// Appends an elementwise post-op.
    ///
    /// The kind of this post-op is #dnnl::primitive::kind::eltwise.
    ///
    /// In the simplest case when the elementwise is the only post-op, the
    /// computations would be `dst[:] := scale * eltwise_op (op(...))` instead
    /// of `dst[:] <- op(...)`, where eltwise_op is configured with the given
    /// parameters.
    ///
    /// @param aalgorithm Elementwise algorithm.
    /// @param alpha Alpha parameter for the elementwise algorithm.
    /// @param beta Beta parameter for the elementwise algorithm.
    void append_eltwise(algorithm aalgorithm, float alpha, float beta);

    /// Returns parameters of an elementwise post-up.
    ///
    /// @param index Index of the post-op.
    /// @param aalgorithm Output elementwise algorithm kind.
    /// @param alpha Output alpha parameter for the elementwise algorithm.
    /// @param beta Output beta parameter for the elementwise algorithm.
    void get_params_eltwise(
            int index, algorithm &aalgorithm, float &alpha, float &beta) const;
};

/// Primitive attributes.
struct primitive_attr {
    /// Constructs default (empty) primitive attributes.
    primitive_attr();

    /// Returns the scratchpad mode.
    scratchpad_mode get_scratchpad_mode() const;

    /// Sets scratchpad mode.
    ///
    /// @param mode Specified scratchpad mode.
    void set_scratchpad_mode(scratchpad_mode mode);

    /// Returns scaling factors correspondence mask for a given
    /// memory argument.
    ///
    /// @param arg Parameter argument index as passed to the
    ///     primitive::execute() call.
    /// @param mask Scaling factors correspondence mask that defines the
    ///     correspondence between the arg tensor dimensions and the
    ///     scales vector.
    void get_scales(int arg, int &mask) const;

    /// Sets scaling factors correspondance mask for a given memory
    /// argument.
    ///
    /// @sa dnnl::primitive_attr::set_scales
    ///
    /// @note
    ///     The order of dimensions does not depend on how elements are laid
    ///     out in memory. For example:
    ///     - for a 2D CNN activations tensor the order is always (n, c)
    ///     - for a 4D CNN activations tensor the order is always (n, c, h, w)
    ///     - for a 5D CNN weights tensor the order is always
    ///
    /// @param arg Parameter argument index as passed to the
    ///     primitive::execute() call.
    /// @param mask Scaling factors correspondence mask that defines the
    ///     correspondence between the @p arg tensor dimensions and the
    ///     scales vector. Setting the i-th bit indicates that a dedicated scaling
    ///     factor is used for each index along that dimension. Set the mask to
    ///     0 to use a common scaling factor for the whole tensor.
    ///     The scales must be passed at execution time as an argument with index
    ///     #DNNL_ARG_ATTR_SCALES.
    void set_scales(int arg, int mask);

    /// Returns zero points correspondence mask and values.
    ///
    /// @param arg Parameter argument index as passed to the
    ///     primitive::execute() call.
    /// @param mask Zero points correspondence mask that defines the
    ///     correspondence between the @p arg tensor dimensions and the
    ///     vector of zero_points. Setting the i-th bit indicates that a
    ///     dedicated zero point is used for each index along that dimension.
    ///     Set the mask to 0 to use a common zero point for the whole tensor.
    void get_zero_points(int arg, int &mask) const;

    /// Sets zero points for primitive operations for a given memory argument.
    ///
    /// @sa dnnl::primitive_attr::set_output_scales
    ///
    /// @param arg Parameter argument index as passed to the
    ///     primitive::execute() call.
    /// @param mask Zero point correspondence mask that defines the
    ///     correspondence between the tensor dimensions and the @p
    ///     zero_points vector. The set i-th bit indicates that a dedicated
    ///     zero point is used for each index along that dimension. Set the
    ///     mask to 0 to use a common zero point for the whole output tensor.
    ///     The zero points must be passed at execution time as an argument with index
    ///     #DNNL_ARG_ATTR_ZERO_POINTS.
    void set_zero_points(int arg, int mask);

    /// Returns post-ops previously set via set_post_ops().
    ///
    /// @returns Post-ops.
    const post_ops get_post_ops() const;

    /// Sets post-ops.
    ///
    /// @note
    ///     There is no way to check whether the post-ops would be supported
    ///     by the target primitive. Any error will be reported
    ///     by the respective primitive descriptor constructor.
    ///
    /// @param ops Post-ops object to copy post-ops from.
    void set_post_ops(const post_ops ops);

    /// Sets quantization scale and shift parameters for RNN data tensors.
    ///
    /// For performance reasons, the low-precision configuration of the RNN
    /// primitives expect input activations to have the unsigned 8-bit integer
    /// data type. The scale and shift parameters are used to quantize
    /// floating-point data to unsigned integer and must be passed to the RNN
    /// primitive using attributes.
    ///
    /// The quantization formula is `scale * (data + shift)`.
    ///
    /// Example usage:
    /// @code
    ///     // RNN parameters
    ///     int l = 2, t = 2, mb = 32, sic = 32, slc = 32, dic = 32, dlc = 32;
    ///     // Activations quantization parameters
    ///     float scale = 2.0f, shift = 0.5f;
    ///
    ///     primitive_attr attr;
    ///
    ///     // Set scale and shift for int8 quantization of activation
    ///     attr.set_rnn_data_qparams(scale, shift);
    ///
    ///     // Create and configure rnn op_desc
    ///     vanilla_rnn_forward::desc rnn_d(/* arguments */);
    ///     vanilla_rnn_forward::primitive_desc rnn_d(rnn_d, attr, engine);
    /// @endcode
    ///
    /// @note
    ///     Quantization scale and shift are common for src_layer, src_iter,
    ///     dst_iter, and dst_layer.
    ///
    /// @param scale The value to scale the data by.
    /// @param shift The value to shift the data by.
    void set_rnn_data_qparams(float scale, float shift);

    /// Sets quantization scaling factors for RNN weights tensors. The
    /// low-precision configuration of the RNN primitives expect input weights
    /// to use the signed 8-bit integer data type. The scaling factors are
    /// used to quantize floating-point data to signed integer and must be
    /// passed to RNN primitives using attributes.
    ///
    /// @note
    ///     The dimension order is always native and does not depend on the
    ///     actual layout used. For example, five-dimensional weights always
    ///     have (l, d, i, g, o) logical dimension ordering.
    ///
    /// @note
    ///     Quantization scales are common for weights_layer and
    ///     weights_iteration
    ///
    /// @param mask Scaling factors correspondence mask that defines the
    ///     correspondence between the output tensor dimensions and the @p
    ///     scales vector. The set i-th bit indicates that a dedicated scaling
    ///     factor should be used each index along that dimension. Set the
    ///     mask to 0 to use a common scaling factor for the whole output
    ///     tensor.
    /// @param scales Constant vector of output scaling factors. The following
    ///     equality must hold:
    ///     \f$scales.size() = \prod\limits_{d \in mask} weights.dims[d].\f$
    ///     Violations can only be detected when the attributes are used to
    ///     create a primitive descriptor.
    void set_rnn_weights_qparams(int mask, const std::vector<float> &scales);
};

/// @} dnnl_api_attributes

/// @addtogroup dnnl_api_primitives_common
/// @{

/// Base class for all primitive descriptors.
struct primitive_desc_base {
    /// Default constructor. Produces an empty object.
    primitive_desc_base();

    /// Returns the engine of the primitive descriptor.
    /// @returns The engine of the primitive descriptor.
    engine get_engine() const;

    /// Returns implementation name.
    /// @returns The implementation name.
    const char *impl_info_str() const;

    /// Returns a memory::dim value (same as int64_t).
    /// @param what The value to query.
    /// @returns The result of the query.
    memory::dim query_s64(query what) const;

    /// Returns a memory descriptor.
    ///
    /// @note
    ///     There are also convenience methods
    ///     #dnnl::primitive_desc_base::src_desc(),
    ///     #dnnl::primitive_desc_base::dst_desc(), and others.
    ///
    /// @param what The kind of parameter to query; can be
    ///     #dnnl::query::src_md, #dnnl::query::dst_md, etc.
    /// @param idx Index of the parameter. For example, convolution bias can
    ///     be queried with what = #dnnl::query::weights_md and idx = 1.
    /// @returns The requested memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     parameter of the specified kind or index.
    memory::desc query_md(query what, int idx = 0) const;

    /// Returns a source memory descriptor.
    /// @param idx Source index.
    /// @returns Source memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     source parameter with index @p pdx.
    memory::desc src_desc(int idx) const;

    /// Returns a destination memory descriptor.
    /// @param idx Destination index.
    /// @returns Destination memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     destination parameter with index @p pdx.
    memory::desc dst_desc(int idx) const;

    /// Returns a weights memory descriptor.
    /// @param idx Weights index.
    /// @returns Weights memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     weights parameter with index @p pdx.
    memory::desc weights_desc(int idx) const;

    /// Returns a diff source memory descriptor.
    /// @param idx Diff source index.
    /// @returns Diff source memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff source parameter with index @p pdx.
    memory::desc diff_src_desc(int idx) const;

    /// Returns a diff destination memory descriptor.
    /// @param idx Diff destination index.
    /// @returns Diff destination memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff destination parameter with index @p pdx.
    memory::desc diff_dst_desc(int idx) const;

    /// Returns a diff weights memory descriptor.
    /// @param idx Diff weights index.
    /// @returns Diff weights memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff weights parameter with index @p pdx.
    memory::desc diff_weights_desc(int idx) const;

    // Separate versions without the index argument for documentation
    // purposes.

    /// Returns a source memory descriptor.
    /// @returns Source memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     source parameter.
    memory::desc src_desc() const;

    /// Returns a destination memory descriptor.
    /// @returns Destination memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     destination parameter.
    memory::desc dst_desc() const;

    /// Returns a weights memory descriptor.
    /// @returns Weights memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     weights parameter.
    memory::desc weights_desc() const;

    /// Returns a diff source memory descriptor.
    /// @returns Diff source memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff source memory with.
    memory::desc diff_src_desc() const;

    /// Returns a diff destination memory descriptor.
    /// @returns Diff destination memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff destination parameter.
    memory::desc diff_dst_desc() const;

    /// Returns a diff weights memory descriptor.
    /// @returns Diff weights memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///     diff weights parameter.
    memory::desc diff_weights_desc() const;

    /// Returns the workspace memory descriptor.
    /// @returns Workspace memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not require
    ///     workspace parameter.
    memory::desc workspace_desc() const;
    /// Returns the scratchpad memory descriptor.
    /// @returns scratchpad memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not require
    ///     scratchpad parameter.
    memory::desc scratchpad_desc() const;

    /// Returns the engine on which the scratchpad memory is located.
    /// @returns The engine on which the scratchpad memory is located.
    engine scratchpad_engine() const;

    /// Returns the primitive attributes.
    /// @returns The primitive attributes.
    primitive_attr get_primitive_attr() const;

    /// Returns the kind of the primitive descriptor.
    /// @returns The kind of the primitive descriptor.
    dnnl::primitive::kind get_kind() const;
};

/// @} dnnl_api_primitives_common

/// @addtogroup dnnl_api_reorder Reorder
///
/// A primitive to copy data between two memory objects. This primitive is
/// typically used to change the way the data is laid out in memory.
///
/// @{

/// Reorder primitive.
struct reorder : public primitive {
    /// Primitive descriptor for a reorder primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for reorder primitive.
        ///
        /// @note
        ///     If @p allow_empty is true, the constructor does not throw if a
        ///     primitive descriptor cannot be created.
        ///
        /// @param src_engine Engine on which the source memory object will be
        ///     located.
        /// @param src_md Source memory descriptor.
        /// @param dst_engine Engine on which the destination memory object
        ///     will be located.
        /// @param dst_md Destination memory descriptor.
        /// @param attr Primitive attributes to use (optional).
        /// @param allow_empty A flag signifying whether construction is allowed
        ///     to fail without throwing an exception. In this case an empty
        ///     object will be produced. This flag is optional and defaults to
        ///     false.
        primitive_desc(const engine &src_engine, const memory::desc &src_md,
                const engine &dst_engine, const memory::desc &dst_md,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// Constructs a primitive descriptor for reorder primitive.
        ///
        /// @param src Source memory object. It is used to obtain the source
        ///     memory descriptor and engine.
        /// @param dst Destination memory object. It is used to obtain the
        ///     destination memory descriptor and engine.
        /// @param attr Primitive attributes to use (optional).
        /// @param allow_empty A flag signifying whether construction is allowed
        ///     to fail without throwing an exception. In this case an empty
        ///     object will be produced. This flag is optional and defaults to
        ///     false.
        primitive_desc(const memory &src, const memory &dst,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// Returns the engine on which the source memory is allocated.
        /// @returns The engine on which the source memory is allocated.
        engine get_src_engine() const;

        /// Returns the engine on which the destination memory is allocated.
        /// @returns The engine on which the destination memory is allocated.
        engine get_dst_engine() const;

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    reorder();

    /// Constructs a reorder primitive.
    /// @param pd Primitive descriptor for reorder primitive.
    reorder(const primitive_desc &pd);

    /// Constructs a reorder primitive that would reorder data between memory
    /// objects having the same memory descriptors as memory objects @p src and
    /// @p dst.
    ///
    /// @param src Source memory object.
    /// @param dst Destination memory object.
    /// @param attr Primitive attributes to use (optional).
    reorder(const memory &src, const memory &dst,
            const primitive_attr &attr = primitive_attr());

    /// Executes the reorder primitive.
    ///
    /// @param astream Stream object. The stream must belong to the same engine
    ///     as the primitive.
    /// @param src Source memory object.
    /// @param dst Destination memory object.
    void execute(const stream &astream, memory &src, memory &dst) const;
};

/// @} dnnl_api_reorder

/// @addtogroup dnnl_api_concat Concat
///
/// A primitive to concatenate data by arbitrary dimension.
///
/// @{

/// Tensor concatenation (concat) primitive.
struct concat : public primitive {
    /// Primitive descriptor for a concat primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an out-of-place concatenation
        /// primitive.
        ///
        /// @param dst Destination memory descriptor.
        /// @param concat_dimension Source tensors will be concatenated over
        ///     dimension with this index. Note that order of dimensions does
        ///     not depend on memory format.
        /// @param srcs Vector of source memory descriptors.
        /// @param aengine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const memory::desc &dst, int concat_dimension,
                const std::vector<memory::desc> &srcs, const engine &aengine,
                const primitive_attr &attr = primitive_attr());

        /// Constructs a primitive descriptor for an out-of-place concatenation
        /// primitive.
        ///
        /// This version derives the destination memory descriptor
        /// automatically.
        ///
        /// @param concat_dimension Source tensors will be concatenated over
        ///     dimension with this index. Note that order of dimensions does
        ///     not depend on memory format.
        /// @param srcs Vector of source memory descriptors.
        /// @param aengine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(int concat_dimension,
                const std::vector<memory::desc> &srcs, const engine &aengine,
                const primitive_attr &attr = primitive_attr());

        /// @copydoc dnnl::primitive_desc_base::src_desc(int)const
        memory::desc src_desc(int idx = 0) const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    concat();

    /// Constructs a concatenation primitive.
    /// @param pd Primitive descriptor for concatenation primitive.
    concat(const primitive_desc &pd);
};

/// @} dnnl_api_concat

/// @addtogroup dnnl_api_sum Sum
///
/// A primitive to sum multiple tensors.
///
/// @{

/// Out-of-place summation (sum) primitive.
struct sum : public primitive {
    /// Primitive descriptor for a sum primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a sum primitive.
        ///
        /// @param dst Destination memory descriptor.
        /// @param scales Vector of scales to multiply data in each source
        ///     memory by.
        /// @param srcs Vector of source memory descriptors.
        /// @param aengine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const memory::desc &dst,
                const std::vector<float> &scales,
                const std::vector<memory::desc> &srcs, const engine &aengine,
                const primitive_attr &attr = primitive_attr());

        /// Constructs a primitive descriptor for a sum primitive.
        ///
        /// This version derives the destination memory descriptor
        /// automatically.
        ///
        /// @param scales Vector of scales by which to multiply data in each
        ///     source memory object.
        /// @param srcs Vector of source memory descriptors.
        /// @param aengine Engine on which to perform the operation.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const std::vector<float> &scales,
                const std::vector<memory::desc> &srcs, const engine &aengine,
                const primitive_attr &attr = primitive_attr());

        /// @copydoc dnnl::primitive_desc_base::src_desc(int)const
        memory::desc src_desc(int idx = 0) const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    sum();

    /// Constructs a sum primitive.
    /// @param pd Primitive descriptor for sum primitive.
    sum(const primitive_desc &pd);
};

/// @} dnnl_api_sum

/// @addtogroup dnnl_api_primitives_common
/// @{

/// A base class for descriptors of all primitives that have an operation
/// descriptor and that support iteration over multiple implementations.
struct primitive_desc : public dnnl::primitive_desc_base {
    /// Default constructor. Produces an empty object.
    primitive_desc();

    /// Advances the primitive descriptor iterator to the next implementation.
    ///
    /// @returns @c true on success, and @c false if the last implementation
    ///     reached, in which case primitive descriptor is not modified.
    bool next_impl();
};

/// @} dnnl_api_primitives_common

/// @addtogroup dnnl_api_convolution Convolution
///
/// A primitive to perform 1D, 2D or 3D convolution. Supported variants are
/// forward propagation, backward propagation, and weights gradient with or
/// without bias.
///
/// @{

/// Convolution forward propagation primitive.
struct convolution_forward : public primitive {
    /// Descriptor for a convolution forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a convolution forward propagation
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param bias_desc Bias memory descriptor. Passing zero memory
        ///     descriptor disables the bias term.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a convolution forward propagation
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated convolution forward
        /// propagation primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param bias_desc Bias memory descriptor. Passing zero memory
        ///     descriptor disables the bias term.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &dilates,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated convolution forward
        /// propagation primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a convolution forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a convolution forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a convolution forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a convolution forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// Returns the bias memory descriptor.
        /// @returns The bias memory descriptor.
        /// @returns A zero memory descriptor if the primitive does not have a
        ///     bias parameter.
        memory::desc bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_forward();

    /// Constructs a convolution forward propagation primitive.
    /// @param pd Primitive descriptor for a convolution forward propagation
    ///     primitive.
    convolution_forward(const primitive_desc &pd);
};

/// Convolution backward propagation primitive.
struct convolution_backward_data : public primitive {

    /// Descriptor for a convolution backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a convolution backward propagation
        /// primitive.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution backward
        /// propagation primitive.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a convolution backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a convolution backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a convolution backward propagation
        ///     primitive.
        /// @param aengine Engine to perform the operation on.
        /// @param hint_fwd_pd Primitive descriptor for a convolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a convolution backward propagation
        ///     primitive.
        /// @param aengine Engine to perform the operation on.
        /// @param attr Primitive attributes to use.
        /// @param hint_fwd_pd Primitive descriptor for a convolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_backward_data();

    /// Constructs a convolution backward propagation primitive.
    /// @param pd Primitive descriptor for a convolution backward propagation
    ///     primitive.
    convolution_backward_data(const primitive_desc &pd);
};

/// Convolution weights gradient primitive.
struct convolution_backward_weights : public primitive {
    /// Descriptor for a convolution weights gradient primitive.
    struct desc {
        /// Constructs a descriptor for a convolution weights gradient primitive
        /// with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_bias_desc Diff bias memory descriptor. Passing zero
        ///     memory descriptor disables the bias term.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a convolution weights gradient primitive
        /// without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated convolution weights gradient
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_bias_desc Diff bias memory descriptor. Passing zero
        ///     memory descriptor disables the bias term.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated convolution weights gradient
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Convolution algorithm. Possible values are
        ///     #dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd, and
        ///     #dnnl::algorithm::convolution_auto.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a convolution weights gradient primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a convolution weights gradient
        /// primitive.
        ///
        /// @param adesc Descriptor for a convolution weights gradient primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a convolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution weights gradient
        /// primitive.
        ///
        /// @param adesc Descriptor for a convolution weights gradient primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a convolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case
        ///     an empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// Returns the diff bias memory descriptor.
        /// @returns The diff bias memory descriptor.
        /// @returns A zero memory descriptor of the primitive does not have a
        ///          diff bias parameter.
        memory::desc diff_bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_backward_weights();

    /// Constructs a convolution weights gradient primitive.
    /// @param pd Primitive descriptor for a convolution weights gradient
    ///     primitive.
    convolution_backward_weights(const primitive_desc &pd);
};

/// @} dnnl_api_convolution
//
/// @addtogroup dnnl_api_deconvolution Deconvolution
///
/// A primitive to perform 1D, 2D or 3D deconvolution. Supported variants are
/// forward propagation, backward propagation, and weights gradient with or
/// without bias.
///
/// @{

/// Deconvolution forward propagation primitive.
struct deconvolution_forward : public primitive {
    /// Descriptor for a deconvolution forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution forward propagation
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Deconvolution algorithm:
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param bias_desc Bias memory descriptor. Passing zero memory
        ///     descriptor disables the bias term.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a deconvolution forward propagation
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Deconvolution algorithm:
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated deconvolution forward
        /// propagation primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Deconvolution algorithm:
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param bias_desc Bias memory descriptor. Passing zero memory
        ///     descriptor disables the bias term.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &dilates,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated deconvolution forward
        /// propagation primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Deconvolution algorithm:
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a deconvolution forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a deconvolution forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a deconvolution forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a deconvolution forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::convolution_forward::primitive_desc::bias_desc()const
        memory::desc bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_forward();

    /// Constructs a deconvolution forward propagation primitive.
    /// @param pd Primitive descriptor for a deconvolution forward propagation
    ///     primitive.
    deconvolution_forward(const primitive_desc &pd);
};

/// Deconvolution backward propagation primitive.
struct deconvolution_backward_data : public primitive {
    /// Descriptor for a deconvolution backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution backward propagation
        /// primitive.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm
        ///     (#dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd).
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated deconvolution backward
        /// propagation primitive.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm
        ///     (#dnnl::algorithm::convolution_direct,
        ///     #dnnl::algorithm::convolution_winograd).
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param weights_desc Weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a deconvolution backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a deconvolution backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a deconvolution backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a deconvolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a deconvolution backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a deconvolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_backward_data();

    /// Constructs a deconvolution backward propagation primitive.
    /// @param pd Primitive descriptor for a deconvolution backward propagation
    ///     primitive.
    deconvolution_backward_data(const primitive_desc &pd);
};

/// Deconvolution weights gradient primitive.
struct deconvolution_backward_weights : public primitive {
    /// Descriptor for a deconvolution weights gradient primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution weights gradient
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm. Possible values are
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_bias_desc Diff bias memory descriptor. Passing zero
        ///     memory descriptor disables the bias term.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a deconvolution weights gradient
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p padding_l, and @p padding_r contain values
        /// for spatial dimensions only and hence must have the same number of
        /// elements as there are spatial dimensions. The order of values is
        /// the same as in the tensor: depth (for 3D tensors), height (for 3D
        /// and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm. Possible values are
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated deconvolution weights gradient
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm. Possible values are
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_bias_desc Diff bias memory descriptor. Passing zero
        ///     memory descriptor disables the bias term.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a dilated deconvolution weights gradient
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// Arrays @p strides, @p dilates, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Deconvolution algorithm. Possible values are
        ///     #dnnl::algorithm::deconvolution_direct, and
        ///     #dnnl::algorithm::deconvolution_winograd.
        /// @param src_desc Source memory descriptor.
        /// @param diff_weights_desc Diff weights memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Strides for each spatial dimension.
        /// @param dilates Dilations for each spatial dimension. A zero value
        ///     means no dilation in the corresponding dimension.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a deconvolution weights gradient primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a deconvolution weights
        /// update primitive.
        ///
        /// @param adesc Descriptor for a deconvolution weights gradient
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a deconvolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception.  In this case
        ///     an empty object will be produced.  This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution weights
        /// update primitive.
        ///
        /// @param adesc Descriptor for a deconvolution weights gradient
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a deconvolution forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::convolution_backward_weights::primitive_desc::diff_bias_desc()const
        memory::desc diff_bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_backward_weights();

    /// Constructs a deconvolution weights gradient primitive.
    /// @param pd Primitive descriptor for a deconvolution weights gradient
    ///     primitive.
    deconvolution_backward_weights(const primitive_desc &pd);
};

/// @} dnnl_api_deconvolution

/// @addtogroup dnnl_api_lrn LRN
///
/// A primitive to perform local response normalization (LRN) across or within
/// channels.
///
/// @{

/// Local response normalization (LRN) forward propagation primitive.
struct lrn_forward : public primitive {
    /// Descriptor for an LRN forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a LRN forward propagation primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm LRN algorithm kind: either
        ///     #dnnl::algorithm::lrn_across_channels, or
        ///     #dnnl::algorithm::lrn_within_channel.
        /// @param src_desc Source memory descriptors.
        /// @param dst_desc Destination memory descriptors.
        /// @param local_size Regularization local size.
        /// @param alpha The alpha regularization parameter.
        /// @param beta The beta regularization parameter.
        /// @param k The k regularization parameter.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc,
                memory::dim local_size, float alpha, float beta, float k = 1.f);
    };

    /// Primitive descriptor for an LRN forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an LRN forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LRN forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an LRN forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LRN forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lrn_forward();

    /// Constructs an LRN forward propagation primitive.
    /// @param pd Primitive descriptor for an LRN forward propagation
    ///     primitive.
    lrn_forward(const primitive_desc &pd);
};

/// Local response normalization (LRN) backward propagation primitive.
struct lrn_backward : public primitive {
    /// Descriptor for an LRN backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an LRN backward propagation primitive.
        ///
        /// @param aalgorithm LRN algorithm kind: either
        ///     #dnnl::algorithm::lrn_across_channels, or
        ///     #dnnl::algorithm::lrn_within_channel.
        /// @param diff_src_desc Diff source destination memory descriptor.
        /// @param diff_dst_desc Diff diff destination memory descriptor.
        /// @param src_desc Source memory descriptor.
        /// @param local_size Regularization local size.
        /// @param alpha The alpha regularization parameter.
        /// @param beta The beta regularization parameter.
        /// @param k The k regularization parameter.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, memory::dim local_size,
                float alpha, float beta, float k = 1.f);
    };

    /// Primitive descriptor for an LRN backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an LRN backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LRN backward propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LRN forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const lrn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an LRN backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LRN backward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LRN forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const lrn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lrn_backward();

    /// Constructs an LRN backward propagation primitive.
    /// @param pd Primitive descriptor for an LRN backward propagation
    ///     primitive.
    lrn_backward(const primitive_desc &pd);
};

/// @} dnnl_api_lrn

/// @addtogroup dnnl_api_pooling Pooling
///
/// A primitive to perform max or average pooling.
///
/// @{

/// Pooling forward propagation primitive.
struct pooling_forward : public primitive {
    /// Descriptor for a pooling forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for pooling forward propagation primitive.
        ///
        /// Arrays @p strides, @p kernel, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Pooling algorithm kind: either
        ///     #dnnl::algorithm::pooling_max,
        ///     #dnnl::algorithm::pooling_avg_include_padding,
        ///     or #dnnl::algorithm::pooling_avg (same as
        ///     #dnnl::algorithm::pooling_avg_exclude_padding).
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param kernel Vector of kernel spatial dimensions.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &kernel,
                const memory::dims &padding_l, const memory::dims &padding_r);
    };

    /// Primitive descriptor for a pooling forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a pooling forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a pooling forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    pooling_forward();

    /// Constructs a pooling forward propagation primitive.
    /// @param pd Primitive descriptor for a pooling forward propagation
    ///     primitive.
    pooling_forward(const primitive_desc &pd);
};

/// Pooling backward propagation primitive.
struct pooling_backward : public primitive {
    /// Descriptor for a pooling backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for pooling backward propagation primitive.
        ///
        /// Arrays @p strides, @p kernel, @p padding_l, and @p padding_r
        /// contain values for spatial dimensions only and hence must have the
        /// same number of elements as there are spatial dimensions. The order
        /// of values is the same as in the tensor: depth (for 3D tensors),
        /// height (for 3D and 2D tensors), and width.
        ///
        /// @param aalgorithm Pooling algorithm kind: either
        ///     #dnnl::algorithm::pooling_max,
        ///     #dnnl::algorithm::pooling_avg_include_padding,
        ///     or #dnnl::algorithm::pooling_avg (same as
        ///     #dnnl::algorithm::pooling_avg_exclude_padding).
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param strides Vector of strides for spatial dimension.
        /// @param kernel Vector of kernel spatial dimensions.
        /// @param padding_l Vector of padding values for low indices for each
        ///     spatial dimension `([[front,] top,] left)`.
        /// @param padding_r Vector of padding values for high indices for
        ///     each spatial dimension `([[back,] bottom,] right)`.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &kernel, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a pooling backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a pooling backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a pooling backward propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a pooling forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const pooling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a pooling backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a pooling backward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a pooling forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const pooling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    pooling_backward();

    /// Constructs a pooling backward propagation primitive.
    /// @param pd Primitive descriptor for a pooling backward propagation
    ///     primitive.
    pooling_backward(const primitive_desc &pd);
};

/// @} dnnl_api_pooling

/// @addtogroup dnnl_api_prelu PReLU
///
/// PReLU primitive
/// A primitive to perform PReLU (leaky ReLU with trainable alpha parameter)
///
/// @{

/// PReLU forward propagation primitive.
struct prelu_forward : public primitive {
    /// Descriptor for a PReLU forward propagation primitive.
    struct desc {
        /// Default constructor. Produces an empty object.
        desc();

        /// Constructs a descriptor for a PReLU forward propagation
        /// primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Source memory descriptors.
        /// @param dst_desc Destination memory descriptors.
        /// @param weight_desc Alpha parameters memory descriptor.
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &dst_desc, const memory::desc &weight_desc)
    };

    /// Primitive descriptor for a PReLU forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a PReLU forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a PReLU forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a PReLU forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a PReLU forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;
    };

    /// Default constructor. Produces an empty object.
    prelu_forward() = default;

    /// Constructs a prelu forward propagation primitive.
    /// @param pd Primitive descriptor for a prelu forward propagation
    ///     primitive.
    prelu_forward(const primitive_desc &pd) : primitive(pd) {}
};

/// PReLU backward propagation primitive.
struct prelu_backward : public primitive {
    /// Descriptor for a PReLU backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a PReLU backward propagation
        /// primitive.
        ///
        /// @param src_desc Source memory descriptors.
        /// @param weights_desc Alpha parameters memory descriptor.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param diff_weights_desc Diff alpha parameters memory descriptor.
        desc(const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc,
                const memory::desc &diff_weights_desc);
    };

    /// Primitive descriptor for prelu backward propagation.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc() = default;

        /// Constructs a primitive descriptor for a PReLU backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a PReLU backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a PReLU forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const prelu_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a PReLU backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a PReLU backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a PReLU forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const prelu_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const {
            return base::diff_weights_desc(0);
        }
    };

    /// Default constructor. Produces an empty object.
    prelu_backward() = default;

    /// Constructs a prelu backward propagation primitive.
    /// @param pd Primitive descriptor for a prelu backward propagation
    ///     primitive.
    prelu_backward(const primitive_desc &pd) : primitive(pd) {}

    /// Constructs a prelu backward propagation primitive from a cache blob.
    /// @param pd Primitive descriptor for a prelu backward propagation
    ///     primitive.
    /// @param cache_blob Cache blob.
    prelu_backward(
            const primitive_desc &pd, const std::vector<uint8_t> &cache_blob)
        : primitive(pd, cache_blob) {}
};

/// @} dnnl_api_prelu

/// @addtogroup dnnl_api_reduction Reduction
///
/// A primitive to compute reduction operation on data tensor
/// using min, max, mul, sum, mean and norm_lp operations.
///
/// @{

/// Reduction.
struct reduction : public primitive {
    /// Descriptor for reduction.
    struct desc {
        /// Default constructor. Produces an empty object.
        desc() = default;

        /// Constructs a descriptor for a reduction primitive using algorithm
        /// specific parameters, source and destination memory descriptors.
        ///
        /// @note
        ///     Destination memory descriptor may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aalgorithm reduction algorithm kind. Possible values:
        ///     #dnnl::algorithm::reduction_max,
        ///     #dnnl::algorithm::reduction_min,
        ///     #dnnl::algorithm::reduction_sum,
        ///     #dnnl::algorithm::reduction_mul,
        ///     #dnnl::algorithm::reduction_mean,
        ///     #dnnl::algorithm::reduction_norm_lp_max,
        ///     #dnnl::algorithm::reduction_norm_lp_sum,
        ///     #dnnl::algorithm::reduction_norm_lp_power_p_max,
        ///     #dnnl::algorithm::reduction_norm_lp_power_p_sum.
        /// @param p algorithm specific parameter.
        /// @param eps algorithm specific parameter.
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        desc(algorithm aalgorithm, const memory::desc &src_desc,
                const memory::desc &dst_desc, float p, float eps);
    };

    /// Primitive descriptor for a reduction primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc() = default;

        /// Constructs a primitive descriptor for a reduction primitive.
        ///
        /// @param adesc Descriptor for a reduction primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a reduction primitive.
        ///
        /// @param adesc Descriptor for a reduction primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false)
            : dnnl::primitive_desc(
                    &adesc.data, &attr, aengine, nullptr, allow_empty) {}

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    reduction() = default;

    /// Constructs a reduction primitive.
    /// @param pd Primitive descriptor for a reduction primitive.
    reduction(const primitive_desc &pd)
};

/// @} dnnl_api_reduction

/// @addtogroup dnnl_api_eltwise Eltwise
///
/// A primitive to perform elementwise operations such as the
/// rectifier linear unit (ReLU).
///
/// Both forward and backward propagation primitives support in-place
/// operation; that is, src and dst can refer to the same memory for forward
/// propagation, and diff_dst and diff_src can refer to the same memory for
/// backward propagation.
///
/// @warning
///     Because the original source data is required for backward propagation,
///     in-place forward propagation is not generally supported in the
///     training mode. However, for algorithms supporting destination as input
///     memory, dst can be used for the backward propagation, which makes it
///     possible to get performance benefit even in the training mode.
///
/// @{

/// Elementwise unary operation forward propagation primitive.
struct eltwise_forward : public primitive {
    /// Descriptor for an elementwise forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an elementwise forward propagation
        /// primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Elementwise algorithm kind.
        /// @param src_desc Source and destination memory descriptors.
        /// @param dst_desc Destination memory descriptors.
        /// @param alpha The alpha parameter for the elementwise operation.
        ///     Specific meaning depends on the algorithm.
        /// @param beta The beta parameter for the elementwise operation.
        ///     Specific meaning depends on the algorithm.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc,
                float alpha = 0, float beta = 0);
    };

    /// Primitive descriptor for an elementwise forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an elementwise forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an elementwise forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an elementwise forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an elementwise forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    eltwise_forward();

    /// Constructs an eltwise forward propagation primitive.
    /// @param pd Primitive descriptor for an eltwise forward propagation
    ///     primitive.
    eltwise_forward(const primitive_desc &pd);
};

/// Elementwise unary operation backward propagation primitive.
///
/// @sa eltwise_forward
struct eltwise_backward : public primitive {
    /// Descriptor for an elementwise backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an elementwise backward propagation
        /// primitive.
        ///
        /// @param aalgorithm Elementwise algorithm kind.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptors.
        /// @param data_desc Source or destination memory descriptor.
        /// @param alpha The alpha parameter for the elementwise operation.
        ///     Specific meaning depends on the algorithm.
        /// @param beta The beta parameter for the elementwise operation.
        ///     Specific meaning depends on the algorithm.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc,
                const memory::desc &data_desc, float alpha = 0, float beta = 0);
    };

    /// Primitive descriptor for eltwise backward propagation.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an elementwise backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an elementwise backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an elementwise forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const eltwise_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an elementwise backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an elementwise backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an elementwise forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const eltwise_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    eltwise_backward();

    /// Constructs an eltwise backward propagation primitive.
    /// @param pd Primitive descriptor for an eltwise backward propagation
    ///     primitive.
    eltwise_backward(const primitive_desc &pd);
};

/// @} dnnl_api_eltwise

/// @addtogroup dnnl_api_softmax Softmax
///
/// A primitive to perform softmax.
///
/// @{

/// Softmax forward propagation primitive.
struct softmax_forward : public primitive {
    /// Descriptor for a softmax forward propagation primitive.
    struct desc {
        /// Default constructor. Produces an empty object.
        desc();
        /// Constructs a descriptor for a softmax forward propagation
        /// primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm Softmax algorithm kind: either
        ///     #dnnl::algorithm::softmax_accurate,
        ///     or #dnnl::algorithm::softmax_log.
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param softmax_axis Axis over which softmax is computed.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc,
                int softmax_axis);
    };

    /// Primitive descriptor for a softmax forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a softmax forward
        /// propagation primitive.
        ///
        /// @param adesc descriptor for a softmax forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a softmax forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a softmax forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    softmax_forward();

    /// Constructs a softmax forward propagation primitive.
    /// @param pd Primitive descriptor for a softmax forward propagation
    ///     primitive.
    softmax_forward(const primitive_desc &pd);
};

/// Softmax backward propagation primitive.
struct softmax_backward : public primitive {
    /// Descriptor for a softmax backward propagation primitive.
    struct desc {
        /// Default constructor. Produces an empty object.
        desc();

        /// Constructs a descriptor for a softmax backward propagation
        /// primitive.
        ///
        /// @param aalgorithm Softmax algorithm kind: either
        ///     #dnnl::algorithm::softmax_accurate,
        ///     or #dnnl::algorithm::softmax_log.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param softmax_axis Axis over which softmax is computed.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, const memory::desc &dst_desc,
                int softmax_axis);
    };

    /// Primitive descriptor for a softmax backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a softmax backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a softmax backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a softmax forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const softmax_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a softmax backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a softmax backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a softmax forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const softmax_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    softmax_backward();

    /// Constructs a softmax backward propagation primitive.
    /// @param pd Primitive descriptor for a softmax backward propagation
    ///     primitive.
    softmax_backward(const primitive_desc &pd);
};

/// @} dnnl_api_softmax

/// @addtogroup dnnl_api_batch_normalization Batch Normalization
///
/// A primitive to perform batch normalization.
///
/// Both forward and backward propagation primitives support in-place
/// operation; that is, src and dst can refer to the same memory for forward
/// propagation, and diff_dst and diff_src can refer to the same memory for
/// backward propagation.
///
/// The batch normalization primitives computations can be controlled by
/// specifying different @ref dnnl::normalization_flags values. For example,
/// batch normalization can compute the mean and variance on its own or take
/// them as inputs.  It can either perform scaling and shifting using gamma
/// and beta parameters or not. Optionally, it can also perform a fused ReLU,
/// which in case of training would also require a workspace.
///
/// @{

/// Batch normalization forward propagation primitive.
struct batch_normalization_forward : public primitive {
    /// Descriptor for a batch normalization forward propagation primitive.
    struct desc {
        /// Constructs a batch normalization descriptor for forward
        /// propagation.
        ///
        /// @note
        ///     In-place operation is supported: the dst can refer to the same
        ///     memory as the src.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Source memory descriptors.
        /// @param dst_desc Destination memory descriptors.
        /// @param epsilon Batch normalization epsilon parameter.
        /// @param flags Batch normalization flags (@ref
        ///     dnnl::normalization_flags).
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &dst_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for a batch normalization forward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a batch normalization forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a batch normalization forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a batch normalization forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a batch normalization forward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// Returns memory descriptor for mean.
        /// @returns Memory descriptor for mean.
        memory::desc mean_desc() const;

        /// Returns memory descriptor for variance.
        /// @returns Memory descriptor for variance.
        memory::desc variance_desc() const;
    };

    /// Default constructor. Produces an empty object.
    batch_normalization_forward();

    /// Constructs a batch normalization forward propagation primitive.
    /// @param pd Primitive descriptor for a batch normalization forward
    ///     propagation primitive.
    batch_normalization_forward(const primitive_desc &pd);
};

/// Batch normalization backward propagation primitive.
struct batch_normalization_backward : public primitive {
    /// Descriptor for a batch normalization backward propagation primitive.
    struct desc {
        /// Constructs a batch normalization descriptor for backward
        /// propagation.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::backward_data and #dnnl::prop_kind::backward
        ///     (diffs for all parameters are computed in this case).
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param src_desc Source memory descriptor.
        /// @param epsilon Batch normalization epsilon parameter.
        /// @param flags Batch normalization flags (@ref
        ///     dnnl::normalization_flags).
        desc(prop_kind aprop_kind, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, const memory::desc &src_desc,
                float epsilon, normalization_flags flags);
    };

    /// Primitive descriptor for a batch normalization backward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a batch normalization backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a batch normalization backward
        ///     propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a batch normalization
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const batch_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a batch normalization backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a batch normalization backward
        ///     propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a batch normalization
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const batch_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::mean_desc()const
        memory::desc mean_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::variance_desc()const
        memory::desc variance_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    batch_normalization_backward();

    /// Constructs a batch normalization backward propagation primitive.
    /// @param pd Primitive descriptor for a batch normalization backward
    ///     propagation primitive.
    batch_normalization_backward(const primitive_desc &pd);
};

/// @} dnnl_api_batch_normalization

/// @addtogroup dnnl_api_layer_normalization Layer Normalization
///
/// A primitive to perform layer normalization. Normalization is performed
/// within the last logical dimension of data tensor.
///
/// Both forward and backward propagation primitives support in-place
/// operation; that is, src and dst can refer to the same memory for forward
/// propagation, and diff_dst and diff_src can refer to the same memory for
/// backward propagation.
///
/// The layer normalization primitives computations can be controlled by
/// specifying different dnnl::normalization_flags values. For example,
/// layer normalization forward propagation can be configured to either
/// compute the mean and variance or take them as arguments. It can either
/// perform scaling and shifting using gamma and beta parameters or not.
/// Optionally, it can also perform a fused ReLU, which in case of training
/// would also require a workspace.
///
/// @{

/// Layer normalization forward propagation primitive.
struct layer_normalization_forward : public primitive {
    /// Descriptor for a layer normalization forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for layer normalization forward
        /// propagation primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param stat_desc Statistics memory descriptors.
        /// @param epsilon Layer normalization epsilon parameter.
        /// @param flags Layer normalization flags (@ref
        ///     dnnl::normalization_flags).
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &dst_desc, const memory::desc &stat_desc,
                float epsilon, normalization_flags flags);
    };

    /// Primitive descriptor for a layer normalization forward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a layer normalization forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a layer normalization forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a layer normalization forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a layer normalization forward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::mean_desc()const
        memory::desc mean_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::variance_desc()const
        memory::desc variance_desc() const;
    };

    /// Default constructor. Produces an empty object.
    layer_normalization_forward();

    /// Constructs a layer normalization forward propagation primitive.
    /// @param pd Primitive descriptor for a layer normalization forward
    ///     propagation primitive.
    layer_normalization_forward(const primitive_desc &pd);
};

/// Layer normalization backward propagation primitive.
struct layer_normalization_backward : public primitive {
    /// Descriptor for a layer normalization backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for layer normalization backward
        /// propagation primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::backward_data and #dnnl::prop_kind::backward
        ///     (diffs for all parameters are computed in this case).
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param src_desc Source memory descriptor.
        /// @param stat_desc Statistics memory descriptors.
        /// @param epsilon Layer normalization epsilon parameter.
        /// @param flags Layer normalization flags (@ref
        ///     dnnl::normalization_flags).
        desc(prop_kind aprop_kind, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, const memory::desc &src_desc,
                const memory::desc &stat_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for a layer normalization backward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a layer normalization backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a layer normalization backward
        ///     propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a layer normalization
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const layer_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a layer normalization backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a layer normalization backward
        ///     propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a layer normalization
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const layer_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::mean_desc()const
        memory::desc mean_desc() const;

        /// @copydoc dnnl::batch_normalization_forward::primitive_desc::variance_desc()const
        memory::desc variance_desc() const;

        /// @copydoc dnnl::primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    layer_normalization_backward();

    /// Constructs a layer normalization backward propagation primitive.
    /// @param pd Primitive descriptor for a layer normalization backward
    ///     propagation primitive.
    layer_normalization_backward(const primitive_desc &pd);
};

/// @} dnnl_api_layer_normalization

/// @addtogroup dnnl_api_inner_product Inner Product
///
/// A primitive to compute an inner product.
///
/// @{

/// Inner product forward propagation primitive.
struct inner_product_forward : public primitive {
    /// Descriptor for an inner product forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an inner product forward propagation
        /// primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Memory descriptor for src.
        /// @param weights_desc Memory descriptor for diff weights.
        /// @param bias_desc Memory descriptor for diff bias.
        /// @param dst_desc Memory descriptor for diff dst.
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &weights_desc, const memory::desc &bias_desc,
                const memory::desc &dst_desc);

        /// Constructs a descriptor for an inner product forward propagation
        /// primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Memory descriptor for src.
        /// @param weights_desc Memory descriptor for diff weights.
        /// @param dst_desc Memory descriptor for dst.
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &weights_desc, const memory::desc &dst_desc);
    };

    /// Primitive descriptor for an inner product forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an inner product forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an inner product forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an inner product forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an inner product forward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;

        /// @copydoc dnnl::convolution_forward::primitive_desc::bias_desc()const
        memory::desc bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_forward();

    /// Constructs an inner product forward propagation primitive.
    /// @param pd Primitive descriptor for an inner product forward
    ///     propagation primitive.
    inner_product_forward(const primitive_desc &pd);
};

/// Inner product backward propagation primitive.
struct inner_product_backward_data : public primitive {
    /// Descriptor for an inner product backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an inner product backward propagation
        /// primitive.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param diff_src_desc Memory descriptor for diff src.
        /// @param weights_desc Memory descriptor for weights.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        desc(const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc);
    };

    /// Primitive descriptor for an inner product backward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an inner product backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an inner product backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an inner product
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an inner product backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an inner product backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an inner product
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_backward_data();

    /// Constructs an inner product backward propagation primitive.
    /// @param pd Primitive descriptor for an inner product backward
    ///     propagation primitive.
    inner_product_backward_data(const primitive_desc &pd);
};

/// Inner product weights gradient primitive.
struct inner_product_backward_weights : public primitive {
    /// Descriptor for an inner product weights gradient primitive.
    struct desc {
        /// Constructs a descriptor for an inner product descriptor weights
        /// update primitive with bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param src_desc Memory descriptor for src.
        /// @param diff_weights_desc Memory descriptor for diff weights.
        /// @param diff_bias_desc Memory descriptor for diff bias.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        desc(const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc);

        /// Constructs a descriptor for an inner product descriptor weights
        /// update primitive without bias.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param src_desc Memory descriptor for src.
        /// @param diff_weights_desc Memory descriptor for diff weights.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        desc(const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc);
    };

    /// Primitive descriptor for an inner product weights gradient primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an inner product weights
        /// update primitive.
        ///
        /// @param adesc Descriptor for an inner product weights gradient
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an inner product
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an inner product weights
        /// update primitive.
        ///
        /// @param adesc Descriptor for an inner product weights gradient
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an inner product
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_weights_desc()const
        memory::desc diff_weights_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;

        /// @copydoc dnnl::convolution_backward_weights::primitive_desc::diff_bias_desc()const
        memory::desc diff_bias_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_backward_weights();

    /// Constructs an inner product weights gradient primitive.
    /// @param pd Primitive descriptor for an inner product weights gradient
    ///     primitive.
    inner_product_backward_weights(const primitive_desc &pd);
};

/// @} dnnl_api_inner_product

/// @addtogroup dnnl_api_rnn RNN
///
/// A primitive to compute recurrent neural network layers.
///
/// @{

/// Base class for primitive descriptors for RNN primitives.
struct rnn_primitive_desc_base : public primitive_desc {
    /// Default constructor. Produces an empty object.
    rnn_primitive_desc_base();

    /// Returns source layer memory descriptor.
    /// @returns Source layer memory descriptor.
    memory::desc src_layer_desc() const;

    /// Returns source iteration memory descriptor.
    /// @returns Source iteration memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          source iteration parameter.
    memory::desc src_iter_desc() const;

    /// Returns source recurrent cell state memory descriptor.
    /// @returns Source recurrent cell state memory descriptor.
    memory::desc src_iter_c_desc() const;

    /// Returns weights layer memory descriptor.
    /// @returns Weights layer memory descriptor.
    memory::desc weights_layer_desc() const;

    /// Returns weights iteration memory descriptor.
    /// @returns Weights iteration memory descriptor.
    memory::desc weights_iter_desc() const;

    /// Returns weights peephole memory descriptor.
    /// @returns Weights peephole memory descriptor.
    memory::desc weights_peephole_desc() const;

    /// Returns weights projection memory descriptor.
    /// @returns Weights projection memory descriptor.
    memory::desc weights_projection_desc() const;

    /// Returns bias memory descriptor.
    /// @returns Bias memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          bias parameter.
    memory::desc bias_desc() const;

    /// Returns destination layer memory descriptor.
    /// @returns Destination layer memory descriptor.
    memory::desc dst_layer_desc() const;

    /// Returns destination iteration memory descriptor.
    /// @returns Destination iteration memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          destination iteration parameter.
    memory::desc dst_iter_desc() const;

    /// Returns destination recurrent cell state memory descriptor.
    /// @returns Destination recurrent cell state memory descriptor.
    memory::desc dst_iter_c_desc() const;

    /// Returns diff source layer memory descriptor.
    /// @returns Diff source layer memory descriptor.
    memory::desc diff_src_layer_desc() const;

    /// Returns diff source iteration memory descriptor.
    /// @returns Diff source iteration memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          diff source iteration parameter.
    memory::desc diff_src_iter_desc() const;

    /// Returns diff source recurrent cell state memory descriptor.
    /// @returns Diff source recurrent cell state memory descriptor.
    memory::desc diff_src_iter_c_desc() const;

    /// Returns diff weights layer memory descriptor.
    /// @returns Diff weights layer memory descriptor.
    memory::desc diff_weights_layer_desc() const;

    /// Returns diff weights iteration memory descriptor.
    /// @returns Diff weights iteration memory descriptor.
    memory::desc diff_weights_iter_desc() const;

    /// Returns diff weights peephole memory descriptor.
    /// @returns Diff weights peephole memory descriptor.
    memory::desc diff_weights_peephole_desc() const;

    /// Returns diff weights projection memory descriptor.
    /// @returns Diff weights projection memory descriptor.
    memory::desc diff_weights_projection_desc() const;

    /// Returns diff bias memory descriptor.
    /// @returns Diff bias memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          diff bias parameter.
    memory::desc diff_bias_desc() const;

    /// Returns diff destination layer memory descriptor.
    /// @returns Diff destination layer memory descriptor.
    memory::desc diff_dst_layer_desc() const;

    /// Returns diff destination iteration memory descriptor.
    /// @returns Diff destination iteration memory descriptor.
    /// @returns A zero memory descriptor if the primitive does not have a
    ///          diff destination iteration parameter.
    memory::desc diff_dst_iter_desc() const;

    /// Returns diff destination recurrent cell state memory descriptor.
    /// @returns Diff destination recurrent cell state memory descriptor.
    memory::desc diff_dst_iter_c_desc() const;
};

/// Vanilla RNN forward propagation primitive.
struct vanilla_rnn_forward : public primitive {
    /// Descriptor for a vanilla RNN forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a vanilla RNN forward propagation
        /// primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc.
        ///
        /// This would then indicate that the RNN forward propagation primitive
        /// should not use them and should default to zero values instead.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc can be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param activation Activation kind. Possible values are
        ///     #dnnl::algorithm::eltwise_relu,
        ///     #dnnl::algorithm::eltwise_tanh, or
        ///     #dnnl::algorithm::eltwise_logistic.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param flags Unused.
        /// @param alpha Negative slope if activation is
        ///     #dnnl::algorithm::eltwise_relu.
        /// @param beta Unused.
        desc(prop_kind aprop_kind, algorithm activation,
                rnn_direction direction, const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                rnn_flags flags = rnn_flags::undef, float alpha = 0.0f,
                float beta = 0.0f);
    };

    /// Primitive descriptor for a vanilla RNN forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a vanilla RNN forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a vanilla RNN forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a vanilla RNN forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a vanilla RNN forward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    vanilla_rnn_forward();

    /// Constructs a vanilla RNN forward propagation primitive.
    /// @param pd Primitive descriptor for a vanilla RNN forward
    ///     propagation primitive.
    vanilla_rnn_forward(const primitive_desc &pd);
};

/// Vanilla RNN backward propagation primitive.
struct vanilla_rnn_backward : public primitive {
    /// Descriptor for a vanilla RNN backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a vanilla RNN backward propagation
        /// primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p diff_src_iter_desc,
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p diff_dst_iter_desc.
        ///
        /// This would then indicate that the RNN backward propagation
        /// primitive should not use the respective data and should use zero
        /// values instead.
        ///
        /// @note
        ///     All the memory descriptors may be initialized with the
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param activation Activation kind. Possible values are
        ///     #dnnl::algorithm::eltwise_relu,
        ///     #dnnl::algorithm::eltwise_tanh, or
        ///     #dnnl::algorithm::eltwise_logistic.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param flags Unused.
        /// @param alpha Negative slope if activation is
        ///     #dnnl::algorithm::eltwise_relu.
        /// @param beta Unused.
        desc(prop_kind aprop_kind, algorithm activation,
                rnn_direction direction, const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                rnn_flags flags = rnn_flags::undef, float alpha = 0.0f,
                float beta = 0.0f);
    };

    /// Primitive descriptor for an RNN backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a vanilla RNN backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a vanilla RNN backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a vanilla RNN
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const vanilla_rnn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a vanilla RNN backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a vanilla RNN backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a vanilla RNN
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const vanilla_rnn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_layer_desc()const
        memory::desc diff_src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_iter_desc()const
        memory::desc diff_src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_layer_desc()const
        memory::desc diff_weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_iter_desc()const
        memory::desc diff_weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_bias_desc()const
        memory::desc diff_bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_layer_desc()const
        memory::desc diff_dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_iter_desc()const
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    vanilla_rnn_backward();

    /// Constructs a vanilla RNN backward propagation primitive.
    /// @param pd Primitive descriptor for a vanilla RNN backward
    ///     propagation primitive.
    vanilla_rnn_backward(const primitive_desc &pd);
};

/// LSTM forward propagation primitive.
struct lstm_forward : public primitive {
    /// Descriptor for an LSTM forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for an LSTM (with or without peephole and
        /// with or without projection) forward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        /// - @p weights_peephole_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM forward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// The @p weights_projection_desc may point to a zero memory
        /// descriptor. This would then indicate that the LSTM doesn't have
        /// recurrent projection layer.
        ///
        /// @note
        ///     All memory descriptors can be initialized with an
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param weights_peephole_desc Memory descriptor for the weights
        ///     applied to the cell states (according to the Peephole LSTM
        ///     formula).
        /// @param weights_projection_desc Memory descriptor for the weights
        ///     applied to the hidden states to get the recurrent projection
        ///     (according to the Projection LSTM formula).
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &weights_peephole_desc,
                const memory::desc &weights_projection_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);

        /// Constructs a descriptor for an LSTM (with or without peephole)
        /// forward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        /// - @p weights_peephole_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM forward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors can be initialized with an
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param weights_peephole_desc Memory descriptor for the weights
        ///     applied to the cell states (according to the Peephole LSTM
        ///     formula).
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &weights_peephole_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);

        /// Constructs a descriptor for an LSTM forward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM forward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors can be initialized with an
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for an LSTM forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an LSTM forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LSTM forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an LSTM forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LSTM forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_c_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_peephole_desc()const
        memory::desc weights_peephole_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_projection_desc()const
        memory::desc weights_projection_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc dst_iter_c_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lstm_forward();

    /// Constructs an LSTM forward propagation primitive.
    /// @param pd Primitive descriptor for an LSTM forward propagation
    ///     primitive.
    lstm_forward(const primitive_desc &pd);
};

/// LSTM backward propagation primitive.
struct lstm_backward : public primitive {
    /// Descriptor for an LSTM backward propagation primitive.
    struct desc {
        /// projection) descriptor for backward propagation using @p prop_kind,
        /// @p direction, and memory descriptors.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        ///   @p diff_src_iter_desc, and @p diff_src_iter_c_desc,
        /// - @p weights_peephole_desc together with
        ///   @p diff_weights_peephole_desc
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc,
        ///   @p diff_dst_iter_desc, and @p diff_dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM backward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// The @p weights_projection_desc together with @p
        /// diff_weights_projection_desc may point to a zero memory descriptor.
        /// This would then indicate that the LSTM doesn't have recurrent
        /// projection layer.
        ///
        /// @note
        ///     All memory descriptors can be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param weights_peephole_desc Memory descriptor for the weights
        ///     applied to the cell states (according to the Peephole LSTM
        ///     formula).
        /// @param weights_projection_desc Memory descriptor for the weights
        ///     applied to the hidden states to get the recurrent projection
        ///     (according to the Projection LSTM formula).
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_src_iter_c_desc Memory descriptor for the diff of
        ///     input recurrent cell state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_weights_peephole_desc Memory descriptor for the diff of
        ///     weights applied to the cell states (according to the Peephole
        ///     LSTM formula).
        /// @param diff_weights_projection_desc Memory descriptor for the diff
        ///     of weights applied to the hidden states to get the recurrent
        ///     projection (according to the Projection LSTM formula).
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param diff_dst_iter_c_desc Memory descriptor for the diff of
        ///     output recurrent cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &weights_peephole_desc,
                const memory::desc &weights_projection_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_src_iter_c_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_weights_peephole_desc,
                const memory::desc &diff_weights_projection_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                const memory::desc &diff_dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);

        /// Constructs an LSTM (with or without peephole) descriptor for
        /// backward propagation using @p prop_kind, @p direction, and memory
        /// descriptors.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        ///   @p diff_src_iter_desc, and @p diff_src_iter_c_desc,
        /// - @p weights_peephole_desc together with
        ///   @p diff_weights_peephole_desc
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc,
        ///   @p diff_dst_iter_desc, and @p diff_dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM backward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param weights_peephole_desc Memory descriptor for the weights
        ///     applied to the cell states (according to the Peephole LSTM
        ///     formula).
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_src_iter_c_desc Memory descriptor for the diff of
        ///     input recurrent cell state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_weights_peephole_desc Memory descriptor for the diff of
        ///     weights applied to the cell states (according to the Peephole
        ///     LSTM formula).
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param diff_dst_iter_c_desc Memory descriptor for the diff of
        ///     output recurrent cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &weights_peephole_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_src_iter_c_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_weights_peephole_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                const memory::desc &diff_dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);

        /// Constructs an LSTM descriptor for backward propagation using @p
        /// prop_kind, @p direction, and memory descriptors.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p src_iter_c_desc,
        ///   @p diff_src_iter_desc, and @p diff_src_iter_c_desc,
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p dst_iter_c_desc,
        ///   @p diff_dst_iter_desc, and @p diff_dst_iter_c_desc.
        ///
        /// This would then indicate that the LSTM backward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param src_iter_c_desc Memory descriptor for the input recurrent
        ///     cell state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param dst_iter_c_desc Memory descriptor for the output recurrent
        ///     cell state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_src_iter_c_desc Memory descriptor for the diff of
        ///     input recurrent cell state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param diff_dst_iter_c_desc Memory descriptor for the diff of
        ///     output recurrent cell state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &src_iter_c_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &dst_iter_c_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_src_iter_c_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                const memory::desc &diff_dst_iter_c_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for LSTM backward propagation.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an LSTM backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for LSTM backward propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LSTM
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const lstm_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an LSTM backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for an LSTM backward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LSTM
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const lstm_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_c_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_peephole_desc()const
        memory::desc weights_peephole_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_projection_desc()const
        memory::desc weights_projection_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc dst_iter_c_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_layer_desc()const
        memory::desc diff_src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_iter_desc()const
        memory::desc diff_src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_iter_c_desc()const
        memory::desc diff_src_iter_c_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_layer_desc()const
        memory::desc diff_weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_iter_desc()const
        memory::desc diff_weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_peephole_desc()const
        memory::desc diff_weights_peephole_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_projection_desc()const
        memory::desc diff_weights_projection_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_bias_desc()const
        memory::desc diff_bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_layer_desc()const
        memory::desc diff_dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_iter_desc()const
        memory::desc diff_dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_iter_c_desc()const
        memory::desc diff_dst_iter_c_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lstm_backward();

    /// Constructs an LSTM backward propagation primitive.
    /// @param pd Primitive descriptor for an LSTM backward propagation
    ///     primitive.
    lstm_backward(const primitive_desc &pd);
};

/// GRU forward propagation primitive.
struct gru_forward : public primitive {
    /// Descriptor for a GRU forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a GRU forward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc.
        ///
        /// This would then indicate that the GRU forward propagation primitive
        /// should not use them and should default to zero values instead.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc may be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor GRU forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a GRU forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for a GRU forward propagation primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a GRU forward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for a GRU forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    gru_forward();

    /// Constructs a GRU forward propagation primitive.
    /// @param pd Primitive descriptor for a GRU forward propagation
    ///     primitive.
    gru_forward(const primitive_desc &pd);
};

/// GRU backward propagation primitive.
struct gru_backward : public primitive {
    /// Descriptor for a GRU backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a GRU backward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p diff_src_iter_desc,
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p diff_dst_iter_desc.
        ///
        /// This would then indicate that the GRU backward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for a GRU backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a GRU backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for a GRU backward propagation primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a GRU
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a GRU backward propagation
        /// primitive.
        ///
        /// @param adesc Descriptor for a GRU backward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a GRU
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_layer_desc()const
        memory::desc diff_src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_iter_desc()const
        memory::desc diff_src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_layer_desc()const
        memory::desc diff_weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_iter_desc()const
        memory::desc diff_weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_bias_desc()const
        memory::desc diff_bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_layer_desc()const
        memory::desc diff_dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_iter_desc()const
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    gru_backward();

    /// Constructs a GRU backward propagation primitive.
    /// @param pd Primitive descriptor for a GRU backward propagation
    ///     primitive.
    gru_backward(const primitive_desc &pd);
};

/// LBR GRU forward propagation primitive.
struct lbr_gru_forward : public primitive {
    /// Descriptor for an LBR GRU forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for LBR GRU forward propagation primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc,
        /// - @p bias_desc,
        /// - @p dst_iter_desc.
        ///
        /// This would then indicate that the LBR GRU forward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc may be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for an LBR GRU forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a LBR GRU forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a LBR GRU forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a LBR GRU forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a LBR GRU forward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lbr_gru_forward();

    /// Constructs an LBR GRU forward propagation primitive.
    /// @param pd Primitive descriptor for an LBR GRU forward propagation
    ///     primitive.
    lbr_gru_forward(const primitive_desc &pd);
};

/// LBR GRU backward propagation primitive.
struct lbr_gru_backward : public primitive {
    /// Descriptor for a LBR GRU backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for LBR GRU backward propagation
        /// primitive.
        ///
        /// The following arguments may point to a zero memory descriptor:
        /// - @p src_iter_desc together with @p diff_src_iter_desc,
        /// - @p bias_desc together with @p diff_bias_desc,
        /// - @p dst_iter_desc together with @p diff_dst_iter_desc.
        ///
        /// This would then indicate that the LBR GRU backward propagation
        /// primitive should not use them and should default to zero values
        /// instead.
        ///
        /// @note
        ///     All memory descriptors may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Must be
        ///     #dnnl::prop_kind::backward.
        /// @param direction RNN direction. See @ref dnnl::rnn_direction for
        ///     more info.
        /// @param src_layer_desc Memory descriptor for the input vector.
        /// @param src_iter_desc Memory descriptor for the input recurrent
        ///     hidden state vector.
        /// @param weights_layer_desc Memory descriptor for the weights
        ///     applied to the layer input.
        /// @param weights_iter_desc Memory descriptor for the weights applied
        ///     to the recurrent input.
        /// @param bias_desc Bias memory descriptor.
        /// @param dst_layer_desc Memory descriptor for the output vector.
        /// @param dst_iter_desc Memory descriptor for the output recurrent
        ///     hidden state vector.
        /// @param diff_src_layer_desc Memory descriptor for the diff of input
        ///     vector.
        /// @param diff_src_iter_desc Memory descriptor for the diff of input
        ///     recurrent hidden state vector.
        /// @param diff_weights_layer_desc Memory descriptor for the diff of
        ///     weights applied to the layer input.
        /// @param diff_weights_iter_desc Memory descriptor for the diff of
        ///     weights applied to the recurrent input.
        /// @param diff_bias_desc Diff bias memory descriptor.
        /// @param diff_dst_layer_desc Memory descriptor for the diff of
        ///     output vector.
        /// @param diff_dst_iter_desc Memory descriptor for the diff of output
        ///     recurrent hidden state vector.
        /// @param flags Unused.
        desc(prop_kind aprop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                const memory::desc &diff_src_layer_desc,
                const memory::desc &diff_src_iter_desc,
                const memory::desc &diff_weights_layer_desc,
                const memory::desc &diff_weights_iter_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_layer_desc,
                const memory::desc &diff_dst_iter_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for an LBR GRU backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc() = default;

        /// Constructs a primitive descriptor for an LBR GRU backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an LBR GRU backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LBR GRU
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const lbr_gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an LBR GRU backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for an LBR GRU backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for an LBR GRU
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const lbr_gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::rnn_primitive_desc_base::src_layer_desc()const
        memory::desc src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::src_iter_desc()const
        memory::desc src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_layer_desc()const
        memory::desc weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::weights_iter_desc()const
        memory::desc weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_layer_desc()const
        memory::desc dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::dst_iter_desc()const
        memory::desc dst_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::workspace_desc()const
        memory::desc workspace_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_layer_desc()const
        memory::desc diff_src_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_src_iter_desc()const
        memory::desc diff_src_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_layer_desc()const
        memory::desc diff_weights_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_weights_iter_desc()const
        memory::desc diff_weights_iter_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_bias_desc()const
        memory::desc diff_bias_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_layer_desc()const
        memory::desc diff_dst_layer_desc() const;

        /// @copydoc dnnl::rnn_primitive_desc_base::diff_dst_iter_desc()const
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lbr_gru_backward();

    /// Constructs an LBR GRU backward propagation primitive.
    /// @param pd Primitive descriptor for an LBR GRU backward propagation
    ///     primitive.
    lbr_gru_backward(const primitive_desc &pd);
};

/// @} dnnl_api_rnn

/// @addtogroup dnnl_api_shuffle Shuffle
///
/// A primitive to shuffle tensor data along an axis.
///
/// @{

/// Shuffle forward propagation primitive.
struct shuffle_forward : public primitive {
    /// Descriptor for a shuffle forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a shuffle forward propagation
        /// primitive.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        /// @param axis The axis along which the data is shuffled.
        /// @param group_size Shuffle group size.
        desc(prop_kind aprop_kind, const memory::desc &src_desc,
                const memory::desc &dst_desc, int axis, int group_size);
    };

    /// Primitive descriptor for a shuffle forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a shuffle forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a shuffle forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    shuffle_forward();

    /// Constructs a shuffle forward propagation primitive.
    /// @param pd Primitive descriptor for a shuffle forward propagation
    ///     primitive.
    shuffle_forward(const primitive_desc &pd);
};

/// Shuffle backward propagation primitive.
struct shuffle_backward : public primitive {
    /// Descriptor for a shuffle primitive backward propagation
    /// primitive.
    struct desc {
        /// Constructs a descriptor for a shuffle backward propagation
        /// primitive.
        ///
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        /// @param axis The axis along which the data is shuffled.
        /// @param group_size Shuffle group size.
        desc(const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, int axis, int group_size);
    };

    /// Primitive descriptor for a shuffle backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a shuffle backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a shuffle backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param hint_fwd_pd Primitive descriptor for a shuffle
        ///     forward propagation primitive. It is used as a hint for
        ///     deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const shuffle_forward::primitive_desc &hint_fwd_pd,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    shuffle_backward();

    /// Constructs a shuffle backward propagation primitive.
    /// @param pd Primitive descriptor for a shuffle backward propagation
    ///     primitive.
    shuffle_backward(const primitive_desc &pd);
};

/// @} dnnl_api_shuffle

/// @addtogroup dnnl_api_binary Binary
///
/// A primitive to perform tensor operations over two tensors.
///
/// @{

/// Elementwise binary operator primitive.
struct binary : public primitive {
    /// Descriptor for an elementwise binary operator primitive.
    struct desc {
        /// Constructs a descriptor for an elementwise binary operator
        /// primitive.
        ///
        /// @param aalgorithm Elementwise algorithm.
        /// @param src0 Memory descriptor for source tensor #0.
        /// @param src1 Memory descriptor for source tensor #1.
        /// @param dst Memory descriptor for destination tensor.
        desc(algorithm aalgorithm, const memory::desc &src0,
                const memory::desc &src1, const memory::desc &dst);
    };

    /// Primitive descriptor for an elementwise binary operator primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an elementwise binary operator
        /// primitive.
        ///
        /// @param adesc Descriptor for an elementwise binary operator primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for an elementwise binary operator
        /// primitive.
        ///
        /// @param adesc Descriptor for an elementwise binary operator primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc(int)const
        memory::desc src_desc(int idx = 0) const;

        /// Returns the memory descriptor for source #0.
        memory::desc src0_desc() const;

        /// Returns the memory descriptor for source #1.
        memory::desc src1_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    binary();

    /// Constructs an elementwise binary operation primitive.
    /// @param pd Primitive descriptor for an elementwise binary operation
    ///     primitive.
    binary(const primitive_desc &pd);
};

/// @} dnnl_api_binary

/// @addtogroup dnnl_api_matmul Matrix Multiplication
///
/// A primitive to perform matrix-matrix multiplication. The batched mode
/// is supported with 3D tensors.
///
/// @{

/// Matrix multiplication (matmul) primitive.
struct matmul : public primitive {
    /// Descriptor for a matmul primitive.
    struct desc {
        /// Constructs a descriptor for a matmul primitive.
        ///
        /// @param src_desc Memory descriptor for source (matrix A).
        /// @param weights_desc Memory descriptor for weights (matrix B).
        /// @param dst_desc Memory descriptor for destination (matrix C).
        desc(const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc);

        /// Constructs a descriptor for a matmul primitive.
        ///
        /// @param src_desc Memory descriptor for source (matrix A).
        /// @param weights_desc Memory descriptor for weights (matrix B).
        /// @param dst_desc Memory descriptor for destination (matrix C).
        /// @param bias_desc Memory descriptor for bias.
        desc(const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc);
    };

    /// Primitive descriptor for a matmul primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a matmul primitive.
        ///
        /// @param adesc Descriptor for a matmul primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a matmul primitive.
        ///
        /// @param adesc Descriptor for a matmul primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::weights_desc()const
        memory::desc weights_desc() const;

        /// @copydoc dnnl::convolution_forward::primitive_desc::bias_desc()const
        memory::desc bias_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    matmul();

    /// Constructs a matmul primitive.
    /// @param pd Primitive descriptor for a matmul primitive.
    matmul(const primitive_desc &pd);
};

/// @} dnnl_api_matmul

/// @addtogroup dnnl_api_resampling Resampling
///
/// A primitive to compute resampling operation on 1D, 2D or 3D data tensor
/// using Nearest Neighbor, or Linear (Bilinear, Trilinear) interpolation
/// method.
///
/// @{

/// Resampling forward propagation.
struct resampling_forward : public primitive {
    /// Descriptor for resampling forward propagation.
    struct desc {
        /// Constructs a descriptor for a resampling forward propagation
        /// primitive using source and destination memory descriptors.
        ///
        /// @note
        ///     The destination memory descriptor may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm resampling algorithm kind: either
        ///     #dnnl::algorithm::resampling_nearest, or
        ///     #dnnl::algorithm::resampling_linear
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc);

        /// Constructs a descriptor for a resampling forward propagation
        /// primitive using source memory descriptor and factors.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm resampling algorithm kind: either
        ///     #dnnl::algorithm::resampling_nearest, or
        ///     #dnnl::algorithm::resampling_linear
        /// @param factors Vector of scaling factors for spatial dimension.
        /// @param src_desc Source memory descriptor.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const std::vector<float> &factors,
                const memory::desc &src_desc);

        /// Constructs a descriptor for a resampling forward propagation
        /// primitive.
        ///
        /// @note
        ///     The destination memory descriptor may be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        /// @param aprop_kind Propagation kind. Possible values are
        ///     #dnnl::prop_kind::forward_training, and
        ///     #dnnl::prop_kind::forward_inference.
        /// @param aalgorithm resampling algorithm kind: either
        ///     #dnnl::algorithm::resampling_nearest, or
        ///     #dnnl::algorithm::resampling_linear
        /// @param factors Vector of scaling factors for spatial dimension.
        /// @param src_desc Source memory descriptor.
        /// @param dst_desc Destination memory descriptor.
        desc(prop_kind aprop_kind, algorithm aalgorithm,
                const std::vector<float> &factors, const memory::desc &src_desc,
                const memory::desc &dst_desc);
    };

    /// Primitive descriptor for a resampling forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a resampling forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a resampling forward propagation
        /// primitive.
        /// @param aengine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a resampling forward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a resampling forward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine, bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::src_desc()const
        memory::desc src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::dst_desc()const
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    resampling_forward();

    /// Constructs a resampling forward propagation primitive.
    /// @param pd Primitive descriptor for a resampling forward propagation
    ///     primitive.
    resampling_forward(const primitive_desc &pd);
};

/// Resampling backward propagation primitive.
struct resampling_backward : public primitive {
    /// Descriptor for a resampling backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a resampling backward propagation
        /// primitive using source and destination memory descriptors.
        ///
        /// @param aalgorithm resampling algorithm kind: either
        ///     #dnnl::algorithm::resampling_nearest, or
        ///     #dnnl::algorithm::resampling_linear
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        desc(algorithm aalgorithm, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc);

        /// Constructs a descriptor for resampling backward propagation
        /// primitive.
        ///
        /// @param aalgorithm resampling algorithm kind: either
        ///     #dnnl::algorithm::resampling_nearest, or
        ///     #dnnl::algorithm::resampling_linear
        /// @param factors Vector of scaling factors for spatial dimension.
        /// @param diff_src_desc Diff source memory descriptor.
        /// @param diff_dst_desc Diff destination memory descriptor.
        desc(algorithm aalgorithm, const std::vector<float> &factors,
                const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc);
    };

    /// Primitive descriptor for resampling backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a resampling backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a resampling backward propagation
        ///     primitive.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a resampling forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const engine &aengine,
                const resampling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a resampling backward
        /// propagation primitive.
        ///
        /// @param adesc Descriptor for a resampling backward propagation
        ///     primitive.
        /// @param attr Primitive attributes to use.
        /// @param aengine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for a resampling forward
        ///     propagation primitive. It is used as a hint for deciding which
        ///     memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///     allowed to fail without throwing an exception. In this case an
        ///     empty object will be produced. This flag is optional and
        ///     defaults to false.
        primitive_desc(const desc &adesc, const primitive_attr &attr,
                const engine &aengine,
                const resampling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// @copydoc dnnl::primitive_desc_base::diff_src_desc()const
        memory::desc diff_src_desc() const;

        /// @copydoc dnnl::primitive_desc_base::diff_dst_desc()const
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    resampling_backward();

    /// Constructs a resampling backward propagation primitive.
    /// @param pd Primitive descriptor for a resampling backward propagation
    ///     primitive.
    resampling_backward(const primitive_desc &pd);
};

/// @} dnnl_api_resampling

/// @} dnnl_api_primitives

} // namespace dnnl

/// @} dnnl_api

#endif
