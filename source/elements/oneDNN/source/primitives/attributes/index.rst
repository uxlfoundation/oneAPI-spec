..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _attributes-link:

Attributes
----------

The parameters passed to create a primitive descriptor specify the problem. An
engine specifies where the primitive will be executed. An operation descriptor
specifies the basics: the operation kind; the propagation kind; the source,
destination, and other tensors; the strides (if applicable); and so on.

**Attributes** specify some extra properties of the primitive. Users must
create them before use and must set required specifics using the corresponding
setters. The attributes are copied during primitive descriptor creation, so
users can change or destroy attributes right after that.

If not modified, attributes can stay empty, which is equivalent to the default
attributes. Primitive descriptors' constructors have empty attributes as
default parameters, so unless required users can simply omit them.

Attributes can also contain *post-ops*, which are computations executed after
the primitive.

.. toctree::
   :maxdepth: 1

   scratchpad.rst
   quantization.rst
   post-ops.rst

.. _attributes_error_handling-link:

Attribute Related Error Handling
++++++++++++++++++++++++++++++++

Since the attributes are created separately from the corresponding primitive
descriptor, consistency checks are delayed.  Users can successfully set
attributes in whatever configuration they want.  However, when they try to
create a primitive descriptor with the attributes they set, it might happen
that there is no primitive implementation that supports such a configuration.
In this case the library will throw the :any:`dnnl::error` exception.

.. rubric:: API

.. doxygenstruct:: dnnl::primitive_attr
   :project: oneDNN
   :members:

.. vim: ts=3 sw=3 et spell spelllang=en
