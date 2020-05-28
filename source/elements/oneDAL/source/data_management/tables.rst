.. highlight:: cpp

.. _tables:

======
Tables
======

This section describes the types related to the :ref:`table <table>` concept.
|dal_short_name| defines types of the table and the :ref:`metadata <metadata>`
concepts associated with it:

- The :code:`table` is a base class that implements the table concept and
  provides its metadata. Each implementation of the :ref:`table <table>` concept
  shall be derived from the :code:`table` class (for more details, see
  :ref:`table_api`).

- The :code:`table_meta` class implements the metadata concept for the
  table. This type can be extended in the types derived from the table (for more
  details, see :ref:`Metadata API`).


------------
Requirements
------------

Each type that implements :ref:`table <table>` concept in |dal_short_name|
shall:

1. Follow definition of the table concept.

2. Be derived from the :code:`table` class. The behavior of this class can be
   extended, but cannot be relaxed.

3. Provide an implementation of the :ref:`metadata <metadata>` concept derived
   from the :code:`table_meta` class.

4. Be :term:`reference-counted <Reference-counted object>`. An assignment
   operator or copy constructor shall be used to create another reference to the
   same data.

   .. code-block:: cpp

      onedal::table table2 = table1;
      // table1 and table2 share the same data (no data copy is performed)

      onedal::table table3 = table2;
      // table1, table2 and table3 share the same data


-----------
Table Types
-----------

|dal_short_name| defines a set of classes. Each class implements the :ref:`table
<table>` concept and represents a specific data format.

.. list-table::
   :header-rows: 1
   :widths: 10 70

   * - Table type
     - Description

   * - :ref:`table <table_api>`
     - A common implementation of the table concept. Base class for
       other table types.

   * - homogen_table_
     - Dense table that contains :term:`contiguous <Contiguous data>`
       :term:`homogeneous <Homogeneous data>` data.

   * - soa_table_
     - Dense heterogeneous table which data are stored column-by-column in list
       of contiguous arrays (structure-of-arrays format).

   * - aos_table_
     - Dense heterogeneous table which data are stored as one contiguous block
       of memory (array-of-structures format).

   * - csr_table_
     - Sparse homogeneous table which data stored in compressed sparse row (CSR)
       format.

.. _table_api:

---------
Table API
---------
::

   class table {
   public:
      table() = default;

      template <typename TableImpl,
               typename = std::enable_if_t<is_table_impl_v<TableImpl>>>
      table(TableImpl&&);

      table(const table&);
      table(table&&);

      table& operator=(const table&);

      std::int64_t get_feature_count() const noexcept;
      std::int64_t get_observation_count() const noexcept;
      bool is_empty() const noexcept;
      const dal::table_meta& get_metadata() const noexcept;
   };

.. namespace:: onedal
.. class:: table

   .. function:: table()

      Creates an empty table with no data and ``table_meta`` constructed by default

   .. function:: table(TableImpl&&)

      Creates a table object using the entity passed as a parameter

      :tparam TableImpl: The class that contains the table's implementation

      Invariants
         | contract ``is_table_impl`` is satisfied

   .. function:: table(const table&)

      Creates new reference object on the table data

   .. function:: table(table&&)

      Moves one table object into another

   .. function:: table& operator=(const table&)

      Sets the current object reference to point to another one

   .. member:: std::int64_t feature_count = 0

      The number of :term:`features <Feature>` :math:`p` in the table.

      Getter
         | ``std::int64_t get_feature_count() const noexcept``

      Invariants
         | ``feature_count >= 0``

   .. member:: std::int64_t observation_count = 0

      The number of :term:`observations <Observation>` :math:`N` in the table.

      Getter
         | ``std::int64_t get_observation_count() const noexcept``

      Invariants
         | ``observation_count >= 0``

   .. member:: bool is_empty = true

      If ``feature_count`` or ``observation_count`` are zero, the
      table is empty.

      Getter
         | ``bool is_empty() const noexcept``

   .. member:: table_meta metadata = table_meta()

      The object that represents data structure inside the table

      Getter
         | ``const dal::table_meta& get_metadata() const noexcept``

      Invariants
         | ``is_empty = false``

.. _homogen_table:

Homogeneous table
-----------------
Class ``homogen_table`` is an implementation of a table type
for which the following is true:

- Its data is dense and it is stored as one contiguous memory block
- All features have the same :ref:`data type <Data type>`
  (but :ref:`feature types <Feature type>` may differ)

::

   class homogen_table : public table {
   public:
      // TODO:
      // Consider constructors with user-provided allocators & deleters

      homogen_table(const homogen_table&);
      homogen_table(homogen_table&&);

      homogen_table(std::int64_t N, std::int64_t p, data_layout layout);

      template <typename T>
      homogen_table(const T* const data_pointer, std::int64_t N, std::int64_t p, data_layout layout);

      homogen_table& operator=(const homogen_table&);

      data_type get_data_type() const noexcept;
      bool has_equal_feature_types() const noexcept;

      template <typename T>
      const T* get_data_pointer() const noexcept;
   };

