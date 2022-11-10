.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


BatchNormInference
##################

The formula is the same as `Batch Normalization
primitive :ref:`batch_normalization-label` like below.

.. math::

   \dst(n, c, h, w) =
       \gamma(c) \cdot \frac{\src(n, c, h, w) - \mu(c)}
                            {\sqrt{\sigma^2(c) + \varepsilon}} + \beta(c),


where

-  :math:`\gamma(c), \beta(c)` are required scale and shift for a
   channel,

-  :math:`\mu(c), \sigma^2(c)` are mean and variance for a
   channel, and

-  :math:`\varepsilon` is a constant to improve numerical
   stability.

Operation Attributes
********************

+--------------------+-------------+------------+-------------+-------------+
|     Attribute      | Description | Value Type |  Supported  | Required or |
|        Name        |             |            |   Values    |  Optional   |
+====================+=============+============+=============+=============+
| |attr_epsilon|     | A number to | f32        | A positive  | Required    |
|                    | be added to |            | float value |             |
|                    | the         |            |             |             |
|                    | variance to |            |             |             |
|                    | avoid       |            |             |             |
|                    | division by |            |             |             |
|                    | zero        |            |             |             |
+--------------------+-------------+------------+-------------+-------------+
| |attr_data_format| | Controls    | string     | ``NCX``,    | Optional    |
|                    | how to      |            | ``NXC``     |             |
|                    | interpret   |            | (default)   |             |
|                    | the shape   |            |             |             |
|                    | of ``src``  |            |             |             |
|                    | and         |            |             |             |
|                    | ``dst``.    |            |             |             |
+--------------------+-------------+------------+-------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ===================================== ====================
Index Argument Name                         Required or Optional
===== ===================================== ====================
0     ``src``                               Required
1     ``gamma``                             Required
2     ``beta``                              Required
3     ``mean``                              Required
4     ``variance`` (:math:`\sigma^2`)       Required
===== ===================================== ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

BatchNormInference operation supports the following data type
combinations.

========= ==============================
Src / Dst Gamma / Beta / Mean / Variance
========= ==============================
f32       f32
bf16      f32, bf16
f16       f32
========= ==============================
