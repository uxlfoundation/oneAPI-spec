=============
InputNodeBody
=============
**[req.input_node_body]**

A type `Body` satisfies the `InputNodeBody` if it meets the following requirements:

----------------------------------------------------------------------

**InputNodeBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( const Body& )

    Copy constructor.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: Output Body::operator()( tbb::flow_control& fc )

    **Requirements:** The type ``Output`` must be the same as template type argument ``Output`` of the
    ``input_node`` instance in which ``Body`` object is passed during construction.

    Apply body to generate next item. Call ``fc.stop()`` when new element can not be generated.
    Since ``Output`` needs to be returned, ``Body`` may return any valid value of ``Output``, to be
    immediately discarded.

