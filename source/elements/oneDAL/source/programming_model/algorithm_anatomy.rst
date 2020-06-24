.. highlight:: cpp
.. default-domain:: cpp

=================
Algorithm Anatomy
=================

oneDAL primarily targets algorithms that are extensively used in data analytics.
These algorithms typically have many parameters, i.e. knobs to control its
internal behavior and produced result. In machine learning, those parameters are
often referred as *meta-parameters* to distinguish them from the model
parameters learnt during the training. `Some algorithms <xgboost_params_>`_
define a dozen meta-parameters, while others depend on another algorithm as, for
example, the logistic regression training procedure depends on optimization
algorithm.

.. _xgboost_params: https://xgboost.readthedocs.io/en/latest/parameter.html

Besides meta-parameters, machine learning algorithms may have different *stages*,
such as :term:`training <Training>` and :term:`inference <Inference>`. Moreover,
the stages of an algorithm may be implemented in a variety of *computational
methods*. For instance, a linear regression model could be trained
by solving a system of linear equations [Friedman17]_ or by applying
an iterative optimization solver directly to the empirical risk function [Zhang04]_.

From computational perspective, algorithm implementation may rely on different
*floating-point types*, such as ``float``, ``double`` or ``bfloat16``. Having a
capability to specify what type is needed is important for the end user as their
precision requirements vary depending on a workload.

To best tackle the mentioned challenges, each algorithm is decomposed into
`descriptors`_ and `operations`_.


.. _descriptors:

-----------
Descriptors
-----------

**A descriptor** is an object that represents an algorithm including all its
meta-parameters, dependencies on other algorithms, floating-point types, and
computational methods. A descriptor serves as:

- A dispatching mechanism for `operations`_. Based on a descriptor
  type, an operation executes a particular algorithm implementation.

- An aggregator of meta-parameters. It provides an interface for setting up
  meta-parameters at either compile-time or run-time.

- An object that stores the state of the algorithm. In the general case, a descriptor is
  a stateful object whose state changes after an operation is applied.

Each oneDAL algorithm has its own dedicated namespace, where the corresponding
descriptor is defined (for more details, see :txtref:`Namespaces
<common_namespaces>`). Descriptor, in its turn, defines the following:

- **Template parameters.** A descriptor is allowed to have any number of template
  parameters, but shall support at least two:

   + ``Float`` is a `floating-point type <floating-point_>`_ that the algorithm
     uses for computations. This parameter is defined first and has the
     ``onedal::default_float_t`` default value.

   + ``Method`` is a tag-type that specifies the `computational method
     <methods_>`_. This parameter is defined second and has the
     ``method::by_default`` default value.

- **Properties.** A property is a run-time parameter that can be accessed by
  means of the corresponding :term:`getter <Getter>` and :term:`setter <Setter>`
  methods.

`The following code sample <descriptor-template_>`_ shows the common structure
of a descriptor's definition for an abstract algorithm. To define a particular
algorithm, the following strings shall be substituted:

- ``%ALGORITHM%`` is the name of an algorithm and its namespace. All classes and
  structures related to that algorithm are defined within the namespace.

- ``%PROPERTY_NAME%`` and ``%PROPERTY_TYPE%`` are the name and the type of one
  of the algorithm's properties.

.. code-block:: cpp
   :name: descriptor-template

   namespace onedal::%ALGORITHM% {

   template <typename Float  = default_float_t,
             typename Method = method::by_default,
             /* more template parameters */>
   class descriptor {
   public:
      /* Getter & Setter for the property called `%PROPERTY_NAME%` */
      descriptor& set_%PROPERTY_NAME%(%PROPERTY_TYPE% value);
      %PROPERTY_TYPE% get_%PROPERTY_NAME%() const;

      /* more properties */
   };

   } // namespace onedal::%ALGORITHM%


Each meta-parameter of an algorithm is mapped to a property that shall satisfy
the following requirements:

- Properties are defined with getter and setter methods. The underlying
  class member variable that stores the property's value is never exposed in the
  descriptor interface.

- The getter returns the value of the underlying class member variable.

- The setter accepts only one parameter of the property's type and assigns it
  to the underlying class member variable.

- Most of the properties are preset with default values, others
  are initialized by passing the required parameters to the constructor.

- The setter returns a reference to the descriptor object to allow chaining
  calls as shown in the example below.

  .. code-block:: cpp

     auto desc = descriptor{}
        .set_property_name_1(value_1)
        .set_property_name_2(value_2)
        .set_property_name_3(value_3);


.. _floating-point:

Floating-point Types
--------------------

It is required for each algorithm to support at least one implementation-defined
floating-point type. Other floating-point types are optional, for example ``float``,
``double``, ``float16``, and ``bfloat16``. It is up to a specific oneDAL
implementation whether or not to support these types.

The floating-point type used as a default in descriptors is
implementation-defined and shall be declared within the top-level namespace.

.. code-block:: cpp

   namespace onedal {
      using default_float_t = /* implementation defined */;
   } // namespace onedal


.. _methods:

Computational Methods
---------------------

The supported computational methods are declared within the
``%ALGORITHM%::method`` namespace using tag-types. Algorithm shall support at
least one computational method and declare the ``by_default`` type alias that
refers to one of the computational methods as shown in the example below.


.. code-block:: cpp

   namespace onedal::%ALGORITHM% {
      namespace method {
         struct x {};
         struct y {};
         using by_default = x;
      } // namespace method
   } // namespace onedal::%ALGORITHM%



.. _operations:

----------
Operations
----------

.. _input:

Input
-----

.. _result:

Result
------
