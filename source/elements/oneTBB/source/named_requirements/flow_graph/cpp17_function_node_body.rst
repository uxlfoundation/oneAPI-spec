.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
Cpp17FunctionNodeBody
=====================
**[req.cpp17_function_node_body]**

A type `Body` satisfies `Cpp17FunctionNodeBody` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Input&`` and return the type ``Output``
  where ``Input`` and ``Output`` are corresponding template arguments of the ``function_node``.

Considering ``body`` to be an object of type ``Body`` and ``input`` to be an object of type ``const Input&``,
applying ``std::invoke(body, input)`` performs operation on the value ``input``.

**_NOTE:_**  It allows to pass pointer-to-function or pointer-to-member of the class ``Input`` as a body of ``function_node``.