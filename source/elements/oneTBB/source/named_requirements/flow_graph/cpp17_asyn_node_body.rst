.. SPDX-FileCopyrightText: 2019-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==================
Cpp17AsyncNodeBody
==================
**[req.cpp17_async_node_body]**

A type `Body` satisfies `Cpp17AsyncNodeBody` if it meets the following requirements:

* The `CopyConstructible` requirements from [copyconstructible] ISO C++ Standard section
* The `Destructible` requirements from [destructible] ISO C++ Standard section
* The `Callable` requirements from [func.wrap.func] ISO C++ Standard section for arguments types ``const Input&, GatewayType&`` and return the type ``void``
  where ``Input`` is the corresponding template argument of the ``async_node``. The ``GatewayType`` is the same as the ``gateway_type`` member type
  of the ``async_type``.

Considering ``body`` to be an object of type ``Body``, ``v`` to be an object of type ``const Value&`` and ``gateway`` be an object of type ``GatewayType&``
applying ``std::invoke(body, v, gateway)`` submits the value ``v`` to the external activity.
The :doc:`gateway interface <gateway_type>` allows the external activity to communicate
with the enclosing flow graph.

**_NOTE:_**  It allows to pass pointer-to-function of the class ``Input`` as a body of ``async_node``.