.. _create_error_handler:

create_error_handler
====================


.. container::


   Creates the local VM Error Handler for a function..


   .. container:: section
      :name: GUID-6F502D48-7B38-47E3-9A84-5A27A98BE930


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. container:: dlsyntaxpara


         .. cpp:function::  error_handler<T> create_error_handler(         buffer<uint8_t, 1> & errarray, int64_t length = 1, uint8_t         errstatus = status::not_defined, T fixup = 0.0, bool copysign =         false )

         USM API:


         .. cpp:function::  error_handler<T> create_error_handler(         uint8_t\* errarray, int64_t length = 1, uint8_t errstatus =         status::not_defined, T fixup = 0.0, bool copysign = false )

         ``create_error_handler`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-411FA652-F957-4C2D-95FA-3538EE600A54


      .. rubric:: Description
         :class: sectiontitle


      The create_error_handler creates the local VM Error handler to be
      passed to VM functions which support error handling.


      The local VM Error Handler supports three modes:


      -  **Single status mode**: all errors happened during function
         execution are being written into one status value.


         At the execution end the single value is either un-changed if
         no errors happened or contained accumulated (merged by bitwise
         OR) error statuses happened in function execution.


         Set the array pointer to any ``status`` object and the length
         equals 1 to enable this mode.


      -  **Multiple status mode**: error statuses are saved as an array
         by indices where they happen.


         Notice that only error statuses are being written into the
         array, the success statuses are not to be written.


         That means the array needs to be allocated and initialized by
         user before function execution.


         To enable this mode allocate ``status`` array with the same
         size as argument and result vectors, set the errarray pointer
         to it and the length to the vector size.


      -  **Fixup mode**: for all arguments which caused specific error
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

            * -  Status 
              -  Description 
            * -  Successful Execution 
            * -  ``status::success`` 
              -  VM function execution completed successfully 
            * -  ``status::not_defined`` 
              -  VM status not defined 
            * -  Warnings 
            * -  ``status::accuracy_warning`` 
              -  VM function execution completed successfully in a different          accuracy mode
            * -  Computational Errors 
            * -  ``status::errdom`` 
              -  Values are out of a range of definition producing invalid          (QNaN) result
            * -  ``status::sing`` 
              -  Values cause divide-by-zero (singularity) errors and          produce and invalid (QNaN or Inf) result
            * -  ``status::overflow`` 
              -  An overflow happened during the calculation process 
            * -  ``status::underflow`` 
              -  An underflow happened during the calculation process 




      Notes:


      -  You must allocate and initialize array errarray before calling
         VM functions in multiple status error handling mode.


         The array should be large enough to contain ``n`` error codes,
         where ``n`` is the same as input\output vector size for the VM
         function.


      -  If no arguments passed to the create_error_handler function,
         then the empty object is created with all of three error
         handling modes disabled.


         In this case, the VM math functions set the global error status
         only.


   .. container:: section
      :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


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
         default value is ``status::not_defined``.


      fixup
         Fixup value for results. This is an optional argument, default
         value is ``0.0``.


      copysign
         Flag for setting the fixup value's sign the same as the
         argument’s. This is an optional argument, default value
         ``false``.


   .. container:: section
      :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


      .. rubric:: Output Parameters
         :class: sectiontitle


      return value
         Specifies the error handler object to be created.


   .. container:: section
      :name: FUNCTN_VML_SETMODE-EX1


      .. rubric:: Examples
         :class: sectiontitle


      The following examples are possible usage models (USM API).


      Single status mode with create_error_handler():


      ::


         error_handler<float>  handler = vm::create_error_handler (st);
             vm::sin(exec_queue, 1000, a, r, handler);
             if ( st[0] & status::errdom)
             {
                 std::cout << ”Errdom status returned” << std::endl;
             }


      Single status mode without create_error_handler():


      ::


         vm::sin(exec_queue, 1000, a, r, {st });
             std::cout << status << std::endl; 
             if ( st[0] & status::errdom)
             {
                 std::cout << ”Errdom status returned” << std::endl;
             }


      The ``st`` contains either ``status::success`` or accumulated
      error statuses if computational errors occurred in ``vm::erfinv``.


      Multiple status mode with create_error_handler():


      ::


         error_handler<float>  handler   = vm::create_error_handler (st, 1000);
             vm::inv(exec_queue, 1000, a, r, handler);
             for(int i=0; i<1000; i++)
                 std::cout << st[i] << std::endl;


      Multiple status mode without create_error_handler():


      ::


         vm::inv(exec_queue, 1000, a, r, {st, 1000});
             for(int i=0; i<1000; i++)
                 std::cout << st[i] << std::endl;


      The ``st`` array contains all codes for computational errors that
      occur at the same vector indices ``i`` as the arguments that
      caused the errors.


      Fixup status mode with create_error_handler():


      ::


         float                 fixup = 1.0;
             error_handler<float>  handler = vm::create_error_handler (nullptr, 0, status::errdom, fixup, true);
             vm::erfinv(exec_queue, 1000, a, r, handler);


      Fixup status mode without create_error_handler():


      ::


         float fixup = 1.0;
             vm::erfinv(exec_queue, 1000, a, r, { nullptr, 0, status::errdom, fixup, true });


      All results in ``r`` which computation generated
      ``status::errdom`` are replaced by ``fixup`` values.


      In the example above all the erfinv function’s NAN results caused
      by greater than \|1\| arguments are replaced by 1.0 value with the
      same sign as the corresponding argument.


      Mixed (Single and Fixup) status mode with create_error_handler():


      ::


         float   fixup = 1e38;
             error_handler<float> handler = vm::create_error_handler (st, 1, status::overflow, fixup);
             vm::exp(exec_queue, 1000, a, r, handler);
             if ( st & status::underflow)
             {
                 std::cout << ”Underflow status returned” << std::endl;
             }


      Mixed (Single and Fixup) status mode without
      create_error_handler():


      ::


         float   fixup = 1e38;
             vm::exp(exec_queue, 1000, a, r, {st, 1, status::overflow, fixup});
             if ( st & status::underflow)
             {
                 std::cout << ”Underflow status returned” << std::endl;
             }


      Mixed (Multiple and Fixup) status mode with
      create_error_handler():


      ::


         float   fixup     = 1.0;
             error_handler<float>  handler   = vm::create_error_handler (st, 1000, status::errdom, fixup);
             vm::acospi(exec_queue, 1000, a, r, handler);
             for(int i=0; i<1000; i++)
                 std::cout << st[i] << std::endl;


      Mixed (Multiple and Fixup) status mode without
      create_error_handler():


      ::


         float   fixup     = 1.0;
             vm::acospi(exec_queue, 1000, a, r,{ st, 1000, status::errdom, fixup});
             for(int i=0; i<1000; i++)
                 std::cout << st[i] << std::endl;


      The ``st`` array contains all codes for computational errors that
      occur at the same vector indices ``i`` as the arguments that
      caused the errors. Additionally, all results in ``r`` which
      computation generated ``status::errdom`` are replaced by ``fixup``
      values.


      No local error handling mode:


      ::


         vm::pow(exec_queue, n, a, b, r);
             uint8_t err = vm::get_status (exec_queue);


             if (err & status::errdom)
             {
                 std::cout << ”Errdom status returned” << std::endl;
             }


             if (err & status::sing)
             {
                 std::cout << ”Singularity status returned” << std::endl;
             }


      Only global accumulated error status ``err`` is set.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


