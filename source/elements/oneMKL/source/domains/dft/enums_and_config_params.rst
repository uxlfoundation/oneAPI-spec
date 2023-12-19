.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_enums:

DFT-related scoped enumeration types
------------------------------------

The following scoped enumeration types, defined in the ``oneapi::mkl::dft``
namespace, are used for constructing and configuring objects of the
:ref:`descriptor<onemkl_dft_descriptor>` class consistently with the DFT(s) they
are meant to define.

.. list-table::
      :header-rows: 1
      :widths: 24 73

      * -   Scoped enumeration type
        -   Description
      * -   :ref:`onemkl_dft_enum_precision`
        -   Represents the precision of the floating-point data format and of
            the floating-point arithmetic to be used for the desired DFT
            calculations. A template parameter ``prec`` of this type is used for
            the :ref:`descriptor<onemkl_dft_descriptor>` class.
      * -   :ref:`onemkl_dft_enum_domain`
        -   Represents the type of forward domain for the desired DFT(s). A
            template parameter ``dom`` of this type is used for the
            :ref:`descriptor<onemkl_dft_descriptor>` class.
      * -   :ref:`onemkl_dft_enum_config_param`
        -   Represents configuration parameters for objects of the
            :ref:`descriptor<onemkl_dft_descriptor>` class. The configuration
            values associated with the configuration parameters
            can be retrieved (resp. set, for writable parameters) via the object's
            :ref:`onemkl_dft_descriptor_get_value` (resp.
            :ref:`onemkl_dft_descriptor_set_value`) member function.
      * -   :ref:`onemkl_dft_enum_config_value`
        -   Represents the possible configuration values for some of the
            :ref:`configuration parameters<onemkl_dft_enum_config_param>` that
            may take only a few determined, non-numeric values.

.. _onemkl_dft_enum_precision:

precision
+++++++++

This scoped enumeration type represents the precision of the floating-point
format to be used for the desired DFT(s). The same precision is to be used for
the user-provided data, the computation being carried out by oneMKL and the
results delivered by oneMKL.

.. container:: section
 
   .. rubric:: Syntax

   .. code:: cpp
      
      enum class precision {
         SINGLE,
         DOUBLE
      };

   .. list-table::
      :header-rows: 1
      :widths: 24 73

      * -   Value
        -   Description
      * -   SINGLE
        -   Single-precision floating-point format (FP32) is used for data
            representation and arithmetic operations.
      * -   DOUBLE
        -   Double-precision floating-point format (FP64) is used for data
            representation and arithmetic operations.

.. _onemkl_dft_enum_domain:

domain
++++++

This scoped enumeration type represents the type of forward domain for the
desired DFTs (as explained in the :ref:`introduction<onemkl_dft_definitions>`,
the backward domain type is always complex).

.. container:: section

   .. rubric:: Syntax

   .. code:: cpp
      
      enum class domain {
         REAL,
         COMPLEX
      };
   
   .. list-table::
      :header-rows: 1
      :widths: 24 73

      * -   Value
        -   Description
      * -   REAL
        -   The forward domain is the set of real :math:`d`-dimensional periodic
            sequences.
      * -   COMPLEX
        -   The forward domain is the set of complex :math:`d`-dimensional
            periodic sequences.


.. _onemkl_dft_enum_config_param:

config_param
++++++++++++

This scoped enumeration type represents configuration parameters for objects of
the :ref:`descriptor<onemkl_dft_descriptor>` class.

