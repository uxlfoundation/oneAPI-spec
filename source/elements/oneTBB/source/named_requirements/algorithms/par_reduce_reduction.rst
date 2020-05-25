=======================
ParallelReduceReduction
=======================
**[req.parallel_reduce_reduction]**

A type `Reduction` satisfies the `ParallelReduceReduction` if it meets the following requirements:

-----------------------------------------------------------------------------------------------------

**ParallelReduceReduction Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Value Reduction::operator()(const Value& x, const Value& y) const

    Combine results ``x`` and ``y``.
    ``Value`` type must be the same as a corresponding template parameter for
    :doc:`parallel_reduce algorithm <../../algorithms/functions/parallel_reduce_func>` algorithm.

See also:

* :doc:`parallel_reduce algorithm <../../algorithms/functions/parallel_reduce_func>`
* :doc:`parallel_determinstic_reduce algorithm <../../algorithms/functions/parallel_deterministic_reduce_func>`
