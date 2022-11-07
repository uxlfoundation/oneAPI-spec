.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

------
Divide
------

**Versioned name**: *Divide-1*

**Category**: *Arithmetic*

**Short description**: *Divide* performs element-wise division operation with
two given tensors applying multi-directional broadcast rules.

**OpenVINO description**: This OP is as same as `OpenVINO OP
<https://docs.openvino.ai/2021.1/openvino_docs_ops_arithmetic_Divide_1.html>`__

**Attributes**:

* *auto_broadcast*

  * **Description**: specifies rules used for auto-broadcasting of input
    tensors.
  * **Range of values**:

    * *none* - no auto-broadcasting is allowed, all input shapes should match
    * *numpy* - numpy broadcasting rules, aligned with ONNX Broadcasting.
      Description is available in `ONNX docs
      <https://github.com/onnx/onnx/blob/master/docs/Broadcasting.md>`__.

  * **Type**: string
  * **Default value**: *numpy*
  * **Required**: *no*

**Inputs**

* **1**: ``input_1`` - dividend tensor. **Required.**
  
  * **Type**: T

* **2**: ``input_2`` - divisor tensor. **Required.**
  
  * **Type**: T

**Outputs**

* **1**: ``output`` - the output tensor of element-wise division operation.
  
  * **Type**: T
  
**Types**:

* **T**: f32, f16, bf16.
* **Note**: Inputs and outputs have the same data type denoted by *T*. For
  example, if input is f32 tensor, then all other tensors have f32 data type.

**Detailed description**:

Before performing arithmetic operation, *input_1* and *input_2* are broadcasted
if their shapes are different and ``auto_broadcast`` attributes is
not ``none``. Broadcasting is performed according to ``auto_broadcast`` value.

After broadcasting *Divide* does the following with  *input_1* and *input_2*:

.. math::
   output_{i} = input\_1_{i} / input\_2_{i}
