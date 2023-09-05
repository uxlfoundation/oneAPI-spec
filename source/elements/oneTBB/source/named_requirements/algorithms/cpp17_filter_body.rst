.. SPDX-FileCopyrightText: 2019-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=============================================
Cpp17MiddleFilterBody and Cpp17LastFilterBody
=============================================
**[req.cpp17_parallel_for_function]**

Cpp17MiddleFilterBody
---------------------

A type `Filter` satisfies `Cpp17MiddleFilterBody` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``InputType`` and return the type ``OutputType``
where ``InputType`` and ``OutputTypes`` type is the same as passed to ``filter``.

Considering ``filter`` to be an object of type ``const Filter`` and ``input`` to be an object of type ``InputType``,
applying ``std::invoke(filter, input)`` processes the received item and then returns it.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``InputType`` as a body of ``parallel_pipeline``.

Cpp17LastFilterBody
-------------------

A type `Filter` satisfies `Cpp17LastFilterBody` if it meets
the `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``InputType`` and return the type ``void``
where ``InputType`` and ``OutputTypes`` type is the same as passed to ``filter``.

Considering ``filter`` to be an object of type ``const Filter`` and ``input`` to be an object of type ``InputType``,
applying ``std::invoke(filter, input)`` processes the received item.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``InputType`` as a body of ``parallel_pipeline``.
