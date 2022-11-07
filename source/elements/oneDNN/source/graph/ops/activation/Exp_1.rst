.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

---
Exp
---

**Versioned name**: *Exp-1*

**Category**: *Activation*

**Short description**: Exponential element-wise activation function.

**OpenVINO description**: This OP is as same as `OpenVINO OP
<https://docs.openvino.ai/2021.1/openvino_docs_ops_activation_Exp_1.html>`__

**Attributes**: has no attributes

**Inputs**:

* **1**: ``input`` - input tensor. **Required.**

  * **Type**: T

**Outputs**

* **1**: ``output`` - result of Exp function applied to the input tensor.
  **Required.**

  * **Type**: T

**Types**:

* **T**: f32, f16, bf16.
* **Note**: Inputs and outputs have the same data type denoted by *T*. For
  example, if input is f32 tensor, then all other tensors have f32 data type.
