.. _get_mode:

get_mode
========


.. container::


   Gets the VM mode.


   .. container:: section
      :name: GUID-E3B47247-72E8-49A0-9017-0230E36B87A4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  uint64_t get_mode( queue& exec_queue )

      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The function get_mode function returns the global VM ``mode``
      parameter that controls accuracy, handling of denormalized
      numbers, and error handling options. The variable value is a
      combination by bitwise OR ( \| ) of the values listed in the
      following table.


      .. list-table:: 
         :header-rows: 1

         * -  Value of mode 
           -  Description 
         * -  Accuracy Control 
         * -  ``mode::ha`` 
           -  High accuracy versions of VM functions. 
         * -  ``mode::la`` 
           -  Low accuracy versions of VM functions. 
         * -  ``mode::ep`` 
           -  Enhanced performance accuracy versions of VM functions. 
         * -  Denormalized Numbers Handling Control 
         * -  ``mode::ftzdazon`` 
           -  Faster processing of denormalized inputs is enabled. 
         * -  ``mode::ftzdazoff`` 
           -  Faster processing of denormalized inputs is disabled. 
         * -  Other 
         * -  ``mode::not_defined`` 
           -  VM status not defined. 




   See example below:


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


   return value (old_mode)
      Specifies the global VM mode.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   ::


      accm = get_mode (exec_queue) & mode::accuracy_mask;
      denm = get_mode (exec_queue) & mode::ftzdaz_mask;


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


.. container::

