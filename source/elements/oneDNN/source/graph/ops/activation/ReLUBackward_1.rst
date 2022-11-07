.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

------------
ReLUBackprop
------------

**Versioned name**: *ReLUBackprop-1*

**Category**: *Activation*

**Short description**:
`Reference <http://caffe.berkeleyvision.org/tutorial/layers/relu.html>`__

**Detailed description**:
`Reference <https://github.com/Kulbear/deep-learning-nano-foundation/wiki/ReLUBackprop-and-Softmax-Activation-Functions#rectified-linear-units>`__

**Attributes**:* *use_dst*

  * **Description**: If true, use *dst* to calculate gradient; else use *src*.
  * **Range of values**: True or False
  * **Type**: bool
  * **Default value**: True
  * **Required**: *no*

**Inputs**:

* **1**:  ``result_forward``/ ``input_forward`` - if *use_dst* is true,
  ``result_forward`` is used, else ``input_forward`` is used. **Required.**

  * **Type**: T

* **2**: ``diff_dst`` - the gradient tensor with respect to the output.
  **Required.**

  * **Type**: T

**Outputs**

* **1**: ``diff_src`` - the gradient tensor with respect to the input of
  ReLU.

  * **Type**: T

**Types**:

* **T**: f32, f16, bf16.
* **Note**: Inputs and outputs have the same data type denoted by *T*. For
  example, if input is f32 tensor, then all other tensors have f32 data type.
