.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

====================
Cpp17ParallelForBody
====================
**[req.cpp17_parallel_for_body]**

A type `Body` satisfies `Cpp17ParallelForBody` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``Range&`` and return the type ``void``
  where ``Range`` type is the same as passed to ``parallel_for``.

  Considering ``body`` to be an object of type ``const Body`` and ``range`` to be an object of type ``Range&``,
  applying ``std::invoke(body, range)`` applies a body to the given range.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Range`` as a body of ``parallel_for``.