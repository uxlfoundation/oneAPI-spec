.. highlight:: cpp
.. default-domain:: cpp

=================
Algorithm Anatomy
=================

Algorithm is fundamental oneDAL entity characterized by `descriptors`_ and
`operations`_.







.. _descriptors:

-----------
Descriptors
-----------

**Descriptor** is an object that represents an algorithm including all its
properties and dependencies on other algorithms. Descriptor serves as:

- Dispatching mechanism for the `operations`_. Depending on descriptor
  type, operation decides what algorithm implementation should be executed.

- Aggregator of parameters. Descriptor provides an interface for setting up both
  compile-time and run-time parameters.

- Object that carries state of the algorithm. In the general case, descriptor is
  stateful object whose state changes after applying an operation.


Each oneDAL algorithm has its own dedicated namespace, where corresponding
descriptor is defined. Descriptor, in its turn, defines a set of template
parameters and **properties** --- run-time parameters can be accessed by means
of the corresponding getter and setter methods. `The following code sample
<descriptor-template_>`_ shows the common structure of descriptor's definition
for an abstract algorithm. To define a particular algorithm the following string
shall be substituted:

- ``%ALGORITHM%`` is the name of algorithm and its namespace. All classes and
  structures related to that algorithm shall be defined within the namespace.

- ``%PROPERTY_NAME%`` and ``%PROPERTY_TYPE%`` are the name and type of the one
  of algorithm's properties.

.. code-block:: cpp
   :name: descriptor-template
   :caption: Common structure of descriptor's definition

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


Descriptor may define any number of properties. Most of the properties are
preset with default values. Some of the properties are initialized by passing
required parameters to the constructor.

Properties are defined by means of getter and setter method. The getter methods
returns value of that type, while the setter accepts it as a parameter. The
underlying class field that stores the property's value is never exposed in the
descriptor interface. In addition, the setter returns a reference to the
descriptor object to allow chaining calls as shown in the example below.

.. code-block:: cpp
   :caption: Example of chaining calls to set some property values to the descriptor

   auto desc = descriptor{}
      .set_property_name_1(value_1)
      .set_property_name_2(value_2)
      .set_property_name_3(value_3);

Descriptor is allowed to have any number of template parameters, but must
support at least two:


.. _floating-point:

--------------------
Floating-point Types
--------------------



.. _methods:

--------------------
Computations Methods
--------------------


.. code-block:: cpp

   namespace onedal::%ALGORITHM% {

   namespace method {
      struct x {};
      struct y {};
      using by_default = x;
   } // namespace method

   } // namespace onedal::%ALGORITHM%




- ``Float`` is a floating-point type that the algorithm uses for computations.
  Algorithms are required to support only ``float`` and ``double`` types. The
  other floating-point types, e.g., ``float16`` or ``bfloat16``, are optional
  and up to specific oneDAL implementation. This parameter is defined first and
  has the :expr:`onedal::default_float_t` default value.

- ``Method`` is a tag-type that specifies an implementation of algorithm.
  Computational scheme of the algorithm may be implemented in different ways, so
  this parameter specifies the method to use while some operation is performed.

  The supported computational methods are declared within the ``method``
  namespace nested to the algorithm's namespace. Algorithm must support at least
  one computation method and define the ``by_default`` type alias that refers to
  the one of computational methods as shown in the example below.



  This parameter is defined second and has the :expr:`method::by_default`
  default value.


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

