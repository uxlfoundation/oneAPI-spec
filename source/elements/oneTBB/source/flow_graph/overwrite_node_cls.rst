=============================
overwrite_node Template Class
=============================


Summary
-------

A template class that is a ``graph_node``,
``receiver<Input>`` and ``sender<Output>``. An
``overwrite_node`` is a buffer of a single item that can be over-written.

Syntax
------

.. code:: cpp

   template < typename T >
   class overwrite_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

This type of node buffers a single item of type T. The value is initially invalid. A
``try_put`` will set the value of the internal buffer, and broadcast the new
value to all successors. Gets from the node are non-destructive. If the internal value is
valid, a ``try_get`` will return ``true`` and copy the buffer
value to the output. If the internal value is invalid, ``try_get`` will
return ``false``.

Rejection of messages by successors is handled using the protocol described in the Message
Passing Protocol.

``T`` must be copy-constructible and assignable.

Example
-------

The example demonstrates ``overwrite_node`` as a single-value storage that
might be updated. Data can be accessed with direct ``try_get()`` call.

.. include:: ./examples/overwrite_node_cls.cpp
   :code: cpp


``overwrite_node`` supports reserving ``join_node`` as its
successor. See example in :doc:`the example section of write_once_node <write_once_node_cls>`.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template< typename T >
   class overwrite_node :
     public graph_node, public receiver<T>, public sender<T> {
   public:
       explicit overwrite_node( graph &g );
       overwrite_node( const overwrite_node &src );
       ~overwrite_node();
   
       // receiver<T>
       typedef T input_type;
       typedef sender<input_type> predecessor_type;
       bool try_put( const input_type &v );
       bool register_predecessor( predecessor_type &p );
       bool remove_predecessor( predecessor_type &p );
   
       // sender<T>
       typedef T output_type;
       typedef receiver<output_type> successor_type;
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type &v );
       bool try_release( );
       bool try_consume( );
   
       bool is_valid( );
       void clear( );
   };
   
   }
   }

The following table provides additional information on the members of this template
class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit overwrite_node( graph &g )``
  \
  Constructs an object of type ``overwrite_node`` with an invalid
  internal buffer item.
------------------------------------------------------------------------------------------
\ ``overwrite_node( const overwrite_node &src )``
  \
  Constructs an object of type ``overwrite_node`` that belongs to the
  ``graph g`` with an invalid internal buffer item. The buffered
  value and list of successors is NOT copied from ``src``.
------------------------------------------------------------------------------------------
\ ``~overwrite_node( )``
  \
  Destroys the ``overwrite_node``.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Stores ``v`` in the internal single item buffer and calls
  ``try_put(v)`` on all successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a list of predecessors.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a list of predecessors.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type &r )``
  \
  Adds ``r`` to the set of successors. If a valid item
  ``v`` is held in the buffer, a task is spawned to call
  ``r.try_put(v)``.
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type &r )``
  \
  Removes ``r`` from the set of successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  If the internal buffer is valid, assigns the value to ``v``.
  
  **Returns**:``true`` if ``v`` is assigned to.
  ``false`` if ``v`` is not assigned to.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  If the internal buffer is valid, assigns the value to ``v``.
  
  **Returns**:``true`` if ``v`` is assigned to.
  ``false`` if ``v`` is not assigned to.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool is_valid( )``
  \
  **Returns**: ``true`` if the buffer holds a valid value,
  otherwise returns ``false``.
------------------------------------------------------------------------------------------
\ ``void clear( )``
  \
  Invalidates the value held in the buffer.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
