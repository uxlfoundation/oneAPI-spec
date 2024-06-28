.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_compute_forward:

compute_forward
===============

This function computes the forward DFT(s), as defined by an instantiation of
the :ref:`descriptor<onemkl_dft_descriptor>` class, on user-provided data.

.. _onemkl_dft_compute_forward_description:

.. rubric:: Description

Given a successfully committed :ref:`descriptor<onemkl_dft_descriptor>` object
whose configuration is not inconsistent with forward DFT calculations, this
function computes the forward transform defined by that object.

The ``compute_forward`` function requires a successfully committed object of the
:ref:`descriptor<onemkl_dft_descriptor>` class and one, two or four "data
container" arguments (depending on the configuration of the
:ref:`descriptor<onemkl_dft_descriptor>` object). If using (pointers to) USM
allocations as data containers, this function may also be provided with an
``std::vector<sycl::event>`` object collecting dependencies to be observed by
the desired DFT calculations and return a ``sycl::event`` tracking the
progress of the DFT calculations enqueued by this function.

.. note::
   The compute_forward function may need to access the internals and
   private/protected members of the :ref:`descriptor<onemkl_dft_descriptor>`
   class.  This could be done, for instance, by labeling it as a friend function
   to the :ref:`descriptor<onemkl_dft_descriptor>` class.

.. onemkl_dft_compute_forward_buffer:

compute_forward (Buffer version)
--------------------------------

.. rubric:: Syntax (in-place transform, except for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename data_type>
      void compute_forward( descriptor_type              &desc,
                            sycl::buffer<data_type, 1>   &inout);
   }


.. rubric:: Syntax (in-place transform, for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type typename data_type>
      void compute_forward( descriptor_type              &desc,
                            sycl::buffer<data_type, 1>   &inout_re,
                            sycl::buffer<data_type, 1>   &inout_im);
   }


