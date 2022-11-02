.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Namespaces
----------

oneDPL uses :code:`namespace oneapi::dpl` for all its functionality including parallel algorithms,
oneDPL execution policies, etc. For the subset of the standard C++ library for kernels, the standard class
and function names are also aliased in :code:`namespace oneapi::dpl`. As a shortcut :code:`namespace dpl`
exists and it contains all the same functionality as :code:`namespace oneapi::dpl`.

The functionality has the same nested namespace as for :code:`std` one where applicable.
The top level namespace remains :code:`oneapi::dpl`. For example oneDPL execution policies
are available in :code:`namespace oneapi::dpl::execution`.
