============
Body Objects
============

Some nodes execute user-provided body objects. These objects can be
created by instantiating function objects or lambda expressions. The nodes that
use body objects include 
``continue_node``, 
``function_node``,
``source_node`` and
``multifunction_node``.

.. caution::

   The body objects passed to the flow graph nodes are copied. Therefore
   updates to member variables will not affect the original object used to
   construct the node. If the state held within a body object must be inspected
   from outside of the node, the 
   ``copy_body`` function can be used to obtain an updated
   copy.

.. caution::

   The source_node has a one-item buffer which may contain a value
   obtained from executing the node's body.  If the source_node has
   emitted ``N`` items, the state of the body returned by
   ``copy_body`` may indicate it has been called ``N + 1`` times.


See also:

* :doc:`copy_body Template Function <copy_body_func>`
