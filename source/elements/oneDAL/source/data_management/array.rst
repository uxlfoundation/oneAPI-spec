.. highlight:: cpp
.. default-domain:: cpp

=====
Array
=====

The array is a simple concept over the data in |dal_short_name|. It represents
a storage that:

1. Holds the data allocated inside it or references to the external data. The
   data are organized as one :term:`homogeneous <Homogeneous data>` and
   :term:`contiguous <Contiguous data>` memory block.

2. Contains information about the memory block size.

3. Supports both :term:`immutable <Immutability>` or mutable data.

4. Provides an ability to change the data state from immutable to
   mutable one.

5. Holds ownership information on the data (see the :txtref:`data_ownership_requirements` section).

6. Ownership information on the data can be shared between several arrays - it is
   possible to create new array from another one without any data copies.

-------------
Usage example
-------------

Next listing provides a brief introduction to the array API and example of basic
usage scenario:

::

   #include <CL/sycl.hpp>
   #include <iostream>
   #include <string>
   #include "oneapi/dal/array.hpp"

   using namespace oneapi;

   void print_property(const std::string& description, const auto& property) {
      std::cout << description << ": " << property << std::endl;
   }

   int main() {
      sycl::queue queue { sycl::default_selector() };

      constexpr std::int64_t data_count = 4;
      const float data[] = { 1.0f, 2.0f, 3.0f, 4.0f };

      // Creating an array from immutable user-defined memory
      auto arr_data = dal::array<float>::wrap(data, data_count);

      // Creating an array from internally allocated memory filled by ones
      auto arr_ones = dal::array<float>::full(queue, data_count, 1.0f);

      print_property("Is arr_data mutable", arr_data.has_mutable_data()); // false
      print_property("Is arr_ones mutable", arr_ones.has_mutable_data()); // true

      // Creating new array from arr_data without data copy - they share ownership information.
      dal::array<float> arr_mdata = arr_data;

      print_property("arr_mdata elements count", arr_mdata.get_count()); // equal to data_count
      print_property("Is arr_mdata mutable", arr_mdata.has_mutable_data()); // false

      /// Copying data inside arr_mdata to new mutable memory block.
      /// arr_data still refers to the original data pointer.
      arr_mdata.need_mutable_data(queue);

      print_property("Is arr_data mutable", arr_data.has_mutable_data()); // false
      print_property("Is arr_mdata mutable", arr_mdata.has_mutable_data()); // true

      queue.submit([&](sycl::handler& cgh){
         auto mdata = arr_mdata.get_mutable_data();
         auto cones = arr_ones.get_data();
         cgh.parallel_for<class array_addition>(sycl::range<1>(data_count), [=](sycl::id<1> idx) {
            mdata[idx[0]] += cones[idx[0]];
         });
      }).wait();

      std::cout << "arr_mdata values: ";
      for(std::int64_t i = 0; i < arr_mdata.get_count(); i++) {
         std::cout << arr_mdata[i] << ", ";
      }
      std::cout << std::endl;

      return 0;
   }

.. _data_ownership_requirements:

---------------------------
Data ownership requirements
---------------------------

Its important to specify the logic how ``array`` shall manage its data:

1. Array shall hold two properties that represent raw pointers on the data:

   - ``data`` for pointer on immutable data,
   - ``mutable_data`` for pointer on mutable data (see the :txtref:`programming_interface`).

2. If array holds mutable data, both properties shall point to the same memory
   block.

3. If array holds immutable data, ``mutable_data`` shall be ``nullptr``.

4. Array shall hold **ownership information** on the data inside it:

   - the count of references, indicating how many array objects refer to the
     same memory block.

   - A **deleter**, the functionality how to free the memory block, when
     references count becomes zero.

5. Array shall create a structure with ownership information for every new
   memory block that do not associated with such information already.

6. When a new memory block is assigned to the array, ``count`` property shall be
   updated to the actual element count in the memory block.

7. Array shall decrement the number of references to the memory block then it
   goes out of the scope. If the number of references becomes zero, the
   deleter on this memory block shall be called.

8. Arrays share the data blocks. The number of references in the ownership
   information shall be equal to the number of arrays that share the data block.

.. _programming_interface:

---------------------
Programming interface
---------------------

All the ``array`` class methods can be divided into several groups:

1. Constructors that are used to create an array from external, mutable or
   immutable memory.

2. Constructors and assignment operators to create an array that shares data
   with another one.

3. The group of ``reset()`` methods to re-assign an array to another external
   memory block.

4. The group of ``reset()`` methods to re-assign an array to an internally
   allocated memory block.

5. The methods to access the data.

6. Static methods that provide simplified ways to create an array from external
   memory or by allocating it inside new object.

The following declarations defined in ``oneapi/dal/array.hpp`` within
``oneapi::dal`` namespace.

.. onedal_class:: oneapi::dal::array
