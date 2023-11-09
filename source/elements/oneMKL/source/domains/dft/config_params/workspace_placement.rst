.. SPDX-FileCopyrightText: Codeplay Software
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_config_workspace_placement:

Workspace placement
--------------------------------------

DFT implementations often require temporary storage for intermediate data whilst computing DFTs.
This temporary storage is referred to as a *workspace*.
Whilst this is managed automatically by default (``config_value::WORKSPACE_AUTOMATIC`` 
set for ``config_param::WORKSPACE_PLACEMENT``), it may be preferable to provide an external 
workspace (``config_value::WORKSPACE_EXTERNAL`` set for ``config_param::WORKSPACE_PLACEMENT``) 
for the following reasons:

* to reduce the number of mallocs / frees;
* to reduce memory consumption.

For some backends and configurations, ``config_value::WORKSPACE_EXTERNAL`` may reduce performance.

A typical workflow for using ``config_value::WORKSPACE_EXTERNAL`` is given in the section :ref:`below<onemkl_dft_typical_usage_of_workspace_external>`.

WORKSPACE_PLACEMENT
+++++++++++++++++++

For ``config_param::WORKSPACE_PLACEMENT``, valid configuration values are ``config_value::WORKSPACE_AUTOMATIC`` and ``config_value::WORKSPACE_EXTERNAL``.

.. _onemkl_dft_config_value_workspace_automatic:

.. rubric:: WORKSPACE_AUTOMATIC

The default value for the ``config_param::WORKSPACE_PLACEMENT`` is ``config_value::WORKSPACE_AUTOMATIC``. 

When set to ``config_value::WORKSPACE_AUTOMATIC`` the user does not need to provide an external workspace. The workspace will be automatically managed by the backend library.

.. _onemkl_dft_config_value_workspace_external:

.. rubric:: WORKSPACE_EXTERNAL

The configuration ``config_param::WORKSPACE_PLACEMENT`` can be set to 
``config_value::WORKSPACE_EXTERNAL`` to allow the workspace to be set manually. 

When a descriptor is committed with ``config_value::WORKSPACE_EXTERNAL`` set 
for ``config_param::WORKSPACE_PLACEMENT``, the user must provide an external 
workspace before calling any compute function.
See :ref:`onemkl_dft_descriptor_set_workspace` and :ref:`onemkl_dft_typical_usage_of_workspace_external`.

.. _onemkl_dft_typical_usage_of_workspace_external:

Typical usage of ``WORKSPACE_EXTERNAL``
+++++++++++++++++++++++++++++++++++++++

Usage of ``config_value::WORKSPACE_EXTERNAL`` typically involves the following order of operations:

#. ``config_value::WORKSPACE_EXTERNAL`` is set for the uncommitted descriptor's ``config_param::WORKSPACE_EXTERNAL``.
#. The descriptor is committed.
#. The required workspace size is queried.
#. A workspace of sufficient size is provided to the descriptor.
#. Compute functions following the type of external workspace provided are called.
#. The user is responsible for freeing the external workspace.

This is shown in the following example code:

.. code-block:: cpp

   // Create a descriptor
   mkl::dft::descriptor<mkl::dft::precision::SINGLE, dom> desc(n);
   // 1. Set the workspace placement to WORKSPACE_EXTERNAL
   desc.set_value(mkl::dft::config_param::WORKSPACE_PLACEMENT, 
                  mkl::dft::config_value::WORKSPACE_EXTERNAL);
   // Set further configuration parameters
   // ...
   // 2. Commit the descriptor
   desc.commit(myQueue);
   // 3. Query the required workspace size
   std::int64_t workspaceBytes{0};
   desc.get_value(mkl::dft::config_param::WORKSPACE_EXTERNAL_BYTES, &workspaceBytes);
   // Obtain a sufficiently large USM allocation or buffer. For this example, a USM allocation is used.
   float* workspaceUsm = sycl::malloc_device<float>(workspaceBytes / sizeof(float), myQueue);
   // 4. Set the workspace
   desc.set_workspace(workspaceUsm);
   // 5. Now USM compute functions can be called.


**Parent topic:** :ref:`onemkl_dft_enums`

