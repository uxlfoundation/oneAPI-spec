.. _table-builders:

==============
Table Builders
==============

This section contains definitions of classes that implement :ref:`table-builder`
concept.

------------
Requirements
------------

Each implementation of :ref:`table-builder` concept in |dal_short_name| shall
follow next requirements:

1. Provide an ability to create single :ref:`table` concept implementation.
   Every builder shall be associated with a single table type.

2. Shall be stateful object, which state can be used to access data inside
   builder via :ref:`accessors <Accessors>` or to create a table object.

3. Shall implement :code:`build()` member function, that creates a new table
   object based on the current snapshot of a builder state.


-------------------
Table Builder Types
-------------------

|dal_short_name| defines a set of accessor classes each associated with single
:ref:`table` implementation.

.. list-table::
   :header-rows: 1

   * - Table builder type
     - Description
   * - simple_homogen_table_builder_
     - Allows to create :ref:`homogen_table` from standart containers.
   * - simple_soa_table_builder_
     - Allows to create :ref:`soa_table` from standart containers.

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
