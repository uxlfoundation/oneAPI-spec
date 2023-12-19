.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_descriptor:

The ``descriptor`` class
========================

Objects of the ``descriptor`` class define DFT(s) to be computed.

.. rubric:: Description

Any desired (batched) DFT is to be fully determined by an object of the
``oneapi::mkl::dft::descriptor`` class, defined in the ``oneapi::mkl::dft``
namespace. The scoped enumeration types :ref:`onemkl_dft_enum_precision`,
:ref:`onemkl_dft_enum_domain`, :ref:`onemkl_dft_enum_config_param` and
:ref:`onemkl_dft_enum_config_value` defined in the same namespace (and the
corresponding ranges of values) are relevant to the definition and
configurations of objects of the ``descriptor`` class. The ``descriptor`` class
allows the user to set several (resp. query all) configuration parameters for (resp.
from) any of its instances by using their
:ref:`onemkl_dft_descriptor_set_value` (resp.
:ref:`onemkl_dft_descriptor_get_value`) member function.

Invoking the member function :ref:`onemkl_dft_descriptor_commit` of an object of
the ``descriptor`` class effectively commits that object to the desired  DFT
calculations, as configured and determined by that very object, on the specified
device encapsulated by the ``sycl::queue`` object required by that function.

The desired forward (resp. backward) DFT calculations may then be computed by
passing such a committed ``descriptor`` object to the
:ref:`onemkl_dft_compute_forward` (resp. :ref:`onemkl_dft_compute_backward`)
function (defined in the ``oneapi::mkl::dft`` namespace as well), along with the
relevant data containers (``sycl::buffer`` object(s) or pointer(s) to a
device-accessible USM allocations) for the  desired DFT(s). This function makes
the ``descriptor`` object enqueue the operations relevant for the desired
calculations to the ``sycl::queue`` object it was given when committing it.

.. note::
   The :ref:`onemkl_dft_compute_forward` and :ref:`onemkl_dft_compute_backward`
   functions may need to be able to access the internals of the ``descriptor``
   object to compute the desired transform(s), this could be done for instance,
   by labeling them as friend functions of the ``descriptor`` class.

.. rubric:: Syntax

The ``descriptor`` class is defined in the ``oneapi::mkl::dft`` namespace.

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      class descriptor {
       public:
          
          // Constructor for 1-dimensional DFT
          descriptor(std::int64_t length); // d = 1;
          
          // Constructor for d-dimensional DFT
          descriptor(std::vector<std::int64_t> lengths); // d = lengths.size();

          descriptor(const descriptor&);

          descriptor(descriptor&&);

          descriptor& operator=(const descriptor&);

          descriptor& operator=(descriptor&&);

          ~descriptor();
      
      
          void set_value(oneapi::mkl::dft::config_param param, ...);
          
          void get_value(oneapi::mkl::dft::config_param param, ...);
         
          void set_workspace(sycl::buffer<scalar_type, 1> &workspaceBuf);
          void set_workspace(scalar_type* workspaceUSM);
      
          void commit(sycl::queue &queue);
      
       };


   }
	

.. _onemkl_dft_descriptor_template_parameters:

.. rubric:: Descriptor class template parameters

:ref:`onemkl_dft_enum_precision` prec
  Specifies the floating-point precision in which the user-provided data is to
  be provided, the transform is to be carried out and the results are to be
  returned. The possible specialization values are
  ``oneapi::mkl::dft::precision::SINGLE`` and
  ``oneapi::mkl::dft::precision::DOUBLE``. Objects of the ``descriptor`` class
  specialized with :ref:`onemkl_dft_enum_precision` template parameter ``prec``
  as value ``oneapi::mkl::dft::precision::SINGLE`` (resp.
  ``oneapi::mkl::dft::precision::DOUBLE``) are referred to as "single-precision
  descriptors" (resp. "double-precision descriptors").

:ref:`onemkl_dft_enum_domain` dom
  Specifies the forward domain of the transform. The possible specialization
  values are ``oneapi::mkl::dft::domain::COMPLEX`` and
  ``oneapi::mkl::dft::domain::REAL``. Objects of the ``descriptor`` class
  specialized with :ref:`onemkl_dft_enum_domain` template parameter ``dom`` as
  value ``oneapi::mkl::dft::precision::COMPLEX`` (resp.
  ``oneapi::mkl::dft::precision::REAL``) are referred to as "complex
  descriptors" (resp. "real descriptors").

