=================
parallel_for Body
=================
**[req.parallel_for_body]**

----------------------------------------------------------------------

**Requirements for parallel_for Body: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( const Body& )

    Copy constructor.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: void Body::operator()( Range& range ) const

    Apply body to range. ``Range`` type shall meet the :doc:`Range requirements <range>`.

