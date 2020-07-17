.. _onemkl_vm_clear_status:

clear_status
============


.. container::


   Sets the VM Status according to ``oneapi::mkl::vm::status::success`` and returns the
   previous VM Status.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function:: uint8_t oneapi::mkl::vm::clear_status (queue& exec_queue )

      .. rubric:: Description
         :class: sectiontitle


      The clear_status function sets the VM status to
      ``oneapi::mkl::vm::status::success`` and returns the previous VM status.


      The global VM Status is a single value and it accumulates all
      errors that happen inside VM functions. The following table lists
      the possible error values.


      .. list-table::
         :header-rows: 1

         * - Status
           - Description
         * - Successful Execution
           -
         * - ``oneapi::mkl::vm::status::success``
           - VM function execution completed successfully
         * - ``oneapi::mkl::vm::status::not_defined``
           - VM status not defined
         * - Warnings
           -
         * - ``oneapi::mkl::vm::status::accuracy_warning``
           - VM function execution completed successfully in a different accuracy mode
         * - Computational Errors
           -
         * - ``oneapi::mkl::vm::status::errdom``
           - Values are out of a range of definition producing invalid (QNaN) result
         * - ``oneapi::mkl::vm::status::sing``
           - Values cause divide-by-zero (singularity) errors and produce and invalid (QNaN or Inf) result
         * - ``oneapi::mkl::vm::status::overflow``
           - An overflow happened during the calculation process
         * - ``oneapi::mkl::vm::status::underflow``
           - An underflow happened during the calculation process




.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (old_status)
      Specifies the former VM status.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_service_functions`


