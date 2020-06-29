.. _data_management:


===============
Data management
===============

This section includes descriptions of concepts and objects that operate on data.
For |dal_short_name|, such set of operations, or **data management**, is
distributed between different stages of the :txtref:`data analytics pipeline
<data_analytics_pipeline>`. From a perspective of data management, this pipeline
contains three main steps of data acquisition, preparation, and computation (see
:txtref:`the picture below <typical_data_management_flow>`):

1. Raw data acquisition

  - Transfer out-of-memory data from various sources (databases, files, remote
    storages) into an in-memory representation.

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
:capterm:`dataset`. It is an in-memory or out-of-memory tabular view of data,
where table rows represent the :capterm:`observations <observation>` and columns
represent the :capterm:`features <feature>`.

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
It is used at the data acquisition and data preparation stages for the
following:

- To extract datasets from external sources such as databases, files, remote
  storages.

- To load datasets into the device's local memory. Data do not always fit
  the local memory, especially when processing with accelerators. A data source
  provides the ability to load data by batches and extracts it directly into the
  device's local memory. Therefore, a data source enables complex data analytics
  scenarios, such as :capterm:`online computations <Online mode>`.

- To filter and normalize :capterm:`feature` values that are being extracted.

- To recover missing :capterm:`feature` values.

- To detect :capterm:`outliers <outlier>` and recover the abnormal data.

- To transform datasets into numerical representation. Data source shall
  automatically transform non-numeric :capterm:`categorical <categorical
  feature>` and :capterm:`continuous <continuous feature>` data values into one
  of the numeric :capterm:`data formats <data format>`.

For details, see :txtref:`data-sources` section.

.. _table:

Table
-----

Table is a concept of a :capterm:`dataset` with in-memory numerical data. It is
used at the data preparation and data processing stages for the following:

- To store heterogeneous in-memory data in various
  :capterm:`data formats <data format>`, such as dense, sparse, chunked,
  contiguous.

- To avoid unnecessary data copies during conversion from external data
  representations.

- To transfer memory ownership of the data from user application to the table,
  or share it between them.

- To connect with the :txtref:`data-source` to convert from an out-of-memory
  into an in-memory dataset representation.

- To support streaming of the data to the algorithm.

- To access the underlying data on a device in a required :capterm:`data
  format`, e.g. by blocks with the defined :capterm:`data layout`.

For thread-safety reasons and better integration with external entities, a table
provides a read-only access to the data within it, thus, table concept
implementations shall be :capterm:`immutable <immutability>`.

This concept has different logical organization and physical :capterm:`format of
the data <data format>`:

- Logically, a table is a :txtref:`dataset` with :math:`n` rows and
  :math:`p` columns. Each row represents an :capterm:`observation` and each
  column is a :capterm:`feature` of a dataset. Physical amount of bytes needed
  to store the data differ from the number of elements :math:`n \times p` within
  a table.

- Physically, a table can be organized in different ways: as a
  :capterm:`homogeneous <homogeneous data>`, :capterm:`contiguous <contiguous
  data>` array of bytes, as a :capterm:`heterogeneous <heterogeneous data>` list
  of arrays of different :capterm:`data types <data type>`, in a
  compressed-sparse-row format.

For details, see :txtref:`tables` section.

.. _metadata:

Metadata
--------

Metadata concept is assotiated with a :txtref:`dataset` and holds information
about its structure and type. This information shall be enough to determine the
particular type of a dataset, and it helps to understand how to interact with a
dataset in |dal_short_name| (for example, how to use it at a particular stage of
:txtref:`data analytics pipeline <data_analytics_pipeline>` or how to access its
data).

For each dataset, its metadata shall contain:

- The number of rows :math:`n` and columns :math:`p` in a dataset.

- The type of each :capterm:`feature` (e.g. :capterm:`nominal <nominal
  feature>`, :capterm:`interval <interval feature>`).

- The :capterm:`data type` of each feature (e.g. :code:`float` or
  :code:`double`).

