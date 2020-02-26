==================
Lightweight policy
==================


Summary
-------

Policy for functional nodes that helps to reduce the overhead associated with the execution scheduling of the node.
This policy should only be applied on a per-node basis after careful evaluation.

Description
-----------

The ``lightweight`` policy indicates that the body of the node contains a small
amount of work and should, if possible, be executed without the overhead of scheduling a
task. All Flow Graph functional nodes, except for ``source_node``, support the
``lightweight`` policy as a possible value of the ``Policy``
template parameter. To use the ``lightweight`` policy, specify the
``Policy`` template parameter of the node to
``queueing_lightweight``, ``rejecting_lightweight``, or
``lightweight``. For functional nodes that have a default value for the
``Policy`` template parameter, specifying the ``lightweight``
policy results in extending the behavior of the default value of ``Policy``
with the behavior defined by the ``lightweight`` policy. For example, if the
default value of ``Policy`` is ``queueing``, specifying
``lightweight`` as the ``Policy`` value is equivalent to
specifying ``queueing_lightweight``.

.. caution::

   Having multiple successors with ``lightweight`` policy for a particular node can significantly reduce the parallelism
   available in the graph.

.. caution::

   Cycles in a flow graph consisting only of nodes with lightweight policies might lead to
   deadlock.


Example
-------

The example below shows the application of the ``lightweight`` policy to a
graph with a pipeline topology. It is reasonable to apply the ``lightweight``
policy to the second and third nodes because the bodies of these nodes are small. This
allows the second and third nodes to execute without task scheduling overhead. The
``lightweight`` policy is not specified for the first node in order to permit
concurrent invocations of the graph.

.. include:: ./examples/lightweight_policy.cpp
   :code: cpp



See also:

* :doc:`Flow Graph functional nodes <../flow_graph/functional_nodes>`
