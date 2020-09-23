=============
 Introduction
=============

The |ccl_full_name| (oneCCL) provides primitives for the
communication patterns that occur in deep learning applications.
oneCCL supports both scale-up for platforms with multiple
oneAPI devices and scale-out for clusters with multiple compute nodes.

oneCCL supports the following communication patterns used in deep learning (DL) algorithms:

- allgatherv
- allreduce
- alltoall
- alltoallv
- broadcast
- reduce
- reduce_scatter

oneCCL exposes controls over additional optimizations and capabilities such as:

* Prioritization for communication operations
* Persistent communication operations (enables decoupling one-time initialization and repetitive execution)
* Unordered communication operations
