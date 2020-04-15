==================
Named Requirements
==================
**[general_information.named_requirements]**

This section describes named requirements used in the oneAPI Threading Building Blocks Specification.

A *named requirement* is a set of requirements on a type. The requirements may be syntactic or semantic.
The *named_requirement* term is similar to “Requirements on types and expressions” term which is defined
by the ISO C++ Standard (chapter “Library Introduction”) or `“Named Requirements” section <https://en.cppreference.com/w/cpp/named_req>`_
on the cppreference.com site.

For example, the named requirement of *sortable* could be defined as a set of requirements that enable
an array to be sorted. A type ``T`` would be *sortable* if:

* ``x < y`` returns a boolean value, and represents a total order on items of type ``T``.
* ``swap(x,y)`` swaps items ``x`` and ``y``

You can write a sorting template function in C++ that sorts an array of any type that is *sortable*.

Two approaches for defining named requirements are *valid expressions* and *pseudo-signatures*.
The ISO C++ standard follows the valid *expressions* approach, which shows what the usage pattern looks like for a requirement.
It has the drawback of relegating important details to notational conventions. This document uses
pseudo-signatures, because they are concise, and can be cut-and-pasted for an initial implementation.

For example, the table below shows pseudo-signatures for a *sortable* type ``T``:

---------------------------------------------------------------------------------------------

**Sortable Requirements : Pseudo-Signature, Semantics**

.. cpp:function:: bool operator<(const T& x, const T& y)

  Compare x and y.

.. cpp:function:: void swap(T& x, T& y)

  Swap x and y.

---------------------------------------------------------------------------------------------

A real signature may differ from the pseudo-signature that it implements in ways where implicit
conversions would deal with the difference. For an example type ``U``, the real signature that
implements operator``<`` in the table above can be expressed as ``int operator<( U x, U y )``,
because C++ permits implicit conversion from ``int`` to ``bool``, and implicit conversion from ``U``
to (``const U&``). Similarly, the real signature ``bool operator<( U& x, U& y )`` is acceptable
because C++ permits implicit addition of a const qualifier to a reference type.

A type *models* a named requirement if all requirements are met.

.. toctree::

   named_requirements/algorithms/range.rst
   named_requirements/algorithms/splittable.rst
   named_requirements/algorithms/par_for_body.rst
   named_requirements/algorithms/par_reduce.rst

