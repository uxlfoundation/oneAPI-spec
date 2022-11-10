.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Convolution
###########


Convolution operation performs the convolution between src tensor and
weight tensor, which is defined as by the following formulas. Variable
names follow the standard :ref:`conventions-label`.

Let \src, \weights and
\dst tensors have shape
:math:`N \times IC \times IH \times IW`,
:math:`OC \times IC \times KH \times KW`, and
:math:`N \times OC \times OH \times OW` respectively.

Furthermore, let the remaining convolution parameters be:

+-------------+--------------+--------------+--------------+-------------------+
|  Parameter  |    Depth     |    Height    |    Width     |      Comment      |
+=============+==============+==============+==============+===================+
| Paddings:   | :math:`PD_L` | :math:`PH_L` | :math:`PW_L` | In the            |
| Front, top, |              |              |              | attributes        |
| and left    |              |              |              | we use            |
|             |              |              |              | |attr_pads_begin| |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | paddings          |
+-------------+--------------+--------------+--------------+-------------------+
| Padding:    | :math:`PD_R` | :math:`PH_R` | :math:`PW_R` | In the            |
| Back,       |              |              |              | attributes        |
| bottom, and |              |              |              | we use            |
| right       |              |              |              | |attr_pads_end|   |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | paddings          |
+-------------+--------------+--------------+--------------+-------------------+
| Stride      | :math:`SD`   | :math:`SH`   | :math:`SW`   | In the            |
|             |              |              |              | attributes        |
|             |              |              |              | we use            |
|             |              |              |              | |attr_strides|    |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | strides           |
+-------------+--------------+--------------+--------------+-------------------+
| Dilation    | :math:`DD`   | :math:`DH`   | :math:`DW`   | In the            |
|             |              |              |              | attributes        |
|             |              |              |              | we use            |
|             |              |              |              | |attr_dilations|  |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | dilations         |
+-------------+--------------+--------------+--------------+-------------------+

To further simplify the formulas, we assume that the attribute
|attr_data_format| and |attr_weights_format| are set to ``NCX`` and ``OIX``
respectively. ``NCX`` means the fist axis represents batch dimension,
the second axis represents channel dimension and the rest represents
spatial dimensions. ``OIX`` means the first axis represents output
channel dimension, the second axis represents input channel dimension
and the rest represents weights spatial dimensions.

Regular Convolution
===================

