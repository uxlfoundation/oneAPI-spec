=================
Memory management
=================

This section describes common memory management types in |dal_short_name|.

---------------------
Programming interface
---------------------

All types and functions in this section shall be declared in the
``oneapi::dal`` namespace and be available via inclusion of the
``oneapi/dal/memory.hpp`` header file.

Empty delete
------------

The function object that does nothing and can be used as empty deleter for
|dal_short_name| objects and their data.

.. onedal_class:: oneapi::dal::empty_delete

Default delete
--------------

The function objects used to free the array of elements of type ``Data``.

.. onedal_class:: oneapi::dal::default_delete

The helper function that creates ``default_delete`` object using SYCL* queue.

.. onedal_func:: oneapi::dal::make_default_delete


