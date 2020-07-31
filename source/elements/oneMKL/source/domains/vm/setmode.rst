.. _onemkl_vm_setmode:

set_mode
========


.. container::


   Sets a new mode for VM functions according to the ``mode`` parameter
   and returns the previous VM mode.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function:: uint64_t oneapi::mkl::vm::set_mode(queue& exec_queue, uint64_t new_mode )

      .. rubric:: Description
         :class: sectiontitle


      The set_mode function sets a new mode for VM functions according
      to the ``new_mode`` parameter and returns the previous VM mode.
      The mode change has a global effect on all the VM functions within
      a thread.


      The ``mode`` parameter is designed to control accuracy and
      handling of denormalized numbers. You can obtain all other
      possible values of the ``mode`` parameter using bitwise OR ( \| )
      operation to combine one value for handling of denormalized
      numbers.


      The oneapi::mkl::vm::mode::ftzdazon is specifically designed to improve the
      performance of computations that involve denormalized numbers at
      the cost of reasonable accuracy loss. This mode changes the
      numeric behavior of the functions: denormalized input values are
      treated as zeros (DAZ = denormals-are-zero) and denormalized
      results are flushed to zero (FTZ = flush-to-zero). Accuracy loss
      may occur if input and/or output values are close to denormal
      range.


      .. list-table::
         :header-rows: 1

         * - Value of mode
           - Description
         * - Accuracy Control
           -
         * - ``oneapi::mkl::vm::mode::ha``
           - High accuracy versions of VM functions.
         * - ``oneapi::mkl::vm::mode::la``
           - Low accuracy versions of VM functions.
         * - ``oneapi::mkl::vm::mode::ep``
           - Enhanced performance accuracy versions of VM functions.
         * - Denormalized Numbers Handling Control
           -
         * - ``oneapi::mkl::vm::mode::ftzdazon``
           - Faster processing of denormalized inputs is enabled.
         * - ``oneapi::mkl::vm::mode::ftzdazoff``
           - Faster processing of denormalized inputs is disabled.
         * - Other
           -
         * - ``oneapi::mkl::vm::mode::not_defined``
           - VM status not defined.




   The default value of the mode parameter is:


   ::


      oneapi::mkl::vm::mode::ha | oneapi::mkl::vm::mode::ftdazoff


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   new_mode
      Specifies the VM mode to be set.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (old_mode)
      Specifies the former VM mode.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_service_functions`


