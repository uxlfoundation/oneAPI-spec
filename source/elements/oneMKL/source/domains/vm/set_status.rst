
set_status
==========


.. container::


   Sets the global VM Status according to new values and returns the
   previous VM Status.


   .. container:: section
      :name: GUID-AE00FF02-7CB7-4B5B-B23F-04D49B61B34F


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  uint8_t set_status (queue& exec_queue,uint_8      new_status )

      .. rubric:: Description
         :class: sectiontitle


      The set_status function sets the global VM Status to new value and
      returns the previous VM Status.


      The global VM Status is a single value and it accumulates via
      bitwise OR ( \| ) all errors that happen inside VM functions. The
      following table lists the possible error values.


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
           -  VM function execution completed successfully in a different       accuracy mode
         * -  Computational Errors 
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


   new_status
      Specifies the VM status to be set.


.. container:: section
   :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (old_status)
      Specifies the former VM status.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   ::


      uint8_t olderr = set_status (exec_queue, status::success);


      if (olderr & status::errdom)
      {
          std::cout << ”Errdom status returned” << std::endl;
      }


      if (olderr & status::sing)
      {
          std::cout << ”Singularity status returned” << std::endl;
      }


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


