===========
Terminology
===========

This section describes terminology used in the oneAPI Threading Building Blocks Specification.

Concept
-------

A *concept* is a set of requirements on a type. The requirements may be syntactic or semantic. For example, the concept of “sortable” could be defined as a set of requirements that enable an array to be sorted. A type ``T`` would be sortable if:

* ``x < y`` returns a boolean value, and represents a total order on items of type ``T``.
* ``swap(x,y)`` swaps items ``x`` and ``y``

You can write a sorting template function in C++ that sorts an array of any type that is sortable.

Two approaches for defining concepts are *valid expressions* and *pseudo-signatures*. The ISO C++ standard follows the valid *expressions* approach, which shows what the usage pattern looks like for a concept. It has the drawback of relegating important details to notational conventions. This document uses pseudo-signatures, because they are concise, and can be cut-and-pasted for an initial implementation.

For example, the table below shows pseudo-signatures for a sortable type ``T``:

= ========================================================================================
\ Pseudo-Signatures for Example Concept “sortable”: Pseudo-Signature, Semantics
==========================================================================================
\ bool operator<(const T& x, const T& y)
  \
  Compare x and y.
------------------------------------------------------------------------------------------
\ void swap(T& x, T& y)
  \
  Swap x and y.
------------------------------------------------------------------------------------------
= ========================================================================================

A real signature may differ from the pseudo-signature that it implements in ways where implicit conversions would deal with the difference. For an example type ``U``, the real signature that implements operator``<`` in the table above can be expressed as ``int operator<( U x, U y )``, because C++ permits implicit conversion from ``int`` to ``bool``, and implicit conversion from ``U`` to (``const U&``). Similarly, the real signature ``bool operator<( U& x, U& y )`` is acceptable because C++ permits implicit addition of a const qualifier to a reference type.

Model
-----

A type *models* a concept if it meets the requirements of the concept. For example, type ``int`` models the sortable concept in the above table if there exists a function ``swap(x,y)`` that swaps two ``int`` values ``x`` and ``y``. The other requirement for sortable, specifically ``x<y``, is already met by the built-in ``operator<`` on type ``int``.

CopyConstructible
-----------------

The library sometimes requires that a type model the *CopyConstructible* concept, which is defined by the ISO C++ standard. The table below shows the requirements for *CopyConstructible* in pseudo-signature form.

= ========================================================================================
\ CopyConstructible Requirements: Pseudo-Signature, Semantics
==========================================================================================
\ T( const T& )
  \
  Construct copy of const T.
------------------------------------------------------------------------------------------
\ ~T()
  \
  Destructor.
------------------------------------------------------------------------------------------
\ T* operator&()
  \
  Take address.
------------------------------------------------------------------------------------------
\ const T* operator&() const
  \
  Take address of const T.
------------------------------------------------------------------------------------------
= ========================================================================================
