.. _clear_status:

clear_status
============


.. container::


   Sets the VM Status according to ``status::success`` and returns the
   previous VM Status.


   .. container:: section
      :name: GUID-927525F3-1A75-4E98-B8F3-7AF6A97263E0


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  uint8_t clear_status (queue& exec_queue )

      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The clear_status function sets the VM status to
      ``status::success`` and returns the previous VM status.


      The global VM Status is a single value and it accumulates all
      errors that happen inside VM functions. The following table lists
      the possible error values.


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
      :name: input-parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


.. container:: section
   :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   return value (old_status)
      Specifies the former VM status.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   ::


      uint8_t olderr = clear_status (exec_queue);


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


