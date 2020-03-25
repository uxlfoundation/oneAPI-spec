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


   -  `VM Mathematical
      Functions <vm/vm-mathematical-functions.html>`__
      compute values of mathematical functions, such as sine, cosine,
      exponential, or logarithm, on vectors stored contiguously in
      memory.


   -  `VM Service
      Functions <vm/vm-service-functions.html>`__
      set/get the accuracy modes and the error codes,and create error
      handlers for mathematical functions.


   The VM mathematical functions take an input vector as an argument,
   compute values of the respective function element-wise, and return
   the results in an output vector. All the VM mathematical functions
   can perform in-place operations, where the input and output arrays
   are at the same memory locations.

   - :ref:`special-value-notations`
   - :ref:`miscellaneous-vm-functions`

.. toctree::
    :hidden:

    vm/special-value-notations
    vm/vm-mathematical-functions
    vm/vm-service-functions
    vm/miscellaneous-vm-functions
    vm/bibliography
