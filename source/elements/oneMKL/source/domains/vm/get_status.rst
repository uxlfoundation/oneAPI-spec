
get_status
==========


.. container::


   Gets the VM Status.


   .. container:: section
      :name: GUID-C9FAAEB3-53AB-477F-92EF-CD2CB190A331


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  uint8_t get_status (queue& exec_queue )

      .. rubric:: Description
         :class: sectiontitle


      The get_status function gets the VM status.


      The global VM Status is a single value and it accumulates via
      bitwise OR ( \| ) all computational errors that happen inside VM
      functions. The following table lists the possible error values.


      .. list-table:: 
         :header-rows: 1

         * -  Status 
           -  Description 
         * -  Successful Execution 
           -   
         * -  ``status::success`` 
           -  VM function execution completed successfully 
         * -  ``status::not_defined`` 
           -  VM status not defined 
         * -  Warnings 
           -   
         * -  ``status::accuracy_warning`` 
           -  VM function execution completed successfully in a different       accuracy mode
         * -  Computational Errors 
           -   
         * -  ``status::errdom`` 
           -  Values are out of a range of definition producing invalid       (QNaN) result
         * -  ``status::sing`` 
           -  Values cause divide-by-zero (singularity) errors and produce       and invalid (QNaN or Inf) result
         * -  ``status::overflow`` 
           -  An overflow happened during the calculation process 
         * -  ``status::underflow`` 
           -  An underflow happened during the calculation process 




.. container:: section
   :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


.. container:: section
   :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (status)
      Specifies the VM status.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   ::


      uint8_t err = get_status (exec_queue);


      if (err & status::errdom)
      {
          std::cout << ”Errdom status returned” << std::endl;
      }


      if (err & status::sing)
      {
          std::cout << ”Singularity status returned” << std::endl;
      }


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


