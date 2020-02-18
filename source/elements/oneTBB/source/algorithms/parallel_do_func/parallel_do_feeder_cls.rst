========================
parallel_do_feeder class
========================


Summary
-------
Inlet into which additional work items for a 
``parallel_do`` can be fed.

Header
------

.. code:: cpp

   #include "tbb/parallel_do.h" 


Syntax
------

.. code:: cpp

   template<typename Item> 
   class parallel_do_feeder;


Description
-----------

A 
``parallel_do_feeder`` enables the body of a 
``parallel_do`` to add more work items.

Only class ``parallel_do`` can create or destroy a 
``parallel_do_feeder``. The only operation other code can
perform on a 
``parallel_do_feeder`` is to invoke method 
``parallel_do_feeder::add``.

Members
-------

.. code:: cpp

   namespace tbb {
       template<typename Item>
       struct parallel_do_feeder {
           void add( const Item& item );
           // Supported since C++11
           void add( Item&& item );
       };
   }

The following table provides additional information on the member
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void add( const Item& item )()``
  \
  **Requirements**: Must be called from
  a call to 
  *body* .``operator()`` created by 
  ``parallel_do``. Otherwise, the termination
  semantics of method 
  ``operator()`` are undefined.
  
  **Effects**: Adds item to collection of work items to be
  processed.
------------------------------------------------------------------------------------------
\ ``void add( Item&& item )()``
  \
  Supported since C++11. Same as the above but uses
  the move constructor of ``Item`` if available.
------------------------------------------------------------------------------------------
= ========================================================================================




