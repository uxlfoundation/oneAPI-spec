.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

========================
Cpp17ParallelScanCombine
========================
**[req.cpp17_parallel_scan_combine]**

A type `Combine` satisfies `Cpp17ParallelScanCombine` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Value&, const Value&`` and return the type ``Value``
where ``Value`` is the same as passed to ``parallel_scan``.

Considering ``combine`` to be an object of type ``const Combine`` and ``x`` and ``y`` to be objects of type ``Value``,
applying ``std::invoke(combine, x, y)`` combines summaries ``x`` and ``y``.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Value`` as a reduction of ``parallel_scan``.