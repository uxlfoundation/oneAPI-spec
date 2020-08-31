=======================
Common type definitions
=======================

This section describes common types used in |dal_short_name|.

---------------------
Programming interface
---------------------

All types and functions in this section shall be declared in the
``oneapi::dal`` namespace and be available via inclusion of the
``oneapi/dal/common.hpp`` header file.

.. _scalar_types:

Scalar types
------------

|dal_short_name| relies on standard C++ scalar types defined in ``<cstdint>``.
This file shall be included in ``oneapi/dal/common.hpp`` and all
|dal_short_name| types shall use this scalar types. For variables indicating
size, amount, count of entities, ``std::int64_t`` type shall be used.

It is recommended to use standard C++ type for applications as well.

Enum classes
------------

It is up to |dal_short_name| implementer when to set particular base type of
``enum`` or ``enum class`` type implementing |dal_short_name| concept unless it
is explicitly specified.

Data type
---------

The implementation of :capterm:`data type` concept. It shall enumerate all the
data types supported by |dal_short_name| to perform computations. The
``data_type`` class shall contain all the :txtref:`scalar_types` and can extend
it.

.. onedal_enumclass:: oneapi::dal::data_type


Range
-----

The range ``[start_index, end_index)`` in the array or another container that
supports value indexing.

.. onedal_class:: oneapi::dal::range
