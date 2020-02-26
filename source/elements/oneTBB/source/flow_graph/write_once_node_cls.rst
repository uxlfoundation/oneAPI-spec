==============================
write_once_node Template Class
==============================


Summary
-------

A template class that is a ``graph_node``,
``receiver<Input>`` and ``sender<Output>``. A
``write_once_node`` is a buffer of a single item that cannot be over-written.

Syntax
------

.. code:: cpp

   template < typename T >
   class write_once_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

This type of node buffers a single item of type T. The value is initially invalid. The first
``try_put`` to the node will set the value of the internal buffer, and
broadcast the new value to all successors. Subsequent puts are ignored, with received values
being lost. The internal buffer may be cleared explicitly, after which a new value may be
set. Gets from the node are non-destructive. If the internal value is valid, a
``try_get`` will return ``true`` and copy the buffer value to
the output. If the internal value is invalid, ``try_get`` will return
``false``.

Rejection of messages by successors is handled using the protocol described in the Message
Passing Protocol.

``T`` must be copy-constructible and assignable.

Example
-------

Usage scenario is similar to
:doc:`overwrite_node <overwrite_node_cls>`
but an internal buffer can be updated only after ``clear()`` call. The
following example shows the possibility to connect the node to a reserving
``join_node``, avoiding direct calls to the ``try_get()`` method
from the body of the successor node.

.. include:: ./examples/write_once_node_cls.cpp
   :code: cpp



Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template< typename T >
   class write_once_node :
     public graph_node, public receiver<T>, public sender<T> {
   public:
       explicit write_once_node( graph &g );
       write_once_node( const write_once_node &src );
       ~write_once_node();
   
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

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit write_once_node( graph &g )``
  \
  Constructs an object of type ``write_once_node`` that belongs to
  the ``graph g``, with an invalid internal buffer item.
------------------------------------------------------------------------------------------
\ ``write_once_node( const write_once_node &src )``
  \
  Constructs an object of type ``write_once_node`` with an invalid
  internal buffer item. The buffered value and list of successors is NOT copied from
  ``src``.
------------------------------------------------------------------------------------------
\ ``~write_once_node( )``
  \
  Destroys the ``write_once_node``.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Stores ``v`` in the internal single item buffer if it does not
  already contain a valid value. If a new value is set, it calls
  ``try_put(v)`` on all successors.
  
  **Returns**: ``true`` for the first time after construction or a
  call to ``clear()``, ``false`` otherwise.
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
  
  **Returns**: ``true`` if ``v`` is assigned to.
  ``false`` if ``v`` is not assigned to.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  If the internal buffer is valid, assigns the value to ``v``.
  
  **Returns**: ``true`` if ``v`` is assigned to.
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
