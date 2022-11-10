.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


BatchNormForwardTraining
########################

BatchNormForwardTraining operation performs batch normalization at
training mode.

Mean and variance are computed at runtime, the following formulas are
used:

-  :math:`\mu(c) = \frac{1}{NHW} \sum\limits_{nhw} \src(n, c, h, w)_{}`,

-  :math:`\sigma^2(c) = \frac{1}{NHW} \sum\limits_{nhw} {}_{} (\src(n, c, h, w) - \mu(c))^2`.

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
| |attr_momentum|    | A number to | f32        | A positive | Optional    |
|                    | be used to  |            | f32 value  |             |
|                    | calculate   |            |            |             |
|                    | running     |            |            |             |
|                    | mean and    |            |            |             |
|                    | running     |            |            |             |
|                    | variance    |            |            |             |
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


===== ================================= ====================
Index Argument Name                     Required or Optional
===== ================================= ====================
0     ``src``                           Required
1     ``mean``                          Required
2     ``variance``                      Required
3     ``gamma``                         Optional
4     ``beta`` (:math:`\sigma^2`)       Optional
===== ================================= ====================

@note ``gamma`` and ``beta`` should be either both provided or neither
provided.

Outputs
=======


===== ==================== ====================
Index Argument Name        Required or Optional
===== ==================== ====================
0     ``dst``              Required
1     ``running_mean``     Required
2     ``running_variance`` Required
3     ``batch_mean``       Required
4     ``batch_variance``   Required
===== ==================== ====================


Supported Data Types
********************

BatchNormInference operation supports the following data type
combinations.

+-----------------------------------+-----------------------------------+
| Src / Dst                         | Gamma / Beta / Mean / Variance /  |
|                                   | Batch_mean / Batch_variance /     |
|                                   | Running_mean / Running_variance   |
+===================================+===================================+
| f32                               | f32                               |
+-----------------------------------+-----------------------------------+
| bf16                              | f32, bf16                         |
+-----------------------------------+-----------------------------------+
| f16                               | f32                               |
+-----------------------------------+-----------------------------------+
