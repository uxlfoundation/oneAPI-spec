.. _onemkl_dft_descriptor:

descriptor
==========

The descriptor class defines a discrete Fourier transform problem to be computed.

.. rubric:: Description

The discrete Fourier transform problem is defined through the use of the ``oneapi::mkl::dft::descriptor`` class which lives in the ``oneapi::mkl::dft::`` namespace. The enum and config_param values associated with the descriptor class can be found in :ref:`onemkl_dft_enums` including :ref:`onemkl_dft_enum_precision`, :ref:`onemkl_dft_enum_domain` and :ref:`onemkl_dft_enum_config_param`. The descriptor class allows to set several configuration parameters using set_value (and query using get_value) and then upon call to :ref:`onemkl_dft_descriptor_commit` with a ``sycl::queue``, is ready to be used in computations on the specified device.  

This class is then passed to a :ref:`onemkl_dft_compute_forward` or :ref:`onemkl_dft_compute_backward` function along with the data for the actual transformation to be applied. 

.. note::
   The :ref:`onemkl_dft_compute_forward` and :ref:`onemkl_dft_compute_backward` functions may need to be able to access the internals of the descriptor to apply the transform, this could be done for instance, by labeling them as friend functions of the descriptor class.


descriptor class
----------------

.. rubric:: Syntax

The descriptor class lives in the ``oneapi::mkl::dft`` namespace.

.. code-block:: cpp
	
	template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
	class descriptor {
	 public:
	    
            // Syntax for 1-dimensional DFT
            descriptor(std::int64_t length);
	    
            // Syntax for N-dimensional DFT
            descriptor(std::vector<std::int64_t> dimensions);
	    
            ~descriptor();
	
	
	    void set_value(config_param param, ...);
	    
            void get_value(config_param param, ...);
	
	    void commit(sycl::queue &queue);

	 };
	


.. cpp:class:: template<oneapi::mkl::dft::precision prec,oneapi::mkl::dft::domain dom>\
               oneapi::mkl::dft::descriptor


.. container:: section

   .. rubric:: Template parameters

   :ref:`onemkl_dft_enum_precision` prec
      Specifies the floating-point precision in which the transform is to be carried out.

   :ref:`onemkl_dft_enum_domain` dom
      Specifies the forward domain for the transformations.

.. container:: section

   .. _onemkl_dft_descriptor_member_table:

   .. rubric:: member functions

   .. list-table:: 
       :header-rows: 1

       * -     Routines
         -     Description   
       * -     :ref:`constructors<onemkl_dft_descriptor_constructor>`
         -     Initialize descriptor for 1-dimensional or N-dimensional transformations
       * -     :ref:`onemkl_dft_descriptor_set_value`
         -     Sets one particular configuration parameter with the specified configuration value.
       * -     :ref:`onemkl_dft_descriptor_get_value`
         -     Gets the configuration value of one particular configuration parameter.
       * -     :ref:`onemkl_dft_descriptor_commit`
         -     Performs all initialization for the actual FFT computation.


.. container:: section

   .. _onemkl_dft_descriptor_constructor:

   .. rubric:: Constructors

   The constructors for the discrete Fourier transform ``descriptor`` class with default 
   configuration settings for a given precision, forward :ref:`onemkl_dft_enum_domain` type 
   and dimension of the transform.

   The constructors allocate memory for the descriptor data
   structure and instantiate it with all the default
   configuration settings for the precision, (forward) :ref:`onemkl_dft_enum_domain`, and
   dimensions of the transform. The constructors do not perform any
   significant computational work, such as computation of twiddle
   factors. The function :ref:`onemkl_dft_descriptor_commit` does this work 
   after the function :ref:`onemkl_dft_descriptor_set_value` has set values 
   of all necessary parameters.

   .. rubric:: Syntax (one-dimensional transform)

   .. cpp:function:: template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom> \
            oneapi::mkl::dft::descriptor<prec,dom>(std::int64_t length)

   .. rubric:: Syntax (multi-dimensional transform)

   .. cpp:function:: template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom> \
            oneapi::mkl::dft::descriptor<prec,dom>(std::vector<std::int64_t> dimensions)

   .. container:: section

      .. rubric:: Input Parameters

      length
         dimension of data for 1-D transform

      dimensions
         vector of N dimensions of data for N-D transform


**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. rubric:: Methods in descriptor class


.. container:: section

   .. _onemkl_dft_descriptor_set_value:

   .. rubric:: set_value

   Sets DFT configuration values before :ref:`onemkl_dft_descriptor_commit`.


   .. 

   .. rubric:: Description

   This function sets one particular configuration parameter with
   the specified configuration value. Each configuration parameter
   is a named constant, and the configuration value must have the
   corresponding type, which can be a named constant or a native
   type. For available configuration parameters and the
   corresponding configuration values, see :ref:`onemkl_dft_enum_config_param`.
   All calls to ``set_param`` must be done before :ref:`onemkl_dft_descriptor_commit`.

   .. rubric:: Syntax

   .. cpp:function:: void descriptor::set_value(config_param param, ...)

   .. container:: section

      .. rubric:: Input Parameters

      param
         The enum value of :ref:`onemkl_dft_enum_config_param` to be set.

      ...
         The corresponding value or container corresponding to the specific parameter. Defined in :ref:`onemkl_dft_enum_config_param`.


**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. container:: section

   .. _onemkl_dft_descriptor_get_value:

   .. rubric:: get_value

   Retrieves current DFT configuration values.

   .. rubric:: Description

   This function gets one particular configuration parameter with
   the specified configuration value. Each configuration parameter
   is a named constant, and the configuration value must have the
   corresponding type, which can be a named constant or a native
   type. For available configuration parameters and the
   corresponding configuration values, see :ref:`onemkl_dft_enum_config_param`.

   .. rubric:: Syntax

   .. cpp:function::  void descriptor::get_value(config_param param, ...)

   .. container:: section

      .. rubric:: Input Parameters

      param
         The enum value of :ref:`onemkl_dft_enum_config_param` to be retrieved.

      ...
         The corresponding value or container corresponding to the specific parameter. Defined in :ref:`onemkl_dft_enum_config_param`.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. container:: section

   .. _onemkl_dft_descriptor_commit:

   .. rubric:: commit

   Finalizes DFT descriptor after all configuration parameters have been set.

   .. rubric:: Description

   This function completes initialization of a previously created
   descriptor, which is required before the descriptor can be used
   for FFT computations. Typically, committing the
   descriptor performs all initialization that is required for the
   actual FFT computation on the device specified through input queue. 
   The initialization performed by the function may involve exploring different
   factorizations of the input length to find the optimal
   computation method.

   All calls to the :ref:`onemkl_dft_descriptor_set_value` function to change configuration
   parameters of a descriptor need to happen after the constructor call for 
   the :ref:`onemkl_dft_descriptor` class and before a call to :ref:`onemkl_dft_descriptor_commit`.
   Typically, a commit function call is immediately followed by a computation 
   function call (see :ref:`onemkl_dft_compute_forward` or :ref:`onemkl_dft_compute_backward`)


   .. rubric:: Syntax

   .. cpp:function::  void descriptor::commit(sycl::queue& queue)

   .. container:: section

      .. rubric:: Input Parameters

      queue 
         Valid DPC++ queue specifying the device and context on which the transformation will be executed.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`




**Parent topic:** :ref:`onemkl_dft`


   
