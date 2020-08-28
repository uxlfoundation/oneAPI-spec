.. highlight:: cpp
.. default-domain:: cpp

.. _data-sources:

============
Data Sources
============

This section describes the types related to the :txtref:`data-source` concept.

Read
====

**Read operation** is a function that transforms a data source and other arguments represented via `an args <args_>`_ object
to `a result <result_>`_ object. The operation is responsible for:

- Executing all of the data retrieval and transformation routines of the data source.

- Passing a SYCL* queue to the data retrieval and transformation routines.

.. _read_operation_definition:

-------------------------
Read operation definition
-------------------------
`The following code sample <read_operation_template_>`_ shows the declaration for a
read operation.

.. code-block:: cpp
   :name: read_operation_template

   namespace oneapi::dal {

   template <typename DatasetType, typename DataSource>
   using read_args_t = /* implementation defined */;

   template <typename DatasetType, typename DataSource>
   using read_result_t = DatasetType;

   template <typename DatasetType, typename DataSource>
   read_result_t<DatasetType, DataSource> read(
      sycl::queue& queue,
      const DataSource& data_source,
      const read_args_t<DatasetType, DataSource>& args);

   } // namespace oneapi::dal


Each operation shall satisfy the following requirements:

- An operation shall accept three parameters in the following order:

  + The SYCL* queue object.
  + The data source.
  + The `args object <args_>`_.

- An operation shall return the `result object <result_>`_.

- The ``read_args_t`` and ``read_result_t`` alias
  templates shall be used for inference of the args and return types.

------------------------
Read operation shortcuts
------------------------
In order to make the code on user side less verbose, oneDAL defines the
following overloaded functions called *shortcuts* for a read operation in addition
to the general one described in section `Read operation definition
<read_operation_definition_>`_.

- A shortcut for execution on :term:`host <Host/Device>`. Performs the same
  operation as the general function on host, but does not require passing the
  queue explicitly.

  .. code-block:: cpp

     template <typename DatasetType, typename DataSource>
     read_result_t<DatasetType, DataSource> read(
        const DataSource& data_source,
        const read_args_t<DatasetType, DataSource>& args);

- A shortcut that allows omitting explicit args creation.

  .. code-block:: cpp

     template <typename DatasetType, typename DataSource, typename... Args>
     read_result_t<DatasetType, DataSource> read(
        sycl::queue& queue,
        const DataSource& data_source,
        Args&&... args);

- A shortcut that allows omitting explicit queue and args creation. This is a
  combination of two previous shortcuts.

  .. code-block:: cpp

     template <typename DatasetType, typename DataSource, typename... Args>
     read_result_t<DatasetType, DataSource> read(
        const DataSource& data_source,
        Args&&... args);


.. _args:

----
Args
----

- The string ``%DATA_SOURCE%`` should be substituted with the name of the data source, for example, ``csv``. 

- ``%PROPERTY_NAME%`` and ``%PROPERTY_TYPE%`` should be substituted with the name and the type of one
  of the data source args properties.

.. code-block:: cpp

   namespace oneapi::dal::%DATA_SOURCE% {

   template <typename DatasetType, typename DataSource>
   class read_args {
   public:
      read_args(
         const %PROPERTY_TYPE_1%& property_name_1,
         const %PROPERTY_TYPE_2%& property_name_2,
         /* more properties */
      )
      /* Getter & Setter for the property called `%PROPERTY_NAME_1%` */
      descriptor& set_%PROPERTY_NAME_1%(%PROPERTY_TYPE_1% value);
      %PROPERTY_TYPE_1% get_%PROPERTY_NAME_1%() const;
      /* Getter & Setter for the property called `%PROPERTY_NAME_2%` */
      descriptor& set_%PROPERTY_NAME_2%(%PROPERTY_TYPE_2% value);
      %PROPERTY_TYPE_2% get_%PROPERTY_NAME_2%() const;
      /* more properties */
   };
   } // namespace oneapi::dal::%DATA_SOURCE%


------
Result
------

The result of a :expr:`read` operation is an instance of an in-memory dataset with :code:`DatasetType` type.

Data Source Types
=================

|dal_short_name| defines a set of classes.

.. list-table::
   :header-rows: 1
   :widths: 10 70

   * - Data source type
     - Description

   * - :txtref:`CSV data source <csv-data-source>`
     - Data source that allows reading data from a text file into a :txtref:`table`.

Details
=======

.. toctree::

   csv_data_source.rst