.. _onemkl_dft_descriptor_member_table:

.. rubric:: Descriptor class member functions

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * -     Routines
     -     Description
   * -     :ref:`constructors<onemkl_dft_descriptor_constructor>`
     -     Creates and default-initializes a ``descriptor`` object for a
           :math:`d`-dimensional DFT of user-defined length(s)
           :math:`\lbrace n_1, \ldots, n_d\rbrace`.
   * -     :ref:`assignment operators<onemkl_dft_descriptor_assignment_operator>`
     -     Performs a deep copy of or moves the argument.
   * -     :ref:`onemkl_dft_descriptor_set_value`
     -     Sets a configuration value for a specific configuration parameter.
   * -     :ref:`onemkl_dft_descriptor_get_value`
     -     Queries the configuration value associated with a particular
           configuration parameter.
   * -     :ref:`onemkl_dft_descriptor_set_workspace`
     -     Sets the external workspace to use when ``config_param::WORKSPACE_PLACEMENT`` is set to ``config_value::WORKSPACE_EXTERNAL``.
   * -     :ref:`onemkl_dft_descriptor_commit`
     -     Commits the ``descriptor`` object to enqueue the operations relevant
           to the (batched) DFT(s) it determines to a given, user-provided
           ``sycl::queue`` object; completes all initialization work relevant to
           and required by the chosen, device-compliant implementation for the
           particular DFT, as defined by the ``descriptor`` object.

.. _onemkl_dft_descriptor_constructor:

Descriptor class constructors
++++++++++++++++++++++++++++++

The constructors for the ``descriptor`` object instantiate
it with all the relevant default configuration settings (which may depend on the
specialization values used for the :ref:`onemkl_dft_enum_precision` template
parameter ``prec`` and for the :ref:`onemkl_dft_enum_domain` template parameter
``dom``). The constructors do not perform any significant initialization work as
changes in the object's configuration(s) may be operated thereafter (via its
:ref:`onemkl_dft_descriptor_set_value` member function) and modify significantly
the nature of that work.

The copy constructor performs a deep copy of ``descriptor`` objects.

.. rubric:: Syntax (one-dimensional transform)

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>(std::int64_t length);

   }


.. rubric:: Syntax (:math:`d`-dimensional transform with :math:`d > 0`)

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>(std::vector<std::int64_t> lengths);

   }

.. rubric:: Copy constructor

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>(const descriptor<prec,dom>& other);

   }

.. rubric:: Move constructor

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>(descriptor<prec,dom>&& other);

   }


.. container:: section

   .. rubric:: Input Parameters

   length
      Length :math:`n_1 > 0` of the data sequence(s) for one-dimensional
      transform(s).

   lengths
      Vector of :math:`d > 0` lengths :math:`\lbrace n_1, \ldots, n_d\rbrace`
      of the data sequence(s) for :math:`d`-dimensional transform(s). The values
      are to be provided in that order and such that
      :math:`n_j > 0,\ \forall j \in \lbrace 1, \ldots, d \rbrace`.

   other
      Another ``descriptor`` object of the same type to copy or move.

.. container:: section

   .. rubric:: Throws

   The ``descriptor::descriptor()`` constructors shall throw the following
   exception if the associated condition is detected. An implementation may
   throw additional implementation-specific exception(s) in case of error
   conditions not covered here:

   :ref:`oneapi::mkl::host_bad_alloc()<onemkl_exception_host_bad_alloc>`
      If any memory allocations on host have failed, for instance due to
      insufficient memory.

   :ref:`oneapi::mkl::unimplemented()<onemkl_exception_unimplemented>`
      If the dimension :math:`d`, *i.e.*, the size of vector ``lengths``, is
      larger than what is supported by the library implementation.
   

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. _onemkl_dft_descriptor_assignment_operator:

Descriptor class assignment operators
+++++++++++++++++++++++++++++++++++++

The copy assignment operator results in a deep copy.

.. rubric:: Copy assignment

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>& descriptor<prec,dom>::operator=(const descriptor<prec,dom>& other);

   }

.. rubric:: Move assignment

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      descriptor<prec,dom>& descriptor<prec,dom>::operator=(descriptor<prec,dom>&& other);

   }


.. container:: section

   .. rubric:: Input Parameters

   other
      The ``descriptor`` object to copy or move from.

