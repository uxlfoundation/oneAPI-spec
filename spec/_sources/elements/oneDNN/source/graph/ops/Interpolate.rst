.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Interpolate
###########

Interpolate layer performs interpolation on \src tensor at
spatial dimensions.

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
transformation mode in string format. Here ``scale[x]``
is ``dst_shape[x]/src_shape[x]`` and ``x_resized`` is a coordinate in
axis ``x``,for any axis ``x`` from the src axis.\n For
``half_pixel``: the coordinate in the original tensor axis ``x`` is
calculated as ``((x_resized + 0.5) / scale[x]) - 0.5``.\n
For ``align_corners``: the coordinate in the original tensor axis ``x``
is calculated as 0 if ``dst_shape[x] == 1`` else
``x_resized * (src_shape[x] - 1)     / (dst_shape[x] - 1)``.

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
1     ``sizes``     Optional
===== ============= ====================

@note ``sizes`` is a 1D tensor describing output shape for spatial axes.
It is a non-differentiable tensor.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================

@note The shape of the dst matches src shape except spatial dimensions.
For spatial dimensions, they should match sizes from sizes or calculated
from |attr_scales| attribute.


Supported Data Types
********************

Interpolate operation supports the following data type combinations.

========= =====
Src / Dst Sizes
========= =====
f32       s32
bf16      s32
f16       s32
========= =====