.. namespace:: onedal
.. class:: homogen_table

   .. function:: homogen_table(const homogen_table&)

      Creates new reference object on the table data

   .. function:: homogen_table(homogen_table&&)

      Moves current reference object into another one

   .. function:: homogen_table(std::int64_t N, std::int64_t p, data_layout layout)

      Creates a homogeneous table of shape :math:`N \times p` with
      default |dal_short_name| allocator

   .. function:: homogen_table(const T* const data_pointer, std::int64_t N, std::int64_t p, data_layout layout)

      :tparam T: The type of pointer to the data

      Creates a homogeneous table of shape :math:`N \times p` with
      the user-defined data. Uses the provided pointer to access data (no copy is performed).

   .. function:: homogen_table& operator=(const homogen_table&)

      Sets the current object reference to point to another

   .. member:: onedal::data_type data_type

      The type of underlying data

      Getter
         | ``data_type get_data_type() const noexcept``

   .. member:: bool feature_types_equal

      Flag that indicates whether or not the `feature_type` fields
      of `metadata` are all equal

      Getter
         | ``bool has_equal_feature_types() const noexcept``

   .. member:: const T* data_pointer

      :tparam T: The type of pointer to the data

      The pointer to underlying data

      Getter
         | ``const T* get_data_pointer() const noexcept``

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

      std::int64_t get_feature_count() const noexcept;
      table_meta& set_feature_count(std::int64_t);

      const feature_info& get_feature(std::int64_t index) const;
      table_meta& add_feature(const feature_info&);

      data_layout get_layout() const noexcept;
      table_meta& set_layout(data_layout);

      bool is_contiguous() const noexcept;
      table_meta& set_contiguous(bool);

      bool is_homogeneous() const noexcept;

      data_format get_format() const noexcept;
      table_meta& set_format(data_format);
   };

.. namespace:: onedal
.. class:: table_meta

   .. member:: std::int64_t feature_count = 0

      The number of :term:`features <Feature>` :math:`p` in the table.

      Getter & Setter
         | ``std::int64_t get_feature_count() const noexcept``
         | ``table_meta& set_feature_count(std::int64_t)``

      Invariants
         | ``feature_count >= 0``

   .. member:: feature_info feature

      Information about a particular :term:`feature <Feature>` in the table

      Getter & Setter
         | ``const feature_info& get_feature(std::int64_t index) const``
         | ``table_meta& add_feature(const feature_info&)``

   .. member:: data_layout layout = data_layout::row_major

      Flag that indicates whether the data is in a row-major or column-major format.

      Getter & Setter
         | ``data_layout get_layout() const noexcept``
         | ``table_meta& set_layout(data_layout)``

   .. member:: bool is_contiguous = true

      Flag that indicates whether the data is stored in contiguous blocks of memory by
      the axis of ``layout``.
      For example, if ``is_contiguous == true`` and ``data_layout`` is ``row_major``,
      the data is stored contiguously in each row.

      Getter & Setter
         | ``bool is_contiguous() const noexcept``
         | ``table_meta& set_contiguous(bool)``

   .. function:: bool is_homogeneous() const noexcept

      Returns true if all features have the same ``data_type``

   .. member:: data_format format = data_format::dense

      Description of the format used for data representation inside the table

      Getter & Setter
         | ``data_format get_format() const noexcept``
         | ``table_meta& set_format(data_format)``

.. _Data layout API:

Data layout
-----------
::

   enum class data_layout : std::int64_t {
      row_major,
      column_major
   };

.. namespace:: onedal
.. class:: data_layout

   Structure that represents underlying data layout

.. _Data format API:

Data format
-----------
::

   enum class data_format : std::int64_t {
      dense,
      csr
   };

.. namespace:: onedal
.. class:: data_format

   Structure that represents underlying format of the data

Feature info
------------
::

   class feature_info {
   public:
      feature(data_type, feature_type);

      data_type get_data_type() const noexcept;
      feature_type get_type() const noexcept;
   };

.. namespace:: onedal
.. class:: feature_info

   Structure that represents information about particular :term:`feature <Feature>`

   Invariants:
      | ``feature_type::nominal`` or ``feature_type::ordinal``
        are available only with integer ``data_type``
      | ``feature_type::contiguous`` available only with floating-point ``data_type``

.. _Data type:

Data type
---------
::

   enum class data_type : std::int64_t {
      u32, u64
      i32, i64,
      f32, f64
   };

.. namespace:: onedal
.. class:: data_type

   Structure that represents runtime information about feature data type.

   |dal_short_name| supports next data types:

   - ``std::uint32_t``
   - ``std::uint64_t``
   - ``std::int32_t``
   - ``std::int64_t``
   - ``float``
   - ``double``

.. _Feature type:

Feature type
------------
::

   enum class feature_type : std::int64_t {
      nominal,
      ordinal,
      contiguous
   };

.. namespace:: onedal
.. class:: feature_type

   Structure that represents runtime information about feature logical type.

   feature_type::nominal
      Discrete feature type, non-ordered

   feature_type::ordinal
      Discrete feature type, ordered

   feature_type::contiguous
      Contiguous feature type
