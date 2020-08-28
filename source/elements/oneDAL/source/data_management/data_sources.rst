.. highlight:: cpp
.. default-domain:: cpp

.. _data-sources:

============
Data Sources
============

This section describes the types related to the :txtref:`data-source` concept.

====
Read
====

**Read operation** is a function that transforms a data source and other arguments represented via `an args <args_>`_ object
to `a result <result_>`_ object. An operation responsible for:

- Execution of all data retrieval and transformation routines of the data source.

- Passing SYCL* queue to data retrieval and transformation routines.

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

- Shortcut for execution on :term:`host <Host/Device>`. Performs the same
  operation as the general function on host, but does not require passing the
  queue explicitly.

  .. code-block:: cpp

     template <typename DatasetType, typename DataSource>
     read_result_t<DatasetType, DataSource> read(
        const DataSource& data_source,
        const read_args_t<DatasetType, DataSource>& args);

- Shortcut that allows omitting explicit args creation.

  .. code-block:: cpp

     template <typename DatasetType, typename DataSource, typename... Args>
     read_result_t<DatasetType, DataSource> read(
        sycl::queue& queue,
        const DataSource& data_source,
        Args&&... args);

- Shortcut that allows omitting explicit queue and args creation. This is
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

---------------
CSV data source
---------------
Class ``csv::data_source`` is an API for accessing the data source represented as a :capterm:`csv file <CSV file>`.
CSV data source shall be used with :expr:`read` operation to extract data in text format from the given input file,
process it using provided parameters (such as delimiter and read options), transform it into numerical representation,
and store it as an in-memory :txtref:`dataset` of a chosen type.

Supported type of in-memory dataset for :expr:`read` operation with CSV data source is :txtref:`table`.

CSV data source requires input file name to be set in the constructor,
while the other parameters of the constructor such as delimiter and read options rely on default values.

Usage example
-------------
::

   const auto data_source = onedal::csv::data_source("data.csv", ',');

   const auto table = ondedal::read<onedal::table>(data_source);


Programming Interface
---------------------
All types and functions in this section shall be declared in the
``oneapi::dal::csv`` namespace and be available via inclusion of the
``oneapi/dal/io/csv.hpp`` header file.

::

   enum class read_options : std::uint32_t {
      default = 0,
      parse_header = 1 << 0
   };

   class data_source {
   public:
      static constexpr char default_delimiter = ',';
      static constexpr read_options default_read_options = read_options::default;

      data_source(const char *file_name,
                  char delimiter = default_delimiter,
                  read_options opts = default_read_options);

      data_source(const std::string &file_name,
                  char delimiter = default_delimiter,
                  read_options opts = default_read_options);

      std::string get_file_name() const;
      char get_delimiter() const;
      read_options get_read_options() const;
   };

.. namespace:: onedal::csv
.. class:: data_source

   .. function:: data_source(const char *file_name, char delimiter = default_delimiter, read_options opts = default_read_options)

      Creates a new instance of a CSV data source with the given :expr:`file_name`, :expr:`delimiter` and read options :expr:`opts` flag.

   .. function:: data_source(const std::string &file_name, char delimiter = default_delimiter, read_options opts = default_read_options);

      Creates a new instance of a CSV data source with the given :expr:`file_name`, :expr:`delimiter` and read options :expr:`opts` flag.

   .. member:: std::string file_name = ""

      String which contains name of the file with the dataset to read.

      Getter
         | ``std::string get_filename() const``

   .. member:: char delimiter = ','

      Symbol that represents delimiter between separate features in the input file.

      Getter
         | ``char get_delimter() const``

   .. member:: read_options options = read_options::default

      Value that stores read options to be applied during reading of the input file.
      Enabled ``parse_header`` option indicates that the first line in the input file shall be processed
      as a header record with features names.

      Getter
         | ``read_options get_read_options() const``


Reading :expr:`onedal::read<DatasetType>(...)`
------------------------------------------------

Args
~~~~
::

   template <typename DatasetType>
   class read_args {
   public:
      read_args();
   };

.. namespace:: oneapi::dal::csv
.. class:: template <typename DatasetType> \
           read_args

   .. function:: read_args()

      Creates args for the read operation with the default attribute
      values.

Operation
~~~~~~~~~

Supported value of the :code:`DatasetType` template parameter for :expr:`read` operation with CSV data source is :code:`onedal::table`.

.. namespace:: onedal
.. function:: template <typename DatasetType, typename DataSource> \
              DatasetType read(const DataSource& ds)

   :tparam DatasetType: oneDAL dataset type that shall be produced as a result of reading from the data source.
   :tparam DataSource: CSV data source :expr:`csv::data_source`.
