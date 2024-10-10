.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Namespaces
----------

oneDPL uses ``namespace oneapi::dpl`` and a shorter variant ``namespace dpl`` for all
functionality including parallel algorithms, oneDPL execution policies, etc.
For the subset of the standard C++ library for kernels, the standard class
and function names are also aliased in ``namespace oneapi::dpl``.

oneDPL uses nested namespaces for the functionality aligned with the C++ standard.
The names of those namespaces are the same as in ``namespace std``. For example,
oneDPL execution policies are provided in ``namespace oneapi::dpl::execution``.
