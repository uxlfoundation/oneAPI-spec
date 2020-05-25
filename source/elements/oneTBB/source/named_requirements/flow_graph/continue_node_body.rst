================
ContinueNodeBody
================
**[req.continue_node_body]**

A type `Body` satisfies the `ContinueNodeBody` if it meets the following requirements:

----------------------------------------------------------------------

**ContinueNodeBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( const Body& )

    Copy constructor.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: Output Body::operator()( const continue_msg &v ) const

    **Requirements:** The type ``Output`` must be the same as template type argument ``Output`` of the
    ``continue_node`` instance in which ``Body`` object is passed during construction.

    Perform operation and return value of type Output.

See also:

* :doc:`continue_node class <../../flow_graph/continue_node_cls>`
* :doc:`continue_msg class <../../flow_graph/continue_msg_cls>`
