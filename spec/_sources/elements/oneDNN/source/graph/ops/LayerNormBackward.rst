.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


LayerNormBackward
#################

LayerNormBackward performs the backward of LayerNorm operation.

The backward propagation computes :math:`\diffsrc(t, n, c)`,
:math:`\diffgamma(c)^*`, and :math:`\diffbeta(c)^*` based
on :math:`\diffdst(t, n, c)`, :math:`src(t, n, c)`,
:math:`\mu(t, n)`, :math:`\sigma^2(t, n)`,
:math:`\gamma(c) ^*`, and :math:`\beta(c) ^*`.

The tensors marked with an asterisk are used only when the operation is
configured to use :math:`\gamma(c)`, and :math:`\beta(c)`

Operation Attributes
********************

+------------------------+------------------------+------------+----------------+-------------+
|       Attribute        |      Description       | Value Type |   Supported    | Required or |
|          Name          |                        |            |     Values     |  Optional   |
+========================+========================+============+================+=============+
| |attr_begin_norm_axis| | |attr_begin_norm_axis| | s64        | [-r,r-1],where | Optional    |
|                        | is used to             |            | r=rank(src).   |             |
|                        | indicate               |            | -1 is default  |             |
|                        | which axis             |            |                |             |
|                        | to start               |            |                |             |
|                        | layer                  |            |                |             |
|                        | normalization.         |            |                |             |
|                        | The                    |            |                |             |
|                        | normalization          |            |                |             |
|                        | is from                |            |                |             |
|                        | |attr_begin_norm_axis| |            |                |             |
|                        | to last                |            |                |             |
|                        | dimension.             |            |                |             |
|                        | Negative               |            |                |             |
|                        | values                 |            |                |             |
|                        | means                  |            |                |             |
|                        | indexing               |            |                |             |
|                        | from right             |            |                |             |
|                        | to left.               |            |                |             |
|                        | This op                |            |                |             |
|                        | normalizes             |            |                |             |
|                        | over the               |            |                |             |
|                        | last                   |            |                |             |
|                        | dimension              |            |                |             |
|                        | by default,            |            |                |             |
|                        | e.g. C in              |            |                |             |
|                        | TNC for 3D             |            |                |             |
|                        | and LDNC               |            |                |             |
|                        | for 4D.                |            |                |             |
+------------------------+------------------------+------------+----------------+-------------+
| |attr_use_affine|      | When set to            | bool       | ``false``,     | Optional    |
|                        | True, this             |            | ``true``       |             |
|                        | module has             |            | (default)      |             |
|                        | learnable              |            |                |             |
|                        | per-element            |            |                |             |
|                        | affine                 |            |                |             |
|                        | parameters.            |            |                |             |
+------------------------+------------------------+------------+----------------+-------------+
| |attr_epsilon|         | The                    | f32        | Arbitrary      | Optional    |
|                        | constant to            |            | positive       |             |
|                        | improve                |            | f32 value,     |             |
|                        | numerical              |            | ``1e-5``       |             |
|                        | stability              |            | (default)      |             |
+------------------------+------------------------+------------+----------------+-------------+

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
2     ``mean``      Required
3     ``variance``  Required
4     ``gamma``     Optional
5     ``beta``      Optional
===== ============= ====================

@note ``gamma`` is scaling for normalized value. ``beta`` is the bias
added to the scaled normalized value. They are both 1D tensor with the
same span as src’s channel axis and required if attribute |attr_use_affine|
is set to True.

Outputs
=======


===== ============== ====================
Index Argument Name  Required or Optional
===== ============== ====================
0     ``diff_src``   Required
1     ``diff_gamma`` Optional
2     ``diff_beta``  Optional
===== ============== ====================


Supported Data Types
********************

LayerNormBackward operation supports the following data type
combinations.

+-----------------------------------+-----------------------------------+
| Src / Diff_dst / Diff_src         | Gamma / Beta / Mean / Variance /  |
|                                   | Diff_gamma / Diff_beta            |
+===================================+===================================+
| f32                               | f32                               |
+-----------------------------------+-----------------------------------+
| bf16                              | f32, bf16                         |
+-----------------------------------+-----------------------------------+
| f16                               | f32                               |
+-----------------------------------+-----------------------------------+
