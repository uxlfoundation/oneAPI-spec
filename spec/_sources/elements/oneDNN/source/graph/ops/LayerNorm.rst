.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


LayerNorm
#########

LayerNorm performs a layer normalization operation on
\src tensor.

The layerNorm operation performs normalization from ``begin_norm_axis``
to last dimension of the data tensor. It is defined by the following
formulas which is the same as :ref:`layer_normalization-label`.

.. math::

   \dst(t, n, c) = \gamma(c)
       \cdot \frac{\src(t, n, c) - \mu(t, n)}
                  {\sqrt{\sigma^2(t, n) + \epsilon}}
       + \beta(c),

where

-  :math:`\gamma(c), \beta(c)` are optional scale and shift for a
   channel

-  :math:`\mu(t, n), \sigma^2(t, n)` are mean and variance (see

-  :math:`\epsilon` is a constant to improve numerical stability.

Mean and variance are computed at runtime or provided by a user. When
mean and variance are computed at runtime, the following formulas are
used:

-  :math:`\mu(t, n) = \frac{1}{C} \sum\limits_{c} \src(t, n, c)_{}`,

-  :math:`\sigma^2(t, n) = \frac{1}{C} \sum\limits_{c} {}_{} (\src(t, n, c) - \mu(t, n))^2`.

Operation Attributes
********************

+------------------------+------------------------+------------+----------------+-------------+
|       Attribute        |      Description       | Value Type |   Supported    | Required or |
|          Name          |                        |            |     Values     |  Optional   |
+========================+========================+============+================+=============+
| |attr_keep_stats|      | Indicate               | bool       | ``false``,     | Optional    |
|                        | whether to             |            | ``true``       |             |
|                        | output mean            |            | (default)      |             |
|                        | and                    |            |                |             |
|                        | variance               |            |                |             |
|                        | which can              |            |                |             |
|                        | be later               |            |                |             |
|                        | passed to              |            |                |             |
|                        | backward op            |            |                |             |
+------------------------+------------------------+------------+----------------+-------------+
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
1     ``gamma``     Optional
2     ``beta``      Optional
===== ============= ====================

@note ``gamma`` is scaling for normalized value. ``beta`` is the bias
added to the scaled normalized value. They are both 1D tensor with the
same span as src’s channel axis and required if attribute ``use_affine``
is set to True.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
1     ``mean``      Optional
2     ``variance``  Optional
===== ============= ====================

@note Both ``mean`` and ``variance`` are required if attribute
``keep_stats`` is set to True.


Supported Data Types
********************

LayerNorm operation supports the following data type combinations.

========= ==============================
Src / Dst Gamma / Beta / Mean / Variance
========= ==============================
f32       f32
bf16      f32, bf16
f16       f32
========= ==============================
