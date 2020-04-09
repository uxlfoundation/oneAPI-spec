=======================================
pre_scan_tag and final_scan_tag Classes
=======================================


Summary
-------
Types that distinguish the phases of 
``parallel_scan``.

Header
------


.. code:: cpp

    #include "tbb/parallel_scan.h"


Syntax
------

.. code:: cpp

   struct pre_scan_tag; 
   struct final_scan_tag;


Description
-----------

Types 
``pre_scan_tag`` and 
``final_scan_tag`` are dummy types used in conjunction
with 
``parallel_scan``. See the example in the parallel_scan
Template Function section for how they are used in the signature of 
``operator()``.

Members
-------

.. code:: cpp

   namespace tbb {
   
       struct pre_scan_tag {
           static bool is_final_scan();
           operator bool();
       };
   
       struct final_scan_tag {
           static bool is_final_scan();
           operator bool();
       };
   
   }

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``bool is_final_scan()``
  \
  ``true`` for a 
  ``final_scan_tag``, otherwise ``false``.
------------------------------------------------------------------------------------------
\ ``operator bool()``
  \
  ``true`` for a 
  ``final_scan_tag``, otherwise ``false``.
------------------------------------------------------------------------------------------
= ========================================================================================




