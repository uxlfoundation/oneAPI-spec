.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=======================
Cpp17ParallelReduceFunc
=======================
**[req.cpp17_parallel_reduce_func]**

A type `Func` satisfies `Cpp17ParallelReduceFunc` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Range&, const Value&`` and return the type ``Value``
where ``Range`` and ``Value`` are the same as passed to ``parallel_reduce``.

Considering ``func`` to be an object of type ``const Func``, ``range`` to be an object of type ``const Range&`` and ``value`` to be an object of type ``const Value&``,
applying ``std::invoke(func, range, value)`` accumulates the result fot a subrange ``range`` starting with the initial value ``value``.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Range`` as a body of ``parallel_reduce``.