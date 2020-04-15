==========
Splittable
==========
**[req.splittable]**

A type is splittable if it has a *splitting constructor* that allows an instance to be split into
two pieces. The splitting constructor takes as arguments a reference to the original object,
and a dummy argument of type ``split``, which is defined by the library. The dummy argument
distinguishes the splitting constructor from a copy constructor. After the constructor runs,
``x`` and the newly constructed object should represent the two pieces of the original
``x.`` The library uses splitting constructors in two contexts:

* *Partitioning* a range into two subranges that can be processed concurrently.
* *Forking* a body (function object) into two bodies that can run concurrently.

Range classes might additionally define an optional *proportional splitting constructor*, distinguished by an
argument of type ``proportional_split``. See the ``proportional_split`` Class and ``blocked_range``
Template Class sections for more info.

------------------------------------------------------

**Splittable Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: X::X(X& x, split)

  Split ``x`` into ``x`` and newly constructed object.
