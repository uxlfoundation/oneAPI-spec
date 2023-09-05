.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

========================
Cpp17ParallelForFunction
========================
**[req.cpp17_parallel_for_function]**

A type `Func` satisfies `Cpp17ParallelForFunction` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``Index`` and return the type ``void``
where ``Index`` type is the same as passed to ``parallel_for``.

Considering ``func`` to be an object of type ``const Func`` and ``index`` to be an object of type ``Index``,
applying ``std::invoke(func, index)`` applies a function to the index.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Range`` as a body of ``parallel_for``.