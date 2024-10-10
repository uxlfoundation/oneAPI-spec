.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


BatchNormTrainingBackward
#########################

BatchNormTrainingBackward operation calculated the gradients of input
tensors.

Operation Attributes
********************

+--------------------+-------------+------------+------------+-------------+
|     Attribute      | Description | Value Type | Supported  | Required or |
|        Name        |             |            |   Values   |  Optional   |
+====================+=============+============+============+=============+
| |attr_epsilon|     | A number to | f32        | A positive | Required    |
|                    | be added to |            | f32 value  |             |
|                    | the         |            |            |             |
|                    | variance to |            |            |             |
|                    | avoid       |            |            |             |
|                    | division by |            |            |             |
|                    | zero        |            |            |             |
+--------------------+-------------+------------+------------+-------------+
| |attr_data_format| | Controls    | string     | ``NCX``,   | Optional    |
|                    | how to      |            | ``NXC``    |             |
|                    | interpret   |            | (default)  |             |
|                    | the shape   |            |            |             |
|                    | of ``src``  |            |            |             |
|                    | and         |            |            |             |
|                    | ``dst``.    |            |            |             |
+--------------------+-------------+------------+------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ================================== ====================
Index Argument Name                      Required or Optional
===== ================================== ====================
0     ``src``                            Required
1     ``diff_dst``                       Required
2     ``mean``                           Required
3     ``variance``                       Required
4     ``gamma`` (:math:`\sigma^2`)       Optional
===== ================================== ====================

Outputs
=======


===== ============== ====================
Index Argument Name  Required or Optional
===== ============== ====================
0     ``diff_src``   Required
1     ``diff_gamma`` Optional
2     ``diff_beta``  Optional
===== ============== ====================

@note ``diff_gamma`` and ``diff_beta`` should be either both provided or
neither provided. If neither provided, the input ``gamma`` will be
ignored.


Supported Data Types
********************

BatchNormTrainingBackward operation supports the following data type
combinations.

========================= ================================================
Src / Diff_dst / Diff_src Mean / Variance / Gamma / Diff_gamma / Diff_beta
========================= ================================================
f32                       f32
bf16                      f32, bf16
f16                       f32
========================= ================================================