This is the same as the formula in `Convolution
primitive :ref:`convolution-label`.

.. math::

   \dst(n, oc, oh, ow) & = \bias(oc) \\
   + \sum_{ic=0}^{IC-1} \sum_{kh=0}^{KH-1} \sum_{kw=0}^{KW-1} &
   \src(n, ic, oh', ow') \cdot \weights(oc, ic, kh, kw).

Here:

-  :math:`OH = \left\lfloor{\frac{IH - KH + PH_L + PH_R}{SH}} \right\rfloor + 1,`

-  :math:`OW = \left\lfloor{\frac{IW - KW + PW_L + PW_R}{SW}} \right\rfloor + 1.`

Convolution with Groups
=======================

The attribute |attr_groups| is set to :math:`>1`.

.. math::

       \dst(n, g \cdot OC_G + oc_g, oh, ow) & = \bias(g \cdot OC_G + oc_g) \\
            + \sum_{ic_g=0}^{IC_G-1} \sum_{kh=0}^{KH-1} \sum_{kw=0}^{KW-1} &
              \src(n, g \cdot IC_G + ic_g, oh', ow')
              \cdot
              \weights(g, oc_g, ic_g, kh, kw),

where

-  :math:`IC_G = \frac{IC}{G}`,

-  :math:`OC_G = \frac{OC}{G}`, and

-  :math:`oc_g \in [0, OC_G).`

Convolution with Dilation
=========================

The attribute |attr_dilations| contains the element which is :math:`>1`.

.. math::

       \dst(n, oc, oh, ow) & = \bias(oc) + \\
            + \sum_{ic=0}^{IC-1} \sum_{kh=0}^{KH-1} \sum_{kw=0}^{KW-1} &
              \src(n, ic, oh'', ow'')
              \cdot
              \weights(oc, ic, kh, kw).

Here:

-  :math:`OH = \left\lfloor{\frac{IH - DKH + PH_L + PH_R}{SH}}  \right\rfloor + 1,`
   where :math:`DKH = 1 + (KH - 1) \cdot DH`, and

-  :math:`OW = \left\lfloor{\frac{IW - DKW + PW_L + PW_R}{SW}}  \right\rfloor + 1,`
   where :math:`DKW = 1 + (KW - 1) \cdot DW`.

Operation Attributes
********************

+-----------------------+-------------------+------------+-----------------+-------------+
|       Attribute       |    Description    | Value Type |    Supported    | Required or |
|         Name          |                   |            |     Values      |  Optional   |
+=======================+===================+============+=================+=============+
| |attr_strides|        | Controls          | s64        | A s64 list      | Required    |
|                       | the strides       |            | containing      |             |
|                       | the weights       |            | positive        |             |
|                       | tensor is         |            | values          |             |
|                       | moved when        |            |                 |             |
|                       | computing         |            |                 |             |
|                       | convolution       |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_begin|     | Controls          | s64        | A s64 list      | Required    |
|                       | number of         |            | containing      |             |
|                       | zeros to be       |            | non-negative    |             |
|                       | add to the        |            | values          |             |
|                       | front/top/left    |            |                 |             |
|                       | of spatial        |            |                 |             |
|                       | dimensions        |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_end|       | Controls          | s64        | A s64 list      | Required    |
|                       | number of         |            | containing      |             |
|                       | zeros to be       |            | non-negative    |             |
|                       | add to the        |            | values          |             |
|                       | back/bottom/right |            |                 |             |
|                       | of spatial        |            |                 |             |
|                       | dimensions        |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_dilations|      | Controls          | s64        | A s64 list      | Required    |
|                       | the amount        |            | containing      |             |
|                       | of                |            | positive        |             |
|                       | stretching        |            | values (>1      |             |
|                       | the kernel        |            | means           |             |
|                       | before            |            | dilated         |             |
|                       | convolution       |            | convolution)    |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_auto_pad|       | Controls          | string     | ``none``        | Optional    |
|                       | how the           |            | (default),      |             |
|                       | padding is        |            | ``same_upper``, |             |
|                       | calculated        |            | ``same_lower``, |             |
|                       |                   |            | ``valid``       |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_groups|         | Controls          | s64        | A positive      | Optional    |
|                       | how input         |            | s64 value,      |             |
|                       | channels          |            | ``1`` by        |             |
|                       | and output        |            | default         |             |
|                       | channels          |            |                 |             |
|                       | are divided       |            |                 |             |
|                       | into              |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_data_format|    | Controls          | string     | ``NCX``,        | Optional    |
|                       | how to            |            | ``NXC``         |             |
|                       | interpret         |            | (default)       |             |
|                       | the shape         |            |                 |             |
|                       | of ``src``        |            |                 |             |
|                       | and               |            |                 |             |
|                       | ``dst``.          |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_weights_format| | Controls          | string     | ``OIX``,        | Optional    |
|                       | how to            |            | ``XIO``         |             |
|                       | interpret         |            | (default)       |             |
|                       | the shape         |            |                 |             |
|                       | of                |            |                 |             |
|                       | ``weights``       |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+

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
1     ``weights``   Required
2     ``bias``      Optional
===== ============= ====================

@note The shape of \weights is
:math:`(out\_channels, in\_channels / groups, spatial\_shape)`
for ``OIX`` format or
:math:`(spatial\_shape, in\_channels / groups, out\_channels)`
for ``XIO`` format. Both :math:`in\_channels` and
:math:`out\_channels` must be divisible by *groups* attribute.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================

Supported Data Types
********************

Convolution operation supports the following data type combinations.

==== ======= ==== ====
Src  Weights Bias Dst
==== ======= ==== ====
f32  f32     f32  f32
bf16 bf16    bf16 bf16
f16  f16     f16  f16
==== ======= ==== ====
