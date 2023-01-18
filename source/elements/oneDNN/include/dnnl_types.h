// Copyright 2016-2020 Intel Corporation
// SPDX-FileCopyrightText: 2016-2020 Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0

/// @file

#ifndef DNNL_TYPES_H
#define DNNL_TYPES_H

#include <stdint.h>

/// Special pointer value that indicates that a memory object should not have
/// an underlying buffer.
#define DNNL_MEMORY_NONE (NULL)

/// Special pointer value that indicates that the library needs to allocate an
/// underlying buffer for a memory object.
#define DNNL_MEMORY_ALLOCATE ((void *)(size_t)-1)

/// Source argument #0.
#define DNNL_ARG_SRC_0 1
/// A special mnemonic for source argument for primitives that have a
/// single source. An alias for #DNNL_ARG_SRC_0.
#define DNNL_ARG_SRC DNNL_ARG_SRC_0
/// A special mnemonic for RNN input vector. An alias for
/// #DNNL_ARG_SRC_0.
#define DNNL_ARG_SRC_LAYER DNNL_ARG_SRC_0
/// A special mnemonic for reorder source argument. An alias for
/// #DNNL_ARG_SRC_0.
#define DNNL_ARG_FROM DNNL_ARG_SRC_0

/// Source argument #1.
#define DNNL_ARG_SRC_1 2
/// A special mnemonic for RNN input recurrent hidden state vector. An alias
/// for #DNNL_ARG_SRC_1.
#define DNNL_ARG_SRC_ITER DNNL_ARG_SRC_1

/// Source argument #2.
#define DNNL_ARG_SRC_2 3
/// A special mnemonic for RNN input recurrent cell state vector. An alias for
/// #DNNL_ARG_SRC_2.
#define DNNL_ARG_SRC_ITER_C DNNL_ARG_SRC_2

/// Destination argument #0.
#define DNNL_ARG_DST_0 17
/// A special mnemonic for destination argument for primitives that have a
/// single destination. An alias for #DNNL_ARG_DST_0.
#define DNNL_ARG_DST DNNL_ARG_DST_0
/// A special mnemonic for reorder destination argument. An alias for
/// #DNNL_ARG_DST_0.
#define DNNL_ARG_TO DNNL_ARG_DST_0
/// A special mnemonic for RNN output vector. An alias for #DNNL_ARG_DST_0.
#define DNNL_ARG_DST_LAYER DNNL_ARG_DST_0

/// Destination argument #1.
#define DNNL_ARG_DST_1 18
/// A special mnemonic for RNN input recurrent hidden state vector. An
/// alias for #DNNL_ARG_DST_1.
#define DNNL_ARG_DST_ITER DNNL_ARG_DST_1

/// Destination argument #2.
#define DNNL_ARG_DST_2 19
/// A special mnemonic for LSTM output recurrent cell state vector. An
/// alias for #DNNL_ARG_DST_2.
#define DNNL_ARG_DST_ITER_C DNNL_ARG_DST_2

/// Weights argument #0.
#define DNNL_ARG_WEIGHTS_0 33
/// A special mnemonic for primitives that have a single weights
/// argument. Alias for #DNNL_ARG_WEIGHTS_0.
#define DNNL_ARG_WEIGHTS DNNL_ARG_WEIGHTS_0
/// A special mnemonic for RNN weights applied to the layer input. An
/// alias for #DNNL_ARG_WEIGHTS_0.
#define DNNL_ARG_WEIGHTS_LAYER DNNL_ARG_WEIGHTS_0

/// Weights argument #1.
#define DNNL_ARG_WEIGHTS_1 34
/// A special mnemonic for RNN weights applied to the recurrent input.
/// An alias for #DNNL_ARG_WEIGHTS_1.
#define DNNL_ARG_WEIGHTS_ITER DNNL_ARG_WEIGHTS_1

/// Bias tensor argument.
#define DNNL_ARG_BIAS 41

/// Mean values tensor argument.
#define DNNL_ARG_MEAN 49
/// Variance values tensor argument.
#define DNNL_ARG_VARIANCE 50
/// Scale values argument of normalization primitives.
#define DNNL_ARG_SCALE 51
/// Shift values argument of normalization primitives.
#define DNNL_ARG_SHIFT 52

/// Workspace tensor argument. Workspace is used to pass information
/// from forward propagation to backward propagation computations.
#define DNNL_ARG_WORKSPACE 64
/// Scratchpad (temporary storage) tensor argument.
#define DNNL_ARG_SCRATCHPAD 80

/// Gradient (diff) of the source argument #0.
#define DNNL_ARG_DIFF_SRC_0 129
/// A special mnemonic for primitives that have a single diff source argument.
/// An alias for #DNNL_ARG_DIFF_SRC_0.
#define DNNL_ARG_DIFF_SRC DNNL_ARG_DIFF_SRC_0
/// A special mnemonic for gradient (diff) of RNN input vector. An alias for
/// #DNNL_ARG_DIFF_SRC_0.
#define DNNL_ARG_DIFF_SRC_LAYER DNNL_ARG_DIFF_SRC_0

/// Gradient (diff) of the source argument #1.
#define DNNL_ARG_DIFF_SRC_1 130
/// A special mnemonic for gradient (diff) of RNN input recurrent hidden state
/// vector. An alias for #DNNL_ARG_DIFF_SRC_1.
#define DNNL_ARG_DIFF_SRC_ITER DNNL_ARG_DIFF_SRC_1

