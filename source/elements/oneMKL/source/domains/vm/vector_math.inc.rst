.. _onemkl_vm:

Vector Math
------------

.. container::


   oneMKL Vector Mathematics functions (VM) compute a mathematical
   function of each of the vector elements. VM includes a set of
   functions (arithmetic, power, trigonometric, exponential,
   hyperbolic, special, and rounding) that operate on vectors of real
   and complex numbers.


   Application programs that improve performance with VM include
   nonlinear programming software, computation of integrals, financial
   calculations, computer graphics, and many others.


   VM functions fall into the following groups according to the
   operations they perform:


   - :ref:`onemkl_vm_mathematical_functions` compute values of mathematical
     functions, such as sine, cosine, exponential, or logarithm, on vectors
     stored contiguously in memory.


   - :ref:`onemkl_vm_service_functions` set/get the accuracy modes and the
     error codes, and create error handlers for mathematical functions.


   The VM mathematical functions take an input vector as an argument,
   compute values of the respective function element-wise, and return
   the results in an output vector. All the VM mathematical functions
   can perform in-place operations, where the input and output arrays
   are at the same memory locations.

   - :ref:`onemkl_vm_special_value_notations`

.. toctree::
    :hidden:

    vm/special-value-notations
    vm/vm-mathematical-functions
    vm/vm-service-functions
    vm/bibliography
