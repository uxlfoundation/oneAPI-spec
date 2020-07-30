.. _onemkl_sparse_linear_algebra:

Sparse Linear Algebra
----------------------

.. container::


   The oneAPI Math Kernel Library provides a Data Parallel C++ interface
   to some of the Sparse Linear Algebra routines.

   :ref:`onemkl_spblas` provides basic operations on sparse vectors and matrices, and
   separates them into two stages: analysis
   (also called inspector stage or optimize stage) and execution. For a given matrix,
   the analysis would typically be called one time and the execution may be called
   multiple times. During the analysis stage, the API inspects the matrix properties
   including size, sparsity pattern and available parallelism and can apply matrix
   format or structure changes to enable a more optimized algorithm.
   In the execution stage, multiple routine calls can take advantage of the analysis
   stage data in order to improve performance.


   In order to save information in between calls to Sparse BLAS computation routines,
   the :ref:`onemkl_sparse_matrix_handle_t` type is introduced, that is essentially
   an opaque pointer, used to store data related to initial sparse matrix
   and data obtained during analysis stage.


.. toctree::
    :hidden:

    spblas/spblas.rst

