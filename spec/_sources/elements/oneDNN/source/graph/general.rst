.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../replacements.inc.rst

##################
Common Definitions
##################

This section lists common types and definitions used by all or multiple
graph operations.

Logical tensor enums and type
*****************************

.. doxygenstruct:: dnnl::graph::logical_tensor
   :project: oneDNN
   :members:

Operation attributes and kinds
******************************

.. doxygenstruct:: dnnl::graph::op
   :project: oneDNN
   :members:

Graph objects member functions
******************************

.. doxygenstruct:: dnnl::graph::graph
   :project: oneDNN
   :members:

Macros to specify unknown shapes
********************************
	     
.. doxygendefine:: DNNL_GRAPH_UNKNOWN_NDIMS
   :project: oneDNN

.. doxygendefine:: DNNL_GRAPH_UNKNOWN_DIM
   :project: oneDNN

