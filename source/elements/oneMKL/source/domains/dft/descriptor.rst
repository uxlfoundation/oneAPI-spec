.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_descriptor:

The ``descriptor`` class template
=================================

Instances of any ``oneapi::mkl::dft::descriptor`` class define DFT(s) to be
computed. The usage of prepended namespace specifiers ``oneapi::mkl::dft`` is
omitted below for conciseness.

Description
+++++++++++

Any desired DFT is fully defined by an instance of a specialization of the
``descriptor`` class template, declared in the ``oneapi::mkl::dft`` namespace.
The :ref:`scoped enumeration types<onemkl_dft_enums>` ``precision``, ``domain``,
``config_param`` and ``config_value`` defined in the same namespace (and the
corresponding ranges of values) are relevant to the definition and
configurations of such objects. Users can set several (resp. query all)
configuration parameters for (resp. from) any ``descriptor`` object by using
its ``set_value`` (resp. ``get_value``) member function.

Invoking the ``commit`` member function of a ``descriptor`` object effectively
commits it to the desired DFT calculations (as it defines it) on the specific
device encapsulated by the ``sycl::queue`` object required by that function.

The desired forward (resp. backward) DFT calculations may then be computed by
passing such a committed ``descriptor`` object to a ``compute_forward`` (resp.
``compute_backward``) function (defined in the ``oneapi::mkl::dft`` namespace as
well), along with the relevant data containers (``sycl::buffer`` object(s) or
pointer(s) to a device-accessible USM allocations) for the  desired DFT(s). This
function makes the ``descriptor`` object enqueue the operations relevant for the
desired calculations to the ``sycl::queue`` object it was given when committing it.

.. note::
   The ``compute_forward`` and ``compute_backward`` functions may need to be
   able to access the internals of the ``descriptor`` object to compute the
   desired transform(s), this could be done for instance, by labeling them as
   friend functions of the ``descriptor`` class template.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      class descriptor {
       private:
          using real_scalar_t = std::conditional_t<prec == precision::DOUBLE, double, float>;

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
      
      
          void set_value(config_param param, ...);
          
          void get_value(config_param param, ...);
         
          void set_workspace(sycl::buffer<real_scalar_t, 1> &workspaceBuf);
          void set_workspace(real_scalar_t* workspaceUSM);
      
          void commit(sycl::queue &queue);
      
       };
   }

.. _onemkl_dft_descriptor_template_parameters:

.. rubric:: Template parameters

``precision prec``
  Specifies the floating-point format of the user-provided data, the results,
  and the precision of the floating-point operations to be enqueued. The
  possible specialization values are ``precision::SINGLE`` and
  ``precision::DOUBLE``, corresponding to single-precision (FP32) and
  double-precision (FP64) floating-point formats, respectively . Objects of a
  ``descriptor`` class specialized with ``precision::SINGLE`` (resp.
  ``precision::DOUBLE``) as ``prec`` are referred to as "single-precision
  descriptors" (resp. "double-precision descriptors").

``domain dom``
  Specifies the type of forward domain for the transform. The possible
  specialization values are ``domain::COMPLEX`` and ``domain::REAL``,
  corresponding to complex and real forward domains, respectively. Objects of
  the ``descriptor`` class specialized with ``domain::COMPLEX`` (resp.
  ``domain::REAL``) as ``dom`` are referred to as "complex descriptors" (resp.
  "real descriptors").

.. _onemkl_dft_descriptor_member_table:

