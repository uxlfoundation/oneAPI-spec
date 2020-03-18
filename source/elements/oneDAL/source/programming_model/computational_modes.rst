===================
Computational modes
===================

-----
Batch
-----
In the batch processing mode, the algorithm works with the entire data set to produce the final
 result. A more complex scenario occurs when the entire data set is not available at the moment
 or the data set does not fit into the device memory.
------
Online
------
In the online processing mode, the algorithm processes a data set in blocks streamed into device
 memory by doing incrementally updating partial results, which are finalized upon processing of
 the last data block.
-----------
Distributed
-----------
In the distributed processing mode, the algorithm operates on a data set distributed across
 several devices (compute nodes). The algorithm produces partial results on each node, which
 are finally merged into the final result on the master node.