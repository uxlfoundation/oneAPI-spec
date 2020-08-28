.. _homogen_table:

=================
Homogeneous table
=================

Class ``homogen_table`` is an implementation of a table type
for which the following is true:

- The data within the table are dense and stored as one contiguous memory block.
- All the columns have the same :capterm:`data type <Data type>`.

---------------------
Programming interface
---------------------

The following declarations are defined in ``oneapi/dal/table/homogen.hpp``
within ``oneapi::dal`` namespace.

.. onedal_class:: oneapi::dal::homogen_table
