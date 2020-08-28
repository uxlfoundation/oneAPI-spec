.. _operations:

==========
Operations
==========

**An operation** is a function that transforms :txtref:`a descriptor
<descriptors>` and other arguments represented via `an input <input_>`_ object
to `a result <result_>`_ object. An operation responsible for:

- Execution of all computational routines of the algorithm represented by the
  descriptor.

- Passing SYCL* queue to computational routines.

- Verification of preconditions and postconditions, before and after execution
  of computational routines.

.. _general_operation:

----------------------------
General operation definition
----------------------------
`The following code sample <operation_template_>`_ shows the declaration for an
abstract operation. To declare a particular operation, the ``%OPERATION_NAME%``
shall be substituted.

.. code-block:: cpp
   :name: operation_template

   namespace oneapi::dal {

   template <typename Descriptor>
   using %OPERATION_NAME%_input_t = /* implementation defined */;

   template <typename Descriptor>
   using %OPERATION_NAME%_result_t = /* implementation defined */;

   template <typename Descriptor>
   %OPERATION_NAME%_result_t<Descriptor> %OPERATION_NAME%(
      sycl::queue& queue,
      const Descriptor& desc,
      const %OPERATION_NAME%_input_t<Descriptor>& input);

   } // namespace oneapi::dal


Each operation shall satisfy the following requirements:

- An operation shall accept tree parameters in the following order:

  + The SYCL* queue object.
  + The descriptor of the algorithm.
  + The `input object <input_>`_.

- An operation shall return the `result object <result_>`_.

- The ``%OPERATION_NAME%_input_t`` and ``%OPERATION_NAME%_result_t`` alias
  templates shall be used for inference of the input and return types.

- If precondition is violated, an operation shall throw an exception derived
  from ``oneapi::dal::logic_error``.

- If postcondition is violated, an operation shall throw an exception derived
  from ``oneapi::dal::runtime_error``.

- The exact list of pre- and post- conditions shall be defined by :txtref:`a
  particular algorithm specification <algorithms>`.

-------------------
Operation shortcuts
-------------------
In order to make the code on user side less verbose, oneDAL defines the
following overloaded functions called *shortcuts* for each operation in addition
to the general one described in section `General operation definition
<general_operation_>`_.

- Shortcut for execution on :term:`host <Host/Device>`. Performs the same
  operation as the general function on host, but does not require passing the
  queue explicitly.

  .. code-block:: cpp

     template <typename Descriptor>
     %OPERATION_NAME%_result_t<Descriptor> %OPERATION_NAME%(
        const Descriptor& desc,
        const %OPERATION_NAME%_input_t<Descriptor>& input);

- Shortcut that allows omitting explicit input creation.

  .. code-block:: cpp

     template <typename Descriptor, typename... Args>
     %OPERATION_NAME%_result_t<Descriptor> %OPERATION_NAME%(
        sycl::queue& queue,
        const Descriptor& desc,
        Args&&... args);

- Shortcut that allows omitting explicit queue and input creation. This is
  combination of two previous shortcuts.

  .. code-block:: cpp

     template <typename Descriptor, typename... Args>
     %OPERATION_NAME%_result_t<Descriptor> %OPERATION_NAME%(
        const Descriptor& desc,
        Args&&... args);



.. _input:

-----
Input
-----

.. code-block:: cpp

   namespace oneapi::dal::%ALGORITHM% {

   template <typename Task = task::by_default>
   class OPERATION_NAME_input {
   public:
      %OPERATION_NAME%_input(
         const %PROPERTY_TYPE_1%& property_name_1,
         const %PROPERTY_TYPE_2%& property_name_2,
         /* more properties */
      )

      /* Getter & Setter for the property called `%PROPERTY_NAME_1%` */
      descriptor& set_%PROPERTY_NAME_1%(%PROPERTY_TYPE_1% value);
      %PROPERTY_TYPE_1% get_%PROPERTY_NAME_1%() const;

      /* Getter & Setter for the property called `%PROPERTY_NAME_2%` */
      descriptor& set_%PROPERTY_NAME_2%(%PROPERTY_TYPE_2% value);
      %PROPERTY_TYPE_2% get_%PROPERTY_NAME_2%() const;

      /* more properties */
   };

   } // namespace oneapi::dal::%ALGORITHM%


.. _result:

------
Result
------

.. code-block:: cpp

   namespace oneapi::dal::%ALGORITHM% {

   template <typename Task = task::by_default>
   class OPERATION_NAME_result {
   public:
      /* Getter & Setter for the property called `%PROPERTY_NAME%` */
      descriptor& set_%PROPERTY_NAME%(%PROPERTY_TYPE% value);
      %PROPERTY_TYPE% get_%PROPERTY_NAME%() const;

      /* more properties */
   };

   } // namespace oneapi::dal::%ALGORITHM%

.. toctree::
   train.rst
   infer.rst
   compute.rst
