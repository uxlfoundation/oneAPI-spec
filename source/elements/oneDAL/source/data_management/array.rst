.. highlight:: cpp
.. default-domain:: cpp

=====
Array
=====

The array is a simple concept over the data in |dal_short_name|. It represents
storage with the following characteristics:

1. Data inside the array are organized as one :term:`homogeneous <Homogeneous
   data>` and :term:`contiguous <Contiguous data>` memory block.
2. The array knows about memory block size.
3. The array can hold either :term:`immutable <Immutability>` or mutable data.
4. The array can change the data state from immutable to mutable one.
5. Array holds ownership information on the data: the references count
   (how many arrays refer to the same data block) and a deleter used to free the
   data when references count becomes zero.
6. Ownership information on the data can be shared between several arrays. It is
   possible to create new array from another one without any data copies: they
   will share reference count and a deleter object.

-------------
Usage example
-------------

Next listing provides a brief introduction to the array API and example of basic
usage scenario:

::

   #include <CL/sycl.hpp>
   #include <iostream>
   #include "oneapi/dal/array.hpp"

   using namespace oneapi;

   int main() {
      sycl::queue queue { sycl::default_selector() };

      constexpr std::int64_t data_count = 4;
      const float data[] = { 1.0f, 2.0f, 3.0f, 4.0f };

      // Creating array from immutable user-defined memory.
      // No data copy is performed.
      auto arr_data = dal::array<float>::wrap(data, data_count);

      // Creating an array of data_count elements filled by ones
      // This array holds mutable data allocated internally on the device
      // specified by queue. Filling operation is also performed on the device.
      // Data are allocated with sycl::alloc::shared kind
      auto arr_ones = dal::array<float>::full(queue, data_count, 1.0f);

      std::cout << "Is arr_data mutable: "
                << arr_data.has_mutable_data() << std::endl; // false
      std::cout << "Is arr_ones mutable: "
                << arr_ones.has_mutable_data() << std::endl; // true

      // Creating new array from arr_data - they share owning information,
      // no data copy is performed.
      dal::array<float> arr_mdata = arr_data;

      std::cout << "arr_mdata elements count: "
                << arr_mdata.get_count() << std::endl; // equal to data_count
      std::cout << "Is arr_data mutable: "
                << arr_data.has_mutable_data() << std::endl; // false

      // Both arrays refer to the original data pointer:
      // arr_mdata.get_data() == arr_data.get_data() == data
      // If we want to modify data of arr_mdata, we need to make it mutable:
      arr_mdata.need_mutable_data(queue);

      // Now arr_mdata holds internal mutable copy of data,
      // while arr_data still refers to the original pointer
      std::cout << "Is arr_data mutable: "
                << arr_data.has_mutable_data() << std::endl; // false
      std::cout << "Is arr_mdata mutable: "
                << arr_mdata.has_mutable_data() << std::endl; // true

      queue.submit([&](sycl::handler& cgh){
         auto mdata = arr_mdata.get_mutable_data();
         auto cones = arr_ones.get_data();
         cgh.parallel_for<class array_addition>(sycl::range<1>(data_count), [=](sycl::id<1> idx) {
            mdata[idx[0]] += cones[idx[0]];
         });
      }).wait();

      std::cout << "arr_mdata values: ";
      for(std::int64_t i = 0; i < arr_mdata.get_count(); i++) {
         std::cout << arr_mdata[i] << ", "; // array has overloaded operator[] for immutable access
      }
      std::cout << std::endl;

      return 0;
   }

---------------------
Programming interface
---------------------

Defined in ``oneapi/dal/array.hpp``

Namespace ``oneapi::dal``

.. onedal_class:: oneapi::dal::array
