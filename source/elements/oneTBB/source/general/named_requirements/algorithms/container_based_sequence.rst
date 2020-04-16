========================
Container Based Sequence
========================
**[general.req.container_based_sequence]**

A type satisfies the `ContainerBasedSequence` requirement if it is an array type or
a type that satisfies the following requirements:

----------------------------------------------------------------

**ContainerBasedSequence Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: ContainerBasedSequence::begin()

    Returns an iterator to the first element of the contained sequence.

.. cpp:function:: ContainerBasedSequence::end()

    Returns an iterator to the element behind the last element of the contained sequence.
