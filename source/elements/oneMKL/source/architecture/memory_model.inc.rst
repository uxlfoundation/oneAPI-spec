.. _onemkl_memory_model:

Memory Model
-------------

The oneMKL memory model shall follow directly from the oneAPI memory model.  Mainly, oneMKL shall support two modes of encapsulating data for consumption on the device: the buffer memory abstraction model and the pointer-based memory model using Unified Shared Memory (USM).  These two paradigms shall also support both synchronous and asynchronous execution models as described in :ref:`onemkl_asynchronous_synchronous_execution`.


.. _onemkl_buffers:

The buffer memory model
+++++++++++++++++++++++

The SYCL 1.2.1 specification defines the buffer container templated on the provided data type which encapsulates the data in a SYCL application across both host and devices.  It provides the concept of accessors as the mechanism to access the buffer data with different modes to read and or write into that data. These accessors allow SYCL to create and manage the data dependencies in the SYCL graph that order the kernel executions.  With the buffer model, all data movement is handled by the SYCL runtime supporting both synchronous and asynchronous execution.

oneMKL provides APIs where buffers (in particular 1D buffers, ``sycl::buffer<T,1>``) contain the memory for all non scalar input and output data arguments. See :ref:`onemkl_synchronization_with_buffers` for details on how oneMKL routines manage any data dependencies with buffer arguments.  Any higher dimensional buffer must be converted to a 1D buffer prior to use in oneMKL APIs, e.g., via ``buffer::reinterpret``.



.. _onemkl_usm:

Unified Shared Memory model
+++++++++++++++++++++++++++

While the buffer model is powerful and elegantly expresses the data dependencies, it can be a burden for programmers to replace all pointers and arrays by buffers in their C++ applications.  A pointer-based model called Unified Shared Memory (USM) has also been provided in the DPC++ language. This alternative approach allows the programmer to use standard C++ pointers that have been allocated using one of the DPC++ provided memory allocation routines (e.g., ``malloc_shared()``). The USM pointers, however, do not manage data dependencies between enqueued actions on the USM data, so DPC++ language provides ``sycl::event`` objects associated with each enqueued submission which can be used to explicitly manage the dependencies.

oneMKL provides APIs where USM pointers contain the memory for all non scalar input and output data arguments. Additionally, oneMKL APIs with USM pointers shall provide means to pass ``sycl::events`` to manage the data depednencies.  See :ref:`onemkl_synchronization_with_usm` for the details.


