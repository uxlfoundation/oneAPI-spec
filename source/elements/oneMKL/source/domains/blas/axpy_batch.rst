.. _onemkl_blas_axpy_batch:

axpy_batch
==========

axpy_batch (USM Version)
------------------------



.. container::


   Computes groups of vector-scalar products added to a vector.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  sycl::event onemkl::blas::axpy_batch(sycl::queue &queue, std::int64_t *n, T *alpha, const T **x, std::int64_t *incx, T **y, std::int64_t *incy, std::int64_t group_count, std::int64_t *group_size_array, const sycl::vector_class<sycl::event> &dependencies = {})

         ``axpy_batch`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 


   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      The ``axpy_batch`` routines perform a series of scalar-vector product
      added to a vector. They are similar to the ``axpy`` routine counterparts,
      but the ``axpy_batch`` routines perform vector operations with groups of
      vectors. The groups contain vectors with the same parameters.

      The operation is defined as
     
      ::
         
         idx = 0
         for i = 0 … group_count – 1
             n, alpha, incx, incy and group_size at position i in n_array, alpha_array, incx_array, incy_array and group_size_array
             for j = 0 … group_size – 1
                 x and y are vectors of size n at position idx in x_array and y_array
                 y := alpha * x + y
                 idx := idx + 1
             end for
         end for

      The number of entries in ``x_array`` and ``y_array`` is
      ``total_batch_count`` = the sum of all of the ``group_size_array`` entries.
    
   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle

      queue
         The queue where the routine should be executed.

      n_array
         Array of size ``group_count``. For the group ``i``,
         ``n_i = n_array[i]`` is the number of elements in
         vectors ``x`` and ``y``.

      alpha_array
          Array of size ``group_count``. For the group ``i``, ``alpha_i = alpha_array[i]`` is the scalar ``alpha``.

      x_array
         Array of size ``total_batch_count`` of pointers used to
         store ``x`` vectors. The array allocated for the ``x`` vectors of the
         group ``i`` must be of size at least ``(1 + (n_i –
         1)*abs(incx_i))``. See `Matrix and Vector Storage
         <../matrix-storage.html>`__ for more details.

      incx_array 
         Array of size ``group_count``. For the group ``i``, ``incx_i = incx_array[i]`` is the stride of vector ``x``.

      y_array
         Array of size ``total_batch_count`` of pointers used to
         store ``y`` vectors. The array allocated for the ``y`` vectors of the
         group ``i`` must be of size at least ``(1 + (n_i –
         1)*abs(incy_i))``. See `Matrix and Vector Storage
         <../matrix-storage.html>`__ for more details.

      incy_array 
         Array of size ``group_count``. For the group ``i``, ``incy_i = incy_array[i]`` is the stride of vector ``y``.

      group_count
         Number of groups. Must be at least 0.

      group_size_array
         Array of size ``group_count``. The element
         ``group_size_array[i]`` is the number of vector in the
         group ``i``. Each element in ``group_size_array`` must be at least 0.

      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      y_array
         Array of pointers holding the ``total_batch_count`` updated vector ``y``.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:**:ref:`blas-like-extensions`
      


