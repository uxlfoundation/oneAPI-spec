.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

--------------------------
ConvolutionBackpropWeights
--------------------------

**Versioned name**: *ConvolutionBackpropWeights-1*

**Category**: Convolution

**Short description**: Computes the gradients of a Convolution operation with
respect to the weights.

**Detailed description**:

ConvolutionBackpropWeights takes the input tensor, the gradient of output tensor,
and weight shape (optional) to compute the gradient of weight.

**Attributes**

* *strides*

  * **Description**: *strides* has the same definition as *strides* for a
    regular Convolution.
  * **Range of values**: positive s64 values.
  * **Type**: s64[]
  * **Required**: *yes*

* *pads_begin*

  * **Description**: *pads_begin* has the same definition as *pads_begin* for a
    regular Convolution. May be omitted specified, in which case pads are
    calculated automatically.
  * **Range of values**: non-negative s64 values.
  * **Type**: s64[]
  * **Required**: *yes*
  * **Note**: the attribute is ignored when *auto_pad* attribute is specified.

* *pads_end*

  * **Description**: *pads_end* has the same definition as *pads_end* for a
    regular Convolution. May be omitted, in which case pads are calculated
    automatically.
  * **Range of values**: non-negative s64 values.
  * **Type**: s64[]
  * **Required**: *yes*
  * **Note**: the attribute is ignored when *auto_pad* attribute is specified.
  
* *dilations*

  * **Description**: *dilations* has the same definition as *dilations* for a
    regular Convolution.
  * **Range of values**: positive s64 values.
  * **Type**: s64[]
  * **Required**: *yes*

* *auto_pad*

  * **Description**: *auto_pad* has the same definition as *auto_pad* for a
    regular Convolution.

    * *none (not specified)*: use explicit padding values from ``pads_begin``
      and ``pads_end``.
    * *same_upper (same_lower)* the input is padded to match the output size.
      In case of odd padding value an extra padding is added at the end
      (at the beginning).
    * *valid* - do not use padding.

  * **Type**: string
  * **Default value**: *none*
  * **Required**: *no*
  * **Note**: *pads_begin* and *pads_end* attributes are ignored when *auto_pad*
    is specified.

* *groups*

  * **Description**: *groups* denotes the number of groups input channels and
    output channels are divided into. In_channels and out_channels must both be
    divisible by groups
  * **Range of values**: a positive s64 value.
  * **Type**: s64
  * **Default value**: 1
  * **Required**: *no*
  
* *data_format*

  * **Description**: *data_format* denotes the data format of the input data and
    output diff.
  * **Range of values**: *NXC* or *NCX* (X means HW for 2D convolution, DHW for
    3D convolution)
  * **Type**: string
  * **Default value**: *NXC*
  * **Required**: *no*

* *weights_format*

  * **Description**: *weights_format* denotes the data format of the weights
    gradient.
  * **Range of values**: *XIO* or *OIX* (X means HW for 2D convolution, DHW for
    3D convolution)
  * **Type**: string
  * **Default value**: *XIO*
  * **Required**: *no*

* *weights_shape*

  * **Description**: *weights_shape* denotes the shape of the weights.
  * **Type**: s64[]
  * **Required**: *no*

**Inputs**:

* **1**: ``src`` - original input tensor of Convolution op.
  **Required**.

  * **Type**: T

* **2**: ``diff_dst`` - the gradient tensor with respect to the output of
  the convolution. **Required**.

  * **Type**: T

* **3**: ``weights_shape`` - 1D integer tensor that specifies shape of the
  weights. The shape of weights is
  :math:`(out_channels, in_channels / groups, spatial_shape)` for OIX format or
  :math:`(spatial_shape, in_channels / groups, out_channels)` for XIO format.
  :math:`in_channels` and :math:`out_channels` must both be divisible by groups.
  If specified, *weights_shape* attribute will be ignored. If not specified,
  users should define *weights_shape* through attribute. **Optional**. 

  * **Type**: s32

**Outputs**:

* **1**: ``diff_weights`` - gradient tensor with respect to the weights of the
  convolution. The format is specified by *weights_format* attribute.

  * **Type**: T

**Types**:

* **T**: f32, f16, bf16.
* **Note**: Inputs and outputs have the same data type denoted by *T*. For
  example, if input is f32 tensor, then all other tensors have f32 data type.
