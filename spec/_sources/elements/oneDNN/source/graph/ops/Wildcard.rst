.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Wildcard
########

Wildcard operation is used to represent any compute logic and help
construct graph. Typically the operation can support mapping any
framework ops which are not supported by the library implementation.
It’s useful to make the graph completed or connected.

Operation Attributes
********************

Wildcard operation does not support any attribute.

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``src``       Optional
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Optional
===== ============= ====================

@note WildCard operation can accept arbitrary number of inputs or
outputs.

Supported Data Types
********************

Wildcard operation supports arbitrary data type combinations.
