.. _onemkl_sparse_release_matrix_handle:

release_matrix_handle
=====================


Releases internal data and sets matrix_handle_t object to NULL.


.. rubric:: Description and Assumptions

The oneapi::mkl::sparse::release_matrix_handle releases any internal data that the
``matrix_handle_t`` object holds and sets it with defaults values, otherwise it
throws an exception. The routine also waits for the dependencies to be finished
before releasing any data in case of USM.


.. rubric:: Syntax


.. cpp:function::  void oneapi::mkl::sparse::release_matrix_handle (matrix_handle_t         handle, const sycl::vector_class<sycl::event> & dependencies = {})


.. container:: section


    .. rubric:: Input parameter


    handle
       Handle to object containing sparse matrix and other internal
       data. Created using one of the
       oneapi::mkl::sparse::set_<sparse_matrix_type>_structure routines.

    dependencies
       List of events that ``handle`` depends on.
       The call waits on the events(if any) before resetting the ``handle`` to default values.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`