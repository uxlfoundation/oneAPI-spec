================
ParallelScanBody
================
**[req.parallel_scan]**

A type `Body` satisfies the `ParallelScanBody` if it meets the following requirements:

--------------------------------------------------------------------------------

**ParallelScanBody Requirements: Pseudo-Signature, Semantics**

.. cpp:function:: void Body::operator()( const Range& r, pre_scan_tag )

    Accumulate summary for range ``r``.
    For example, if computing a running sum of an array,
    the summary for a range ``r`` is the sum of the array elements corresponding to ``r``.

.. cpp:function:: void Body::operator()( const Range& r, final_scan_tag )

    Compute scan result and summary for range ``r``.

.. cpp:function:: Body::Body( Body& b, split )

    Split ``b`` so that ``this`` and ``b`` can accumulate summaries separately.

.. cpp:function:: void Body::reverse_join( Body& b )

    Merge summary accumulated by ``b`` into summary accumulated by ``this``,
    where ``this`` was created earlier from ``b`` by splitting constructor.

.. cpp:function:: void Body::assign( Body& b )

    Assign summary of ``b`` to ``this``.