/// Gradient (diff) of the source argument #2.
#define DNNL_ARG_DIFF_SRC_2 131
/// A special mnemonic for gradient (diff) of RNN input recurrent cell state
/// vector. An alias for #DNNL_ARG_DIFF_SRC_1.
#define DNNL_ARG_DIFF_SRC_ITER_C DNNL_ARG_DIFF_SRC_2

/// Gradient (diff) of the destination argument #0.
#define DNNL_ARG_DIFF_DST_0 145
/// A special mnemonic for primitives that have a single diff destination
/// argument. An alias for #DNNL_ARG_DIFF_DST_0.
#define DNNL_ARG_DIFF_DST DNNL_ARG_DIFF_DST_0
/// A special mnemonic for gradient (diff) of RNN output vector. An alias for
/// #DNNL_ARG_DIFF_DST_0.
#define DNNL_ARG_DIFF_DST_LAYER DNNL_ARG_DIFF_DST_0

/// Gradient (diff) of the destination argument #1.
#define DNNL_ARG_DIFF_DST_1 146
/// A special mnemonic for gradient (diff) of RNN input recurrent hidden state
/// vector. An alias for #DNNL_ARG_DIFF_DST_1.
#define DNNL_ARG_DIFF_DST_ITER DNNL_ARG_DIFF_DST_1

/// Gradient (diff) of the destination argument #2.
#define DNNL_ARG_DIFF_DST_2 147
/// A special mnemonic for gradient (diff) of RNN input recurrent cell state
/// vector. An alias for #DNNL_ARG_DIFF_DST_2.
#define DNNL_ARG_DIFF_DST_ITER_C DNNL_ARG_DIFF_DST_2

/// Gradient (diff) of the weights argument #0.
#define DNNL_ARG_DIFF_WEIGHTS_0 161
/// A special mnemonic for primitives that have a single diff weights
/// argument. Alias for #DNNL_ARG_DIFF_WEIGHTS_0.
#define DNNL_ARG_DIFF_WEIGHTS DNNL_ARG_DIFF_WEIGHTS_0
/// A special mnemonic for diff of scale and shift argument of normalization
/// primitives. Alias for #DNNL_ARG_DIFF_WEIGHTS_0.
#define DNNL_ARG_DIFF_SCALE_SHIFT DNNL_ARG_DIFF_WEIGHTS_0
/// A special mnemonic for diff of RNN weights applied to the layer input. An
/// alias for #DNNL_ARG_DIFF_WEIGHTS_0.
#define DNNL_ARG_DIFF_WEIGHTS_LAYER DNNL_ARG_DIFF_WEIGHTS_0

/// Gradient (diff) of the weights argument #1.
#define DNNL_ARG_DIFF_WEIGHTS_1 162
/// A special mnemonic for diff of RNN weights applied to the recurrent input.
/// An alias for #DNNL_ARG_DIFF_WEIGHTS_1.
#define DNNL_ARG_DIFF_WEIGHTS_ITER DNNL_ARG_DIFF_WEIGHTS_1

/// Gradient (diff) of the bias tensor argument.
#define DNNL_ARG_DIFF_BIAS 169

/// Scale gradient argument of normalization primitives.
#define DNNL_ARG_DIFF_SCALE 255
/// Shift gradient argument of normalization primitives.
#define DNNL_ARG_DIFF_SHIFT 256


/// Scaling factors provided at execution time.
#define DNNL_ARG_ATTR_SCALES 4096
/// Zero points provided at execution time.
#define DNNL_ARG_ATTR_ZERO_POINTS 8192

/// Starting point for post operation arguments.
#define DNNL_ARG_ATTR_MULTIPLE_POST_OP_BASE 32768
/// Arguments for a binary post operation.
#define DNNL_ARG_ATTR_MULTIPLE_POST_OP(idx) \
    (DNNL_ARG_ATTR_MULTIPLE_POST_OP_BASE * ((idx) + 1))

/// Starting index for source arguments for primitives that take a variable
/// number of source arguments.
#define DNNL_ARG_MULTIPLE_SRC 1024
/// Starting index for destination arguments for primitives that produce a
/// variable number of destination arguments.
#define DNNL_ARG_MULTIPLE_DST 2048

/// A wildcard value for dimensions that are unknown at a primitive creation
/// time.
#define DNNL_RUNTIME_DIM_VAL INT64_MIN

/// A `size_t` counterpart of the #DNNL_RUNTIME_DIM_VAL.
/// For instance, this value is returned by #dnnl::memory::desc::get_size() if
/// either of the dimensions or strides equal to #DNNL_RUNTIME_DIM_VAL.
#define DNNL_RUNTIME_SIZE_VAL ((size_t)DNNL_RUNTIME_DIM_VAL)

/// @cond DO_NOT_DOCUMENT_THIS
/// Hex representation for a **special** quiet NAN (!= NAN from math.h)
static const union {
    unsigned u;
    float f;
} DNNL_RUNTIME_F32_VAL_REP = {0x7fc000d0};
/// @endcond

/// A wildcard value for floating point values that are unknown at a primitive
/// creation time.
#define DNNL_RUNTIME_F32_VAL (DNNL_RUNTIME_F32_VAL_REP.f)

/// @cond DO_NOT_DOCUMENT_THIS
static const int DNNL_RUNTIME_S32_VAL_REP = INT32_MIN;
/// @endcond

/// A wildcard value for int32_t values that are unknown at a primitive creation
/// time.
#define DNNL_RUNTIME_S32_VAL DNNL_RUNTIME_S32_VAL_REP


#endif
