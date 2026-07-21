.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


BiasAddBackward
###############

BiasAddBackward operation computes the gradients on the bias tensor for
BiasAdd operator. This op accumulates all the values from
:math:`\diffdst` into the channel dimension, the axis depends on
the layout of \src tensor.

Operation Attributes
********************

+--------------------+----------------+------------+-----------+-------------+
|     Attribute      |  Description   | Value Type | Supported | Required or |
|        Name        |                |            |  Values   |  Optional   |
+====================+================+============+===========+=============+
| |attr_data_format| | Controls       | string     | ``NCX`` , | Optional    |
|                    | how to         |            | ``NXC``   |             |
|                    | interpret      |            | (default) |             |
|                    | the shape      |            |           |             |
|                    | of             |            |           |             |
|                    | ``diff_dst``   |            |           |             |
|                    | and            |            |           |             |
|                    | ``diff_bias``. |            |           |             |
+--------------------+----------------+------------+-----------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_dst``  Required
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_bias`` Required
===== ============= ====================


Supported Data Types
********************

BiasAddBackward operation supports the following data type combinations.

======== =========
diff_dst diff_bias
======== =========
f32      f32
bf16     bf16
f16      f16
======== =========
