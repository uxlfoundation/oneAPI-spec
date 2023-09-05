.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
Cpp17ParallelScanFunc
=====================
**[req.cpp17_parallel_scan_func]**

A type `Func` satisfies `Cpp17ParallelScanFunc` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Range&, const Value&, bool`` and return the type ``Value``
where ``Range`` and ``Value`` are the same as passed to ``parallel_scan``.

Considering ``func`` to be an object of type ``const Func``, ``range`` to be an object of type ``Range``, ``sum`` be an object of type ``Value``
and ``is_final`` be an object of type ``bool``,
applying ``std::invoke(func, range, sum, is_final)`` starting with ``sum``, computes the summary and, for ``is_final == true``,
the scan result for range ``range``. Returns the computed summary.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Range`` as a body of ``parallel_scan``.