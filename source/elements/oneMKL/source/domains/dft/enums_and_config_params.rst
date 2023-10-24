.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_enums:

Configuration Parameters and Enums
------------------------------------

The following enum classes are defined in the ``oneapi::mkl::dft`` namespace which are used for configuring the discrete Fourier transform problem in the :ref:`onemkl_dft_descriptor` class prior to a call to :ref:`onemkl_dft_descriptor_commit`.  

.. list-table::
      :header-rows: 1

      * -   enum class 
        -   Description
      * -   :ref:`onemkl_dft_enum_precision`
        -   The floating-point precision in which the transform is carried out. Used as a template argument for :ref:`onemkl_dft_descriptor` class.
      * -   :ref:`onemkl_dft_enum_domain`
        -   The forward domain data type for dft transformation. Used as a template argument for :ref:`onemkl_dft_descriptor` class.
      * -   :ref:`onemkl_dft_enum_config_param`
        -   The configuration parameters to specify the DFT transformation desired.  These can be set and retrieved via the :ref:`onemkl_dft_descriptor_set_value` and :ref:`onemkl_dft_descriptor_get_value` functions.
      * -   :ref:`onemkl_dft_enum_config_value`
        -   Some possible enum values that the :ref:`onemkl_dft_enum_config_param` configuration parameters can take on.




.. _onemkl_dft_enum_precision:

precision
+++++++++

The floating-point precision in which the transform is to be carried out.  The data must be presented in this precision, the computation is carried out in this precision, and the result is delivered in this precision.

.. container:: section
 
   .. rubric:: Syntax

   .. code:: cpp
      
      enum class precision {
         SINGLE,
         DOUBLE
      };

   .. list-table::
      :header-rows: 1

      * -   Value
        -   Description
      * -   SINGLE
        -   data and transforms are executed using single (fp32) precision
      * -   DOUBLE
        -   data and transforms are executed using double (fp64) precision


.. _onemkl_dft_enum_domain:

domain
++++++

The discrete Fourier transform supports forward transformations on input sequences of two domains, from the forward domain to the backward domain. The backward transformation operates on input sequences from the backward domain to the forward domain.  This ``domain`` value defines the forward domain and the backward domain is always implied to be complex-valued.

.. container:: section

   .. rubric:: Syntax

   .. code:: cpp
      
      enum class domain {
         REAL,
         COMPLEX
      };
   
   .. list-table::
      :header-rows: 1

      * -   Value
        -   Forward domain
        -   Backward domain
        -   Description
      * -   REAL
        -   real-valued
        -   complex-valued
        -   Forward transformation is real-to-complex, backward transform is complex-to-real.
      * -   COMPLEX
        -   complex-valued
        -   complex-valued
        -   Forward and backward transformations are complex-to-complex.


.. _onemkl_dft_enum_config_param:

config_param
++++++++++++