.. rubric:: Member functions of the ``descriptor`` class template

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * -     Routines
     -     Description
   * -     :ref:`constructors<onemkl_dft_descriptor_constructors>`
     -     Creates a ``descriptor`` object. The parameterized constructors
           enable the (one-time) definition of the length(s)
           :math:`\lbrace n_1, \ldots, n_d\rbrace` (the dimension :math:`d` is
           deduced accordingly). The parameterized constructors default-initialize
           the object; copy and move constructors do not.
   * -     :ref:`assignment operators<onemkl_dft_descriptor_assignment_operators>`
     -     Performs a deep copy of or moves the argument.
   * -     ``set_value`` :ref:`member function<onemkl_dft_descriptor_set_value>`
     -     Sets a configuration value for a specific configuration parameter.
   * -     ``get_value`` :ref:`member function<onemkl_dft_descriptor_get_value>`
     -     Queries the configuration value associated with a particular
           configuration parameter.
   * -     ``set_workspace`` :ref:`member function<onemkl_dft_descriptor_set_workspace>`
     -     Equips the ``descriptor`` object with an external workspace.
   * -     ``commit`` :ref:`member function<onemkl_dft_descriptor_commit>`
     -     Commits the ``descriptor`` object to enqueue the operations relevant
           to the DFT(s) it determines to a given, user-provided ``sycl::queue``
           object; completes all initialization work relevant to and required by
           the chosen, device-compliant implementation for the particular DFT,
           as defined by the ``descriptor`` object.

.. _onemkl_dft_descriptor_constructors:

Constructors
++++++++++++

The parameterized constructors for a ``descriptor`` object instantiate it with
all the relevant default configuration settings (which may depend on the
specialization values for ``prec`` and ``dom``). The constructors do not perform
any significant initialization work as changes in the object's configuration(s)
may be operated thereafter (via its ``set_value``
:ref:`member function<onemkl_dft_descriptor_set_value>`) and modify significantly
the nature of that work.

The copy constructor performs a deep copy of ``descriptor`` objects.

The move constructor transfers the resources owned by a ``descriptor`` object,
without copying them.

.. rubric:: Parameterized constructor (one-dimensional transform)

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>::descriptor(std::int64_t length);

   }


.. rubric:: Parameterized constructor (transform of any dimension)

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>::descriptor(std::vector<std::int64_t> lengths);

   }

.. rubric:: Copy constructor

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>::descriptor(const descriptor<prec,dom>& other);

   }

.. rubric:: Move constructor

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>::descriptor(descriptor<prec,dom>&& other);

   }


.. container:: section

   .. rubric:: Input Parameters

   ``length``
      Length :math:`n_1 > 0` of the data sequence(s) for one-dimensional
      transform(s).

   ``lengths``
      Vector of :math:`d > 0` lengths :math:`\lbrace n_1, \ldots, n_d\rbrace`
      of the data sequence(s) for :math:`d`-dimensional transform(s). The values
      are to be provided in that order and such that
      :math:`n_j > 0,\ \forall j \in \lbrace 1, \ldots, d \rbrace`.

   ``other``
      Another ``descriptor`` object of the same type to copy or move.

.. container:: section

   .. rubric:: Throws

   The constructors shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here:

   ``oneapi::mkl::host_bad_alloc()``
      If any memory allocations on host have failed, for instance due to
      insufficient memory.

   ``oneapi::mkl::unimplemented()``
      If the dimension :math:`d`, *i.e.*, the size of ``lengths``, is larger
      than what is supported by the library implementation.
   

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. _onemkl_dft_descriptor_assignment_operators:

Assignment operators
++++++++++++++++++++

The copy assignment operator results in a deep copy.

.. rubric:: Copy assignment

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>& descriptor<prec,dom>::operator=(const descriptor<prec,dom>& other);

   }

.. rubric:: Move assignment

.. code-block:: cpp
   
   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      descriptor<prec,dom>& descriptor<prec,dom>::operator=(descriptor<prec,dom>&& other);

   }


.. container:: section

   .. rubric:: Input Parameters

   ``other``
      Another ``descriptor`` object to copy or move from.

.. container:: section

   .. rubric:: Throws

   The assignment operators shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here:

   ``oneapi::mkl::host_bad_alloc()``
      If any memory allocations on host have failed, for instance due to
      insufficient memory.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_set_value:

