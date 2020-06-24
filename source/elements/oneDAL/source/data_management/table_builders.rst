.. _table-builders:

==============
Table Builders
==============

This section contains definitions of classes that implement
:txtref:`table-builder` concept.

------------
Requirements
------------

Each implementation of :txtref:`table-builder` concept shall:

1. Provide the ability to create a single :txtref:`table` concept
   implementation. Each builder shall be associated with a single table type.

2. Be a stateful object which state is used to access data inside
   builder via :txtref:`accessors` or to create a table object.

3. Provide :code:`build()` member function that creates a new table
   object based on the current snapshot of a builder state.


-------------------
Table Builder Types
-------------------

|dal_short_name| defines a set of accessor classes each associated with a single
:txtref:`table` implementation.

.. list-table::
   :header-rows: 1

   * - Table builder type
     - Description
   * - simple_homogen_table_builder_
     - Allows to create :txtref:`homogen_table <homogen_table>` from raw
       pointers and standard C++ smart pointers.
   * - simple_soa_table_builder_
     - Allows to create :txtref:`soa_table <soa_table>` from raw pointers and
       standard C++ smart pointers.

.. _simple_homogen_table_builder:

--------------------------------
Simple Homogeneous Table Builder
--------------------------------

TBD

.. _simple_soa_table_builder:

------------------------
Simple SOA Table Builder
------------------------

TBD
