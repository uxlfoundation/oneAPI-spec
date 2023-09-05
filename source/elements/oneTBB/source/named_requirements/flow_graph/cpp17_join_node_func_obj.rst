.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

===========================
Cpp17JoinNodeFunctionObject
===========================
**[req.cpp17_join_node_function_object]**

A type `FunctionObject` satisfies `Cpp17JoinNodeFunctionObject` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Input&`` and return the type ``Key``
  where ``Key`` is the same as the corresponding template argument of ``join_node`` and the ``Input`` is the corresponding
  element of the ``OutputTuple`` template argument of the ``join_node``.

Considering ``f`` to be an object of type ``FunctionObject`` and ``input`` to be an object of type ``const Input&``,
applying ``std::invoke(f, input)`` returns the key to be used for hashing ``input``.

**_NOTE:_**  It allows to pass pointer-to-function or pointer-to-member of the class ``Input`` as a body of ``join_node``.