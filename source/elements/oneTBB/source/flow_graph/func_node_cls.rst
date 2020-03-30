============================
function_node Template Class
============================


Summary
-------

A template class that is a ``graph_node``,
``receiver<Input>`` and a ``sender<Output>``. This
node may have concurrency limits as set by the user. By default, a
``function_node`` has an internal FIFO buffer at its input. Messages that
cannot be immediately processed due to concurrency limits are temporarily stored in this
FIFO buffer. A template argument can be used to disable this internal buffer. If the FIFO
buffer is disabled, incoming messages will be rejected if they cannot be processed
immediately while respecting the concurrency limits of the node.

Syntax
------

.. code:: cpp

   template < typename Input, typename Output = continue_msg,
              typename Policy = queueing,
              typename A = cache_aligned_allocator<Input> >
   class function_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A ``function_node`` receives messages of type ``Input`` at a
single input port and generates a single output message of type ``Output``
that is broadcast to all successors.  Rejection of messages by successors is handled using
the protocol described in Message Passing Protocol.

If ``Policy`` includes ``queueing`` (see
``lightweight`` policy reference for more details), an internal unbounded input
buffer is maintained using memory obtained through an allocator of type
``A``.

A ``function_node`` maintains an internal constant threshold T and an
internal counter C. At construction, C = 0 and T is set the value passed in to the
constructor. The behavior of a call to ``try_put`` is determined by the value
of T and C as shown below.

.. table:: Behavior of a call to a function_node's try_put

   ======================== ================== ===========================================================
   Value of threshold T     Value of counter C ``bool try_put( const input_type &v )``
   ======================== ================== ===========================================================
   ``T == flow::unlimited`` NA                 A task is spawned that broadcasts the result of ``body(v)``
                                               to all successors. Returns ``true``.
   ------------------------ ------------------ -----------------------------------------------------------
   ``T != flow::unlimited`` C < T              Increments C. A task is spawned that broadcasts the result
                                               of ``body(v)`` to all successors and then decrements C.
                                               Returns ``true``.
   ------------------------ ------------------ -----------------------------------------------------------
   ``T != flow::unlimited`` C >= T             If the template argument ``Policy`` includes ``queueing``,
                                               ``v`` is stored in an internal FIFO buffer until C < T.
                                               When T becomes less than C, C is incremented and a task is
                                               spawned that broadcasts the result of ``body(v)`` to all
                                               successors and then decrements C. Returns ``true``.

                                               If the template argument ``Policy`` includes
                                               ``rejecting`` and C >= T, returns ``false``.
   ======================== ================== ===========================================================

A ``function_node`` has a user-settable concurrency limit.  It can have
``flow::unlimited`` concurrency, which allows an unlimited number of
invocations of the body to execute concurrently. It can have ``flow::serial``
concurrency, which allows only a single call of body to execute concurrently. The user can
also provide a value of type ``size_t`` to limit concurrency to a value
between 1 and ``unlimited``.

A ``function_node`` with ``Policy==rejecting`` will maintain a
predecessor set as described in the Message Passing Protocol. If the
``function_node`` transitions from a state where C >= T to a state where C
< T, it will try to get new messages from its set of predecessors until C >= T or
there are no valid predecessors left in the set.

.. note::

   A ``function_node`` can serve as a terminal node in the graph. The
   convention is to use an ``Output`` of ``continue_msg`` and
   attach no successor.

``Input`` and ``Output`` must be copy-constructible and
assignable.

The Body concept for ``function_node`` is shown in below.

= ========================================================================================
\ function_node<Input, Output> Body Concept: Pseudo-Signature, Semantics
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
  Assignment. The return type ``void`` in the pseudo-signature denotes
  that ``operator=`` is not required to return a value.  The actual
  ``operator=`` can return a value, which will be ignored.
------------------------------------------------------------------------------------------
\ ``Output B::operator() (const Input &v) const``
  \
  Perform operation on ``v`` and return value of type
  ``Output``.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   The body object passed to a ``function_node`` is copied. Therefore updates
   to member variables will not affect the original object used to construct the node. If the
   state held within a body object must be inspected from outside of the node, the
   ``copy_body`` function can be used to obtain an updated copy.

.. note::

   The body object may throw or cancel its enclosing graph.  See task_group_context and
   Exceptions sections for a description.


Example
-------

:doc:`Data Flow Graph example <message_flow_graph_example>`
illustrates how ``function_node`` could do computation on input data
and pass the result to successors.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template < typename Input, typename Output = continue_msg,
              typename Policy = queueing,
              typename A = cache_aligned_allocator<Input> >
   class function_node :
     public graph_node, public receiver<Input>, public sender<Output> {
   public:
       template<typename Body>
       function_node( graph &g, size_t concurrency, Body body );
       function_node( const function_node &src );
   
       // receiver<Input>
       typedef Input input_type;
       typedef sender<input_type> predecessor_type;
       bool try_put( const input_type &v );
       bool register_predecessor( predecessor_type &p );
       bool remove_predecessor( predecessor_type &p );
   
       // sender<Output>
       typedef Output output_type;
       typedef receiver<output_type> successor_type;
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type &v );
       bool try_release( );
       bool try_consume( );
   };
   
   }
   }

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template< typename Body > function_node( graph &g, size_t concurrency, Body body )``
  \
  Constructs a ``function_node`` that will invoke a copy of
  ``body``. At most ``concurrency`` calls to
  ``body`` may be made concurrently.
------------------------------------------------------------------------------------------
\ ``function_node( const function_node &src )``
  \
  Constructs a ``function_node`` that has the same initial state that
  ``src`` had when it was constructed. The
  ``function_node`` that is constructed will have a reference to the
  same ``graph`` object as ``src``, will have a copy
  of the initial body used by ``src``, and have the same concurrency
  threshold as ``src``. The predecessors and successors of
  ``src`` will not be copied.
  
  .. caution::

     The new body object is copy-constructed from a copy of the original body
     provided to ``src`` at its construction. Therefore changes made
     to member variables in ``src``'s body after the construction of
     ``src`` will not affect the body of the new
     ``function_node.``
  
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  See the table above, "Behavior of a call to a ``function_node``'s
  ``try_put``," for more information.
  
  **Returns**: ``true`` if the input was accepted; and
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool register_predecessor(predecessor_type &p )``
  \
  Adds ``p`` to the set of predecessors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Removes ``p`` from the set of predecessors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type &r )``
  \
  Adds ``r`` to the set of successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type &r )``
  \
  Removes ``r`` from the set of successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  A ``function_node`` does not contain buffering of its
  output. Therefore it always rejects ``try_get`` calls.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  A ``function_node`` does not contain buffering of its
  output. Therefore it cannot be reserved.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  A ``function_node`` does not contain buffering of its
  output. Therefore it cannot be reserved.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  A ``function_node`` does not contain buffering of its
  output. Therefore it cannot be reserved.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`copy_body Template Function <copy_body_func>`
* :doc:`task_group_context <../task_scheduler/task_group_context>`
* :doc:`Exceptions <../exceptions>`
* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
* :doc:`Lightweight policy <lightweight_policy>`
