.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_generate:

generate
========


Entry point to obtain random numbers from a given engine with proper statistics of a given distribution.


.. contents::
    :local:
    :depth: 1

API
***


Syntax
------

.. code-block:: cpp

   template<typename Distr, typename Engine>
   auto generate(Distr& distr, Engine& engine) ->
     typename std::conditional<Engine::vec_size == 1, typename Distr::result_type,
                               sycl::vec<typename Distr::result_type, Engine::vec_size>>::type


Include Files
-------------

- ``oneapi/mkl/rng/device.hpp``


Input Parameters
----------------

.. list-table::
      :header-rows: 1

      * - Name
        - Type
        - Description
      * - distr
        - Distr&
        - Distribution object. See :ref:`onemkl_device_rng_distributions` for details.
      * - engine
        - Engine&
        - Engine object. See :ref:`onemkl_device_rng_engines` for details.


Output Parameters
-----------------

.. list-table::
      :header-rows: 1

      * - Name
        - Type
        - Description
      * - result
        - ``sycl::vec<typename Distr::result_type``, ``Engine::vec_size>`` or typename ``Distr::result_type``
        - Function returns ``sycl::vec`` of type specified by the Distribution object and vector size specified by the Engine object filled with random numbers or a scalar random number in case ``vec_size`` =1.