``set_value`` member function
+++++++++++++++++++++++++++++

The ``set_value`` member function of any ``descriptor`` object sets a
configuration value corresponding to a (read-write) configuration parameter for
the DFT(s) that it defines. This function is to be used as many times as
required for all the necessary configuration parameters to be set prior to
committing the object (by calling its ``commit``
:ref:`member function<onemkl_dft_descriptor_commit>`).

This function requires and expects exactly **two** arguments: it sets the
configuration value (second argument) corresponding to the configuration
parameter (first argument) ``param`` of type ``config_param``. The expected type
of the configuration value (second argument) depends on ``param``: it can be
``config_value`` or a native type like ``std::int64_t`` or ``float`` (more
details available in the :ref:`section<onemkl_dft_enum_config_param>` dedicated
to the ``config_param`` type and its values).

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      void descriptor<prec,dom>::set_value(config_param param, ...);

   }

.. container:: section

   .. rubric:: Input Parameters

   ``param``
      One of the possible values of type ``config_param`` representing the
      (writable) configuration parameter to be set.

   ``...``
      An element of the appropriate type for the configuration value
      corresponding to the targeted configuration
      parameter ``param`` (appropriate types are listed in the
      :ref:`section<onemkl_dft_enum_config_param>` dedicated to
      the ``config_param`` type and its values).

.. container:: section

   .. rubric:: Throws

   The ``set_value`` member function shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here:

   ``oneapi::mkl::invalid_argument()``
      If the provided ``param`` and/or configuration value are/is not valid.

   ``oneapi::mkl::unimplemented()``
      If the provided ``param`` and configuration value are valid, but not
      supported by the library implementation.
 
   
