================
ParallelScanFunc
================
**[req.parallel_scan_func]**

A type `Scan` satisfies the `ParallelScanFunc` if it meets the following requirements:

--------------------------------------------------------------------------------

**ParallelScanFunc Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: Value Scan::operator()(const Range& r, const Value& sum, bool is_final) const

    Starting with ``sum``, compute the summary and, for ``is_final == true``,
    the scan result for range ``r``. Return the computed summary.
    ``Value`` type must be the same as a corresponding template parameter for ``parallel_scan`` algorithm.