.. container:: section

   .. code:: cpp
      
      enum class config_param {

         FORWARD_DOMAIN,
         DIMENSION,
         LENGTHS,
         PRECISION,
         
         FORWARD_SCALE,
         BACKWARD_SCALE,
         
         NUMBER_OF_TRANSFORMS,
         
         COMPLEX_STORAGE,
         REAL_STORAGE,
         CONJUGATE_EVEN_STORAGE,
         
         PLACEMENT,

         FWD_STRIDES,
         BWD_STRIDES,
         INPUT_STRIDES, // deprecated
         OUTPUT_STRIDES, // deprecated
         
         FWD_DISTANCE,
         BWD_DISTANCE,
         
         WORKSPACE,
         ORDERING,
         TRANSPOSE,
         COMMIT_STATUS
      };

   Many of the config_param enum's will take values in :ref:`onemkl_dft_enum_config_value` or other ``std::int64_t``, ``std::vector<std::int64_t>``, or floating-point :ref:`onemkl_dft_enum_precision` values as specified in the following table.

   .. list-table::
      :header-rows: 1

      * -   Value
        -   Description
      * -   FORWARD_DOMAIN
        -   Read-only value of forward :ref:`onemkl_dft_enum_domain` set at :ref:`onemkl_dft_descriptor` construction time. 
      * -   DIMENSION
        -   Read-only value of the dimension of the transformation. Value is a positive integer of type ``std::int64_t`` set at :ref:`onemkl_dft_descriptor` construction.
      * -   LENGTHS
        -   For a one-dimensional transform, the transform length is specified by a positive integer value represented in an integer scalar (``std::int64_t``). For multi-dimensional (:math:`\geq 2`) transform, the lengths of each of the dimensions are supplied in an integer vector (``std::vector<std::int64_t>``) at :ref:`onemkl_dft_descriptor` construction time.
      * -   PRECISION
        -   Read-only value of :ref:`onemkl_dft_enum_precision` set at :ref:`onemkl_dft_descriptor` construction time. 
      * -   :ref:`FORWARD_SCALE<onemkl_dft_config_scale>`
        -   The forward transform is associated with a scale factor, :math:`\sigma`, of real floating-point type :ref:`onemkl_dft_enum_precision`, the default value is 1.0.
      * -   :ref:`BACKWARD_SCALE<onemkl_dft_config_scale>`
        -   The backward transform is associated with a scale factor, :math:`\sigma`, of real floating-point type :ref:`onemkl_dft_enum_precision`, the default value is 1.0.
      * -   :ref:`NUMBER_OF_TRANSFORMS<onemkl_dft_config_number_of_transforms>`
        -   If you need to perform a large number of identical DFTs, you can do this in a single call to a compute_forward function with the value of this equal to the actual number of the transforms. Takes a value of ``std::int64_t`` with default value of 1.
      * -   :ref:`onemkl_dft_complex_storage`
        -   Specifies the forward- and backward-domain data storage format for descriptors of ``COMPLEX`` template :ref:`onemkl_dft_enum_domain`.
      * -   :ref:`REAL_STORAGE<onemkl_dft_real_and_conjugate_even_storage>`
        -   Specifies the forward-domain data storage format for descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`.
      * -   :ref:`CONJUGATE_EVEN_STORAGE<onemkl_dft_real_and_conjugate_even_storage>`
        -   Specifies the backward-domain data storage format for descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`.
      * -   PLACEMENT
        -   Choose between in-place (value is ``config_value::INPLACE``) and out-of-place (value is ``config_value::NOT_INPLACE``) transformations. For in-place transformation, the computational functions overwrite the input data with the output results.  The default is ``config_value::INPLACE``.  When the configuration parameter is set to ``config_value::NOT_INPLACE``, the input and output data sets must have no common elements.
      * -   :ref:`FWD_STRIDES<onemkl_dft_config_data_layouts>`
        -   Defines the data layout in the forward domain. The value for a :math:`d`-dimensional transform is a :math:`(d+1)`-long vector of type ``std::vector<std::int64_t>`` containing the offset and stride(s) for the forward-domain data. See :ref:`onemkl_dft_config_data_layouts` for more details and default values.
      * -   :ref:`BWD_STRIDES<onemkl_dft_config_data_layouts>`
        -   Defines the data layout in the backward domain. The value for a :math:`d`-dimensional transform is a :math:`(d+1)`-long vector of type ``std::vector<std::int64_t>`` containing the offset and stride(s) for the backward-domain data. See :ref:`onemkl_dft_config_data_layouts` for more details and default values.
      * -   :ref:`INPUT_STRIDES<onemkl_dft_config_data_layouts>` (deprecated)
        -   Defines the input data layout. The value for a :math:`d`-dimensional transform is a :math:`(d+1)`-long vector of type ``std::vector<std::int64_t>`` containing the offset and stride(s) for the input data. See :ref:`onemkl_dft_config_data_layouts` for more details and default values
      * -   :ref:`OUTPUT_STRIDES<onemkl_dft_config_data_layouts>` (deprecated)
        -   Defines the output data layout. The value for a :math:`d`-dimensional transform is a :math:`(d+1)`-long vector of type ``std::vector<std::int64_t>`` containing the offset and stride(s) for the output data. See :ref:`onemkl_dft_config_data_layouts` for more details and default values
      * -   :ref:`FWD_DISTANCE<onemkl_dft_config_data_layouts>`
        -   If computing multiple (batched) transforms, this parameter specifies the distance (in elements) between the first data elements of consecutive data sets in the forward domain. Provided in type ``std::int64_t``, the default value is 0.
      * -   :ref:`BWD_DISTANCE<onemkl_dft_config_data_layouts>`
        -   If computing multiple (batched) transforms, this parameter specifies the distance (in elements) between the first data elements of consecutive data sets in the backward domain. Provided in type ``std::int64_t``, the default value is 0.
      * -   WORKSPACE
        -   Some FFT algorithm computation steps require a scratch space for permutations or other purposes.  To manage the use of auxiliary storage, set to ``config_value::ALLOW`` to permit the use of auxiliary storage and ``config_value::AVOID`` to avoid using auxiliary storage if possible.
      * -   ORDERING
        -   Some FFT algorithms apply an explicit permutation stage that can be time consuming.  The value of ``config_value::ORDERED`` (default) applies the data ordering for all transformations.  The value of ``config_value::BACKWARD_SCRAMBLED`` applies ordering for forward transform, but allows backward transform to have scrambled data if it gives a performance advantage. 
      * -   TRANSPOSE
        -   A boolean value to indicate providing the transposition of output results (for multi-dimensional transforms). Default value is ``false``.
      * -   COMMIT_STATUS
        -   Read-only value indicates whether the descriptor is ready for computation after a successful :ref:`onemkl_dft_descriptor_commit`.  Value of ``config_value::COMMITTED`` indicates a successful call to :ref:`onemkl_dft_descriptor_commit`.  A value of ``config_value::UNCOMMITTED`` (default) is set after descriptor constructor call and before successful call to :ref:`onemkl_dft_descriptor_commit`.

.. _onemkl_dft_enum_config_value:

config_value
++++++++++++

These are some of the non-integer/floating-point values that the :ref:`onemkl_dft_enum_config_param` configuration parameters can take on.

.. container:: section

   .. code:: cpp
      
      enum class config_value {

         // for config_param::COMMIT_STATUS
         COMMITTED,
         UNCOMMITTED,

         // for config_param::COMPLEX_STORAGE,
         //     config_param::REAL_STORAGE and 
         //     config_param::CONJUGATE_EVEN_STORAGE
         COMPLEX_COMPLEX,
         REAL_REAL,

         // for config_param::PLACEMENT
         INPLACE,
         NOT_INPLACE,

         // for config_param::ORDERING
         ORDERED,
         BACKWARD_SCRAMBLED,

         // Allow/avoid certain usages
         ALLOW,
         AVOID
      };



**Parent topic:** :ref:`onemkl_dft`

.. toctree::
   :hidden:

   config_params/scaling_factor
   config_params/number_of_transforms
   config_params/data_layouts
   config_params/storage_formats

