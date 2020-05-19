
setmode
=======


.. container::


   Sets a new mode for VM functions according to the ``mode`` parameter
   and returns the previous VM mode.


   .. container:: section
      :name: GUID-6F502D48-7B38-47E3-9A84-5A27A98BE930


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  uint64_t set_mode(queue& exec_queue, uint64_t      new_mode )

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


      The mode::ftzdazon is specifically designed to improve the
      performance of computations that involve denormalized numbers at
      the cost of reasonable accuracy loss. This mode changes the
      numeric behavior of the functions: denormalized input values are
      treated as zeros (DAZ = denormals-are-zero) and denormalized
      results are flushed to zero (FTZ = flush-to-zero). Accuracy loss
      may occur if input and/or output values are close to denormal
      range.


      .. list-table:: 
         :header-rows: 1

         * -  Value of mode 
           -  Description 
         * -  Accuracy Control 
           -   
         * -  ``mode::ha`` 
           -  High accuracy versions of VM functions. 
         * -  ``mode::la`` 
           -  Low accuracy versions of VM functions. 
         * -  ``mode::ep`` 
           -  Enhanced performance accuracy versions of VM functions. 
         * -  Denormalized Numbers Handling Control 
           -   
         * -  ``mode::ftzdazon`` 
           -  Faster processing of denormalized inputs is enabled. 
         * -  ``mode::ftzdazoff`` 
           -  Faster processing of denormalized inputs is disabled. 
         * -  Other 
           -   
         * -  ``mode::not_defined`` 
           -  VM status not defined. 




   The default value of the mode parameter is:


   ::


      mode::ha | mode::ftdazoff


.. container:: section
   :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   new_mode
      Specifies the VM mode to be set.


.. container:: section
   :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


   .. rubric:: Output Parameters
      :class: sectiontitle


   return value (old_mode)
      Specifies the former VM mode.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   ::


      oldmode = set_mode (exec_queue , mode::la);
      oldmode = set_mode (exec_queue , mode::ep | mode::ftzdazon);


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `VM Service
      Functions <vm-service-functions.html>`__


