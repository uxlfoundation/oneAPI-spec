.. _onemkl_vm_create_error_handler:

create_error_handler
====================


.. container::


   Creates the local VM Error Handler for a function..


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. container:: dlsyntaxpara


         .. cpp:function:: oneapi::mkl::vm::error_handler<T> oneapi::mkl::vm::create_error_handler( buffer<uint8_t, 1> & errarray, int64_t length = 1, uint8_t errstatus = oneapi::mkl::vm::status::not_defined, T fixup = {}, bool copysign = false )

         USM API:


         .. cpp:function:: oneapi::mkl::vm::error_handler<T> oneapi::mkl::vm::create_error_handler( uint8_t* errarray, int64_t length = 1, uint8_t errstatus = oneapi::mkl::vm::status::not_defined, T fixup = {}, bool copysign = false )

         ``create_error_handler`` supports the following precisions.


         .. list-table::
            :header-rows: 1

            * - T
            * - ``float``
            * - ``double``
            * - ``std::complex<float>``
            * - ``std::complex<double>``




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      The create_error_handler creates the local VM Error handler to be
      passed to VM functions which support error handling.


      The local VM Error Handler supports three modes:


      - **Single status mode**: all errors happened during function
         execution are being written into one status value.


         At the execution end the single value is either un-changed if
         no errors happened or contained accumulated (merged by bitwise
         OR) error statuses happened in function execution.


         Set the array pointer to any ``status`` object and the length
         equals 1 to enable this mode.


      - **Multiple status mode**: error statuses are saved as an array
         by indices where they happen.


         Notice that only error statuses are being written into the
         array, the success statuses are not to be written.


         That means the array needs to be allocated and initialized by
         user before function execution.


         To enable this mode allocate ``status`` array with the same
         size as argument and result vectors, set the errarray pointer
         to it and the length to the vector size.


      - **Fixup mode**: for all arguments which caused specific error
         status results to be overwritten by a user-defined value.


         To enable this mode set desirable errstatus and fixup values.
         The fixup value is written to results for each argument which
         caused the errstatus error.


         If the copysign is set to true then fixup value’s sign set to
         the same sign of the argument which caused the errstatus – a
         suitable option for symmetric math functions.


      The following table lists the possible computational error values.


      .. container:: tablenoborder


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
              - VM function execution completed successfully in a different
                accuracy mode
            * - Computational Errors
              -
            * - ``oneapi::mkl::vm::status::errdom``
              - Values are out of a range of definition producing invalid
                (QNaN) result
            * - ``oneapi::mkl::vm::status::sing``
              - Values cause divide-by-zero (singularity) errors and produce
                and invalid (QNaN or Inf) result
            * - ``oneapi::mkl::vm::status::overflow``
              - An overflow happened during the calculation process
            * - ``oneapi::mkl::vm::status::underflow``
              - An underflow happened during the calculation process




      Notes:


      - You must allocate and initialize array errarray before calling
         VM functions in multiple status error handling mode.


         The array should be large enough to contain ``n`` error codes,
         where ``n`` is the same as the input/output vector size for the VM
         function.


      - If no arguments are passed to the create_error_handler function, then
        an empty object is created with all three error handling modes
        disabled.


         In this case, the VM math functions set the global error status
         only.


   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      errarray
         Array to store error statuses (should be a buffer for buffer
         API).


      length
         Length of the errarray. This is an optional argument, default
         value is ``1``.


      errcode
         Error status to fixup results. This is an optional argument,
         default value is ``oneapi::mkl::vm::status::not_defined``.


      fixup
         Fixup value for results. This is an optional argument, default
         value is ``0.0``.


      copysign
         Flag for setting the fixup value's sign the same as the
         argument’s. This is an optional argument, default value
         ``false``.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      return value
         Specifies the error handler object to be created.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_service_functions`


