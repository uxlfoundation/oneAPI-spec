=================
source_node Class
=================


Summary
-------

A template class that is both a 
``graph_node`` and a 
``sender<Output>``. This node can have no
predecessors. It executes a user-provided 
``body`` function object to generate messages that are
broadcast to all successors. It is a serial node and will never call its 
``body`` concurrently. It is able to buffer a single item.
If no successor accepts an item that it has generated, the message is buffered
and will be provided to successors before a new item is generated.

Syntax
------

.. code:: cpp

   template < typename Output > class source_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

This type of node generates messages of type 
``Output`` by invoking the user-provided 
``body`` and broadcasts the result to all of its
successors.

A 
``source_node`` is a serial node. Calls to 
``body`` will never be made concurrently.

A 
``source_node`` will continue to invoke 
``body`` and broadcast messages until the 
``body`` returns 
``false`` or it has no valid successors. A message may
be generated and then rejected by all successors. In that case, the message is
buffered and will be the next message sent once a successor is added to the
node or 
``try_get`` is called. Calls to 
``try_get`` will return a buffer message if available or
will invoke 
``body`` to attempt to generate a new message. A call to

``body`` is made only when the internal buffer is empty.

Rejection of messages by successors is handled using the protocol described in
the Message Passing Protocol.

``Output`` must be copy-constructible and assignable.

= ========================================================================================
\ source_node<Output> Body Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``B::B( const B& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``B::~B()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void operator=( const B& )``
  \
  Assignment. The return type 
  ``void`` in the pseudo-signature denotes that 
  ``operator=`` is not required to return a value.
  The actual 
  ``operator=`` can return a value, which will be
  ignored.
------------------------------------------------------------------------------------------
\ ``bool B::operator() (Output &v)``
  \
  Returns 
  ``true`` when it has assigned a new value to 
  ``v``. Returns 
  ``false`` when no new values may be generated.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   The body object passed to a 
   ``source_node`` is copied. Therefore updates to member
   variables will not affect the original object used to construct the node. If
   the state held within a body object must be inspected from outside of the node,
   the 
   ``copy_body`` function can be used to obtain an
   updated copy.

.. note::

   The body object may throw or cancel its enclosing graph. See
   task_group_context and Exceptions sections for a description.

Example
-------

The example from "Using source_node" section of TBB Developer Guide
shows usage specifics for this node type.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
    
   template < typename Output >
   class source_node : public graph_node, public sender< Output > {
   public:
       typedef Output output_type;
       typedef receiver< output_type > successor_type;
    
       template< typename Body >
       source_node( graph &g, Body body, bool is_active = true );
       source_node( const source_node &src );
       ~source_node();
    
       void activate();
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type &v );
       bool try_release( );
       bool try_consume( );
   };
    
   }
   }

The following table provides additional information on the
members of this class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template< typename Body >source_node( graph &g, Body body, bool is_active=true )``
  \
  Constructs a 
  ``source_node`` that will invoke 
  ``body``. By default the node is created in
  the active state, that is, it will begin generating messages immediately. If 
  ``is_active`` is 
  ``false``, messages will not be generated
  until a call to 
  ``activate`` is made.
------------------------------------------------------------------------------------------
\ ``source_node( const source_node &src )``
  \
  Constructs a 
  ``source_node`` that has the same initial
  state that 
  ``src`` had when it was constructed. The 
  ``source_node`` that is constructed will have
  a reference to the same 
  ``graph`` object as 
  ``src``, will have a copy of the initial body
  used by 
  ``src,`` and have the same initial active
  state as 
  ``src``. The predecessors and successors of 
  ``src`` will not be copied.
  
  .. caution::

     The new body object is copy-constructed from a copy of
     the original body provided to 
     ``src`` at its construction. Therefore
     changes made to member variables in 
     ``src``'s body after the construction of 
     ``src`` will not affect the body of the new 
     ``source_node.``
  
------------------------------------------------------------------------------------------
\ ``void activate()``
  \
  Sets the 
  ``source_node`` to the active state, allowing
  it to begin generating messages.
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type &r )``
  \
  Adds 
  ``r`` to the set of successors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type &r )``
  \
  Removes 
  ``r`` from the set of successors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  Will copy the buffered message into 
  ``v`` if available or will invoke 
  ``body`` to attempt to generate a new message
  that will be copied into 
  ``v``.
  
  **Returns**:``true`` if a message is
  copied to v. 
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  Reserves the 
  ``source_node`` if possible. If a message can
  be buffered and the node is not already reserved, the node is reserved for the
  caller, and the value is copied into 
  ``v``.
  
  **Returns**: 
  ``true`` if the node is reserved for the
  caller. 
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Releases any reservation held on the 
  ``source_node``. The message held in the
  internal buffer is retained.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  Releases any reservation held on the 
  ``source_node`` and clears the internal
  buffer.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`make_edge Template Function <make_edge_func>`
* :doc:`remove_edge Template Function <remove_edge_func>`
* :doc:`copy_body Template Function <copy_body_func>`
* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
* :doc:`task_group_context <../task_scheduler/task_group_context>`
* :doc:`Exceptions <../exceptions>`
