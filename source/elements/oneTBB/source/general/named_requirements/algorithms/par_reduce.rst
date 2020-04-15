========================================
parallel_reduce Body, Func and Reduction
========================================
**[req.parallel_reduce]**

-----------------------------------------------------------------------------------------------------

.. _par_reduce_body:

**Requirements for parallel_reduce Body: Pseudo-Signature, Semantics**

.. cpp:function:: Body::Body( Body&, split )

    Splitting constructor. Must be able to run concurrently with ``operator()`` and method ``join``.

.. cpp:function:: Body::~Body()

    Destructor.

.. cpp:function:: void Body::operator()(const Range& range)

    Accumulate result for subrange. ``Range`` type shall meet the :doc:`Range requirements <range>`.

.. cpp:function:: void Body::join( Body& rhs )

    Join results. The result in rhs should be merged into the result of ``this``.

-----------------------------------------------------------------------------------------------------

.. _par_reduce_func_reduction:

**Requirements for parallel_reduce Func and Reduction: Pseudo-Signature, Semantics**

.. cpp:function:: Value Func::operator()(const Range& range, const Value& x) const

    Accumulate result for subrange, starting with initial value ``x``.
    ``Range`` type shall meet the :doc:`Range requirements <range>`.

.. cpp:function:: Value Reduction::operator()(const Value& x, const Value& y) const

    Combine results ``x`` and ``y``.

``Value`` type must be the same as a corresponding template parameter for ``parallel_reduce`` algorithm.

