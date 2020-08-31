============
Common types
============

This section describes common types of |dal_short_name|.

---------------------
Programming interface
---------------------

All types and functions in this section shall be declared in the
``oneapi::dal`` namespace and be available via inclusion of the
``oneapi/dal/common.hpp`` header file.

Data type
---------

The implementation of :capterm:`data type` concept. It shall enumerate all the
data types supported by |dal_short_name| to perform computations.

.. onedal_enumclass:: oneapi::dal::data_type


Range
-----

The range ``[start_index, end_index)`` in some sequence of elements.

.. onedal_class:: oneapi::dal::range
