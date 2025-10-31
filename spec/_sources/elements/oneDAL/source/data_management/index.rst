.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _data_management:


===============
Data management
===============

This section includes concepts and objects that operate on data. For
|dal_short_name|, such set of operations, or **data management**, is distributed
between different stages of the :txtref:`data analytics pipeline
<data_analytics_pipeline>`. From a perspective of data management, this pipeline
contains three main steps of data acquisition, preparation, and computation (see
:txtref:`the picture below <typical_data_management_flow>`):

1. Raw data acquisition

  - Transfer out-of-memory data from various sources (databases, files, remote
    storage) into an in-memory representation.

2. Data preparation

  - Support different in-memory :capterm:`data formats <data format>`.
  - Compress and decompress the data.
  - Convert the data into numeric representation.
  - Recover missing values.
  - Filter the data and perform data normalization.
  - Compute various statistical metrics for numerical data, such as mean, variance,
    and covariance.

3. Algorithm computation

  - Stream in-memory numerical data to the algorithm.

In complex usage scenarios, data flow goes through these three stages back and
forth. For example, when the data are not fully available at the start of the
computation, it can be done step-by-step using blocks of data. After the
computation on the current block is completed, the next block should be obtained
and prepared.

.. _typical_data_management_flow:

.. image:: _static/data_management_flow.png
  :width: 800
  :alt: Typical data management flow

Key concepts
============

|dal_short_name| provides a set of concepts to operate on out-of-memory and
in-memory data during different stages of the :txtref:`data analytics pipeline
<data_analytics_pipeline>`.

.. _dataset:

Dataset
--------

The main data-related concept that |dal_short_name| works with is a
:capterm:`dataset`. It is a tabular view of data, where table rows represent the
:capterm:`observations <observation>` and columns represent the
:capterm:`features <feature>`.

.. image:: _static/dataset.png
  :width: 400
  :alt: Dataset

The dataset is used across all stages of the data analytics pipeline. For
example:

1. At the acquisition stage, it is downloaded into the
   local memory.

2. At the preparation stage, it is converted into a numerical
   representation.

3. At the computation stage, it is used as one of the :txtref:`inputs <Input>` or
   :txtref:`results <Result>` of an algorithm or a :txtref:`descriptor <descriptors>`
   properties.

.. _data-source:

Data source
-----------

Data source is a concept of an out-of-memory storage for a :capterm:`dataset`.
It is used at the data acquisition and data preparation stages to:

- Extract datasets from external sources such as databases, files, remote
  storage.

- Load datasets into the device's local memory. Data do not always fit
  the local memory, especially when processing with accelerators. A data source
  provides the ability to load data by batches and extracts it directly into the
  device's local memory. Therefore, a data source enables complex data analytics
  scenarios, such as :capterm:`online computations <Online mode>`.

- Transform datasets into their numerical representation. Data source shall
  automatically transform non-numeric :capterm:`categorical <categorical
  feature>` and :capterm:`continuous <continuous feature>` data values into one
  of the numeric :capterm:`data formats <data format>`.

For details, see :txtref:`data-sources` section.

.. _table:

Table
-----

Table is a concept of in-memory numerical data that are organized in a tabular
view with several rows and columns. It is used at the data preparation and data
processing stages to:

- Be an in-memory representation of a :txtref:`dataset` or another tabular
  data (for example, matrices, vectors, and scalars).

- Store heterogeneous data in various
  :capterm:`data formats <data format>`, such as dense, sparse, chunked,
  contiguous.

- Avoid unnecessary data copies during conversion from external data
  representations.

- Transfer memory ownership of the data from user application to the table,
  or share it between them.

- Connect with the :txtref:`data-source` to convert data from an
  out-of-memory into an in-memory representation.

- Support streaming of the data to the algorithm.

- Access the underlying data on a device in a required :capterm:`data
  format`, e.g. by blocks with the defined :capterm:`data layout`.

.. note::
  For thread-safety reasons and better integration with external entities, a
  table provides a read-only access to the data within it, thus, table object
  shall be :capterm:`immutable <immutability>`.

This concept has different logical organization and physical :capterm:`format of
the data <data format>`:

- Logically, a table contains :math:`n` rows and :math:`p` columns.
  Every column may have its own type of data values and a set of allowed
  operations.

- Physically, a table can be organized in different ways: as a
  :capterm:`homogeneous <homogeneous data>`, :capterm:`contiguous <contiguous
  data>` array of bytes, as a :capterm:`heterogeneous <heterogeneous data>` list
  of arrays of different :capterm:`data types <data type>`, in a
  compressed-sparse-row format. The number of bytes needed to store the data
  differs from the number of elements :math:`n \times p` within a table.

For details, see :txtref:`tables` section.

.. _table_metadata:

Table metadata
--------------

Table metadata concept provides an additional information about data in the
table:

1. The :capterm:`data types <Data type>` of the columns.

2. The logical types of data in the columns:
   :capterm:`nominal <Nominal feature>`, :capterm:`ordinal <Ordinal feature>`,
   :capterm:`interval <Interval feature>`, or :capterm:`ratio <Ratio feature>`.

Only the properties of data that do not affect table concept definition shall be
the part of metadata concept.

.. warning::
  While extending the table concept, specification implementer shall distinguish
  whether a new property they are adding is a property of a particular ``table``
  sub-type or a property of table metadata.

  For example, :capterm:`data layout` and :capterm:`data format` are properties
  of table objects since they affect the structure of a table, its contract, and
  behavior. The list of names of features or columns inside the table is the
  example of metadata property.

.. _accessor:

Accessor
--------

Accessor is a concept that defines a single way to extract the data from a
:txtref:`table`. It allows to:

- Have unified access to the data from :txtref:`table` objects of different
  types, without exposing their implementation details.

- Provide a :capterm:`flat <flat data>` view on the data blocks of a
  :txtref:`table` for better data locality. For example, the accessor returns a
  column of the table stored in row-major format as a contiguous array.

- Acquire data in a desired :capterm:`data format` for which
  a specific set of operations is defined.

- Have read-only access to the data.

For details, see :txtref:`accessors` section.

Example of interaction between table and accessor objects
---------------------------------------------------------

This section provides a basic usage scenario of the :txtref:`table` and
:txtref:`accessor` concepts and demonstrates the relations between them.
:txtref:`The following diagram <table_accessor_usage_example>` shows objects
of these concepts, which are highlighted by colors:

- :txtref:`table` object is dark blue

- :txtref:`accessor` is orange

- :txtref:`table_metadata` is light blue

.. _table_accessor_usage_example:

.. image:: _static/table_accessor_usage_example.png
  :width: 800
  :alt: Sequence diagram of accessor-builder-table relations

To perform computations on a dataset, one shall create a :txtref:`table` object
first. It can be done either using a :txtref:`data-source` or directly from
user-defined memory. The diagram shows the creation of a :txtref:`table` object
`t` from the data provided by user (not shown on the diagram). During a table
creation, an object `tm` of table metadata is constructed and initialized using
the data.

Once a table object is created, it can be used as an input in computations or as
a parameter of some algorithm. The data in the table can be accessed via its own
interface or via read-only accessor as shown on the diagram.

Details
=======

This section includes the detailed descriptions of all data management objects in
|dal_short_name|.

.. toctree::

   array.rst
   accessors.rst
   data_sources.rst
   tables.rst
