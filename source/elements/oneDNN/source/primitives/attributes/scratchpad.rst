..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Scratchpad Mode
---------------

Some primitives might require a temporary buffer while performing their
computations. For instance, the operations that do not have enough independent
work to utilize all cores on a system might use parallelization over the
reduction dimension (the K dimension in the GEMM notation). In this case
different threads compute partial results in private temporary buffers, and
then the private results are added to produce the final result. Another
example is using matrix multiplication (GEMM) to implement convolution. Before
calling GEMM, the source activations need to be transformed using the
``im2col`` operation. The transformation result is written to a temporary
buffer that is then used as an input for the GEMM.

In both of these examples, the temporary buffer is no longer required once the
primitive computation is completed. oneDNN refers to such kind of a memory
buffer as a *scratchpad*.

Both types of implementation might need extra space for the reduction in case
there are too few independent tasks. The amount of memory required by the
``im2col`` transformation is proportional to the size of the source image
multiplied by the weights spatial size. The size of a buffer for reduction is
proportional to the tensor size to be reduced (e.g., ``diff_weights`` in the
case of backward by weights) multiplied by the number of threads in the
reduction groups (the upper bound is the total number of threads).

By contrast, some other primitives might require very little extra space. For
instance, one of the implementation of the :any:`dnnl::sum` primitive requires
temporary space only to store the pointers to data for each and every input
array (that is, the size of the scratchpad is ``n * sizeof(void *)``, where
``n`` is the number of summands).

oneDNN supports two modes for handling scratchpads:

.. doxygenenum:: dnnl::scratchpad_mode
   :project: oneDNN

The scratchpad mode is controlled though the @ref
:any:`dnnl::primitive_attr::set_scratchpad_mode` primitive attributes.

If the user provides scratchpad memory to a primitive, this memory must be
created using the same engine that the primitive uses.

All primitives support both scratchpad modes.

.. note::

   Primitives are not thread-safe by default. The only way to make the
   primitive execution fully thread-safe is to use the
   :any:`dnnl::scratchpad_mode::user` mode and not pass the same scratchpad
   memory to two primitives that are executed concurrently.

.. rubric:: Examples

.. rubric:: Library Manages Scratchpad

As mentioned above, this is a default behavior. We only want to highlight how
a user can query the amount of memory consumed by a primitive due to a
scratchpad.

.. code:: cpp

    // Use default attr, hence the library allocates scratchpad
    dnnl::primitive::primitive_desc op_pd(params, /* other arguments */);

    // Print how much memory would be hold by a primitive due to scratchpad
    std::cout << "primitive will use "
              << op_pd.query_s64(dnnl::query::memory_consumption_s64)
              << " bytes" << std::endl;

    // In this case scratchpad is internal, hence user visible scratchpad memory
    // descriptor should be empty:
    auto zero_md = dnnl::memory::desc();

.. rubric:: Library Manages Scratchpad

.. code:: cpp

    // Create an empty (default) attributes
    dnnl::primitive_attr attr;

    // Default scratchpad mode is `library`:
    assert(attr.get_scratchpad_mode() == dnnl::scratchpad_mode::library);

    // Set scratchpad mode to `user`
    attr.set_scratchpad_mode(dnnl::scratchpad_mode::user);

    // Create a primitive descriptor with custom attributes
    dnnl::primitive::primitive_desc op_pd(op_d, attr, engine);

    // Query the scratchpad memory descriptor
    dnnl::memory::desc scratchpad_md = op_pd.scratchpad_desc();

    // Note, that a primitive doesn't consume memory in this configuration:
    assert(op_pd.query_s64(dnnl::query::memory_consumption_s64) == 0);

    // Create a primitive
    dnnl::primitive prim(op_pd);

    // ... more code ..

    // Create a scratchpad memory
    // NOTE: if scratchpad is not required for a particular primitive the
    //       scratchpad_md.get_size() will return 0. It is fine to have
    //       scratchpad_ptr == nullptr in this case.
    void *scratchpad_ptr = user_memory_manager::allocate(scratchpad_md.get_size());
    // NOTE: engine here must much the engine of the primitive
    dnnl::memory scratchpad(scratchpad_md, engine, scratchpad_ptr);

    // Pass a scratchpad memory to a primitive
    prim.execute(stream, { /* other arguments */,
            {DNNL_ARG_SCRATCHPAD, scratchpad}});

.. vim: ts=3 sw=3 et spell spelllang=en