.. note::
  Metadata can contain both compile-time and run-time information. For example,
  basic compile-time metadata is the type of a dataset - whether it is a
  particular :txtref:`data-source` or a :txtref:`table`. Run-time information
  can contain the :capterm:`feature` types and :capterm:`data types <data type>`
  of a dataset.

.. _table-builder:

Table builder
-------------

A table :capterm:`builder` is a concept that is associated with a particular
:txtref:`table` type and is used at the data preparation and data processing
stages for:

- Iterative construction of a :txtref:`table` from another :txtref:`<table>s` or
  a different in-memory :txtref:`dataset` representations.

- Construction of a :txtref:`table` from different entities that hold blocks of
  data, such as arrays, pointers to the memory, external entities.

- Changing dataset values. Since :txtref:`table` is an
  :capterm:`immutable <immutability>` dataset, a builder provides the ability to
  change the values in a dataset under construction.

- Encapsulating construction process of a :txtref:`table`. This is used to hide the
  implementation details as they are irrelevant for users. This also allow to
  select the most appropriate table implementation for each particular case.

- Providing additional information on how to create a :txtref:`table` inside an
  algorithm for :txtref:`<result>s`. This information includes metadata, memory
  allocators that shall be used, or even a particular table implementation.

For details, see :txtref:`table-builders` section.

.. _accessor:

Accessor
--------

Accessor is a concept that defines a single way to get the data from an
in-memory numerical :txtref:`dataset`. It allows:

- To have unified access to the data from various sets of different objects,
  such as :txtref:`<table>s` or :txtref:`<table-builder>s`,
  without exposing their implementation details.

- To convert a variety of numeric :capterm:`data formats <data format>` into a
  smaller set of formats.

- To provide a :capterm:`flat <flat data>` view on the data blocks of a
  :txtref:`dataset` for better a data locality. For example, some accessor
  implementation returns :capterm:`feature` values as a contiguous array, while
  the original dataset stored row-by-row (there are strides between values of a
  single feature).

- To acquire data in a desired :capterm:`data format` for which
  a specific set of operations is defined.

- To have read-only, read-write and write-only access to the data. Accessor
  implementations are not required to have read-write and write-only access
  modes for :capterm:`immutable <immutability>` entities like
  :txtref:`<table>s`.

For details, see :txtref:`accessors` section.

Use-case example for table, accessor and table builder
------------------------------------------------------

This section provides a basic usage scenario of the :txtref:`table`,
:txtref:`table-builder`, and :txtref:`accessor` concepts and demonstrates the
relations between them. :txtref:`The following diagram
<data_management_sequence_diagram>` shows objects of these concepts, which are
highlighted by colors:

- :txtref:`Table builder <table-builder>` objects are blue.

- :txtref:`Table <table>` objects are cyan.

- :txtref:`Accessors <Accessor>` are yellow.

- Grey objects are not a part of |dal_short_name| specification and they are
  provided just for illustration purposes.

.. _data_management_sequence_diagram:

.. image:: _static/table_builder_accessor_sequence.png
  :width: 800
  :alt: Sequence diagram of accessor-builder-table relations

To perform computations on a dataset, one shall create a :txtref:`table` object
first. It can be done using a :txtref:`data-source` or a :txtref:`table-builder`
object depending on the situation. The diagram briefly shows the situation when
:txtref:`table` is interatively created from a various external entities (not
shown on a diagram) using a :txtref:`table-builder`.

Once a table object is created, the data inside it can be accessed by its own
interface or with a help of a read-only accessor as shown on the diagram. The
table can be used as an input in computations or as a parameter of some
algorithm.

Algorithms' results also contain table objects. If one needs to change the data
within some table, a builder object can be constructed for this. Data inside a
table builder can be retrieved by read-only, write-only or read-write accessors.

Accessors shown on the diagram allow to get data from tables and table builders
as :capterm:`flat <flat data>` blocks of rows.

Details
=======

.. toctree::

   data_sources.rst
   tables.rst
   table_builders.rst
   accessors.rst
