.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==========================
Cpp17MultifunctionNodeBody
==========================
**[req.cpp17_multifunction_node_body]**

A type `Body` satisfies `Cpp17MultifunctionNodeBody` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Input&, OutputPortsType&`` and return the type ``void``
  where ``Input`` is the corresponding template argument of the ``multifunction_node``. The ``OutputPortsType`` is the same as the ``output_ports_type`` member type
  of the ``multifunction_node``.

Considering ``body`` to be an object of type ``Body``, ``input`` to be an object of type ``const Input&`` and ``output_ports``` to be an object of type ``OutputPortsType&``,
applying ``std::invoke(body, input, output_ports)`` performs operation on ``input``. May call ``try_put()`` on zero or more of the output ports in ``output_ports``.
May call ``try_put()`` on any output port multiple times.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Input`` as a body of ``multifunction_node``.