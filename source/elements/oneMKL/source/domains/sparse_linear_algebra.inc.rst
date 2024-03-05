.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_linear_algebra:

Sparse Linear Algebra
----------------------

.. container::

   The oneAPI Math Kernel Library provides a Data Parallel C++ interface to some
   of the Sparse Linear Algebra routines.

   :ref:`onemkl_spblas` provides basic operations on sparse vectors and
   matrices, and separates them into three stages: query of the external
   workspace size, optimization stage and execution. For a given configuration,
   the first two stages would typically be called once and the execution may be
   called multiple times. During the optimization stage, the API inspects the
   matrix properties including size, sparsity pattern and available parallelism
   and can apply matrix format or structure changes to enable a more optimized
   algorithm. In the execution stage, multiple routine calls can take advantage
   of the optimization stage data in order to improve performance.

.. toctree::
   :hidden:

   spblas/spblas.rst

