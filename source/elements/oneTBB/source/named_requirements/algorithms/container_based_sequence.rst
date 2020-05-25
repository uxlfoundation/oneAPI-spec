======================
ContainerBasedSequence
======================
**[req.container_based_sequence]**

A type `T` satisfies the `ContainerBasedSequence` if it is an array type or
a type that meets the following requirements:

----------------------------------------------------------------

**ContainerBasedSequence Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: T::begin()

    Returns an iterator to the first element of the contained sequence.

.. cpp:function:: T::end()

    Returns an iterator to the element behind the last element of the contained sequence.
