.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_arch_other:

Other Features
----------------
This section covers all other features in the design of oneMKL architecture.


.. _onemkl_spec_current_version:

Version of oneMKL Specification
+++++++++++++++++++++++++++++++++++++++++++++

This is the oneMKL specification which is part of the oneAPI specification.

The implementation must define a macro, `ONEMKL_SPEC_VERSION` as having the numerical value of the specification version.

The specification version can be created by appending all digits of the specification version in the format of <MAJOR><MINOR>. MINOR version always uses two digits. This version can be used to check the compatibility of the implementation with the specification version.

Version Example
  | oneAPI 1.1 rev 1 will be represented as a numerical value of 101
  | oneAPI 1.2 rev 1 will be represented as a numerical value of 102
  | oneAPI 1.2 rev 2 will be represented as a numerical value of 102

Macro Example

.. code-block:: c

  // For oneAPI 1.2 rev 1
  #define ONEMKL_SPEC_VERSION 102

  // For oneAPI 1.2 rev 2
  #define ONEMKL_SPEC_VERSION 102

  // For oneAPI 1.3 rev 1
  #define ONEMKL_SPEC_VERSION 103


.. _onemkl_pre_post_conditions:

Pre/Post Condition Checking
+++++++++++++++++++++++++++++++++++++++

The individual oneMKL computational routines will define any preconditions and postconditions and will define in this specification any specific checks or verifications that should be enabled for all implementations.


