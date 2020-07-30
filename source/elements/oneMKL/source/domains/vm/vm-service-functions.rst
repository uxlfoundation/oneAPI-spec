.. _onemkl_vm_service_functions:

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

         * - Function Short Name
           - Description
         * - :ref:`onemkl_vm_setmode`
           - Sets the VM mode
         * - :ref:`onemkl_vm_get_mode`
           - Gets the VM mode
         * - :ref:`onemkl_vm_set_status`
           - Sets the VM Error Status
         * - :ref:`onemkl_vm_get_status`
           - Gets the VM Error Status
         * - :ref:`onemkl_vm_clear_status`
           - Clears the VM Error Status
         * - :ref:`onemkl_vm_create_error_handler`
           - Creates the local VM error handler for a function


**Parent topic:** :ref:`onemkl_vm`

.. toctree::
    :hidden:

    setmode
    get_mode
    set_status
    get_status
    clear_status
    create_error_handler