.. container:: section

   .. code:: cpp
      
      enum class config_param {
         // read-only parameters:
         FORWARD_DOMAIN,
         DIMENSION,
         LENGTHS,
         PRECISION,
         COMMIT_STATUS,
         // writable parameters:
         FORWARD_SCALE,
         BACKWARD_SCALE,
         
         NUMBER_OF_TRANSFORMS,
         
         COMPLEX_STORAGE,
         
         PLACEMENT,

         FWD_STRIDES,
         BWD_STRIDES,
         INPUT_STRIDES, // deprecated
         OUTPUT_STRIDES, // deprecated
         
         FWD_DISTANCE,
         BWD_DISTANCE,

         WORKSPACE_PLACEMENT,
         WORKSPACE_EXTERNAL_BYTES
      };

   Configuration parameters represented by ``config_param::FORWARD_DOMAIN`` and
   ``config_param::PRECISION`` are associated with configuration values of type
   :ref:`domain<onemkl_dft_enum_domain>` and
   :ref:`precision<onemkl_dft_enum_precision>` respectively. Other
   configuration parameters are associated with configuration values of type
   :ref:`onemkl_dft_enum_config_value` or of a native type like
   ``std::int64_t``, ``std::vector<std::int64_t>``, ``float`` or ``double``.
   This is further specified in the following table.

   .. list-table::
      :header-rows: 1
      :widths: 10 50 40

      * -   | Value of ``config_param``
            |
        -   | Represented configuration parameter(s)
            |
        -   | Type of associated configuration value
            | [default value]
      * -   FORWARD_DOMAIN
        -   Type of forward domain, set at construction time as the
            specialization value of :ref:`onemkl_dft_enum_domain` template
            parameter ``dom``. This parameter is read-only.
        -   | :ref:`onemkl_dft_enum_domain`
            | [``dom``]
      * -   DIMENSION
        -   Value of the dimension :math:`d` of the desired DFTs, set at
            construction time. This parameter is read-only.
        -   | ``std::int64_t``
            | [:math:`d`]
      * -   LENGTHS
        -   Values :math:`\lbrace n_1, \ldots, n_d\rbrace` of the periods (or
            "lengths") of the desired DFT, set at construction time. This
            parameter is read-only.
        -   | ``std::vector<std::int64_t>`` of size :math:`d` or, if :math:`d = 1`, ``std::int64_t``
            | [``std::vector<int64_t>({n_1,...,n_d})``]
      * -   PRECISION
        -   Floating-point precision to be considered by and used for the DFT
            calculation(s), set at construction time as the specialization value
            of :ref:`onemkl_dft_enum_precision` template parameter ``prec``.
            This parameter is read-only.
        -   | :ref:`onemkl_dft_enum_precision`
            | [``prec``]
      * -   COMMIT_STATUS
        -   Status flag indicating whether the object is ready for computations
            after a successful call to :ref:`onemkl_dft_descriptor_commit`. This
            parameter is read-only.
        -   | :ref:`onemkl_dft_enum_config_value` (possible values are self-explanatory ``config_value::COMMITTED`` or ``config_value::UNCOMMITTED``).
            | [``config_value::UNCOMMITTED``]
      * -   FORWARD_SCALE
        -   Value of :math:`\sigma` for the forward DFT.
        -   | ``float`` (resp. ``double``) for single-precision (resp. double-precision) descriptors
            | [1.0]
      * -   BACKWARD_SCALE
        -   Value of :math:`\sigma` for the backward DFT.
        -   | ``float`` (resp. ``double``) for single-precision (resp. double-precision) descriptors
            | [1.0]
      * -   :ref:`NUMBER_OF_TRANSFORMS<onemkl_dft_num_dft_data_layouts_batched_dfts>`
        -   Value of :math:`M`. This is relevant (and *must* be set) for
            batched DFT(s), *i.e.*, if :math:`M > 1`.
        -   | ``std::int64_t``
            | [1]
      * -   :ref:`COMPLEX_STORAGE<onemkl_dft_complex_storage>`
        -   Data storage type used (relevant for complex descriptors only).
        -   | :ref:`onemkl_dft_enum_config_value` (possible values are ``config_value::COMPLEX_COMPLEX`` or ``config_value::REAL_REAL``)
            | [``config_value::COMPLEX_COMPLEX``]
      * -   PLACEMENT
        -   | Parameter specifying whether the DFT calculations should be done in-place (results overwriting the input data) or out-of-place (input and output in separate data containers having no common elements).
            | Note: even for out-of-place configurations, some implementations may not preserve the original input data.
        -   | :ref:`onemkl_dft_enum_config_value` (possible values are self-explanatory ``config_value::INPLACE`` or ``config_value::NOT_INPLACE``)
            | [``config_value::INPLACE``]
      * -   :ref:`FWD_STRIDES<onemkl_dft_fwd_bwd_strides>`
        -   Offset and strides defining the layout within a given data sequence
            in the forward domain.
        -   | ``std::vector<std::int64_t>`` of size :math:`(d+1)`
            | [defined :ref:`here<onemkl_dft_fwd_bwd_strides>`]
      * -   :ref:`BWD_STRIDES<onemkl_dft_fwd_bwd_strides>`
        -   Offset and strides defining the layout within a given data sequence
            in the backward domain.
        -   | ``std::vector<std::int64_t>`` of size :math:`(d+1)`
            | [defined :ref:`here<onemkl_dft_fwd_bwd_strides>`]
      * -   :ref:`INPUT_STRIDES<onemkl_dft_io_strides_deprecated>` (deprecated)
        -   Offset and strides defining the layout within a given *input* data
            sequence.
        -   | ``std::vector<std::int64_t>`` of size :math:`(d+1)`
            | [``std::vector<std::int64_t>(d+1, 0)``]
      * -   :ref:`OUTPUT_STRIDES<onemkl_dft_io_strides_deprecated>` (deprecated)
        -   Offset and strides defining the layout within a given *output* data
            sequence.
        -   | ``std::vector<std::int64_t>`` of size :math:`(d+1)`
            | [``std::vector<std::int64_t>(d+1, 0)``]
      * -   :ref:`FWD_DISTANCE<onemkl_dft_num_dft_data_layouts_batched_dfts>`
        -   Distance in number of elements of
            :ref:`implicitly-assumed data type<onemkl_dft_config_data_implicitly_assumed_elementary_data_type>`
            between forward-domain entries
            :math:`\left(\cdot\right)^{m}_{k_1, k_2, \ldots, k_d}` and
            :math:`\left(\cdot\right)^{m + 1}_{k_1, k_2, \ldots, k_d}` for all
            :math:`0\leq m < M - 1` and
            :math:`\left(k_1, k_2, \ldots, k_d\right)` in
            :ref:`valid range<onemkl_dft_elementary_range_of_indices>`. This is
            relevant (and *must* be set) for batched DFT(s), *i.e.*, if
            :math:`M > 1`.
        -   | ``std::int64_t``
            | [0]
      * -   :ref:`BWD_DISTANCE<onemkl_dft_num_dft_data_layouts_batched_dfts>`
        -   Distance in number of elements of
            :ref:`implicitly-assumed data type<onemkl_dft_config_data_implicitly_assumed_elementary_data_type>`
            between backward-domain entries
            :math:`\left(\cdot\right)^{m}_{k_1, k_2, \ldots, k_d}` and
            :math:`\left(\cdot\right)^{m + 1}_{k_1, k_2, \ldots, k_d}` for all
            :math:`0\leq m < M - 1` and
            :math:`\left(k_1, k_2, \ldots, k_d\right)` in
            :ref:`valid range<onemkl_dft_elementary_range_of_indices>`. This is
            relevant (and *must* be set) for batched DFT(s), *i.e.*, if
            :math:`M > 1`.
        -   | ``std::int64_t``
            | [0]
      * -   :ref:`WORKSPACE_PLACEMENT<onemkl_dft_config_workspace_placement>`
        -   Some FFT algorithm computation steps require a scratch space for permutations or other purposes. 
            This parameter controls whether this scratch space is automatically allocated or provided by the user.
        -   | :ref:`onemkl_dft_enum_config_value` (possible values are ``config_value::WORKSPACE_AUTOMATIC`` or ``config_value::WORKSPACE_EXTERNAL``).
            | [``config_value::WORKSPACE_AUTOMATIC``]
      * -   WORKSPACE_EXTERNAL_BYTES
        -   The required minimum external workspace size for use by :ref:`set_workspace<onemkl_dft_descriptor_set_workspace>`.
            A read-only value, on committed descriptors only.
        -   | ``std::int64_t``


.. _onemkl_dft_enum_config_value:

config_value
++++++++++++

This scoped enumeration type represents possible non-numeric configuration
values associated with some
:ref:`configuration parameters<onemkl_dft_enum_config_param>`.

.. container:: section

   .. code:: cpp
      
      enum class config_value {
         // for config_param::COMMIT_STATUS
         COMMITTED,
         UNCOMMITTED,

         // for config_param::COMPLEX_STORAGE,
         COMPLEX_COMPLEX,
         REAL_REAL,

         // for config_param::PLACEMENT
         INPLACE,
         NOT_INPLACE
         
         // For config_param::WORKSPACE_PLACEMENT
         WORKSPACE_AUTOMATIC,
         WORKSPACE_EXTERNAL,
      };

**Parent topic:** :ref:`onemkl_dft`

.. toctree::
   :hidden:

   config_params/data_layouts
   config_params/storage_formats
   config_params/workspace_placement
