.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_generate_single:

generate_single
===============


Entry point to obtain a single random number from a given vector engine with proper statistics of a given distribution.


.. contents::
    :local:
    :depth: 1


API
***


Syntax
------

.. code-block:: cpp

   template<typename Distr, typename Engine>
   typename Distr::result_type generate_single(Distr& distr, Engine& engine)


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

      * -     Name
        -     Type
        -     Description
      * -     result
        -     typename ``Distr::result_type``
        -     Function returns a scalar random number, may be used for engines with ``vec_size`` > 1.


