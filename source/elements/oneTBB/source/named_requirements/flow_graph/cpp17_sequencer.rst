.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==============
Cpp17Sequencer
==============
**[req.cpp17_sequencer]**

A type `Sequencer` satisfies `Cpp17FunctionNodeBody` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const T&`` and return the type ``size_t``
  where ``T`` is the corresponding template argument of the ``sequencer_node``.

Considering ``s`` to be an object of type ``Sequencer`` and ``v`` to be an object of type ``const T&``,
applying ``std::invoke(s, v)`` returns the sequence number for the provided message ``v``.

**_NOTE:_**  It allows to pass pointer-to-function or pointer-to-member of the class ``T`` as a body of ``sequencer_node``.