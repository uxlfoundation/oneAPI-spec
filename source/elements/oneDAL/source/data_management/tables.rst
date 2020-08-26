.. highlight:: cpp

.. _tables:

======
Tables
======

This section describes the types related to the :txtref:`table` concept.

|dal_short_name| defines a set of classes that implement the
:txtref:`table` concept and represents a specific data format:

.. list-table::
   :header-rows: 1
   :widths: 10 70

   * - Table type
     - Description

   * - :txtref:`table <table_programming_interface>`
     - A common implementation of the table concept. Base class for
       other table types.

   * - homogen_table_
     - Dense table that contains :term:`contiguous <Contiguous data>`
       :term:`homogeneous <Homogeneous data>` data.

The :txtref:`table` concept bound with other concepts and terms like
:txtref:`table_metadata` or :capterm:`data layout`. |dal_short_name| defines
next types for these table-related terms:

.. list-table::
   :header-rows: 1
   :widths: 10 70

   * - Type
     - Description

   * - :txtref:`table_metadata <metadata_programming_interface>`
     - An implementation of :txtref:`table_metadata` concept.

   * - data_layout_
     - An enumeration of :capterm:`data layouts<data layout>` used to store
       contiguous data blocks inside the table.

   * - feature_type_
     - An enumeration of :capterm:`feature` types used in |dal_short_name| to
       define set of available operations onto the data.

---------------------------
Requirements on table types
---------------------------

Each implementation of :txtref:`table` concept shall:

1. Follow definition of the :txtref:`table concept <table>` and its restrictions
   (e.g., :capterm:`immutability`).

2. Be derived from the :code:`table` class. The behavior of this class can be
   extended, but cannot be weaken.

3. Be :term:`reference-counted <Reference-counted object>`.

4. Every new :code:`table` sub-type shall define a unique id number - the "kind"
   that represents objects of that type in runtime.

Next listing provides an example of table API regarding kinds and copy-assignment operation:

.. code-block:: cpp

  using namespace onedal;

  // Creating homogen_table sub-type.
  dal::homogen_table table1 = homogen_table::wrap(queue, data_ptr, row_count, column_count);

  // table1 and table2 share the same data (no data copy is performed)
  dal::table table2 = table1;

  // Creating an empty table
  dal::table table3;

  std::cout << table1.get_kind()     == table2.get_kind() << std::endl; // true
  std::cout << homogen_table::kind() == table2.get_kind() << std::endl; // true
  std::cout << table2.get_kind()     == table3.get_kind() << std::endl; // false

  // Referring table3 to the table2.
  table3 = table2;
  std::cout << table2.get_kind() == table3.get_kind() << std::endl; // true


.. _table_programming_interface:

-----
Table
-----

A base implementation of :txtref:`table` concept.

Programming interface
---------------------

.. onedal_class:: oneapi::dal::table

.. _homogen_table:

-----------------
Homogeneous table
-----------------

Class ``homogen_table`` is an implementation of a table type
for which the following is true:

- Its data is dense and it is stored as one contiguous memory block.
- All columns have the same :capterm:`data type <Data type>`.

Programming interface
---------------------

.. onedal_class:: oneapi::dal::homogen_table

.. _metadata_programming_interface:

--------------
Table metadata
--------------

An implementation of :txtref:`table_metadata` concept. Holds additional
information about data inside the table, that is not a part of table concept.

Programming interface
---------------------

.. onedal_class:: oneapi::dal::table_metadata

.. _data_layout:

-----------
Data layout
-----------

An implementation of :capterm:`data layout` term.

Programming interface
---------------------

::

   enum class data_layout { unknown, row_major, column_major };

.. namespace:: oneapi::dal
.. enum-class:: data_layout

   data_layout::unknown
      Represents the :capterm:`data layout` that is undefined or unknown at this moment.

   data_layout::row_major
      The data block elements are stored row-by-row.

   data_layout::column_major
      The data block elements are stored column-by-column.

.. _feature_type:

------------
Feature type
------------

An implementation of data logical types.

Programming interface
---------------------

::

   enum class feature_type { nominal, ordinal, interval, ratio };

.. namespace:: oneapi::dal
.. enum-class:: feature_type

   feature_type::nominal
      Represents the type of :capterm:`Nominal feature`.

   feature_type::ordinal
      Represents the type of :capterm:`Ordinal feature`.

   feature_type::interval
      Represents the type of :capterm:`Interval feature`.

   feature_type::ratio
      Represents the type of :capterm:`Ratio feature`.
