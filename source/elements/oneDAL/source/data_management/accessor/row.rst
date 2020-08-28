.. highlight:: cpp
.. default-domain:: cpp

.. _row_accessor:

============
Row accessor
============

The ``row_accessor`` class provides a read-only access to the rows of
:txtref:`table` types as :capterm:`homogeneous <homogeneous data>`,
:capterm:`contiguous <contiguous data>` array.

-------------
Usage example
-------------

::

   #include <CL/sycl.hpp>
   #include <iostream>

   #include "oneapi/dal/table/homogen.hpp"
   #include "oneapi/dal/table/row_accessor.hpp"

   using namespace oneapi;

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
      dal::row_accessor<const float> acc { t };

      auto block = acc.pull(queue, {1, 3});
      for(std::int64_t i = 0; i < block.get_count(); i++) {
         std::cout << block[i] << ", ";
      }
      std::cout << std::endl;

      sycl::free(shared_data, queue);
      return 0;
   }

---------------------
Programming interface
---------------------

The following declarations defined in ``oneapi/dal/table/row_accessor.hpp``
within ``oneapi::dal`` namespace.

.. onedal_class:: oneapi::dal::row_accessor
