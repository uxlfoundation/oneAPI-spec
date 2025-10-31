.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../replacements.inc.rst

.. _graph_programming_model-label:

=================
Programming Model
=================

oneDNN Graph programming model allows users to pass a computation
graph and get partitions. Users then compile partitions, bind tensor
data, and execute compiled partitions. Partitions are decided by the
oneDNN Graph implementation, which allows a scalable (no change in
user code to benefit from new fusion patterns) and platform aware
partitioning.

The programming model assumes that the main usage is to support deep learning
(DL) frameworks or inference engines. DL frameworks have their own
representation for the computation graph. oneDNN Graph API is used to offload or
accelerate graph partitions from a framework graph. In the description below,
“graph” refers to the graph built by oneDNN Graph implementation, and
“framework graph” refers to the graph built by the DL framework.

A deep learning computation graph consists of deep neural network (DNN)
operations. A DNN operation is a function that takes input data and returns
output data. The input and output data are multidimensional arrays called
tensors. A DNN operation may consume multiple tensors and produce multiple
tensors. A tensor must be produced by a single operation and may be consumed by
multiple operations.

oneDNN Graph API uses logical tensor, OP, and graph to represent a computation
graph. Logical tensor represents tensor’s metadata, like element data type,
shape, and layout. OP represents an operation on a computation graph. OP has
kind, attribute, and input and output logical tensors. OPs are added to a graph.
Both OP and logical tensor contains a unique ID, so that the graph knows how to
connect a producer OP to a consumer OP through a logical tensor. The graph
constructed is immutable. The purpose of creating the graph object is to get
partitions. After partitions are created, the graph object is not useful anymore.
Once users get partitions, users should not add OP to the graph.

oneDNN Graph defines operation set. Users should convert their DNN operation
definition to oneDNN Graph operation for graph construction. For operation
outside oneDNN Graph operation set, users may use wild-card OP. The wild-card OP
represents any OP. With its input and output logical tensors, it enables the
oneDNN Graph implementation to receive a full graph and conduct a complete
analysis. User needs to use a special “End” op to indicate output tensors of the
graph. For any tensors needs to be alive after a graph being executed, it needs
to be connected to a “End” op which consumes the tensor. Users may have multiple
“End” ops for one graph. For each OP users add to the graph, users must describe
its input and output logical tensors. Users must describe data type for each
logical tensor. If tensor's shape and layout are known, users must describe them
along with the logical tensor.

A partition is a connected subgraph in a graph. oneDNN Graph implementation
analyzes a graph and returns a number of partitions. The returned partitions
completely cover all the OPs of the graph and follow topological order. A
partition typically contains multiple Ops. Sometimes a partition may contain
just one OP, like a Wildcard OP or unsupported OP. A partition contains a flag
to indicate whether the partition is supported and thus can be compiled and
executed. User needs to check the flag before using the partition.

Partition’s input and output is also called as port. The ports record the
logical tensor information which was passed during graph construction. With the
logical tensor ID, users can track the producer and consumer relationship
between partitions. The ports also record the data type of corresponding logical
tensors. 

The returned partitions to users must not form a dependence cycle. For example,
a graph contains 3 OPs: A, B, and C. If C consumes A’s output and produces B’s
input, oneDNN Graph implementation must not put A and B into one partition.
However, if C is not added to the graph, the returned partition may include A
and B, since C is not visible to oneDNN Graph implementation. In this case, it
is the user’s responsibility to detect the dependence cycle. Once users pass a
complete graph, users don’t need to check the dependence cycle among the
partitions returned by oneDNN Graph.

A partition needs to be compiled before execution. The compilation lowers down
the compute logic to hardware ISA level and generates binary code. The generated
code is specialized for the input and output tensor’s metadata. Users must
create new logical tensors to pass complete metadata with the compilation API.
The logical tensors should fully specify id, data type, shape (can be incomplete
for outputs), and layout, the compilation should succeed. The logical tensors
passed during compilation time must match IDs with partition’s ports. The
logical tensors must have same data types with the ports with the port of the
same ID.

For the output logical tensors, users must either specify a public layout using
size and stride for each tensor dimension or request oneDNN Graph implementation
to decide a target-specific layout. For the input logical tensors, users must
either specify a public layout or using a target-specific layout produced by
predecessor partition compilation.  For the logical tensor with target-specific
layout, it must be produced by a partition and used only by partitions.

