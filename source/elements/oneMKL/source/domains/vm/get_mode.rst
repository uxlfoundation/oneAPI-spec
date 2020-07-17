.. _onemkl_vm_get_mode:

get_mode
========


.. container::


   Gets the VM mode.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function:: uint64_t oneapi::mkl::vm::get_mode( queue& exec_queue )

      .. rubric:: Description
         :class: sectiontitle


      The function get_mode function returns the global VM ``mode``
      parameter that controls accuracy, handling of denormalized
      numbers, and error handling options. The variable value is a
      combination by bitwise OR ( \| ) of the values listed in the
      following table.


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


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (old_mode)
      Specifies the global VM mode.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_service_functions`


