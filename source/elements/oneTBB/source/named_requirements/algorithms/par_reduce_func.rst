==================
ParallelReduceFunc
==================
**[req.parallel_reduce_body]**

A type `Func` satisfies the `ParallelReduceFunc` if it meets the following requirements:

-----------------------------------------------------------------------------------------------------

**ParallelReduceFunc Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Value Func::operator()(const Range& range, const Value& x) const

    Accumulate result for subrange, starting with initial value ``x``.
    ``Range`` type shall meet the :doc:`Range requirements <range>`.
    ``Value`` type must be the same as a corresponding template parameter for
    :doc:`parallel_reduce algorithm <../../algorithms/functions/parallel_reduce_func>` algorithm.

See also:

* :doc:`parallel_reduce algorithm <../../algorithms/functions/parallel_reduce_func>`
* :doc:`parallel_determinstic_reduce algorithm <../../algorithms/functions/parallel_deterministic_reduce_func>`
