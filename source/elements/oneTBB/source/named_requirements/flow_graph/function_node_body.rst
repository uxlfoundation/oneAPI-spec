================
FunctionNodeBody
================
**[req.function_node_body]**

A type `Body` satisfies the `FunctionNodeBody` if it meets the following requirements:

----------------------------------------------------------------------

**FunctionNodeBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( const Body& )

    Copy constructor.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: void operator=( const B& )

    Assignment.

.. cpp:function:: Output Body::operator()( const Input& v )

    **Requirements:** The ``Input`` and ``Output`` types must be the same as the ``Input`` and ``Output``
    template type arguments of the ``fucntion_node`` instance in which ``Body`` object is passed
    during construction.

    Perform operation on ``v`` and return value of type ``Output``.
  

