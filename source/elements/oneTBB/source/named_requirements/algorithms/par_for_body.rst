===============
ParallelForBody
===============
**[req.parallel_for_body]**

A type `Body` satisfies the `ParallelForBody` if it meets the following requirements:

----------------------------------------------------------------------

**ParallelForBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( const Body& )

    Copy constructor.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: void Body::operator()( Range& range ) const

    Apply body to range. ``Range`` type shall meet the :doc:`Range requirements <range>`.

See also:

* :doc:`parallel_for algorithm <../../algorithms/functions/parallel_for_func>`
