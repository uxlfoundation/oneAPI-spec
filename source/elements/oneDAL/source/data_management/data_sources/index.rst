.. highlight:: cpp
.. default-domain:: cpp

=======
Data Sources
=======

Data source is a concept of an out-of-memory storage for a :capterm:`dataset`.
It is used at the data acquisition and data preparation stages for the
following:

- To extract datasets from external sources such as databases, files, remote
  storage.

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

CSV data source
-----------------
Class ``csv::data_source`` is an api for accessing the data source represented as csv file.
A comma-separated values file (csv) is a text file. Each line of the csv file is a record, containing fields separated by the delimiter.
Fields can have numerical or text format, where text usually refers to some categorized values.
Delimiter is a comma by default, but generally can be any given symbol.
For more details, see <https://en.wikipedia.org/wiki/Comma-separated_values>.

::

::

   class data_source {
   public:
      csv_data_source(const char *file_name);
      csv_data_source(const std::string &file_name);

      char get_delimiter() const;
      bool get_parse_header() const;
      std::string get_file_name() const;

      csv_data_source& set_delimiter(char);
      csv_data_source& set_parse_header(bool);
      csv_data_source& set_file_name(const char *);
      csv_data_source& set_file_name(const std::string &);
   };

.. namespace:: onedal::csv
.. class:: data_source

   .. function:: data_source(const char *file_name)

      Creates new instance of csv data source with the given :expr:`file_name`, the
      other attributes get default values.

   .. function:: data_source(const std::string &file_name)

      Creates new instance of csv data source with the given :expr:`file_name`, the
      other attributes get default values.

   .. member:: char delimiter = ','

      Symbol that represents delimiter between continuous feature columns in the input file.

      Getter & Setter
         | ``char get_delimter() const``
         | ``data_source& set_delimiter(char)``

   .. member:: bool parse_header = false

      Flag that indicates whether or not first line in the input file should be processed
      as a header record which contains information about features and should not be included in the dataset.

      Getter & Setter
         | ``bool get_parse_header() const``
         | ``data_source& set_parse_header(bool)``

   .. member:: std::string file_name = ""

      String which contains name of the file with the dataset for read.

      Getter & Setter
         | ``std::string get_filename() const``
         | ``data_source& set_file_name(const char *)``
         | ``data_source& set_file_name(const std::string &)``

-------------
Usage example
-------------
::

   const auto data_source = onedal::csv::data_source("data.csv")
      .set_delimiter(',');

   const auto table = ondedal::read<onedal::table>(data_source);


Reading :expr:`onedal::read<onedal::table>(...)`
-----------------------------------
Args
~~~~~
::

   template<>
   class read_args<onedal::table> {
   public:
      read_args();

   };

.. class:: template<> read_args<onedal::table>

   .. function:: read_args()

      Creates arguments for the table reading operation with the default attribute
      values.

Result
~~~~~~

Result of a read operation with a specified :code:`onedal::table` template parameter is a :txtref:`table`.

Operation semantics
~~~~~~~~~~~~~~~~~~~

Supported type of data objects (referred as Object template parameter) for :expr:`read` operation is :expr:`Object = onedal::table`.

.. namespace:: onedal
.. function:: template <typename Object, typename DataSource> \
              Object read(const DataSource& ds)

   :tparam Object: oneDAL data object that should be produced as a result of reading data from the data source.
   :tparam DataSource: CSV data source :expr:`csv::data_source`.

   Preconditions

   Postconditions

.. namespace:: onedal
.. function:: template <typename Object, typename DataSource> \
              Object read(const DataSource& ds, \
                          const csv::read_args& args)

   :tparam Object: oneDAL data object that should be produced as a result of reading data from the data source.
   :tparam DataSource: CSV data source :expr:`csv::data_source`.

   Preconditions

   Postconditions
