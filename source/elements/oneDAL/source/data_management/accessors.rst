.. _accessors:

=========
Accessors
=========

This section defines `requirements <accessor_reqs_>`_ to an :ref:`accessor
<accessor>` implementation and introduces several `accessor types
<accessor_types_>`_.

.. _accessor_reqs:

------------
Requirements
------------

Each accessor implementation shall:

1. Define a single :term:`format of the data <Data format>` for the
   accessor. Every single accessor type shall return and use only one data
   format.

2. Provide an access to at least one in-memory :ref:`dataset` implementation
   (such as :code:`table`, its sub-types, or :ref:`table builders
   <table-builder>`).

3. Provide read-only, write-only, or read-write access to the data. If an
   accessor supports several :ref:`dataset` implementations to be passed in, it
   is not necessary for an accessor to support all access modes for every input
   object. For example, tables shall support a single read-only mode according
   to their :ref:`concept <table>` definition.

4. Provide the names for read and write operations following the pattern:

   - :code:`pull_*()` for reading

   - :code:`push_*()` for writing

5. Be lightweight. Its constructors from :ref:`dataset` implementations
   shall not have heavy operations such as copy of data, reading, writing, any
   sort of conversions. These operations shall be performed by heavy operations
   :code:`pull_*()` and :code:`push_*()`. It is not necessary to have copy- or
   move- constructors for accessor implementations since it shall be designed
   for use in a local scope.


.. _accessor_types:

--------------
Accessor Types
--------------

|dal_short_name| defines a set of accessor classes. Each class is associated
with a single specific way of interacting with data within a :ref:`dataset`. The
following table briefly explains these classes and shows which :ref:`dataset`
implementations are supported by each accessor type.

.. list-table::
   :header-rows: 1
   :widths: 10 45 45

   * - Accessor type
     - Description
     - List of supported types
   * - row_accessor_
     - Provides access to the range of dataset rows as one :term:`contiguous
       <Contiguous data>` :term:`homogeneous <Homogeneous data>` block of memory.
     - :code:`homogen_table`, :code:`soa_table`, :code:`aos_table`,
       :code:`csr_table`, and their builders.
   * - column_accessor_
     - Provides access to the range of values within a single column as one
       :term:`contiguous <Contiguous data>` :term:`homogeneous <Homogeneous
       data>` block of memory.
     - :code:`homogen_table`, :code:`soa_table`, :code:`aos_table`,
       :code:`csr_table`, and their builders.


.. _row_accessor:

Row accessor
------------

TBD

.. _column_accessor:

Column accessor
---------------

TBD
