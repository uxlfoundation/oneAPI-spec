.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst

.. _op_typecast-label:

TypeCast
########

TypeCast operation performs element-wise cast from input data type to
the data type given by output tensor. It requires that
\src and \dst have the same shape and layout.
Rounding to nearest even will be used during cast.

Operation Attributes
********************

TypeCast operation does not support any attribute.

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
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================

Supported Data Types
********************

TypeCast operation supports the following data type combinations.

========= =========
Src       Dst
========= =========
bf16, f16 f32
f32       bf16, f16
========= =========

@note This operation is to support :ref:`mixed
precision<graph_quantization_model-label>` computation.
