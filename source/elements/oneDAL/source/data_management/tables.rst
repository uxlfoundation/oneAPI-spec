.. highlight:: cpp

======
Tables
======

Table is a generic |dal_short_name| concept over numerical data. It provides uniformed way
to pass the data to the library as *inputs* or *parameters* or get them as *results*.

Table object is a container of two entities: *data* and *metadata*.

- *Data* are organized in a shape of :math:`(N \times p)`,
  where :math:`N` is a number of observations in a table and :math:`p`
  is a number of *features*. Each feature has :math:`N` values of concrete
  data type, while any two features can have different data types.

- *Metadata* defines detailed structure of the data and therefore
  |dal_short_name| knows how to access them efficiently (see :ref:`Metadata API` section for details).

-------------------------------
Table types in |dal_short_name|
-------------------------------
|dal_short_name| defines a set of classes, each implement table contact for a restricted set of metadata values:

.. list-table::
  :header-rows: 1

  * - Table type
    - Data layout
    - Data format
    - Is continuous
    - Is homogeneous
  * - homogen_table_
    - row_major/column_major
    - dense
    - yes
    - yes
  * - soa_table_
    - column_major
    - dense
    - yes
    - yes/no
  * - aos_table_
    - row_major
    - dense
    - yes
    - yes/no
  * - csr_table_
    - row_major
    - csr
    - yes
    - yes

-----------------------------
Requirements on table objects
-----------------------------
Each table object in |dal_short_name| must follow next requirements:

1. Table objects in |dal_short_name| are **immutable**. This means, when created, it is not possible
   to change data or metadata values inside the table. To create compex table types,
   *builders* can be used.

2. Table objects in |dal_short_name| are **reference-counted**. One can use assignment operator on table
   objects to create another reference on it. Hense no data copy is made.

3. Every table type must be inherited from the base ``table`` class, which represents
   a generalized table API. (see :ref:`Table API` for details)

4. Every table type is implemented over particular set of metadata values and must hide other
   implementation details from public API.

.. _Table API:

---------
Table API
---------
::

   class table {
   public:
      table() = default;

      template <typename TableImpl,
               typename = std::enable_if_t<is_table_contract_v<TableImpl>>>
      table(TableImpl&&);

      table(const table&);
      table(table&&);

      table& operator=(const table&);

      int64_t get_feature_count() const noexcept;
      int64_t get_observation_count() const noexcept;
      bool is_empty() const noexcept;
      const dal::table_meta& get_metadata() const noexcept;
   };

TableImpl ``template``
   The class, containing some table implementation

   Invariants
      | contract ``is_table_contract`` is satisfied

feature_count ``int64_t`` ``default = 0``
   The number of features :math:`p` in the table.

   Invariants
      | ``feature_count >= 0``

observation_count ``int64_t`` ``default = 0``
   The number of observations :math:`N` in the table.

   Invariants
      | ``observation_count >= 0``

is_empty ``bool`` ``default = true``
   If ``feature_count`` or ``observation_count`` are zero, the
   table is empty.

metadata ``table_metadata`` ``default = table_metadata()`` ``[read-only]``
   The object represents data structure inside the table

   Invariants
      | ``is_empty = false``

.. _homogen_table:

Homogeneous table
-----------------
Class ``homogen_table`` is an implementation of table which data:

- Are dense and stored as one continuous memory block
- All features have the same data type (but feature types may differ)

::

   class homogen_table : public table {
   public:
      homogen_table(const homogen_table&);
      homogen_table(homogen_table&&);

      homogen_table(int64_t N, int64_t p, data_layout layout);

      template <typename T>
      homogen_table(T* data_pointer, int64_t N, int64_t p, data_layout layout);

      homogen_table& operator=(const homogen_table&);

      data_type get_data_type() const noexcept;
      bool is_feature_types_equal() const noexcept;

      template <typename T>
      const T* get_data_pointer() const noexcept;
   };

data_type ``data_type`` ``[read-only]``
   The actual type of underlying data

feature_types_equal ``bool``
   Flag indication whether the `feature_type` fields
   of `metadata` are all equal

data_pointer ``const T*``
   The pointer to underlying data

.. _soa_table:

Structure-of-arrays table
-------------------------
TBD

.. _aos_table:

Arrays-of-structure table
-------------------------
TBD

.. _csr_table:

Compressed-sparse-row table
---------------------------
TBD

.. _Metadata API:

------------
Metadata API
------------
Table metadata contains structures describing how the data
are stored inside the table and how efficiently access them.

::

   class table_meta {
   public:
      table_meta();

      int64_t get_feature_count() const noexcept;
      table_meta& set_features_count(int64_t);

      const feature_info& get_feature(std::int64_t index) const;
      table_meta& add_feature(const feature_info&);

      data_layout get_layout() const noexcept;
      table_meta& set_layout(data_layout);

      bool is_continuous() const noexcept;
      table_meta& set_continuous(bool);

      bool is_homogeneous() const noexcept;

      data_format get_format() const noexcept;
      table_meta& set_format(data_format);
   };

feature_count ``int64_t`` ``default = 0``
   The number of features :math:`p` in the table.

   Invariants
      | ``feature_count >= 0``

feature ``feature_info``
   An info about particular feature in the table

layout ``data_layout`` ``default = data_layout::row_major``
   Flag indicating whether the data are in C or Fortran format.

is_continuous ``bool`` ``default=true``
   Indicates whether the data are stored in continuous blocks of memory by
   the axis of ``layout``.
   E.g., if ``is_continuous == true`` and ``data_layout`` is ``row_major``,
   the data are stored continuously in each row.

is_homogeneous ``bool`` ``default=true``
   True if all features has the same ``data_type``

format ``data_format`` ``default=dense``
   Description of format used for data representation inside the table

Data layout
-----------
::

   enum class data_layout : std::int64_t {
      row_major,
      column_major
   };

Data format
-----------
::

   enum class data_format : std::int64_t {
      dense,
      csr
   };

Feature info
------------
::

   class feature_info {
   public:
      feature(data_type, feature_type);

      data_type get_data_type() const noexcept;
      feature_type get_type() const noexcept;
   };

feature_info
   Invariants:
      | ``feature_type::nominal`` or ``feature_type::ordinal``
        are avaliable only with integer ``data_type``
      | ``feature_type::continuous`` avaliable only with floating-point ``data_type``

Data type
---------
Structure representing runtime information about feature data type.

|dal_short_name| supports signed/unsigned 32/64 bit integer types
and 32/64 bit floating point types for table data.

::

   enum class data_type : std::int64_t {
      u32, u64
      i32, i64,
      f32, f64
   };

Feature type
------------
Structure representing runtime information about feature logical type.

::

   enum class feature_type : std::int64_t {
      nominal,
      ordinal,
      continuous
   };

feature_type::nominal
   Discrete feature type, non-ordered

feature_type::ordinal
   Discrete feature type, ordered

feature_type::continuous
   Continuous feature type
