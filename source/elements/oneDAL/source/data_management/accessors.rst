.. highlight:: cpp
.. default-domain:: cpp

.. _accessors:

=========
Accessors
=========

This section defines :txtref:`requirements <accessor_reqs>` to an
:txtref:`accessor` implementation and introduces several
:txtref:`accessor_types`.

.. _accessor_reqs:

------------
Requirements
------------

Each accessor implementation shall:

1. Define a single :term:`format of the data <Data format>` for the
   access. Every single accessor type shall return and use only one data format.

2. Provide read-only access to the data in the :txtref:`table` types.

3. Provide the :code:`pull()` operation for obtaining the values from the table.

4. Be lightweight. Its constructors shall not have heavy operations such as copy
   of data, reading, any sort of conversions. These operations shall be
   performed by method :code:`pull()`. It is not necessary to have copy- or
   move- constructors for accessor implementations since it shall be designed
   for use in a local scope.

5. Method :code:`pull()` shall avoid data copies and conversions when it is
   possible to use memory directly from the table.


.. _accessor_types:

--------------
Accessor Types
--------------

|dal_short_name| defines a set of accessor classes. Each class is associated
with a single specific way of interacting with data within a :txtref:`table`.

All accessor classes in |dal_short_name| are listed below:

.. list-table::
   :header-rows: 1
   :widths: 25 50 25

   * - Accessor type
     - Description
     - List of supported types
   * - :txtref:`row_accessor`
     - Provides access to the range of rows as one :term:`contiguous
       <Contiguous data>` :term:`homogeneous <Homogeneous data>` block of memory.
     - :code:`homogen_table`
   * - :txtref:`column_accessor`
     - Provides access to the range of values within a single column as one
       :term:`contiguous <Contiguous data>` :term:`homogeneous <Homogeneous
       data>` block of memory.
     - :code:`homogen_table`

-------
Details
-------

.. toctree::

   accessor/column.rst
   accessor/row.rst
