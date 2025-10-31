.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_vm_exceptions:

Exceptions
==========


.. container::

    All VM mathematical functions throw exceptions in exceptional cases.
    The following table summarizes the conditions.

    +----------------------------------+------------------------------------+
    |  exception                       |   when thrown                      |
    +----------------------------------+------------------------------------+
    | oneapi::mkl::invalid_argument    | buffer API:                        |
    |                                  |  n < 0;                            |
    |                                  |                                    |
    |                                  |  y.get_count() < n;                |
    |                                  |                                    |
    |                                  |  z.get_count() < n; // for sincos  |
    |                                  |                                    |
    |                                  +------------------------------------+
    |                                  | USM API:                           |
    |                                  |  n < 0;                            |
    |                                  |                                    |
    |                                  |  any pointer argument is nullptr   |
    +----------------------------------+------------------------------------+
    | oneapi::mkl::host_bad_alloc      | USM API:                           |
    |                                  |  when internal copying to and      |
    |                                  |  from  host memory is used         |
    |                                  |  and corresponding allocation      |
    |                                  |  fails                             |
    +----------------------------------+------------------------------------+
    | oneapi::mkl::device_bad_alloc    | USM API:                           |
    |                                  |  when internal copying to and      |
    |                                  |  from device memory is used        |
    |                                  |  and corresponding allocation      |
    |                                  |  fails                             |
    +----------------------------------+------------------------------------+

