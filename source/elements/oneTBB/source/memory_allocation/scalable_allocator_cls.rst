=================================
scalable allocator Template Class
=================================


Summary
-------

Template class for scalable memory allocation.

Syntax
------

.. code:: cpp

   template<typename T> class scalable_allocator;


Header
------

.. code:: cpp

   #include "tbb/scalable_allocator.h"


Description
-----------

A 
``scalable_allocator`` allocates and frees memory in a way
that scales with the number of processors. A 
``scalable_allocator`` models the Allocator Concept. Using
a 
``scalable_allocator`` in place of 
``std::allocator`` may improve program performance. Memory
allocated by a 
``scalable_allocator`` should be freed by a 
``scalable_allocator``, not by a 
``std::allocator``.

.. caution::

   The 
   ``scalable_allocator`` requires the memory allocator
   library. If the library is missing, calls to the scalable allocator fail. In
   contrast, if the memory allocator library is not available, 
   ``tbb_allocator`` falls back on 
   ``malloc`` and 
   ``free``.


Members
-------

See Allocator concept.

See also:

* :doc:`C Interface to Scalable Allocator <c_interface_to_scalable_allocator>`
