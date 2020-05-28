.. _accessors:

=========
Accessors
=========

**An accessor** is a common concept of an object that provides a specific
interface for reading and modifying the data stored in other objects. Each
accessor implementation shall satisfy the following requirements:

1. Define a single :term:`format of the data <Data format>` for the
   accessor. Every single accessor type shall return and use
   only one :term:`format of the data <Data format>` .

2. Allow it to have access to at least of one in-memory :ref:`dataset`
   implementation (such as :code:`table`, its sub-types, or :ref:`table builders
   <table-builder>`).

3. Provide read-only, write-only, or read-write access to the data. If an
   accessor supports several :ref:`dataset` implementations to be passed in, it
   is not necessary for an accessor to support all access modes for every input object. For
   example, tables shall support a single read-only mode according to their
   :ref:`concept <table>` definition.

4. Shall name reading and writing operations consistently. Their names
   shall follow these patterns: :code:`pull_*()` for a reading operation
   and :code:`push_*()` for a writing operation.

5. Shall be lightweight. Its constructors from :ref:`dataset` implementations
   shall not have heavy operations such as copy of data, reading, writing, any
   sort of conversions. These operations shall be performed by heavy operations
   :code:`pull_*()` and :code:`push_*()`. It is not necessary to have copy- or
   move- constructors for accessor implementations since it shall be designed
   for use in a local scope.

--------------
Accessor Types
--------------

|dal_short_name| defines a set of accessor classes each associated with single
way how to interact with data inside a :ref:`dataset`. Next table briefly
explains these classes and shows which :ref:`dataset` implementations are
supported by each accessor.

.. list-table::
   :header-rows: 1
   :widths: 10 45 45

   * - Accessor type
     - Description
     - List of supported types
   * - row_accessor_
     - Provides an access to the range of dataset rows as one :term:`contiguous
       <Contiguous data>` and :term:`homogeneous <Homogeneous data>` block of memory.
     - :code:`homogen_table`, :code:`soa_table`, :code:`aos_table`,
       :code:`csr_table`, and their builders.
   * - column_accessor_
     - Provides an access to the values range of a single column as one
       :term:`contiguous <Contiguous data>` and :term:`homogeneous <Homogeneous
       data>` block of memory.
     - :code:`homogen_table`, :code:`soa_table`, :code:`aos_table`,
       :code:`csr_table`, and their builders.


.. _row_accessor:

------------
Row accessor
------------

TBD

.. _column_accessor:

---------------
Column accessor
---------------

TBD
