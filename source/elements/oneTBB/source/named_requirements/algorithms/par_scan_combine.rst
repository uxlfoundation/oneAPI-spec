===================
ParallelScanCombine
===================
**[req.parallel_scan_combine]**

A type `Combine` satisfies the `ParallelScanCombine` if it meets the following requirements:

--------------------------------------------------------------------------------

**ParallelScanCombine Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Value Combine::operator()(const Value& left, const Value& right) const

    Combine summaries ``left`` and ``right``, and return the result
    ``Value`` type must be the same as a corresponding template parameter for ``parallel_scan`` algorithm.

