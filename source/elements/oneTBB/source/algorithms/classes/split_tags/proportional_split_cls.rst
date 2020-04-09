========================
proportional split Class
========================


Summary
-------

Type of an argument for a proportional splitting constructor of Range.

Header
------


.. code:: cpp

   #include "tbb/tbb_stddef.h"


Syntax
------

.. code:: cpp

   class proportional_split;


Description
-----------

An argument of type ``proportional_split`` may be used by classes that implement Range concept to distinguish a proportional
splitting constructor from a basic splitting constructor and from a copy constructor, and to suggest a ratio in which a particular instance of
the class should be split.

Members
-------

.. code:: cpp

   namespace tbb {
           class proportional_split {
           public:
               proportional_split(size_t _left = 1, size_t _right = 1);
   
               size_t left() const;
               size_t right() const;
   
               operator split() const;
           };
   }
         


The following table provides additional information on the members of this class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``proportional_split( size_t _left = 1, size_t _right = 1 )``
  \
  Constructs a proportion with the ratio specified by coefficients *_left* and *_right*.
------------------------------------------------------------------------------------------
\ ``size_t left() const``
  \
  Returns size of the left part of the proportion.
------------------------------------------------------------------------------------------
\ ``size_t right() const``
  \
  Returns size of the right part of the proportion.
------------------------------------------------------------------------------------------
\ ``operator split() const``
  \
  Makes ``proportional_split`` implicitly convertible to ``split`` type to use with
  ranges that do not support proportional splitting.
------------------------------------------------------------------------------------------
= ========================================================================================


See "Range Concept" for an example of proportional splitting constructor implementation.

See also:

* :doc:`split <split_cls>`
* :doc:`Range Concept <../../../general/named_requirements/range>`
