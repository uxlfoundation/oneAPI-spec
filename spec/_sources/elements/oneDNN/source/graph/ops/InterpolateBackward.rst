.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


InterpolateBackward
###################

InterpolateBackward computes the gradients of Interpolate operation.

Operation Attributes
********************

+--------------------+-------------+------------+-------------------+-------------+
|     Attribute      | Description | Value Type |     Supported     | Required or |
|        Name        |             |            |      Values       |  Optional   |
+====================+=============+============+===================+=============+
| |attr_mode|        | Specifies   | string     | ``nearest``,      | Required    |
|                    | type of     |            | ``linear``,       |             |
|                    | in          |            | ``bilinear``,     |             |
|                    | terpolation |            | ``trilinear``     |             |
+--------------------+-------------+------------+-------------------+-------------+
| |attr_coo_trmode|  | Specifies   | string     | ``half_pixel``    | Optional    |
|                    | how to      |            | (default),        |             |
|                    | transform   |            | ``align_corners`` |             |
|                    | the         |            |                   |             |
|                    | coordinate  |            |                   |             |
|                    | in the      |            |                   |             |
|                    | resized     |            |                   |             |
|                    | tensor to   |            |                   |             |
|                    | the         |            |                   |             |
|                    | coordinate  |            |                   |             |
|                    | in the      |            |                   |             |
|                    | original    |            |                   |             |
|                    | tensor      |            |                   |             |
+--------------------+-------------+------------+-------------------+-------------+
| |attr_sizes|       | Specifies   | s64        | A s64 list        | Optional    |
|                    | dst shape   |            | containing        |             |
|                    | for spatial |            | positive          |             |
|                    | axes.       |            | values,           |             |
|                    |             |            | ``none`` is       |             |
|                    |             |            | default           |             |
+--------------------+-------------+------------+-------------------+-------------+
| |attr_scales|      | Specifies   | f32        | A f32 list,       | Optional    |
|                    | ``scales``  |            | ``none`` is       |             |
|                    | for spatial |            | default           |             |
|                    | axes.       |            |                   |             |
|                    |             |            |                   |             |
+--------------------+-------------+------------+-------------------+-------------+
| |attr_data_format| | Controls    | string     | ``NCX``,          | Optional    |
|                    | how to      |            | ``NXC``           |             |
|                    | interpret   |            | (default)         |             |
|                    | the shape   |            |                   |             |
|                    | of ``src``  |            |                   |             |
|                    | and ``dst`` |            |                   |             |
+--------------------+-------------+------------+-------------------+-------------+

@note Either ``sizes`` or ``scales`` should be provided. When ``sizes``
is used, ``scales`` will be ignored.

@note The attribute |attr_coo_trmode| is the name of
transformation mode in string format.\n Here ``scale[x]``
is ``dst_shape[x]/src_shape[x]`` and ``x_resized`` is a coordinate in
axis ``x``,for any axis ``x`` from the src axis.\n For
``half_pixel``: the coordinate in the original tensor axis ``x`` is
calculated as ``((x_resized + 0.5) / scale[x]) - 0.5``.\n
For ``align_corners``: the coordinate in the original tensor axis ``x``
is calculated as 0 if ``dst_shape[x] == 1`` else
``x_resized * (src_shape[x] - 1)     / (dst_shape[x] - 1)``.\n

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``src``       Required
1     ``diff_dst``  Required
2     ``sizes``     Optional
===== ============= ====================

@note ``src`` is original input tensor of Interpolate op.\n
``diff_dst`` is the gradient tensor with respect to the
dst.\n ``sizes`` is a 1D tensor describing output shape for
spatial axes.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================

@note ``diff_src`` is the gradient tensor with respect to the src of
Interpolate.


Supported Data Types
********************

InterpolateBackward operation supports the following data type
combinations.

==== ======== ======== =====
Src  Diff_dst Diff_src Sizes
==== ======== ======== =====
f32  f32      f32      s32
bf16 bf16     bf16     s32
f16  f16      f16      s32
==== ======== ======== =====