.. container:: section

   .. rubric:: Throws

   The assignment operators shall throw the following exceptions if the
   associated condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here:

   :ref:`oneapi::mkl::host_bad_alloc()<onemkl_exception_host_bad_alloc>`
      If any memory allocations on host have failed, for instance due to
      insufficient memory.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_set_value:

set_value
+++++++++

The ``set_value`` member function of the ``descriptor`` class sets a
configuration value corresponding to a (read-write) configuration parameter for
the DFT(s) that a ``descriptor`` object defines. This function is to be used as
many times as required for all the necessary configuration parameters to be set
prior to committing the ``descriptor`` object (by calling its member function
:ref:`onemkl_dft_descriptor_commit`).

This function requires and expects exactly **two** arguments: it sets the
configuration value (second argument) corresponding to the configuration
parameter (first argument) ``param`` of type ``oneapi::mkl::dft::config_param``.
The type of the configuration value (second argument) to be set depends on the
value of ``param``: it can be ``oneapi::mkl::dft::config_value`` or a native
type like ``std::int64_t`` or ``float`` (more details available
:ref:`here<onemkl_dft_enum_config_param>`).

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      void descriptor<prec,dom>::set_value(oneapi::mkl::dft::config_param param, ...);

   }

.. container:: section

   .. rubric:: Input Parameters

   param
      One of the possible values of type :ref:`onemkl_dft_enum_config_param`
      representing the (writable) configuration parameter to be set.

   ...
      An element of the appropriate type for the configuration value
      corresponding to the targeted configuration
      parameter ``param`` (appropriate type defined
      :ref:`here<onemkl_dft_enum_config_param>`).

.. container:: section

   .. rubric:: Throws

   The ``descriptor::set_value()`` routine shall throw the following exceptions
   if the associated condition is detected. An implementation may throw
   additional implementation-specific exception(s) in case of error conditions
   not covered here:

   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the provided :ref:`onemkl_dft_enum_config_param` and/or configuration
      value is not valid.

   :ref:`oneapi::mkl::unimplemented()<onemkl_exception_unimplemented>`
      If the provided :ref:`onemkl_dft_enum_config_param` and configuration
      value are valid, but not supported by the library implementation.
 
   
**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. _onemkl_dft_descriptor_get_value:

get_value
+++++++++

The ``get_value`` member function of the ``descriptor`` class queries the
configuration value corresponding to any configuration parameter for the DFT
that a ``descriptor`` object defines.

This function requires and expects exactly **two** arguments: it returns the
configuration value (into the element pointed by the second argument)
corresponding to the queried configuration parameter (first argument) ``param``
of type ``oneapi::mkl::dft::config_param``. The type of the second argument
depends on the value of ``param``: it is  a pointer to a writable element of
type ``oneapi::mkl::dft::domain``, ``oneapi::mkl::dft::precision``,
``oneapi::mkl::dft::config_value`` or a native type like ``std::int64_t`` or
``float`` (more details available :ref:`here<onemkl_dft_enum_config_param>`).

.. note::
   The value returned by ``get_value`` corresponds to the latest value set for
   the corresponding configuration parameter being  queried or the
   corresponding default value if that parameter was not set or if it is not
   writable, even if that value was set after the descriptor was committed.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      void descriptor<prec,dom>::get_value(oneapi::mkl::dft::config_param param, ...);

   }

.. container:: section

   .. rubric:: Input Parameters

   param
      One of the possible values of type :ref:`onemkl_dft_enum_config_param`
      representing the configuration parameter being queried.

   ...
      A pointer to a writable element of the appropriate type for the
      configuration value corresponding to the queried configuration
      parameter ``param`` (appropriate type of pointed element defined
      :ref:`here<onemkl_dft_enum_config_param>`).

.. container:: section

   .. rubric:: Throws

   The ``descriptor::get_value()`` routine shall throw the following exceptions
   if the associated condition is detected. An implementation may throw
   additional implementation-specific exception(s) in case of error conditions
   not covered here:
   
   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the requested :ref:`onemkl_dft_enum_config_param` is not valid.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_set_workspace:

set_workspace
+++++++++++++

Sets the workspace for when ``config_param::WORKSPACE_PLACEMENT`` is set to ``config_value::WORKSPACE_EXTERNAL``.

.. rubric:: Description

This function sets the workspace to use when computing DFTs for when an
external workspace is set. 
This function may only be called after the descriptor has been committed.
The size of the provided workspace must be equal to or larger than the required 
workspace size obtained by calling ``descriptor<prec, dom>::get_value(config_param::WORKSPACE_EXTERNAL_BYTES, &workspaceBytes)``.

