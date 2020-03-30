.. _vm-service-functions:

VM Service Functions
====================


.. container::


   The VM Service functions enable you to set/get the accuracy mode and
   error code. These functions are available both in the Fortran and C
   interfaces. The table below lists available VM Service functions and
   their short description.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Function Short Name 
           -  Description 
         * -        `set_mode <setmode.html>`__
           -  Sets the VM mode 
         * -        `get_mode <get_mode.html>`__
           -  Gets the VM mode 
         * -        `set_status <set_status.html>`__
           -  Sets the VM Error Status 
         * -        `get_status <get_status.html>`__
           -  Gets the VM Error Status 
         * -        `clear_status <clear_status.html>`__
           -  Clears the VM Error Status 
         * -        `create_error_handler <create_error_handler.html>`__
           -  Creates the local VM error handler for a function 


**Parent topic:** :ref:`onemkl_vm`

.. toctree::
    :hidden:

    setmode
    get_mode
    set_status
    get_status
    clear_status
    create_error_handler