A compiled partition represents the generated code specialized for target
hardware and tensor metadata passed with compilation API. Users may cache the
compiled partition to amortize the compilation cost among many iterations. If
tensor metadata is identical, a compiled partition generated in previous
iterations may be reused.  Alternatively, implementations may reduce the
partition compilation cost by caching the compiled partition internally. This
optimization falls outside of the scope of this specification.

To execute a compiled partition, users must pass input and output tensors. Input
tensors must bind input data buffers to logical tensors. Users may query the
compiled partition for output data buffer sizes. If the sizes are known, users
may allocate the output data buffers and bind to output tensors. If the sizes
are unknown, users must provide an allocator for oneDNN Graph implementation to
allocate the output tensor buffer. The execution API takes a compiled partition,
input tensors, and return output tensors with the data buffer updated.

An engine represents a target device and context in the system. It needs to be
passed as a parameter for partition compilation. A stream abstracts hardware
execution resources of a target device. It is required to execute a compiled
partition.

.. image:: resources/programming_concepts.png

The diagram above summarizes the key programming concepts, and how they interact
with each other. The arrow indicates the destination object contains or uses the
source object. For example, OP contains logical tensor, and compiled partition
uses partition.

--------------
Logical Tensor
--------------

*Logical tensor* describes the metadata of the input or output tensor, like
element data type, number of dimensions, size for each dimension, layout.

Besides helping oneDNN Graph implementation to build the graph, Logical tensor
plays a critical role to exchange tensor metadata information between users and
oneDNN Graph implementation. Users pass input tensor shape information and get
the inferred shape for output tensors from a partition. Users pass logical
tensors to compilation API for specifying shape and layout information. Users
also use a special logical tensor to allow oneDNN Graph implementation to decide
the layout for output tensors. After compilation, users can query the compiled
partition for output tensors’ shape, layout, and sizes.

Each logical tensor has an ID. The tensor metadata may include new shape
information in the framework graph as it progresses toward execution. As a
logical tensor is not mutable, users must create a new logical tensor with the
same ID to pass any new additional information to oneDNN Graph implementation.
Users should guarantee that the logical tensor ID is unique within the graph
which the logical tensor belongs to.

----------
Operations
----------

An operation (or *OP*) describes a deep neural network operation. OP
contains kind, attribute, and input and output logical tensor shapes
and properties. In particular, activation and weights tensor formats
are specified as attributes to the operation.

Each operation has a unique ID and users should guarantee that
uniqueness within the graph which the OP is added to.

-----
Graph
-----

*Graph* contains a set of OPs. |add_op| adds an OP and its logical tensors
to a graph. oneDNN Graph implementation accumulates the OPs and logical tensors
and constructs and validates the graph as internal state. During |add_op|,
the target OP will be validated against its schema. Once the validation fails,
an exception will be thrown out from the API. When ``allow_exception=false`` is
specified, |add_op| call returns a status. It is the user’s responsibility
to handle the error either by checking the return value of the API or handling
the exception.

A same logical tensor may appear more than twice in |add_op| call, since it
is passed with the producer OP and consumer OPs. oneDNN Graph validates logical
tensors with the same id should be identical at the graph construction time.

Once the graph is fully described, |finalize| should be called. This
prevents any other operation from being added, and allows to call
|get_partitions| in order to get the set of partitions for that
graph. The graph does not hold any meaning to the user after
partitioning and should freed by the user.

All the OPs added to the graph will be contained in one of the returned
partitions. If an OP is not supported by the oneDNN Graph API implementation,
the corresponding partition will be marked as “not supported”. Users can check
the supporting status of a partition via the |is_supported|. Partitions
should not form cyclic dependence within the graph. If user does not pass a
complete graph, it is the user's responsibility to detect any dependence cycle
between the partitions and operations not passing to oneDNN Graph implementation.

The logical tensor passed at the graph construction stage might contain
incomplete information, for example, dimension and shape information are
spatially known. Complete information is not required but helps the oneDNN Graph
to form better partition decisions. Adding op to a graph is not thread-safe.
Users must create a graph, add op, and get partition in the same thread.


---------
Partition
---------

