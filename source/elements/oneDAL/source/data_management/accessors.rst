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

2. Provide read-only, write-only, or read-write access to the data. If an
   accessor supports several object types to be passed in,
   it is not necessary for an accessor to support all access modes for every
   input object. For example, tables shall support a single read-only mode
   according to their :txtref:`<table> concept` definition.


3. Provide the names for available operations following the pattern:

   - :code:`pull_*()` for obtaining values from accessed object.

   - :code:`push_*()` for updating the accessed object data.

4. Be lightweight. Its constructors shall not have heavy operations such as copy
   of data, reading, writing, any sort of conversions. These operations shall be
   performed by methods :code:`pull_*()` and :code:`push_*()`. It is not
   necessary to have copy- or move- constructors for accessor implementations
   since it shall be designed for use in a local scope.

5. Methods :code:`pull_*()` and :code:`push_*()` shall avoid data copies and
   conversions when it is possible to use memory directly from the accessed object.


.. _accessor_types:

--------------
Accessor Types
--------------

|dal_short_name| defines a set of accessor classes. Each class is associated
with a single specific way of interacting with data within a :txtref:`table`.

Below are listed all accessor classes in |dal_short_name|:

.. list-table::
   :header-rows: 1
   :widths: 10 45 45

   * - Accessor type
     - Description
     - List of supported types
   * - row_accessor_
     - Provides access to the range of rows as one :term:`contiguous
       <Contiguous data>` :term:`homogeneous <Homogeneous data>` block of memory.
     - :code:`homogen_table`
   * - column_accessor_
     - Provides access to the range of values within a single column as one
       :term:`contiguous <Contiguous data>` :term:`homogeneous <Homogeneous
       data>` block of memory.
     - :code:`homogen_table`

Usage example
-------------

Next listing provides a brief introduction of ``row_accessor`` and
``column_accessor`` APIs and example of how to use them with ``homogen_table``.

::

   #include <CL/sycl.hpp>
   #include <iostream>

   #include "oneapi/dal/table/homogen.hpp"
   #include "oneapi/dal/table/row_accessor.hpp"
   #include "oneapi/dal/table/column_accessor.hpp"

   using namespace onedal;

   int main() {
      sycl::queue queue { sycl::default_selector() };

      constexpr float host_data[] = {
         1.0f, 1.5f, 2.0f,
         2.1f, 3.2f, 3.7f,
         4.0f, 4.9f, 5.0f,
         5.2f, 6.1f, 6.2f
      };

      constexpr std::int64_t row_count = 4;
      constexpr std::int64_t column_count = 3;

      auto shared_data = sycl::malloc_shared<float>(row_count * column_count, queue);
      auto event = queue.memcpy(shared_data, host_data, sizeof(float) * row_count * column_count);
      auto t = dal::homogen_table::wrap(queue, data, row_count, column_count, { event });

      // Accessing second and third rows of the table
      {
         dal::row_accessor<const float> acc { t };
         auto block = acc.pull(queue, {1, 3});
         for(std::int64_t i = 0; i < block.get_count(); i++) {
            std::cout << block[i] << ", ";
         }
         std::cout << std::endl;
      }

      // Accessing whole elements in a first column
      {
         dal::column_accessor<const float> acc { t };
         auto block = acc.pull(queue, 0);
         for(std::int64_t i = 0; i < block.get_count(); i++) {
            std::cout << block[i] << ", ";
         }
         std::cout << std::endl;
      }

      sycl::free(shared_data, queue);
      return 0;
   }

.. _row_accessor:

Row accessor programming interface
----------------------------------

Defined in ``oneapi/dal/table/row_accessor.hpp``

Namespace ``oneapi::dal``

.. onedal_class:: oneapi::dal::row_accessor

.. _column_accessor:

Column accessor programming interface
-------------------------------------

Defined in ``oneapi/dal/table/column_accessor.hpp``

Namespace ``oneapi::dal``

.. onedal_class:: oneapi::dal::column_accessor
