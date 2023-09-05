.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

============================
Cpp17ParallelReduceReduction
============================
**[req.cpp17_parallel_reduce_reduction]**

A type `Reduction` satisfies `Cpp17ParallelReduceReduction` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Value&, const Value&`` and return the type ``Value``
where ``Value`` is the same as passed to ``parallel_reduce``.

Considering ``reduction`` to be an object of type ``const Reduction`` and ``x`` and ``y`` to be objects of type ``const Value&``,
applying ``std::invoke(reduction, x, y)`` combines results ``x`` and ``y``.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Value`` as a reduction of ``parallel_reduce``.