.. rubric:: Syntax (out-of-place transform, except for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {
   
      template <typename descriptor_type, typename input_type, typename output_type>
      void compute_forward( descriptor_type              &desc,
                            sycl::buffer<input_type, 1>  &in,
                            sycl::buffer<output_type, 1> &out);
   }

.. rubric:: Syntax (out-of-place transform, for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename input_type, typename output_type>
      void compute_forward( descriptor_type              &desc,
                            sycl::buffer<input_type, 1>  &in_re,
                            sycl::buffer<input_type, 1>  &in_im,
                            sycl::buffer<output_type, 1> &out_re,
                            sycl::buffer<output_type, 1> &out_im);
   }


.. container:: section

   .. rubric:: Input Parameters

   :ref:`desc<onemkl_dft_descriptor>`
      A fully configured and committed object of the
      :ref:`descriptor<onemkl_dft_descriptor>` class, whose configuration is not
      inconsistent with forward DFT calculations.

   inout
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining all the relevant data sequences, as configured by ``desc``
      (configured for in-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   inout_re
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the real parts of all the relevant data sequences, as configured
      by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   inout_im
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant data sequences, as
      configured by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   in
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining all the relevant forward-domain data sequences, as
      configured by ``desc`` (configured for out-of-place operations and not
      with :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   in_re
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the real parts of all the relevant forward-domain data sequences,
      as configured by ``desc``. Only with complex descriptors configured for
      out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.

   in_im
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant forward-domain data
      sequences, as configured by ``desc``. Only with complex descriptors configured for
      out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.


.. container:: section

   .. rubric:: Output Parameters

   inout
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining all the relevant data sequences, as configured by ``desc``
      (configured for in-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   inout_re
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the real parts of all the relevant data sequences, as configured
      by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   inout_im
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant data sequences, as
      configured by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   out
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining all the relevant backward-domain data sequences, as configured by
      ``desc`` (configured for out-of-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   out_re
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the real parts of all the relevant backward-domain data sequences,
      as configured by ``desc``. Only with complex descriptors configured for
      out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.

   out_im
      ``sycl::buffer`` object of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant backward-domain data
      sequences, as configured by ``desc``. Only with complex descriptors configured
      for out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.

.. container:: section

   .. rubric:: Throws

   The ``oneapi::mkl::dft::compute_forward`` routine shall throw the following
   exceptions if the associated condition is detected. An implementation may
   throw additional implementation-specific exception(s) in case of error
   conditions not covered here:

   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the provided :ref:`descriptor<onemkl_dft_descriptor>` object ``desc``
      is invalid, for instance, if its configuration value associated with
      configuration parameter ``config_param::COMMIT_STATUS`` is not
      ``config_param::COMMITTED``.

.. onemkl_dft_compute_forward_usm:

compute_forward (USM version)
-----------------------------

.. rubric:: Syntax (in-place transform, except for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename data_type>
      sycl::event compute_forward( descriptor_type                               &desc,
                                   data_type                                     *inout,
                                   const std::vector<sycl::event>                &dependencies = {});
   }

.. rubric:: Syntax (in-place transform, for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename data_type>
      sycl::event compute_forward( descriptor_type                               &desc,
                                   data_type                                     *inout_re,
                                   data_type                                     *inout_im,
                                   const std::vector<sycl::event>                &dependencies = {});
   }

.. rubric:: Syntax (out-of-place transform, except for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename input_type, typename output_type>
      sycl::event compute_forward( descriptor_type                               &desc,
                                   input_type                                    *in,
                                   output_type                                   *out,
                                   const std::vector<sycl::event>                &dependencies = {});
   }

.. rubric:: Syntax (out-of-place transform, for complex descriptors with :ref:`onemkl_dft_complex_storage_real_real`)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <typename descriptor_type, typename input_type, typename output_type>
      sycl::event compute_forward( descriptor_type                               &desc,
                                   input_type                                    *in_re,
                                   input_type                                    *in_im,
                                   output_type                                   *out_re,
                                   output_type                                   *out_im,
                                   const std::vector<sycl::event>                &dependencies = {});
   }

.. container:: section

   .. rubric:: Input Parameters

   :ref:`desc<onemkl_dft_descriptor>`
      A fully configured and committed object of the
      :ref:`descriptor<onemkl_dft_descriptor>` class, whose configuration is not
      inconsistent with forward DFT calculations.

   inout
      Pointer to USM allocation of sufficient capacity to store the elements
      defining all the relevant data sequences, as configured by ``desc``
      (configured for in-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   inout_re
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the real parts of all the relevant data sequences, as configured
      by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   inout_im
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant data sequences, as
      configured by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   in
      Pointer to USM allocation of sufficient capacity to store the elements
      defining all the relevant forward-domain data sequences, as configured by
      ``desc`` (configured for out-of-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   in_re
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the real parts of all the relevant forward-domain data sequences,
      as configured by ``desc``. Only with complex descriptors configured for out-of-place
      operations with :ref:`onemkl_dft_complex_storage_real_real`.

   in_im
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant forward-domain data
      sequences, as configured by ``desc``. Only with complex descriptors configured for
      out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.

   dependencies
      An ``std::vector<sycl::event>`` object collecting the events returned by
      previously enqueued tasks that must be finished before this transform can
      be calculated.

.. container:: section

   .. rubric:: Output Parameters

   inout
      Pointer to USM allocation of sufficient capacity to store the elements
      defining all the relevant data sequences, as configured by ``desc``
      (configured for in-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   inout_re
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the real parts of all the relevant data sequences, as configured
      by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   inout_im
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant data sequences, as
      configured by ``desc``. ``data_type`` must be single or double precision
      floating-point, as described by the descriptor's precision. Only with
      complex descriptors configured for in-place operations with
      :ref:`onemkl_dft_complex_storage_real_real`.

   out
      Pointer to USM allocation of sufficient capacity to store the elements
      defining all the relevant backward-domain data sequences, as configured by
      ``desc`` (configured for out-of-place operations and not with
      :ref:`onemkl_dft_complex_storage_real_real`, if complex).

   out_re
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the real parts of all the relevant backward-domain data sequences,
      as configured by ``desc``. Only with complex descriptors configured for out-of-place
      operations with :ref:`onemkl_dft_complex_storage_real_real`.

   out_im
      Pointer to USM allocation of sufficient capacity to store the elements
      defining the imaginary parts of all the relevant backward-domain data
      sequences, as configured by ``desc``. Only with complex descriptors configured for
      out-of-place operations with :ref:`onemkl_dft_complex_storage_real_real`.

.. container:: section

   .. rubric:: Throws

   The ``oneapi::mkl::dft::compute_forward()`` routine shall throw the following
   exceptions if the associated condition is detected. An implementation may
   throw additional implementation-specific exception(s) in case of error
   conditions not covered here:

   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the provided :ref:`descriptor<onemkl_dft_descriptor>` object ``desc``
      is invalid, for instance, if its configuration value associated with
      configuration parameter ``config_param::COMMIT_STATUS`` is not
      ``config_param::COMMITTED``. It will also be thrown if any required
      input/output pointer is ``nullptr``.

.. container:: section

   .. rubric:: Return Values

   This function returns a ``sycl::event`` object that allows to track progress
   of the forward DFT, and can be passed as a dependency to other routines that
   may depend on the result of the forward transform(s) before proceeding with
   other operations.

**Parent topic:** :ref:`onemkl_dft`