*Partition* represents a collection of OPs identified by oneDNN Graph
implementation as the basic unit for compilation and execution. It contains a
list of OP, input ports, output ports, and a flag indicating whether the
partition is supported. When a partition is created, it's assigned with an ID.
oneDNN Graph implementation should guarantee the partition ID is globally unique.

Users can pass the output logical tensors with incomplete shape
information (containing |DNNL_GRAPH_UNKNOWN_NDIMS| or
|DNNL_GRAPH_UNKNOWN_DIM|) to partition compilation API. oneDNN Graph
implementation needs calculate the output shapes according to the
given input shapes and schema of the OP. After compilation finished, a
compiled partition will be generated with full shape information for
the input and output logical tensors. Users can query the compiled
partition for the output logical tensors and get the shapes.

Partition can be compiled to generate a |compiled_partition|: an
executable object to run the computation for that partition. Users
must create an input logical tensor list and an output logical tensor
list to pass the additional tensor metadata as parameters to the
compilation API. The input and output logical tensors must match the
id of partitions’ ports, which captures the logical tensors
information during graph partitioning.  Typically, the more
information is given before the partition step (e.g. number of
dimensions and tensor dimensions), the most performant the code under
the compiled partition will be.

Users must specify ``strided``, ``any``, or ``opaque`` as the ``layout_type``
for the parameter logical tensors. When users specify ``any`` for a logical
tensor, the tensor must be an output tensor, and oneDNN Graph implementation
decides the best performant layout for the compiled partition. If it is
``strided``, it must use the public data layout described by the logical tensor.
For ``opaque``, the parameter logical tensor contains a target-specific layout,
which must be determined by the compilation of preceding partitions producing
the tensor. If the layout is row-major contiguous, the compilation must succeed.
If the layout has a stride, it is implementation dependent whether the
compilation succeed. If certain dimension of shape or the rank is unknown, it is
implementation dependent whether the compilation succeed. If the compilation
succeeds for unknown dimension or rank, the compiled partition should be able to
handle any value for that dimension or any rank at the execution time. 


------
Tensor
------

*Tensor* is an abstraction for multidimensional input and output data needed in
the execution of a compiled partition. A tensor contains a logical tensor, an
engine and a data handle.

Users are responsible for managing the tensor’s lifecycle, e.g. free the
resource allocated, when it is not used anymore.


------------------
Compiled Partition
------------------

A *compiled partition* represents the generated code specialized for target
hardware and meta data described by parameter logical tensors. Compiled
partition contains a partition and a handle representing the target specific
compiled object.

After the compilation API is invoked, users must query the logical output tensor
of the compiled partition to know the output tensor’s layout id and size. The
layout id is an opaque identifier for the target-specific layout. Users may pass
the layout id for the next partition compilation so that it can be optimized to
expect a specific input layout.  Users may use the size to allocate the memory
buffer of the output tensors for execution.

Framework passes the tensors and compiled partition as parameters to execution
API. The parameter logical tensors must be in the same order when they are
passed in the compilation API, and their IDs must match with the compiled
partition’s internal logical tensors. The layout type of each tensor must be
``strided`` or ``opaque``.

The compiled partition may support in-place optimization, which reuses the input
tensor data buffer for the output tensor for lower memory footprint and better
data locality. For each compiled partition, users can get pairs of input and
output ports. For the pair of input and output ports, user can use a same memory
buffer when passing input and output tensors along with execution API. The
in-place optimization is optional, when users use another memory buffer for the
output tensor, oneDNN Graph must update the output tensor.

If users place a tensor with data buffer pointer in outputs, the backend shall
use the data buffer provided by users.

Users may convert the parameter tensor with public layout to the target specific
layout expected by the compiled partition. A common optimization in deep
learning inference is that users may prepack the weight in the target-specific
layout required by the compiled partition and cache the reordered weight for
late use.

------
Engine
------

*Engine* (|engine|) are an abstraction of a computational device. The
graph extension additionally allows to create an engine with specific
host/device allocators to conveniently manage memory inside the Graph
API calls.

------
Stream
------

*Stream* (|stream|) encapsulate execution context tied to a particular
engine.

-----------------
General API notes
-----------------

There are certain assumptions on how oneDNN Graph objects behave:

* Logical tensor behave similarly to trivial types.
* All other objects behave like shared pointers. Copying is always shallow.

--------------
Error Handling
--------------

The C++ API throws exceptions for error handling.
