.. highlight:: cpp
.. default-domain:: cpp

=================
Algorithm anatomy
=================

.. _descriptors:

-----------
Descriptors
-----------

**Descriptor** is an object that represents an algorithm, aggregates its
parameters and dependencies on other descriptors. Descriptor serves as:

- Dispatching mechanism for the `operations`_. Depending on descriptor
  type, operation decides what algorithm implementation should be called.

- Object that carry state of the algorithm.



::

   namespace onedal::A {

   template <typename Float  = default_float_t,
             typename Task   = method::by_default,
             typename Method = method::by_default>
   class descriptor {
   public:
      descriptor& set_X(T value);
      T get_X() const;
   };

   } // onedal::A



::

   namespace onedal::A {

   namespace task {
      struct task_a {};
      struct task_b {};
      using by_default = task_a;
   } // namespace task

   namespace method {
      struct method_c {};
      struct method_d {};
      using by_default = method_d;
   } // namespace method

   } // namespace onedal::A


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