**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`


.. _onemkl_dft_descriptor_get_value:

``get_value`` member function
+++++++++++++++++++++++++++++

The ``get_value`` member function of any ``descriptor`` object queries the
configuration value corresponding to any configuration parameter for the DFT
that it defines.

This function requires and expects exactly **two** arguments: it returns the
configuration value (into the element pointed by the second argument)
corresponding to the queried configuration parameter (first argument) ``param``
of type ``config_param``. The type of the second argument
depends on the value of ``param``: it is  a pointer to a writable element of
type ``domain``, ``precision``, ``config_value`` or a native type like
``std::int64_t`` or ``float`` (more details available in the
:ref:`section<onemkl_dft_enum_config_param>` dedicated to the ``config_param``
type and its values).

.. note::
   When querying the value associated with a writable configuration parameter,
   the returned value corresponds to the latest value that was set, even if it
   was set after committing the descriptor. If the value was never set
   explicitly, the corresponding default value is returned.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      void descriptor<prec,dom>::get_value(config_param param, ...);

   }

.. container:: section

   .. rubric:: Input Parameters

   ``param``
      One of the possible values of type ``config_param`` representing the
      configuration parameter being queried.

   ``...``
      A pointer to a writable element of the appropriate type for the
      configuration value corresponding to the queried configuration
      parameter ``param`` (appropriate types are listed in the
      :ref:`section<onemkl_dft_enum_config_param>` dedicated to
      the ``config_param`` type and its values).

.. container:: section

   .. rubric:: Throws

   The ``get_value`` member function shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here:
   
   ``oneapi::mkl::invalid_argument()``
      If the queried ``param`` is not valid.

   ``oneapi::mkl::unimplemented()``
      If the queried ``param`` is valid, but not supported by the library
      implementation.

**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_set_workspace:

``set_workspace`` member function
+++++++++++++++++++++++++++++++++

The ``set_workspace`` member function of any ``descriptor`` object sets the
workspace (possible additional memory required by the object for computation
purposes) to use when computing DFTs.

This function may only be called after the ``descriptor`` object has been
committed. The size of the provided workspace must be equal to or larger than
the required workspace size, *i.e.*, the configuration value associated with
``config_param::WORKSPACE_EXTERNAL_BYTES`` (queryable via the ``get_value``
member function).

A ``descriptor`` object where ``config_value::WORKSPACE_EXTERNAL`` is specified
for  ``config_param::WORKSPACE_PLACEMENT`` is not a valid object for compute
calls until its workspace has been successfully set using this member function.

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

      template <precision prec, domain dom>
      void descriptor<prec,dom>::set_workspace(sycl::buffer<real_scalar_t, 1> &workspaceBuf);
   }

.. rubric:: Syntax (USM workspace)

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      void descriptor<prec,dom>::set_workspace(real_scalar_t* workspaceUSM);

   }

.. container:: section

   .. rubric:: Input Parameters

   ``workspaceBuf``
      A workspace buffer where ``real_scalar_t`` is the floating-point type
      according to ``prec``. This buffer must be sufficiently large or an
      exception will be thrown. A sub-buffer cannot be used.

   ``workspaceUSM``
      A workspace USM allocation where ``real_scalar_t`` is the floating-point
      type according to ``prec``. This allocation must be accessible on the
      device on which the descriptor is committed. It is assumed that this USM
      allocation is sufficiently large. The pointer is expected to be aligned
      to ``real_scalar_t``.

.. container:: section

   .. rubric:: Throws

   The ``set_workspace`` member function shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here:
   
   ``oneapi::mkl::invalid_argument()``
      If the provided buffer ``workspaceBuf`` is not sufficiently large or is a
      sub-buffer, or if the provided USM allocation ``workspaceUSM`` is
      ``nullptr`` when an external workspace of size greater than zero is
      required, or if the provided USM allocation ``workspaceUSM`` is not
      accessible by the device.

   ``oneapi::mkl::uninitialized()``
      If ``set_workspace`` is called before the descriptor is committed.


**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

.. _onemkl_dft_descriptor_commit:

``commit`` member function
++++++++++++++++++++++++++

The ``commit`` member function commits a ``descriptor`` object to the DFT
calculations it defines consistently with its configuration settings, by
completing all the initialization work (*e.g.*, algorithm selection, algorithm
tuning, choice of factorization, memory allocations, calculation of twiddle
factors, etc.) required by the chosen implementation for the desired DFT(s) on
the targeted device. Objects of any ``descriptor`` class **must** be committed
prior to using them in any call to ``compute_forward`` or ``compute_backward``
(which trigger actual DFT calculations).

As specified :ref:`above<onemkl_dft_descriptor_set_value>`, all required
configuration parameters must be set before this function is called. Any change
in configuration operated on a ``descriptor`` object via a call to its
``set_value`` member function *after* it was committed results in an undefined
state not suitable for computation until this ``commit`` member function is
called again.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::dft {

      template <precision prec, domain dom>
      void descriptor<prec,dom>::commit(sycl::queue& queue);
   }

.. container:: section

   .. rubric:: Input Parameters

   ``queue``
      Valid ``sycl::queue`` object to which the operations relevant to the
      desired DFT(s) are to be enqueued.

.. container:: section

   .. rubric:: Throws

   The ``commit`` member function shall throw the following
   :ref:`exception<onemkl_common_exceptions>` if the associated condition is
   detected. An implementation may throw additional implementation-specific
   exception(s) in case of error conditions not covered here (if the
   ``descriptor`` object's configuration was found to be inconsistent, for
   instance):
   
   ``oneapi::mkl::invalid_argument()``
      If ``queue`` is found to be invalid in any way.

   ``oneapi::mkl::host_bad_alloc()``
      If any host side only memory allocations fail, for instance due to lack of
      memory.

   ``oneapi::mkl::device_bad_alloc()``
      If any device or shared memory allocation fail.
 
**Descriptor class member table:** :ref:`onemkl_dft_descriptor_member_table`

**Parent topic:** :ref:`onemkl_dft`
