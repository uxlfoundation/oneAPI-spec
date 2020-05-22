==========
FilterBody
==========
**[req.filter_body]**

A type `Body` should meet one of the following requiements depending on the filter type:

----------------------------------------------------------------

**MiddleFilterBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: OutputType Body::operator()( InputType item ) const

    Process the received item and then returns it.

----------------------------------------------------------------

**FirstFilterBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: OutputType Body::operator()( tbb::flow_control fc ) const

    Returns the next item from an input stream. Calls ``fc.stop()`` at the end of an input stream.

----------------------------------------------------------------

**LastFilterBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: void Body::operator()( InputType item ) const

    Process the received item.

----------------------------------------------------------------

**SingleFilterBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: void Body::operator()( tbb::flow_control fc ) const

    Process element from an input stream. Calls ``fc.stop()`` at the end of an input stream.
