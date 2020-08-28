.. highlight:: cpp
.. default-domain:: cpp

.. _data-sources:

============
Data Sources
============

This section describes the types related to the :txtref:`data-source` concept.

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

-------------
Usage example
-------------
::

   const auto data_source = onedal::csv::data_source("data.csv", ',');

   const auto table = ondedal::read<onedal::table>(data_source);


---------------------
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

Result
~~~~~~

The result of a :expr:`read` operation is an instance of an in-memory dataset with :code:`DatasetType` type.

Operation
~~~~~~~~~

Supported value of :code:`DatasetType` template parameter for :expr:`read` operation with CSV data source is :code:`onedal::table`.

.. namespace:: onedal
.. function:: template <typename DatasetType, typename DataSource> \
              DatasetType read(const DataSource& ds)

   :tparam DatasetType: oneDAL dataset type that shall be produced as a result of reading from the data source.
   :tparam DataSource: CSV data source :expr:`csv::data_source`.
