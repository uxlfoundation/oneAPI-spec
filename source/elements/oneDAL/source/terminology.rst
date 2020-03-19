.. _terminology:

============
Terminology
============

.. list-table::
   :widths: 25 25 25
   :header-rows: 1
   :align: left

   * - Term
     - Definition
   * - Batch Mode 
     - The computation mode for an algorithm in oneDAL, where all the data needed for
computation are available at the start and fits the memory of the device where computations will
be performed.

   * - Dataset
     - A pair of a matrix $X$ of size $N \times p$ and a vector $Y$ of size $N$, where $X$
contains $N$ feature vectors in rows and $Y$ stores all corresponding responses. Vector $Y$ is
optional and may not be present if responses are unknown.

   * - DPC++
     - DPC++ --- Technology (programming language, compiler, and runtime) that
is based on SYCL* specification and extends it.

   * - Feature
     - A single column of matrix $X$ from a dataset.

   * - Feature vector
     - A single real-valued vector of length $p$ that encodes information about a real
object or an event.

   * - Host/Device
     - OpenCL terms for referring to CPU that controls the connected GPU executing kernels.

   * - JIT
     - Just in Time Compilation --- compilation during execution of program.

   * - Kernel
     - Code written in OpenCL or SYCL and executed on a GPU device.

   * - Observation
     - A pair of a feature vector and a response if response is known, otherwise a feature
vector.

   * - Model
     - A result of training machine-learning algorithm that stores information necessary to run
inference (prediction) on a new dataset.

   * - oneDAL
     - Intel(R) oneAPI Data Analytics Library (oneDAL).

   * - Online Mode
     - The computation mode for an algorithm in oneDAL, where the data needed for computation
becomes available in parts during the time.

   * - Response
     - A single value corresponding to an observation. For example, response may be a label
indicating that an observation belongs to a particular class.

   * - SPIR-V
     - Language for intermediate representation of compute kernels.

   * - SYCL
     - SYCL(TM) --- high-level programming model for OpenCL(TM) that enables code for heterogeneous
processors to be written in a "single-source" style using completely standard C++.

   * - Use case
     - A scenario that describes how a user might interact with a data analytics algorithm.

   * - Workload
     - A task of applying a data analytics algorithm to a dataset.