A descriptor where ``config_value::WORKSPACE_EXTERNAL`` is specified for 
``config_param::WORKSPACE_PLACEMENT`` is not a valid descriptor for compute 
calls until this function has been successfully called.

The type of workspace must match the compute calls for which it is used.
That is, if the workspace is provided as a ``sycl::buffer``, the compute
calls must also use ``sycl::buffer`` for their arguments. Likewise, a USM
allocated workspace must only be used with USM compute calls.
Failing to do this will result in an invalid descriptor for compute calls.

If the workspace is a USM allocation, the user must not use it for other purposes
in parallel whilst the DFT ``compute_forward`` or ``compute_backward`` are in progress.

This function can be called on committed descriptors where the workspace placement
is not ``config_value::WORKSPACE_EXTERNAL``. The provided workspace may or may not
be used in compute calls. However, the aforementioned restrictions will still apply.

.. rubric:: Syntax (buffer workspace)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      void descriptor<prec,dom>::set_workspace(sycl::buffer<scalar_type, 1> &workspaceBuf);
   }

.. rubric:: Syntax (USM workspace)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      void descriptor<prec,dom>::set_workspace(scalar_type* workspaceUSM);

   }

.. container:: section

   .. rubric:: Input Parameters

   workspaceBuf
      A workspace buffer where ``scalar_type`` is the floating-point type according to ``prec``. This buffer must be sufficiently large or an exception will be thrown. A sub-buffer cannot be used.

   workspaceUSM
      A workspace USM allocation where ``scalar_type`` is the floating-point type according to ``prec``. This allocation must be accessible on the device on which the descriptor is committed. It is assumed that this USM allocation is sufficiently large. The pointer is expected to be aligned to ``scalar_type``.

.. container:: section

   .. rubric:: Throws

   The ``descriptor::set_workspace()`` routine shall throw the following exceptions if the associated condition is detected. An implementation may throw additional implementation-specific exception(s) in case of error conditions not covered here:
   
   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the provided buffer ``workspaceBuf`` is not sufficiently large or is a sub-buffer, or if the provided USM allocation ``workspaceUSM`` is ``nullptr`` when an external workspace of size greater than zero is required.

   :ref:`oneapi::mkl::uninitialized()<onemkl_exception_uninitialized>`
      If ``set_workspace`` is called before the descriptor is committed.


**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_commit:

commit
++++++

The ``commit`` member function commits a ``descriptor`` object to the DFT
calculations it defines consistently with its configuration settings, by
completing all the initialization work (*e.g.*, algorithm selection, algorithm
tuning, choice of factorization, memory allocations, calculation of twiddle
factors, etc.) required by the chosen implementation for the desired DFT(s) on
the targeted device. Objects of the ``descriptor`` class **must** be committed
prior to using them in any call to :ref:`onemkl_dft_compute_forward` or
:ref:`onemkl_dft_compute_backward` (which trigger actual DFT calculations).

As specified :ref:`above<onemkl_dft_descriptor_set_value>`, all required
configuration parameters must be set before this function is called. Any change
in configuration operated on a ``descriptor`` object via a call to its
:ref:`onemkl_dft_descriptor_set_value` member function *after* it was committed
results in an undefined state not suitable for computation until this ``commit`` member
function is called again.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <oneapi::mkl::dft::precision prec, oneapi::mkl::dft::domain dom>
      void descriptor<prec,dom>::commit(sycl::queue& queue);
   }

.. container:: section

   .. rubric:: Input Parameters

   queue 
      Valid ``sycl::queue`` object to which the operations relevant to the
      desired DFT(s) are to be enqueued.

.. container:: section

   .. rubric:: Throws

   The ``descriptor::commit()`` routine shall throw the following exceptions if
   the associated condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here (if the ``descriptor`` object's configuration was found to be
   inconsistent, for instance):
   
   :ref:`oneapi::mkl::invalid_argument()<onemkl_exception_invalid_argument>`
      If the queue is found to be invalid in any way.

   :ref:`oneapi::mkl::host_bad_alloc()<onemkl_exception_host_bad_alloc>`
      If any host side only memory allocations fail, for instance due to lack of
      memory.

   :ref:`oneapi::mkl::device_bad_alloc()<onemkl_exception_device_bad_alloc>`
      If any device or shared memory allocation fail.
 
**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

**Parent topic:** :ref:`onemkl_dft`
