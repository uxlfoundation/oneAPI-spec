/*******************************************************************************
* Copyright 2016-2020 Intel Corporation
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

/// @file

#ifndef DNNL_TYPES_H
#define DNNL_TYPES_H

#include <stdint.h>

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
/// A special mnemonic for scale and shift argument of normalization
/// primitives. Alias for #DNNL_ARG_WEIGHTS_0.
#define DNNL_ARG_SCALE_SHIFT DNNL_ARG_WEIGHTS_0
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

/// Output scaling factors provided at execution time.
#define DNNL_ARG_ATTR_OUTPUT_SCALES 513

/// Starting index for source arguments for primitives that take a variable
/// number of source arguments.
#define DNNL_ARG_MULTIPLE_SRC 1024
/// Starting index for destination arguments for primitives that produce a
/// variable number of destination arguments.
#define DNNL_ARG_MULTIPLE_DST 2048

/// Zero points provided at execution time.
#define DNNL_ARG_ATTR_ZERO_POINTS 4096

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
