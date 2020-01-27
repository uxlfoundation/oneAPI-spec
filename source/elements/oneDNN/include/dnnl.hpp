/*******************************************************************************
* Copyright 2016-2019 Intel Corporation
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

/// @file dnnl.hpp
/// oneDNN API

/// @addtogroup onednn_api oneDNN API
/// @{

#ifndef DNNL_HPP
#define DNNL_HPP

/// @cond DO_NOT_DOCUMENT_THIS
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <vector>
#include <unordered_map>

#include "CL/sycl.hpp"
/// @endcond

namespace dnnl {

/// Exception class.
struct error : public std::exception {};

struct stream;
struct memory;

/// Base class for all computational primitives.
class primitive {
public:
    /// Kinds of primitives supported of oneDNN.
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
        /// An LRN primitive.
        lrn,
        /// A batch normalization primitive.
        batch_normalization,
        /// A layer normalization primitive.
        layer_normalization,
        /// An inner product primitive.
        inner_product,
        /// A rnn primitive.
        rnn,
        /// A binary primitive.
        binary,
    };

    /// Executes computations specified by the primitive in a specified stream.
    ///
    /// @param stream Stream object. The stream must belong to the same engine
    ///               as the primitive.
    /// @param args Arguments map.
    ///
    void execute(
            stream &stream, const std::unordered_map<int, memory> &args) const;

    /// Executes computations specified by the primitive in a specified stream
    /// (SYCL-aware version).
    ///
    /// @param stream Stream object. The stream must belong to the same engine
    ///               as the primitive.
    /// @param args Arguments map.
    /// @param deps Vector of SYCL events that the execution should depend on.
    ///
    /// @returns SYCL event that corresponds to the SYCL queue underlying the
    ///          @p stream.
    cl::sycl::event execute_sycl(stream &stream,
            const std::unordered_map<int, memory> &args,
            const std::vector<cl::sycl::event> &deps = {}) const;

    /// Assignment operator.
    primitive &operator=(const primitive &rhs);
};

/// Scratchpad mode.
enum class scratchpad_mode {
    /// The library manages scratchpad (default).
    library,
    /// A user shall provide the scratchpad memory to primitives.
    user,
};

/// Propagation kind.
enum class prop_kind {
    /// Undefined propagation kind.
    undef,
    /// Forward data propagation (training mode). In this mode primitives
    /// perform computations necessary for subsequent backward propagation.
    forward_training,
    /// Forward data propagation (inference mode). In this mode primitives
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

/// Algorithm kinds
enum class algorithm {
    undef,
    /// Convolution algorithm(either direct or Winograd) is chosen just in time
    convolution_auto,
    /// Direct convolution
    convolution_direct,
    /// Winograd convolution
    convolution_winograd,
    /// Direct deconvolution
    deconvolution_direct,
    /// Winograd deconvolution
    deconvolution_winograd,
    /// Eltwise: ReLU
    eltwise_relu,
    /// Eltwise: hyperbolic tangent non-linearity (tanh)
    eltwise_tanh,
    /// Eltwise: parametric exponential linear unit (elu)
    eltwise_elu,
    /// Eltwise: square
    eltwise_square,
    /// Eltwise: abs
    eltwise_abs,
    /// Eltwise: square root
    eltwise_sqrt,
    /// Eltwise: x*sigmoid(a*x)
    eltwise_swish,
    /// Eltwise: linear
    eltwise_linear,
    /// Eltwise: bounded_relu
    eltwise_bounded_relu,
    /// Eltwise: soft_relu
    eltwise_soft_relu,
    /// Eltwise: logistic
    eltwise_logistic,
    /// Eltwise: exponent
    eltwise_exp,
    /// Eltwise: gelu
    eltwise_gelu,
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
    /// GRU cell with linear before reset
    ///
    /// Modification of original GRU cell. Differs from
    /// #dnnl::algorithm::vanilla_gru in how the new memory gate is
    /// calculated:
    /// \f[ c_t = tanh(W_c*x_t + b_{c_x} + r_t*(U_c*h_{t-1}+b_{c_h})) \f]
    /// Primitive expects 4 biases on input:
    /// \f$[b_{u}, b_{r}, b_{c_x}, b_{c_h}]\f$
    lbr_gru,
    /// Binary add
    binary_add,
    /// Binary mul
    binary_mul,
};

/// Flags for batch normalization primitive (can be combined via '|')
enum class normalization_flags : unsigned {
    /// Use global statistics
    ///
    /// If specified
    ///  - on forward propagation use mean and variance provided by user (input)
    ///  - on backward propagation reduces the amount of computations, since
    ///    mean and variance are considered as constants
    ///
    ///  If not specified:
    ///   - on forward propagation mean and variance are computed and stored in
    ///     output
    ///   - on backward propagation compute full derivative wrt to data
    use_global_stats,

    /// Use scale and shift parameters
    ///
    /// If specified:
    ///  - on forward propagation use scale and shift (aka scale and bias) for
    ///    the batch normalization results
    ///  - on backward propagation
    ///    (for prop_kind == #dnnl::prop_kind::backward) compute
    ///    diff wrt to scale and shift (hence one extra output used)
    ///
    /// If not specified:
    ///  - on backward propagation
    ///    prop_kind == #dnnl::prop_kind::backward_data has the
    ///    same behavior as prop_kind == #dnnl::prop_kind::backward
    use_scale_shift,

    /// Fuse with ReLU
    ///
    /// If specified:
    ///  - on inference this option behaves the same as if the primitive were
    ///    fused with ReLU via post ops API
    ///  - on training primitive requires workspace (required to be able to
    ///    perform backward propagation)
    fuse_norm_relu
};

/// Bitwise OR operation for batch normalization flags.
normalization_flags operator|(normalization_flags lhs, normalization_flags rhs);

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

/// Primitive descriptor query specification.
enum class query {
    /// no query
    undef,

    /// execution engine
    engine,
    /// primitive kind
    primitive_kind,

    /// number of inputs expected
    num_of_inputs_s32,
    /// number of outputs expected
    num_of_outputs_s32,

    /// runtime estimation (seconds), unimplemented
    time_estimate_f64,
    /// memory consumption (bytes)
    ///
    /// extra (scratch) memory, additional to all inputs and outputs memory
    memory_consumption_s64,

    /// scratchpad engine
    ///
    /// engine to be used for creating scratchpad memory
    scratchpad_engine,

    /// reorder source engine
    reorder_src_engine,
    /// reorder destination engine
    reorder_dst_engine,

    /// implementation name
    impl_info_str,

    /// operation descriptor
    op_d,
    /// convolution descriptor
    convolution_d,
    /// deconvolution descriptor
    deconvolution_d,
    /// shuffle descriptor
    shuffle_d,
    /// eltwise descriptor
    eltwise_d,
    /// softmax descriptor
    softmax_d,
    /// pooling descriptor
    pooling_d,
    /// lrn descriptor
    lrn_d,
    /// batch normalization descriptor
    batch_normalization_d,
    /// layer normalization descriptor
    layer_normalization_d,
    /// inner product descriptor
    inner_product_d,
    /// rnn descriptor
    rnn_d,
    /// binary descriptor
    binary_d,

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
};

/// Post-ops.
///
/// Post-ops are performed after the computation specified by a primitive and
/// allow optimizing away bandwidth-bound operations.
struct post_ops {
    /// Constructs an empty sequence of post operations.
    post_ops();

    /// Returns the number of post-ops entries.
    int len() const;

    /// Returns the primitive kind of post-op at entry with a certain index.
    ///
    /// @param index Index of the post-op to return the kind for.
    ///
    /// @returns primitive kind of the postop at the specified index.
    primitive::kind kind(int index) const;

    /// Appends an accumulation (sum) post operation. Prior to accumulating the
    /// result, the previous value would be multiplied by a scaling factor
    /// @p scale.
    ///
    /// The kind of this post operation is #dnnl::primitive::kind::sum.
    ///
    /// This feature might improve performance for cases like residual learning
    /// blocks, where the result of convolution is accumulated to the previously
    /// computed activations. The parameter @p scale might be extreme for the
    /// integer-based computations when the result and previous activations have
    /// different logical scaling factors.
    ///
    /// In the simplest case when the accumulation is the only post operation,
    /// the computations would be:
    ///
    /// dst[] <- scale * dst[] + op(...) instead of dst[] <- op(...)
    ///
    /// @note
    ///     This post operation (as well as all the others) disregards the
    ///     original layout of the destination; that is, the layout of the
    ///     original destination is expected to be the same as the layout of the
    ///     stored destination.
    ///
    /// @param scale Scaling factor.
    void append_sum(float scale = 1.);

    /// Returns the parameters of a sum post-op.
    ///
    /// @param index Index of the sum post-op.
    /// @param scale Scaling factor of the sum post-op.
    void get_params_sum(int index, float &scale) const;

    /// Appends an eltwise post operation.
    ///
    /// The kind of this post operation is #dnnl::primitive::kind::eltwise.
    ///
    /// In the simplest case when the eltwise is the only post operation, the
    /// computations would be:
    /// dst[] <- scale * eltwise_op ( op(...) ) instead of dst[] <- op(...)
    /// where eltwise_op is configured with the given parameters.
    ///
    /// @param scale Scaling factor.
    /// @param alg Eltwise algorithm.
    /// @param alpha Alpha parameter for the eltwise algorithm.
    /// @param beta Beta parameter for the eltwise algorithm.
    void append_eltwise(float scale, algorithm alg, float alpha, float beta);

    /// Returns the eltwise parameters of a post-up.
    ///
    /// @param index Index of the post-op.
    /// @param scale Scaling factor.
    /// @param alg Eltwise algorithm.
    /// @param alpha Alpha parameter for the eltwise algorithm.
    /// @param beta Beta parameter for the eltwise algorithm.
    void get_params_eltwise(int index, float &scale, algorithm &alg,
            float &alpha, float &beta) const;
};

/// Primitive attributes
struct primitive_attr {
    /// Constructs default (empty) primitive attributes.
    primitive_attr();

    /// Returns the scratchpad mode.
    scratchpad_mode get_scratchpad_mode() const;

    /// Sets scratchpad mode.
    void set_scratchpad_mode(scratchpad_mode mode);

    /// Returns the output scaling factors correspondence mask and vector.
    ///
    /// @param mask Scaling factors correspondence mask that defines the
    ///             correspondence between the output tensor dimensions and
    ///             the @p scales vector. The set i-th bit indicates that a
    ///             dedicated scaling factor should be used for any dimension
    ///             j with j >= i. The mask value of 0 implies a common
    ///             scaling factor for the whole output tensor.
    /// @param scales Vector of output scaling factors.
    void get_output_scales(int &mask, std::vector<float> &scales) const;

    /// Sets the output scale correspondence mask and values.
    ///
    /// @param mask Scaling factors correspondence mask that defines the
    ///             correspondence between the output tensor dimensions and
    ///             the @p scales vector. The set i-th bit indicates that a
    ///             dedicated scaling factor should be used for any dimension
    ///             j with j >= i. Set the mask to 0 to use a common scaling
    ///             factor for the whole output tensor.
    /// @param scales Vector of output scaling factors.
    ///
    /// @note
    ///      The order of dimensions does not depend on how elements are laid
    ///      out in memory. For example:
    ///       - for a 2D CNN activations tensor the order is always (n, c)
    ///       - for a 4D CNN activations tensor the order is always (n, c, h, w)
    ///       - for a 5D CNN weights tensor the order is always
    ///         (g, oc, ic, kh, kw)
    void set_output_scales(int mask, const std::vector<float> &scales);

    /// @returns post-ops previously set via set_post_ops().
    const post_ops get_post_ops() const;

    /// Sets post-ops.
    ///
    /// @param ops Post-ops object to copy post-ops from.
    void set_post_ops(const post_ops ops);

    /// Sets quantization scale and shift parameters for RNN data tensors.
    ///
    /// For performance reasons, the low-precision configuration of the RNN
    /// primitive expects input activations to have the unsigned 8-bit integer
    /// data type. The scale and shift parameters are used to quantize
    /// floating-point data to unsigned integer must be passed to the RNN
    /// primitive using attributes.  The quantization formula is scale * (data
    /// + shift).
    ///
    /// @note Quantization scale and shift are common for src_layer, src_iter,
    ///     dst_iter, and dst_layer.
    ///
    /// @param scale The value to scale the data by.
    /// @param shift The value to shift the data by.
    void set_rnn_data_qparams(float scale, float shift);

    /// Sets quantization scaling factors for RNN weights tensors. The
    /// low-precision configuration of the RNN primitive expects input weights
    /// to have the signed int8 data type. The scaling factors are used to
    /// quantize floating-point data to signed integer and need to be passed
    /// to RNN primitives using attributes.
    ///
    /// @param mask Scaling factors correspondence mask that defines the
    ///             correspondence between the output tensor dimensions and
    ///             the @p scales vector. The set i-th bit indicates that a
    ///             dedicated scaling factor should be used for any dimension
    ///             j with j >= i. Set the mask to 0 to use a common scaling
    ///             factor for the whole output tensor.
    /// @param scales Vector of output scaling factors.
    ///
    /// @note
    ///      The dimension order is always native and does not depend on the
    ///      actual layout used. For example, five-dimensional weights always
    ///      have (l, d, i, g, o) logical dimension ordering.
    ///
    /// @note
    ///     Quantization scales are common for weights_layer and
    ///     weights_iteration
    ///
    /// @note
    ///     There is no way to check whether @p count corresponds to @p mask
    ///     until an actual primitive descriptor is created, so it is the user's
    ///     responsibility to set proper values. The following formula must
    ///     hold:
    ///
    ///     \f[count = \prod\limits_{d \in mask} output.dims[d]\f]
    void set_rnn_weights_qparams(int mask, const std::vector<float> &scales);
};

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
    /// @param kind The kind of engines to count.
    static size_t get_count(kind kind);

    /// Constructs an engine.
    ///
    /// @param kind The kind of engine to construct.
    /// @param index The index of the engine. Must be less than the value
    ///              returned by #get_count() for this particular kind
    ///              of engine.
    engine(kind kind, size_t index);

    /// Constructs an engine from SYCL device and context objects.
    ///
    /// @param kind The kind of engine to construct.
    /// @param dev SYCL device.
    /// @param ctx SYCL context.
    engine(kind kind, const cl::sycl::device &dev,
            const cl::sycl::context &ctx);

    /// @returns the kind of the engine.
    kind get_kind() const;

    /// Returns the underlying SYCL context object.
    cl::sycl::context get_sycl_context() const;

    /// Returns the underlying SYCL device object.
    cl::sycl::device get_sycl_device() const;
};

/// An execution stream.
struct stream {
    /// Stream flags. Can be combined using the bitwise OR operator.
    enum class flags : unsigned {
        /// Default order execution. Either in-order or out-of-order depending
        /// on the engine runtime.
        default_order,
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
    /// controlled by the specified flags
    ///
    /// @param engine Engine to create the stream on.
    /// @param flags Flags controlling stream behavior.
    stream(const engine &engine, flags flags = flags::default_flags);

    /// Constructs a stream for the specified engine and the SYCL queue.
    ///
    /// @param engine Engine to create the stream on.
    /// @param queue SYCL queue to use for the stream.
    stream(const engine &engine, cl::sycl::queue &queue);

    /// @returns the underlying SYCL queue object.
    cl::sycl::queue get_sycl_queue() const;

    /// Waits for all primitives executing in the stream to finish.
    stream &wait();
};

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

    /// Data type of elements stored in a memory object.
    enum class data_type {
        /// Undefined data type (used for empty memory descriptors).
        undef,
        /// 16-bit/half-precision floating point.
        f16,
        /// non-standard 16-bit floating point with 7-bit mantissa.
        bf16,
        /// 32-bit/single-precision floating point.
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
    ///  - Domain-agnostic names, i.e. names the do not depend on the tensor
    ///    usage in the specific primitive. These names use letters from `a`
    ///    to `l` to denote logical dimensions and form the order in which the
    ///    dimensions are laid in memory. For example,
    ///    #dnnl::memory::format_tag::ab is used to denote 2D tensor where the
    ///    second logical dimension (aka `b`) is the innermost, i.e. has
    ///    stride = 1, and the first logical dimension (`a`) laid out in
    ///    memory with stride equal to the size of second dimension. On the
    ///    other hand, #dnnl::memory::format_tag::ba is the transposed version
    ///    of the same tensor: the outermost dimension (`a`) becomes the
    ///    innermost one.
    ///
    ///  - Domain-specific names, i.e. names that make sense only in the
    ///    context of a certain domain, such as CNN. This names are
    ///    aliases to the corresponding domain-agnostic tags and used mostly
    ///    for the convenience. For example, #dnnl::memory::format_tag::nc
    ///    is used to denote 2D CNN activations tensor memory format, where
    ///    the channels dimension is the innermost one and the batch dimension
    ///    is the outermost one. Moreover, #dnnl::memory::format_tag::nc is
    ///    an alias for #dnnl::memory::format_tag::ab, since for oneDNN
    ///    CNN primitives the logical dimensions of activations tensors come
    ///    in order: batch, channels, spatial.  In other words, batch
    ///    corresponds to the first logical dimension (`a`), channels
    ///    correspond to the second one (`b`).
    ///
    /// The following domain-specific notation applies to memory format tags:
    ///  - @c 'n' denotes the mini-batch dimension
    ///  - @c 'c' denotes a channels dimension
    ///  - When there are multiple channel dimensions (for example,
    ///    in convolution weights tensor), @c 'i' and @c 'o' denote dimensions
    ///    of input and output channels
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
        acdb,
        /// permuted 4D tensor
        bacd,
        /// permuted 4D tensor
        bcda,
        /// permuted 4D tensor
        cdba,

        /// plain 5D tensor
        abcde,
        /// permuted 5D tensor
        abdec,
        /// permuted 5D tensor
        acbde,
        /// permuted 5D tensor
        acdeb,
        /// permuted 5D tensor
        bcdea,
        /// permuted 5D tensor
        cdeba,
        /// permuted 5D tensor
        decab,
        /// plain 6D tensor
        abcdef,

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
        /// 5D CNN weights tensor; an alias for #dnnl::memory::format_tag::bcdea
        idhwo = bcdea,

        /// 4D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcd
        goiw = abcd,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcde
        goihw = abcde,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::decab
        hwigo = decab,
        /// 5D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::acbde
        giohw = acbde,
        /// 6D CNN weights tensor with groups; an alias for #dnnl::memory::format_tag::abcdef
        goidhw = abcdef,

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
        /// Constructs a zero (empty) memory descriptor. Such memory
        /// descriptor may be used to indicate absence of an argument.
        desc();

        /// Constructs a memory descriptor.
        ///
        /// @param dims Tensor dimensions.
        /// @param data_type Data precision/type.
        /// @param format_tag Memory format tag.
        desc(const memory::dims &dims, data_type data_type,
                format_tag format_tag);

        /// Constructs a memory descriptor by strides.
        ///
        /// @param dims Tensor dimensions.
        /// @param data_type Data precision/type.
        /// @param strides Strides for each of the dimensions.
        desc(const memory::dims &dims, data_type data_type,
                const memory::dims &strides);

        /// Constructs a sub-memory descriptor.
        //
        /// @param dims Sizes of a sub-memory.
        /// @param offsets Offsets of a sub-memory from the encompassing
        ///                memory object in each dimension
        desc submemory_desc(
                const memory::dims &dims, const memory::dims &offsets);

        /// Constructs a memory descriptor by reshaping existing one.
        //
        /// @param dims New dimensions. The product of dimensions must
        /// remain constant.
        desc reshape(const memory::dims &dims);

        /// Returns the number of bytes required to allocate memory buffer for
        /// the memory object described by this memory descriptor including
        /// the padding area.
        size_t get_size() const;

        /// Returns true if the memory descriptor describes an empty memory.
        bool is_zero() const;

        /// An equality operator.
        /// @param other Another memory descriptor.
        /// @returns Whether this and the other memory descriptors have
        ///          the same format tag, dimensions, strides, blocking, etc.
        bool operator==(const desc &other) const;

        /// An inequality operator.
        /// @param other Another memory descriptor.
        /// @returns Whether this and the other memory descriptors describe
        ///          different memory.
        bool operator!=(const desc &other) const;
    };

    // Default constructor.
    //
    // Constructs an empty memory object which can be used to indicate absence
    // of a parameter.
    memory();

    /// Constructs a memory object.
    ///
    /// @param md Memory descriptor.
    /// @param engine Engine to store the data on.
    /// @param handle Handle of the memory buffer to use as an underlying
    ///               storage. On CPU this is a pointer.
    memory(const desc &md, const engine &engine, void *handle);

    /// Constructs a memory object using a SYCL buffer as the underlying
    /// storage.
    ///
    /// @param md Memory descriptor.
    /// @param engine Engine to store the data on.
    /// @param buf SYCL buffer as the underlying store.
    template <typename T, int ndims = 1>
    memory(const desc &md, const engine &engine,
            cl::sycl::buffer<T, ndims> &buf);

    /// Constructs a memory.
    ///
    /// The underlying storage for the memory will be allocated by the library.
    ///
    /// @param md Memory descriptor.
    /// @param engine Engine to store the data on.
    memory(const desc &md, const engine &engine);

    /// Returns the associated memory descriptor.
    desc get_desc() const;

    /// Returns the associated engine.
    engine get_engine() const;

    /// Returns the underlying memory buffer.
    ///
    /// On the CPU engine, or when using USM, this is a pointer to the
    /// allocated memory.
    void *get_data_handle() const;

    /// Sets memory buffer.
    ///
    /// @param handle Memory buffer to use as the underlying storage. It must
    ///               have at least get_desc().get_size() bytes allocated.
    void set_data_handle(void *handle) const;

    /// Returns the underlying SYCL buffer object.
    ///
    /// @tparam T Type of the requested buffer.
    /// @tparam ndims Number of dimensions of the requested buffer.
    /// @param offset Offset within the returned buffer at which the memory
    ///               object's data starts. Only meaningful for 1D buffers.
    template <typename T, int ndims = 1>
    cl::sycl::buffer<T, ndims> get_sycl_buffer(size_t *offset = nullptr) const;

    /// Sets the underlying buffer to the given SYCL buffer.
    ///
    /// @tparam T Type of the buffer.
    /// @tparam ndims Number of dimensions of the buffer.
    /// @param buf SYCL buffer.
    template <typename T, int ndims>
    void set_sycl_buffer(cl::sycl::buffer<T, ndims> &buf);
};

/// Base class for all primitive descriptors.
struct primitive_desc_base {
    /// Default constructor. Produces an empty object.
    ///
    /// Constructs an empty primitive descriptor base.
    primitive_desc_base();

    /// Returns the engine of the primitive descriptor.
    engine get_engine() const;

    /// Returns implementation name.
    const char *impl_info_str() const;

    /// Queries for an memory::dim value (same as int64_t).
    memory::dim query_s64(query what) const;

    /// Queries for and returns requested memory descriptor.
    memory::desc query_md(query what, int idx = 0) const;

    /// @returns scratchpad memory descriptor.
    ///
    /// @returns a zero_md if no scratchpad is required by the primitive
    /// descriptor.
    memory::desc scratchpad_desc() const;

    /// @returns the engine that owns the scratchpad memory.
    engine scratchpad_engine() const;

    /// Returns the primitive attributes.
    primitive_attr get_primitive_attr() const;
};

/// Reorder primitive.
struct reorder : public primitive {
    /// Primitive descriptor for reorder primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a reorder primitive using the description of the source
        /// (@p src_engine and @p src_md) and destination (@p dst_engine and
        /// @p dst_md) memory, and an @p attr attributes.
        primitive_desc(const engine &src_engine, const memory::desc &src_md,
                const engine &dst_engine, const memory::desc &dst_md,
                const primitive_attr &attr = primitive_attr());

        /// Constructs a reorder primitive moving data between memory objects
        /// @p src and @p dat with @p attr attributes.
        ///
        /// Note that the memory objects are used only to obtain information
        /// about memory descriptors and engines.
        primitive_desc(const memory &src, const memory &dst,
                const primitive_attr &attr = primitive_attr());

        /// @returns the engine on which the source memory is allocated.
        engine get_src_engine() const;

        /// @returns the engine on which the destination memory is allocated.
        engine get_dst_engine() const;
    };

    /// Default constructor. Produces an empty object.
    reorder();

    /// Constructs a reorder primitive from a primitive descriptor @p pd
    /// of a corresponding type.
    reorder(const primitive_desc &pd);

    /// Constructs a reorder primitive that would reorder data between memory
    /// objects having same memory descriptors as memory objects @p src and @p
    /// dst.
    ///
    /// @param src Source memory object.
    /// @param dst Destination memory object.
    reorder(const memory &src, const memory &dst);

    /// Executes the reorder primitive.
    ///
    /// @param stream Stream object. The stream must belong to the same engine
    ///               as the primitive.
    /// @param src Source memory object.
    /// @param dst Destination memory object.
    void execute(stream stream, memory &src, memory &dst);

    /// Executes the reorder primitive (SYCL-aware version)
    ///
    /// @param stream Stream object. The stream must belong to the same engine
    ///               as the primitive.
    /// @param src Source memory object.
    /// @param dst Destination memory object.
    /// @param deps Vector of SYCL events that the execution should depend on.
    ///
    /// @returns SYCL event that corresponds to the SYCL queue underlying the
    ///          @p stream.
    cl::sycl::event execute_sycl(stream &stream, memory &src, memory &dst,
            const std::vector<cl::sycl::event> &deps = {});
};

/// Tensor concatenation (concat) primitive.
struct concat : public primitive {
    /// Primitive descriptor for concat primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for an out-of-place
        /// concatenation primitive.
        ///
        /// @param dst Destination memory descriptor
        /// @param concat_dimension Source tensors will be concatenated over
        ///                         dimension with this index. Note that order
        ///                         of dimensions does not depend on memory
        ///                         format.
        /// @param srcs Vector of source memory descriptors.
        /// @param engine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const memory::desc &dst, int concat_dimension,
                const std::vector<memory::desc> &srcs, const engine &engine,
                const primitive_attr &attr = primitive_attr());

        /// Constructs a primitive descriptor for an out-of-place
        /// concatenation primitive.
        ///
        /// This version derives the destination memory descriptor
        /// automatically.
        ///
        /// @param concat_dimension Source tensors will be concatenated over
        ///                         dimension with this index. Note that order
        ///                         of dimensions does not depend on memory
        ///                         format.
        /// @param srcs Vector of source memory descriptors.
        /// @param engine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(int concat_dimension,
                const std::vector<memory::desc> &srcs, const engine &engine,
                const primitive_attr &attr = primitive_attr());

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    concat();

    /// Constructs a concatenation primitive from a primitive descriptor @p pd
    /// of a corresponding type.
    concat(const primitive_desc &pd);
};

/// Summation (sum) primitive.
struct sum : public primitive {
    /// Primitive descriptor for sum primitive.
    struct primitive_desc : public dnnl::primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs an out-of-place primitive descriptor for a sum
        /// primitive.
        ///
        /// @param dst Destination memory descriptor.
        /// @param scales Vector of scales to multiply data in each source
        ///               memory by.
        /// @param srcs Vector of source memory descriptors.
        /// @param engine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const memory::desc &dst,
                const std::vector<float> &scales,
                const std::vector<memory::desc> &srcs, const engine &engine,
                const primitive_attr &attr = primitive_attr());

        /// Constructs an out-of-place primitive descriptor for a sum
        /// primitive.
        ///
        /// This version derives the destination memory descriptor
        /// automatically.
        ///
        /// @param scales Vector of scales to multiply data in each source
        ///               memory by.
        /// @param srcs Vector of source memory descriptors.
        /// @param engine Engine to perform the operation on.
        /// @param attr Primitive attributes to use (optional).
        primitive_desc(const std::vector<float> &scales,
                const std::vector<memory::desc> &srcs, const engine &engine,
                const primitive_attr &attr = primitive_attr());

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    sum();

    /// Constructs a sum primitive from a primitive descriptor @p pd of a
    /// corresponding type.
    sum(const primitive_desc &pd);
};

/// A base class for primitive descriptors of all primitives that have an
/// operation descriptor and that support iteration over multiple
/// implementations.
struct primitive_desc : public dnnl::primitive_desc_base {
    /// Default constructor. Produces an empty object.
    primitive_desc();
};

/// Convolution forward propagation primitive.
struct convolution_forward : public primitive {
    /// Descriptor for convolution forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a convolution forward propagation
        /// primitive without bias using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), @p
        /// algorithm, memory descriptors, @p strides, @p padding_l, and @p
        /// padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a convolution forward propagation
        /// primitive with bias using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), @p
        /// algorithm, memory descriptors, @p strides, @p padding_l, and @p
        /// padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution forward
        /// propagation primitive without bias using @p prop_kind (possible
        /// values are #dnnl::forward_training and #dnnl::forward_inference),
        /// @p algorithm, memory descriptors, @p strides, @p dilates, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &dilates,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution forward
        /// propagation primitive with bias using @p prop_kind (possible
        /// values are #dnnl::forward_training and #dnnl::forward_inference),
        /// @p algorithm, memory descriptors, @p strides, @p dilates, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
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
        /// @param desc Descriptor for convolution forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for convolution forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc creation
        /// time.
        memory::desc bias_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_forward();

    /// Constructs a convolution forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    convolution_forward(const primitive_desc &pd);
};

/// Convolution backward propagation primitive.
struct convolution_backward_data : public primitive {

    /// Descriptor for convolution backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a convolution backward propagation
        /// primitive using @p algorithm, memory descriptors, @p strides, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution backward
        /// propagation using @p algorithm, memory descriptors, @p strides, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &diff_src_desc,
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
        /// @param desc Descriptor for convolution backward propagation
        ///             primitive.
        /// @param engine Engine to perform the operation on.
        /// @param hint_fwd_pd Primitive descriptor for convolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for convolution backward propagation
        ///             primitive.
        /// @param engine Engine to perform the operation on.
        /// @param attr Primitive attributes to use.
        /// @param hint_fwd_pd Primitive descriptor for convolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_backward_data();

    /// Constructs a convolution backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    convolution_backward_data(const primitive_desc &pd);
};

/// Convolution weights update primitive.
struct convolution_backward_weights : public primitive {
    /// Descriptor for convolution weights update primitive.
    struct desc {
        /// Constructs a descriptor for a convolution weights update primitive
        /// with bias using @p algorithm, memory descriptors, @p strides, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a convolution weights update primitive
        /// without bias using @p algorithm, memory descriptors, @p strides,
        /// @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution weights update
        /// primitive with bias using @p algorithm, memory descriptors, @p
        /// strides, @p dilates @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for dilated convolution weights update
        /// primitive without bias using @p algorithm, memory descriptors, @p
        /// strides, @p dilates @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a convolution weights update primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a convolution weights update
        /// primitive.
        ///
        /// @param desc Descriptor for convolution weights update primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for convolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a convolution weights update
        /// primitive.
        ///
        /// @param desc Descriptor for convolution weights update primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for convolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const convolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the diff weights memory descriptor.
        memory::desc diff_weights_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    convolution_backward_weights();

    /// Constructs a convolution weights update primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    convolution_backward_weights(const primitive_desc &pd);
};

/// Deconvolution forward propagation primitive.
struct deconvolution_forward : public primitive {
    /// Descriptor for convolution forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution forward propagation
        /// primitive with bias using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), @p
        /// algorithm, memory descriptors, @p strides, @p padding_l, and @p
        /// padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for a deconvolution forward propagation
        /// primitive without bias using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), @p
        /// algorithm, memory descriptors, @p strides, @p padding_l, and @p
        /// padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated deconvolution forward
        /// propagation primitive with bias using @p prop_kind (possible
        /// values are #dnnl::forward_training and #dnnl::forward_inference),
        /// @p algorithm memory descriptors, @p strides, @p dilates, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &weights_desc,
                const memory::desc &bias_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &dilates,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated deconvolution forward
        /// propagation primitive without bias using @p prop_kind (possible
        /// values are #dnnl::forward_training and #dnnl::forward_inference),
        /// @p algorithm, memory descriptors, @p strides, @p dilates, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm algorithm,
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
        /// @param desc Descriptor for deconvolution forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for deconvolution forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_forward();

    /// Constructs a deconvolution forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    deconvolution_forward(const primitive_desc &pd);
};

/// Deconvolution backward propagation primitive.
struct deconvolution_backward_data : public primitive {
    /// Descriptor for deconvolution backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution backward propagation
        /// primitive using @p algorithm, memory descriptors, @p strides, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs descriptor for dilated deconvolution backward
        /// propagation primitive using @p algorithm, memory descriptors, @p
        /// strides, @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &diff_src_desc,
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
        /// @param desc Descriptor for deconvolution backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for deconvolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for deconvolution backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for deconvolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_backward_data();

    /// Constructs a deconvolution backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    deconvolution_backward_data(const primitive_desc &pd);
};

/// Deconvolution weights update primitive.
struct deconvolution_backward_weights : public primitive {
    /// Descriptor for deconvolution weights update primitive.
    struct desc {
        /// Constructs a descriptor for a deconvolution weights primitive update
        /// with bias using @p algorithm, memory descriptors, @p strides, @p
        /// padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for a deconvolution weights update primitive
        /// without bias using @p algorithm, memory descriptors, @p strides,
        /// @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &padding_l, const memory::dims &padding_r);

        /// Constructs a descriptor for dilated deconvolution weights update
        /// primitive with bias using @p algorithm, memory descriptors, @p
        /// strides, @p dilates @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);

        /// Constructs a descriptor for dilated deconvolution weights update
        /// primitive without bias using @p algorithm, memory descriptors, @p
        /// strides, @p dilates @p padding_l, and @p padding_r.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(algorithm algorithm, const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &dilates, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for a deconvolution weights update primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a deconvolution weights
        /// update primitive.
        ///
        /// @param desc Descriptor for deconvolution weights update primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for deconvolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a deconvolution weights
        /// update primitive.
        ///
        /// @param desc Descriptor for deconvolution weights update primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for deconvolution forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const deconvolution_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the diff weights memory descriptor.
        memory::desc diff_weights_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    deconvolution_backward_weights();

    /// Constructs a deconvolution weights update primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    deconvolution_backward_weights(const primitive_desc &pd);
};

/// Local response normalization (LRN) forward propagation primitive.
struct lrn_forward : public primitive {
    /// Descriptor for LRN forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for LRN forward propagation primitive
        /// using @p prop_kind (acceptable values are #dnnl::forward_training
        /// and #dnnl::forward_inference), @p algorithm, memory descriptor @p
        /// data_desc, and regularization parameters @p local_size, @p alpha,
        /// @p beta, and @p k.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, memory::dim local_size,
                float alpha, float beta, float k = 1.f);
    };

    /// Primitive descriptor for LRN forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LRN forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LRN forward propagation primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LRN forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LRN forward propagation primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lrn_forward();

    /// Constructs an LRN forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    lrn_forward(const primitive_desc &pd);
};

/// Local response normalization (LRN) backward propagation primitive.
struct lrn_backward : public primitive {
    /// Descriptor for LRN backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for LRN backward propagation primitive
        /// using @p algorithm, memory descriptors @p data_desc and @p
        /// diff_data_desc, and regularization parameters @p local_size, @p
        /// alpha, @p beta, and @p k.
        desc(algorithm algorithm, const memory::desc &data_desc,
                const memory::desc &diff_data_desc, memory::dim local_size,
                float alpha, float beta, float k = 1.f);
    };

    /// Primitive descriptor for LRN backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LRN backward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LRN backward propagation primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for LRN forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const lrn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LRN backward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LRN backward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for LRN forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const lrn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lrn_backward();

    /// Constructs an LRN backward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    lrn_backward(const primitive_desc &pd);
};

/// Pooling forward propagation primitive.
struct pooling_forward : public primitive {
    /// Descriptor for pooling forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for pooling forward propagation primitive
        /// using @p prop_kind (acceptable values are #dnnl::forward_training
        /// and #dnnl::forward_inference), @p algorithm, memory descriptors,
        /// and pooling parameters in the spatial domain: @p strides, @p
        /// kernel sizes, @p padding_l, and @p padding_r.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, const memory::desc &dst_desc,
                const memory::dims &strides, const memory::dims &kernel,
                const memory::dims &padding_l, const memory::dims &padding_r);
    };

    /// Primitive descriptor for pooling forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for pooling forward propagation primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for pooling forward propagation primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    pooling_forward();

    /// Constructs an pooling forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    pooling_forward(const primitive_desc &pd);
};

/// Pooling backward propagation primitive.
struct pooling_backward : public primitive {
    /// Descriptor for pooling backward propagation primitive.
    struct desc {
        /// Constructs a pooling descriptor for pooling backward propagation
        /// primitive using @p algorithm, memory descriptors, and pooling
        /// parameters in the spatial domain: @p strides, @p kernel sizes, @p
        /// padding_l, and @p padding_r.
        desc(algorithm algorithm, const memory::desc &diff_src_desc,
                const memory::desc &diff_dst_desc, const memory::dims &strides,
                const memory::dims &kernel, const memory::dims &padding_l,
                const memory::dims &padding_r);
    };

    /// Primitive descriptor for pooling backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for pooling forward propagation primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for pooling forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const pooling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for a pooling forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for pooling forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for pooling forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const pooling_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    pooling_backward();

    /// Constructs an pooling backward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    pooling_backward(const primitive_desc &pd);
};

/// Elementwise unary operation forward propagation primitive.
///
/// This primitive computes unary elementwise operations such as rectified
/// linear unit (ReLU), Sigmoid, tanh or others for each element of the
/// source.
///
/// Both forward and backward propagation primitives support in-place
/// operation; that is, src and dst can point to the same memory for forward
/// propagation, and diff_dst and diff_src can point to the same memory for
/// backward propagation.
struct eltwise_forward : public primitive {
    /// Descriptor for elementwise forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for elementwise forward propagation
        /// primitive using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), @p
        /// algorithm algorithm, memory descriptor @p data_desc, @p alpha, and
        /// @p beta parameters.
        desc(prop_kind prop_kind, algorithm algorithm,
                const memory::desc &src_desc, float alpha = 0, float beta = 0);
    };

    /// Primitive descriptor for elementwise forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for elementwise forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for elementwise forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for elementwise forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for elementwise forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    eltwise_forward();

    /// Constructs an elementwise forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    eltwise_forward(const primitive_desc &pd);
};

/// Elementwise unary operation backward propagation primitive.
///
/// @sa eltwise_forward
struct eltwise_backward : public primitive {
    /// Descriptor for elementwise backward propagation primitive.
    struct desc {
        /// Constructs an eltwise descriptor for backward propagation using @p
        /// algorithm algorithm memory descriptors @p diff_data_desc and @p
        /// data_desc, and the @p alpha and @p beta parameters.
        desc(algorithm algorithm, const memory::desc &diff_data_desc,
                const memory::desc &data_desc, float alpha = 0, float beta = 0);
    };

    /// Primitive descriptor for eltwise backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for elementwise backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for elementwise backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for elementwise forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const eltwise_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for elementwise backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for elementwise backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for elementwise forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const eltwise_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    eltwise_backward();

    /// Constructs an elementwise backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    eltwise_backward(const primitive_desc &pd);
};

/// Softmax forward propagation primitive.
struct softmax_forward : public primitive {
    /// Descriptor for softmax forward propagation primitive.
    struct desc {
        /// Constructs a softmax descriptor for forward propagation using @p
        /// prop_kind (acceptable values are #dnnl::forward_training and
        /// #dnnl::forward_inference) and memory descriptor @p data_desc.
        desc(prop_kind prop_kind, const memory::desc &data_desc,
                int softmax_axis);
    };

    /// Primitive descriptor for softmax forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for softmax forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for softmax forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for softmax forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for softmax forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    softmax_forward();

    /// Constructs an softmax forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    softmax_forward(const primitive_desc &pd);
};

/// Softmax backward propagation primitive.
struct softmax_backward : public primitive {
    /// Descriptor for softmax backward propagation primitive.
    struct desc {
        /// Constructs a softmax descriptor for backward propagation using
        /// memory descriptors @p diff_desc and @p data_desc.
        desc(const memory::desc &diff_desc, const memory::desc &data_desc,
                int softmax_axis);
    };

    /// Primitive descriptor for softmax backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for softmax backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for softmax backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for softmax forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const softmax_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for softmax backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for softmax backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for softmax forward
        ///                    propagation primitive. It is used as a hint
        ///                    when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const softmax_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    softmax_backward();

    /// Constructs an softmax backward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    softmax_backward(const primitive_desc &pd);
};

/// Batch normalization forward propagation primitive.
struct batch_normalization_forward : public primitive {
    /// Descriptor for batch normalization forward propagation primitive.
    struct desc {
        /// Constructs a batch normalization descriptor for forward
        /// propagation using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), memory
        /// descriptor @p data_desc, normalization parameter @p epsilon, and
        /// flags set using bit @p flags.
        desc(prop_kind prop_kind, const memory::desc &src_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for batch normalization forward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for batch normalization forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for batch normalization forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for batch normalization forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for batch normalization forward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the weights (scale and shift) memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the mean memory descriptor.
        memory::desc mean_desc() const;

        /// Returns the variance memory descriptor.
        memory::desc variance_desc() const;
    };

    /// Default constructor. Produces an empty object.
    batch_normalization_forward();

    /// Constructs an batch normalization forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    batch_normalization_forward(const primitive_desc &pd);
};

/// Batch normalization backward propagation primitive.
struct batch_normalization_backward : public primitive {
    /// Descriptor for batch normalization backward propagation primitive.
    struct desc {
        /// Constructs a batch normalization descriptor for backward
        /// propagation with respect to data and scale-shift parameters using
        /// memory descriptors @p data_desc and @p diff_data_desc,
        /// normalization parameter @p epsilon, and flags set using bit @p
        /// flags.
        desc(prop_kind prop_kind, const memory::desc &diff_data_desc,
                const memory::desc &data_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for batch normalization backward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for batch normalization backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for batch normalization backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for batch normalization
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const batch_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for batch normalization backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for batch normalization backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for batch normalization
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const batch_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the mean memory descriptor.
        memory::desc mean_desc() const;

        /// Returns the variance memory descriptor.
        memory::desc variance_desc() const;

        /// Returns the weights (scale and shift) memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff weights (scale and shift) memory descriptor.
        memory::desc diff_weights_desc() const;
    };

    /// Default constructor. Produces an empty object.
    batch_normalization_backward();

    /// Constructs an batch normalization backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    batch_normalization_backward(const primitive_desc &pd);
};

/// Layer normalization forward propagation primitive.
struct layer_normalization_forward : public primitive {
    /// Descriptor for layer normalization forward propagation primitive.
    struct desc {
        /// Constructs a layer normalization descriptor for forward
        /// propagation using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), data memory
        /// descriptor @p data_desc, statistics memory descriptor @p
        /// stat_desc, normalization parameter @p epsilon, and flags set
        /// using bit @p flags.
        desc(prop_kind prop_kind, const memory::desc &data_desc,
                const memory::desc &stat_desc, float epsilon,
                normalization_flags flags);

        /// Constructs a layer normalization descriptor for forward
        /// propagation using @p prop_kind (acceptable values are
        /// #dnnl::forward_training and #dnnl::forward_inference), data memory
        /// descriptor @p data_desc, statistics memory descriptor @p
        /// stat_desc, normalization parameter @p epsilon, and flags set
        /// using bit @p flags.
        desc(prop_kind prop_kind, const memory::desc &src_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for layer normalization forward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for layer normalization forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for layer normalization forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for layer normalization forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for layer normalization forward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the weights (scale and shift) memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the mean memory descriptor.
        memory::desc mean_desc() const;

        /// Returns the variance memory descriptor.
        memory::desc variance_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    layer_normalization_forward();

    /// Constructs an layer normalization forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    layer_normalization_forward(const primitive_desc &pd);
};

/// Layer normalization backward propagation primitive.
struct layer_normalization_backward : public primitive {
    /// Descriptor for layer normalization backward propagation primitive.
    struct desc {
        /// Constructs a layer normalization descriptor for backward
        /// propagation with respect to data and scale-shift parameters using
        /// memory descriptors @p diff_data_desc, @p data_desc and @p
        /// stat_desc, normalization parameter @p epsilon, and p flags set
        /// using bit @p flags.
        desc(prop_kind prop_kind, const memory::desc &diff_data_desc,
                const memory::desc &data_desc, const memory::desc &stat_desc,
                float epsilon, normalization_flags flags);

        /// Constructs a layer normalization descriptor for backward
        /// propagation with respect to data and scale-shift parameters using
        /// memory descriptors @p diff_data_desc and @p data_desc
        /// normalization parameter @p epsilon, and flags set using bit
        /// @p flags.
        desc(prop_kind prop_kind, const memory::desc &diff_data_desc,
                const memory::desc &data_desc, float epsilon,
                normalization_flags flags);
    };

    /// Primitive descriptor for layer normalization backward propagation
    /// primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for layer normalization backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for layer normalization backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for layer normalization
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const layer_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for layer normalization backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for layer normalization backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for layer normalization
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const layer_normalization_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the mean memory descriptor.
        memory::desc mean_desc() const;

        /// Returns the variance memory descriptor.
        memory::desc variance_desc() const;

        /// Returns the weights (scale and shift) memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff weights (scale and shift) memory descriptor.
        memory::desc diff_weights_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    layer_normalization_backward();

    /// Constructs an layer normalization backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    layer_normalization_backward(const primitive_desc &pd);
};

/// Inner product forward propagation primitive.
struct inner_product_forward : public primitive {
    /// Descriptor for inner product forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for inner product forward propagation
        /// primitive using @p prop_kind (acceptable values are
        /// #dnnl::prop_kind::forward_training and
        /// #dnnl::prop_kind::forward_inference) and memory descriptors. In
        /// order to create an inner product without bias, the @p bias_desc
        /// should be initialized with a zero memory descriptor.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, const memory::desc &src_desc,
                const memory::desc &weights_desc, const memory::desc &bias_desc,
                const memory::desc &dst_desc);

        /// Constructs an descriptor for inner product forward propagation
        /// primitive using @p prop_kind (acceptable values are
        /// #dnnl::prop_kind::forward_training and
        /// #dnnl::prop_kind::forward_inference) and memory descriptors.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, const memory::desc &src_desc,
                const memory::desc &weights_desc, const memory::desc &dst_desc);
    };

    /// Primitive descriptor for inner product forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for inner product forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for inner product forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for inner product forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for inner product forward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_forward();

    /// Constructs an inner product forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    inner_product_forward(const primitive_desc &pd);
};

/// Inner product backward propagation primitive.
struct inner_product_backward_data : public primitive {
    /// Descriptor for inner product backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for inner product backward propagation
        /// primitive.
        ///
        /// @param diff_src_desc Memory descriptor for diff src.
        /// @param weights_desc Memory descriptor for weights.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(const memory::desc &diff_src_desc,
                const memory::desc &weights_desc,
                const memory::desc &diff_dst_desc);
    };

    /// Primitive descriptor for inner product backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for inner product backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for inner product backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for inner product
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for inner product backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for inner product backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for inner product
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the weights memory descriptor.
        memory::desc weights_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_backward_data();

    /// Constructs an inner product backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    inner_product_backward_data(const primitive_desc &pd);
};

/// Inner product weights update primitive.
struct inner_product_backward_weights : public primitive {
    /// Descriptor for inner product weights update primitive.
    struct desc {
        /// Constructs a descriptor for inner product descriptor weights
        /// update primitive.
        ///
        /// @param src_desc Memory descriptor for src.
        /// @param diff_weights_desc Memory descriptor for diff weights.
        /// @param diff_bias_desc Memory descriptor for diff bias.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_bias_desc,
                const memory::desc &diff_dst_desc);

        /// Constructs a descriptor for inner product descriptor weights
        /// update primitive.
        ///
        /// @param src_desc Memory descriptor for src.
        /// @param diff_weights_desc Memory descriptor for diff weights.
        /// @param diff_dst_desc Memory descriptor for diff dst.
        ///
        /// @note
        ///     Memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(const memory::desc &src_desc,
                const memory::desc &diff_weights_desc,
                const memory::desc &diff_dst_desc);
    };

    /// Primitive descriptor for inner product weights update primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for inner product weights update
        /// primitive.
        ///
        /// @param desc Descriptor for inner product weights update primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for inner product
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for inner product weights update
        /// primitive.
        ///
        /// @param desc Descriptor for inner product weights update primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for inner product
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const inner_product_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the diff weights memory descriptor.
        memory::desc diff_weights_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    inner_product_backward_weights();

    /// Constructs an inner product weights update primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    inner_product_backward_weights(const primitive_desc &pd);
};

/// Base class for primitive descriptors for RNN primitives.
struct rnn_primitive_desc_base : public primitive_desc {
    /// Default constructor. Produces an empty object.
    rnn_primitive_desc_base();
};

/// Vanilla RNN forward propagation primitive.
struct vanilla_rnn_forward : public primitive {
    /// Descriptor for vanilla RNN forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for vanilla RNN forward propagation
        /// primitive using @p prop_kind, @p activation, @p direction, and
        /// memory descriptors.
        ///
        /// If @p activation is #eltwise_relu, @p alpha represents the
        /// negative slope. The @p beta and @p flags are currently ignored.
        ///
        /// The @p src_iter_desc, @p bias_desc, and @p dst_iter_desc are
        /// allowed to point to a zero memory descriptor, which would indicate
        /// that the primitive should not use them.
        ///
        /// @note
        ///     If @p prop_kind equals #dnnl::forward_training, you must
        ///     query for workspace memory descriptor before creating the
        ///     primitive.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc can be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        desc(prop_kind prop_kind, algorithm activation, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                rnn_flags flags = rnn_flags::undef, float alpha = 0.0f,
                float beta = 0.0f);
    };

    /// Primitive descriptor for vanilla RNN forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for vanilla RNN forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for vanilla RNN forward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for vanilla RNN forward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for vanilla RNN forward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iteration memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    vanilla_rnn_forward();

    /// Constructs a vanilla RNN forward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    vanilla_rnn_forward(const primitive_desc &pd);
};

/// Vanilla RNN backward propagation primitive.
struct vanilla_rnn_backward : public primitive {
    /// Vanilla RNN descriptor backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for vanilla RNN backward propagation
        /// primitive using @p prop_kind, @p activation, @p direction, and
        /// memory descriptors.
        ///
        /// If @p activation is #eltwise_relu, @p alpha represents the
        /// negative slope. The @p beta and @p flags are currently ignored.
        ///
        /// The @p src_iter_desc (simultaneously with @p diff_src_iter_desc),
        /// @p bias_desc (simultaneously with @p diff_bias_desc), and @p
        /// dst_iter_desc (simultaneously with @p diff_src_iter_desc) are
        /// allowed point to a zero memory descriptor, which would indicate
        /// that the primitive should not use them and consider them to be
        /// zero values.
        ///
        /// @note
        ///     All memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, algorithm activation, rnn_direction direction,
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
                rnn_flags flags = rnn_flags::undef, float alpha = 0.0f,
                float beta = 0.0f);
    };

    /// Primitive descriptor for RNN backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for vanilla RNN backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for vanilla RNN backward propagation
        ///             primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for vanilla RNN
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const vanilla_rnn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for vanilla RNN backward
        /// propagation primitive.
        ///
        /// @param desc Descriptor for vanilla RNN backward propagation
        ///             primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for vanilla RNN
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const vanilla_rnn_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iteration memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the diff source layer memory descriptor.
        memory::desc diff_src_layer_desc() const;

        /// Returns the diff source iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_src_iter was specified at op_desc
        /// creation time.
        memory::desc diff_src_iter_desc() const;

        /// Returns the diff weights layer memory descriptor.
        memory::desc diff_weights_layer_desc() const;

        /// Returns the diff weights iteration memory descriptor.
        memory::desc diff_weights_iter_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination layer memory descriptor.
        memory::desc diff_dst_layer_desc() const;

        /// Returns the diff destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_dst_iter was specified at op_desc
        /// creation time.
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    vanilla_rnn_backward();

    /// Constructs a vanilla RNN backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    vanilla_rnn_backward(const primitive_desc &pd);
};

/// LSTM forward propagation primitive.
struct lstm_forward : public primitive {
    /// Descriptor for LSTM forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for LSTM forward propagation primitive
        /// using @p prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is currently ignored.
        ///
        /// The @p src_iter_desc, @p src_iter_c_desc, @p bias_desc, @p
        /// dst_iter_desc and @p dst_iter_c_desc are allowed to point
        /// to a zero memory descriptor, which would indicate that the
        /// LSTM forward propagation primitive should not use them.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc can be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @note
        ///     If @p prop_kind equals #dnnl::forward_training, you must query
        ///     for workspace memory descriptor before creating the primitive.
        ///
        desc(prop_kind prop_kind, rnn_direction direction,
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

    /// Primitive descriptor for LSTM forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LSTM forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LSTM forward propagation primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LSTM forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LSTM forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the source recurrent cell state memory descriptor.
        memory::desc src_iter_c_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the destination recurrent cell state memory descriptor.
        memory::desc dst_iter_c_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lstm_forward();

    /// Constructs an LSTM forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    lstm_forward(const primitive_desc &pd);
};

/// LSTM backward propagation primitive.
struct lstm_backward : public primitive {
    /// Descriptor for LSTM backward propagation primitive.
    struct desc {
        /// Constructs an LSTM descriptor for backward propagation using @p
        /// prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is currently ignored.
        ///
        /// The @p src_iter_desc (simultaneously with @p diff_src_iter_desc),
        /// @p src_iter_c_desc (simultaneously with @p diff_src_iter_c_desc),
        /// @p bias_desc (simultaneously with @p diff_bias_desc), @p
        /// dst_iter_desc (simultaneously with @p diff_src_iter_desc) and @p
        /// dst_iter_c_desc (simultaneously with @p diff_src_iter_c_desc) are
        /// allowed point to a zero memory descriptor, which would indicate
        /// that the LSTM primitive should not use them and consider them to
        /// be zero values.
        ///
        /// @note
        ///     All memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        desc(prop_kind prop_kind, rnn_direction direction,
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

    /// Primitive descriptor for LSTM backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LSTM forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LSTM forward propagation primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for LSTM
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const lstm_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LSTM forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for LSTM forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for LSTM
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const lstm_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the source recurrent cell state memory descriptor.
        memory::desc src_iter_c_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the destination recurrent cell state memory descriptor.
        memory::desc dst_iter_c_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the diff source layer memory descriptor.
        memory::desc diff_src_layer_desc() const;

        /// Returns the diff source recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no diff_src_iter was specified at op_desc
        /// creation time.
        memory::desc diff_src_iter_desc() const;

        /// Returns the diff source recurrent cell state memory descriptor.
        memory::desc diff_src_iter_c_desc() const;

        /// Returns the diff weights layer memory descriptor.
        memory::desc diff_weights_layer_desc() const;

        /// Returns the diff weights iteration memory descriptor.
        memory::desc diff_weights_iter_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination layer memory descriptor.
        memory::desc diff_dst_layer_desc() const;

        /// Returns the diff destination recurrent hidden state memory descriptor.
        ///
        /// Returns a zero_md if no diff_dst_iter was specified at op_desc
        /// creation time.
        memory::desc diff_dst_iter_desc() const;

        /// Returns the diff destination recurrent cell state memory descriptor.
        memory::desc diff_dst_iter_c_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lstm_backward();

    /// Constructs a vanilla RNN backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    lstm_backward(const primitive_desc &pd);
};

/// GRU forward propagation primitive.
struct gru_forward : public primitive {
    /// Descriptor for GRU forward propagation primitive.
    struct desc {
        /// Constructs a descriptor for GRU forward propagation primitive
        /// using @p prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is currently ignored.
        ///
        /// The @p src_iter_desc, @p bias_desc, and @p dst_iter_desc are allowed
        /// to point to a zero memory descriptor, which would indicate that
        /// the GRU primitive should not use them and will default to zero
        /// values.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc can be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @note
        ///     If @p prop_kind equals #dnnl::forward_training, you must query
        ///     a workspace memory descriptor before creating the primitive.
        ///
        desc(prop_kind prop_kind, rnn_direction direction,
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

        /// Constructs a primitive descriptor for GRU forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for GRU forward propagation primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for GRU forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for GRU forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iteration memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    gru_forward();

    /// Constructs a GRU forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    gru_forward(const primitive_desc &pd);
};

/// GRU backward propagation primitive.
struct gru_backward : public primitive {
    /// Descriptor for GRU backward propagation primitive.
    struct desc {
        /// Constructs a descriptor for GRU backward propagation primitive
        /// using @p prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is ignored.
        ///
        /// The @p src_iter_desc (simultaneously with @p diff_src_iter_desc),
        /// @p bias_desc (simultaneously with @p diff_bias_desc), and @p
        /// dst_iter_desc (simultaneously with @p diff_src_iter_desc) are
        /// allowed point to a zero memory descriptor, which would indicate
        /// that the GRU primitive should not use them and consider them to be
        /// zero values.
        ///
        /// @note
        ///     All memory descriptors are allowed to be initialized with
        ///     #dnnl::memory::format_tag::any value of @p format_tag.
        desc(prop_kind prop_kind, rnn_direction direction,
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

    /// Primitive descriptor for GRU backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for GRU forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for GRU forward propagation primitive.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for GRU
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                const gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for GRU forward propagation
        /// primitive.
        ///
        /// @param desc Descriptor for GRU forward propagation primitive.
        /// @param attr Primitive attributes to use.
        /// @param engine Engine to use.
        /// @param hint_fwd_pd Primitive descriptor for GRU
        ///                    forward propagation primitive. It is used as a
        ///                    hint when deciding which memory format to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iter memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the diff source layer memory descriptor.
        memory::desc diff_src_layer_desc() const;

        /// Returns the diff source iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_src_iter was specified at op_desc
        /// creation time.
        memory::desc diff_src_iter_desc() const;

        /// Returns the diff weights layer memory descriptor.
        memory::desc diff_weights_layer_desc() const;

        /// Returns the diff weights iteration memory descriptor.
        memory::desc diff_weights_iter_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination layer memory descriptor.
        memory::desc diff_dst_layer_desc() const;

        /// Returns the diff destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_dst_iter was specified at op_desc
        /// creation time.
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    gru_backward();

    /// Constructs a vanilla RNN backward propagation primitive from a
    /// primitive descriptor @p pd of a corresponding type.
    gru_backward(const primitive_desc &pd);
};

/// LBR GRU forward propagation primitive.
struct lbr_gru_forward : public primitive {
    /// Descriptor for LBR GRU forward propagation primitive.
    struct desc {
        /// Constructs an LBR GRU descriptor for forward propagation using @p
        /// prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is currently ignored.
        ///
        /// The @p src_iter_desc, @p bias_desc, and @p dst_iter_desc are allowed
        /// to point to a zero memory descriptor, which would indicate that
        /// the LBR GRU primitive should not use them and will default to zero
        /// values.
        ///
        /// @note
        ///     All memory descriptors except @p src_iter_desc can be
        ///     initialized with an #dnnl::memory::format_tag::any value of @p
        ///     format_tag.
        ///
        /// @note
        ///     If @p prop_kind equals #dnnl::forward_training, you must query
        ///     a workspace memory descriptor before creating the primitive.
        ///
        desc(prop_kind prop_kind, rnn_direction direction,
                const memory::desc &src_layer_desc,
                const memory::desc &src_iter_desc,
                const memory::desc &weights_layer_desc,
                const memory::desc &weights_iter_desc,
                const memory::desc &bias_desc,
                const memory::desc &dst_layer_desc,
                const memory::desc &dst_iter_desc,
                rnn_flags flags = rnn_flags::undef);
    };

    /// Primitive descriptor for LBR GRU forward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LBR GRU forward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine. The @p allow_empty flag signifies whether
        /// construction is allowed to fail, in which case an empty primitive
        /// would be produced.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LBR GRU forward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine, and primitive attributes @p attr. The @p
        /// allow_empty flag signifies whether construction is allowed to
        /// fail, in which case an empty primitive would be produced.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iteration memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lbr_gru_forward();

    /// Constructs a LBR GRU forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    lbr_gru_forward(const primitive_desc &pd);
};

/// LBR GRU backward propagation primitive.
struct lbr_gru_backward : public primitive {
    /// LBR_GRU descriptor for backward propagation primitive.
    struct desc {
        /// Constructs a descriptor LBR_GRU backward propagation primitive
        /// using @p prop_kind, @p direction, and memory descriptors.
        ///
        /// The @p flags parameter is currently ignored.
        ///
        /// The @p src_iter_desc (simultaneously with @p diff_src_iter_desc),
        /// @p bias_desc (simultaneously with @p diff_bias_desc), and @p
        /// dst_iter_desc (simultaneously with @p diff_src_iter_desc) are
        /// allowed point to a zero memory descriptor, which would indicate
        /// that the LBR GRU primitive should not use them and consider them
        /// to be zero values.
        ///
        /// @note All memory descriptors are allowed to be initialized with
        ///       #dnnl::memory::format_tag::any value of @p format_tag.
        ///
        desc(prop_kind prop_kind, rnn_direction direction,
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

    /// Primitive descriptor for LBR GRU backward propagation primitive.
    struct primitive_desc : public rnn_primitive_desc_base {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for LBR GRU backward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine, and LBR GRU forward propagation primitive
        /// descriptor hint @p hint_fwd_pd. The @p allow_empty flag signifies
        /// whether construction is allowed to fail, in which case an empty
        /// primitive would be produced..
        primitive_desc(const desc &desc, const engine &engine,
                const lbr_gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for LBR GRU backward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine, LBR GRU forward propagation primitive descriptor
        /// hint @p hint_fwd_pd, and primitive attributes @p attr. The @p
        /// allow_empty flag signifies whether construction is allowed to
        /// fail, in which case an empty primitive would be produced.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine,
                const lbr_gru_forward::primitive_desc &hint_fwd_pd,
                bool allow_empty = false);

        /// Returns the source layer memory descriptor.
        memory::desc src_layer_desc() const;

        /// Returns the source iteration memory descriptor.
        ///
        /// Returns a zero_md if no src_iter was specified at op_desc
        /// creation time.
        memory::desc src_iter_desc() const;

        /// Returns the weights layer memory descriptor.
        memory::desc weights_layer_desc() const;

        /// Returns the weights iteration memory descriptor.
        memory::desc weights_iter_desc() const;

        /// Returns the bias memory descriptor.
        ///
        /// Returns a zero_md if no bias was specified at op_desc
        /// creation time.
        memory::desc bias_desc() const;

        /// Returns the destination layer memory descriptor.
        memory::desc dst_layer_desc() const;

        /// Returns the destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no dst_iter was specified at op_desc
        /// creation time.
        memory::desc dst_iter_desc() const;

        /// Returns the workspace memory descriptor.
        ///
        /// Returns a zero_md if no workspace is required.
        memory::desc workspace_desc() const;

        /// Returns the diff source layer memory descriptor.
        memory::desc diff_src_layer_desc() const;

        /// Returns the diff source iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_src_iter was specified at op_desc
        /// creation time.
        memory::desc diff_src_iter_desc() const;

        /// Returns the diff weights layer memory descriptor.
        memory::desc diff_weights_layer_desc() const;

        /// Returns the diff weights iteration memory descriptor.
        memory::desc diff_weights_iter_desc() const;

        /// Returns the diff bias memory descriptor.
        memory::desc diff_bias_desc() const;

        /// Returns the diff destination layer memory descriptor.
        memory::desc diff_dst_layer_desc() const;

        /// Returns the diff destination iteration memory descriptor.
        ///
        /// Returns a zero_md if no diff_dst_iter was specified at op_desc
        /// creation time.
        memory::desc diff_dst_iter_desc() const;
    };

    /// Default constructor. Produces an empty object.
    lbr_gru_backward();

    /// Constructs a LBR GRU backward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    lbr_gru_backward(const primitive_desc &pd);
};

/// Shuffle forward propagation primitive.
struct shuffle_forward : public primitive {
    /// Descriptor for shuffle forward propagation primitive.
    struct desc {
        /// Constructs a descriptor shuffle forward propagation primitive
        /// using @p prop_kind, memory descriptor @p data_desc, @p axis, and
        /// @p group_size.
        desc(prop_kind prop_kind, const memory::desc &data_desc, int axis,
                int group_size);
    };

    /// Primitive descriptor for shuffle forward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for shuffle forward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine, and primitive attributes @p attr. The @p
        /// allow_empty flag signifies whether construction is allowed to
        /// fail, in which case an empty primitive would be produced.
        primitive_desc(const desc &desc, const engine &engine,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// Returns the source memory descriptor.
        memory::desc src_desc() const;

        /// Returns the destination memory descriptor.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    shuffle_forward();

    /// Constructs a shuffle forward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    shuffle_forward(const primitive_desc &pd);
};

/// Shuffle backward propagation primitive.
struct shuffle_backward : public primitive {
    /// Descriptor for shuffle primitive backward propagation
    /// primitive.
    struct desc {
        /// Constructs a primitive descriptor for a shuffle backward
        /// propagation primitive using a memory descriptor @p diff_data_desc,
        /// @p axis, and @p group_size.
        desc(const memory::desc &diff_data_desc, int axis, int group_size);
    };

    /// Primitive descriptor for shuffle backward propagation primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for shuffle backward propagation
        /// primitive from a corresponding operation descriptor @p desc using
        /// engine @p engine, shuffle forward propagation primitive descriptor
        /// hint @p hint_fwd_pd, and primitive attributes @p attr. The @p
        /// allow_empty flag signifies whether construction is allowed to
        /// fail, in which case an empty primitive would be produced.
        primitive_desc(const desc &desc, const engine &engine,
                const shuffle_forward::primitive_desc &hint_fwd_pd,
                const primitive_attr &attr = primitive_attr(),
                bool allow_empty = false);

        /// Returns the diff source memory descriptor.
        memory::desc diff_src_desc() const;

        /// Returns the diff destination memory descriptor.
        memory::desc diff_dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    shuffle_backward();

    /// Constructs a shuffle backward propagation primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    shuffle_backward(const primitive_desc &pd);
};

/// Elementwise binary operator primitive.
struct binary : public primitive {
    /// Descriptor for a elementwise binary operator primitive.
    struct desc {
        /// Constructs a descriptor for elementwise binary operator primitive.
        ///
        /// @param algorithm Elementwise algorithm.
        /// @param src0 Memory descriptor for source tensor #0.
        /// @param src1 Memory descriptor for source tensor #1.
        /// @param dst Memory descriptor for destination tensor.
        desc(algorithm algorithm, const memory::desc &src0,
                const memory::desc &src1, const memory::desc &dst);
    };

    /// Primitive descriptor for elementwise binary operator primitive.
    struct primitive_desc : public dnnl::primitive_desc {
        /// Default constructor. Produces an empty object.
        primitive_desc();

        /// Constructs a primitive descriptor for elementwise binary operator
        /// primitive.
        ///
        /// @param desc Descriptor for elementwise binary operator primitive.
        /// @param engine Engine to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const engine &engine,
                bool allow_empty = false);

        /// Constructs a primitive descriptor for elementwise binary operator
        /// primitive.
        ///
        /// @param desc Descriptor for elementwise binary operator primitive.
        /// @param engine Engine to use.
        /// @param attr Primitive attributes to use.
        /// @param allow_empty A flag signifying whether construction is
        ///                    allowed to fail without throwing an exception.
        ///                    In this case an empty object will be produced.
        ///                    This flag is optional and defaults to false.
        primitive_desc(const desc &desc, const primitive_attr &attr,
                const engine &engine, bool allow_empty = false);

        /// Returns the memory descriptor for source #0.
        memory::desc src0_desc() const;

        /// Returns the memory descriptor for source #1.
        memory::desc src1_desc() const;

        /// Returns the memory descriptor for destination.
        memory::desc dst_desc() const;
    };

    /// Default constructor. Produces an empty object.
    binary();

    /// Constructs a elementwise binary operator primitive from a primitive
    /// descriptor @p pd of a corresponding type.
    binary(const primitive_desc &pd);
};

} // namespace dnnl

/// @}

#endif
