.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_arch_other:

Other Features
----------------
This section covers all other features in the design of oneMKL architecture.


.. _onemkl_spec_current_version:

Specification Version and Compliance
+++++++++++++++++++++++++++++++++++++++++++++

Each oneMKL domain must define a preprocessor macro to represent the version of the specification that the implementation is compliant with.

The macros for each domain are listed as follows:

  | ONEMKL_BLAS_SPEC_VERSION
  | ONEMKL_LAPACK_SPEC_VERSION
  | ONEMKL_SPARSE_SPEC_VERSION
  | ONEMKL_DFT_SPEC_VERSION
  | ONEMKL_RNG_SPEC_VERSION
  | ONEMKL_VM_SPEC_VERSION

The specification version can be created by appending all digits of the specification version in the format of <MAJOR><MINOR>. MINOR version always uses two digits. This version can be used to check the compatibility of the implementation with the specification version.

Version Example

  | oneAPI 1.1 rev 1 will be represented as a numerical value of 101
  | oneAPI 1.2 rev 1 will be represented as a numerical value of 102
  | oneAPI 1.2 rev 2 will be represented as a numerical value of 102

Macro Example

.. code-block:: c

  // For oneAPI 1.2 rev 1
  #define ONEMKL_BLAS_SPEC_VERSION 102

  // For oneAPI 1.2 rev 2
  #define ONEMKL_DFT_SPEC_VERSION 102

  // For oneAPI 1.3 rev 1
  #define ONEMKL_VM_SPEC_VERSION 103


.. _onemkl_pre_post_conditions:

Pre/Post Condition Checking
+++++++++++++++++++++++++++++++++++++++

The individual oneMKL computational routines will define any preconditions and postconditions and will define in this specification any specific checks or verifications that should be enabled for all implementations.


