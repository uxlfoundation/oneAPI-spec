.. _onemkl_architecture:

oneMKL Architecture
====================

The oneMKL element of oneAPI has several general assumptions, requirements and recommendations for all domains contained therein.  These will be addressed in this architecture section.  
In particular, DPC++ allows for a great control over the execution of kernels on the various devices.  We discuss the supported execution models of oneMKL APIs in :ref:`onemkl_execution_model`. 
A discussion of how data is stored and passed in and out of the APIs is addressed in :ref:`onemkl_memory_model`.
The general structure and design of oneMKL APIs including namespaces and common data types are expressed in :ref:`onemkl_api_design`.
The exceptions and error handling are described in :ref:`onemkl_exceptions`.  
Finally all the other necessary aspects related to oneMKL architecture can be found in :ref:`onemkl_arch_other` including versioning and discussion of pre and post conditions. 


.. include:: execution_model.inc.rst
.. include:: memory_model.inc.rst
.. include:: api_design.inc.rst
.. include:: exceptions.inc.rst
.. include:: other_architecture.inc.rst
