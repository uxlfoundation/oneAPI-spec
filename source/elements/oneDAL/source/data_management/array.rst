.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

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

2. Contains information about the memory block's size.

3. Supports both :term:`immutable <Immutability>` and mutable data.

4. Provides an ability to change the data state from immutable to
   mutable one.

5. Holds ownership information on the data (see the :txtref:`data_ownership_requirements` section).

6. Ownership information on the data can be shared between several arrays. It is
   possible to create a new array from another one without any data copies.

-------------
Usage example
-------------

The following listing provides a brief introduction to the array API and an example of basic
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

The array shall satisfy the following requirements on managing the memory blocks:

1. An array represents either immutable or mutable data.

2. An array shall retain:

   -  Pointer to the immutable data block;

   -  Pointer to the mutable data block.

3. If an array represents mutable data, both pointers shall point to the mutable data block.

4. If an array represents immutable data, pointer to the mutable data shall be ``nullptr``.

5. An array shall use shared ownership semantics to manage lifetime of the stored data blocks:

   - Several arrays objects may own the same data block;

   - The memory block is deallocated when either of the following happens:

     - The last remaining array owning data block is destroyed;

     - The last remaining array owning data block is assigned another memory block via
       ``operator=`` or ``reset()``;

   - The data block is deallocated using the deleter object that is provided to array during
     construction.

6. An array object may own no data. In this case, it is called **empty**:

   - Pointers to the immutable and mutable data of the empty array shall be ``nullptr``;
   - The data block size shall be ``0``.


.. _implementation_notes:

--------------------
Implementation notes
--------------------

1. An array implementation holds the following member variables:

   - Pointer to the immutable data;

   - Pointer to the mutable data;

   - Pointer to the ownership structure;

   - The data block size;

2. The ownership structure is an object that stores:

   - Either a pointer immutable or mutable data block:

     - If an array represents the immutable data, pointer to immutable data;

     - If an array represents the mutable data, pointer to mutable data;

   - The deleter object;

   - The reference counter (the number of array instances that owns the associated data block);

3. The destructor of an array decrements the reference counter. If that counter reaches zero, the
   ownership structure deallocates the associated memory block and the ownership structure instance is
   destoryed itself.

4. If the array object changes its state from immutable to mutable via ``need_mutable_data()``,
   the reference counter of the ownership structure is decremented. If that counter reaches zero,
   the ownership structure deallocates the immutable memory block and the ownership structure
   instance is destoryed itself. The new instance of ownership structure owning the mutable data
   block is created and replaces the old one.


.. _programming_interface:

---------------------
Programming interface
---------------------

All types and functions in this section shall be declared in the
``oneapi::dal`` namespace and be available via inclusion of the
``oneapi/dal/array.hpp`` header file.

All the ``array`` class methods can be divided into several groups:

1. Constructors that are used to create an array from external, mutable or
   immutable memory.

2. Constructors and assignment operators that are used to create an array that shares its data
   with another one.

3. The group of ``reset()`` methods that are used to re-assign an array to another external
   memory block.

4. The group of ``reset()`` methods that are used to re-assign an array to an internally
   allocated memory block.

5. The methods that are used to access the data.

6. Static methods that provide simplified ways to create an array either from external
   memory or by allocating it within a new object.

.. onedal_class:: oneapi::dal::array
