.. _terminology:

============
Terminology
============

.. glossary::

   Batch Mode 
     The computation mode for an algorithm in |dal_short_name|, where all the data needed for
     computation are available at the start and fits the memory of the device where computations will
     be performed.

   Dataset
     A pair of a matrix :math:`X` of size :math:`N * p` and a vector :math:`Y` of size :math:`N`, where :math:`X`
     contains :math:`N` :term:`feature vectors <feature vector>` in rows and :math:`Y` stores all corresponding
     :term:`responses <response>`. Vector :math:`Y` is optional and may not be present if responses are unknown.

   DPC++
     Data Parallel C++ (DPC++) is a high-level language designed for data parallel programming productivity.
     DPC++ is based on :term:`SYCL* <sycl>` from the Khronos* Group to support data parallelism and heterogeneous programming.
     
   Feature
     A single column of matrix :math:`X` from a dataset.

   Feature vector
     A single real-valued vector of length :math:`p` that encodes information about a real
     object or an event.

   Host/Device
     OpenCL [OpenCLSpec]_ terms for referring to CPU that controls the connected GPU executing kernels. 

   JIT
     Just in Time Compilation --- compilation during execution of a program.

   Kernel
     Code written in OpenCL or SYCL and executed on a GPU device.

   Observation
     A pair of a :term:`feature vector <feature vector>` and a response if response is known, otherwise a feature
     vector.

   Model
     A result of training machine-learning algorithm that stores information necessary to run
     inference (prediction) on a new dataset.

   oneDAL
     |dal_full_name| (|dal_short_name|).

   Online Mode
     The computation mode for an algorithm in |dal_short_name|, where the data needed for computation
     becomes available in parts during the time.

   Response
     A single value corresponding to an observation. For example, response may be a label
     indicating that an observation belongs to a particular class.

   SPIR-V
     Standard Portable Intermediate Representation - V is a language for intermediate representation of compute kernels.

   SYCL
     SYCL(TM) [SYCLSpec]_ --- high-level programming model for OpenCL(TM) that enables code for heterogeneous
     processors to be written in a "single-source" style using completely standard C++.

   Use case
     A scenario that describes how a user might interact with a |dal_short_name| algorithm.

   Workload
     A task of applying a |dal_short_name| algorithm to a dataset.

