=================
Concurrent Access
=================

Member classes 
``const_accessor`` and 
``accessor`` are called 
*accessors*. Accessors allow multiple threads to concurrently
access pairs in a shared 
``concurrent_hash_map``. An 
*accessor* acts as a smart pointer to a pair in a 
``concurrent_hash_map``. It holds an implicit lock on a
pair until the instance is destroyed or method 
``release`` is called on the accessor.

Classes 
``const_accessor`` and 
``accessor`` differ in the kind of access that they
permit.



.. table:: Differences Between const_accessor and accessor

   ================== ================================ ==============================
   Class ``pair``             ``value_type``                   Implied Lock on 
   ================== ================================ ==============================
   ``const_accessor`` ``const std::pair<const Key,T>`` Reader lock – permits shared access with
                                                       other readers.
   ------------------ -------------------------------- ------------------------------
   ``accessor``       ``std::pair<const Key,T>``       Writer lock – permits exclusive access by a
                                                       thread. Blocks access by other threads.
   ================== ================================ ==============================

Accessors cannot be assigned or copy-constructed,
because allowing such would greatly complicate the locking semantics.

const_accessor
--------------

**Summary**

Provides read-only access to a pair in a 
``concurrent_hash_map``.

Syntax
------

.. code:: cpp

   template<typename Key, typename T, typename HashCompare, typename A> 
   class concurrent_hash_map<Key,T,HashCompare,A>::const_accessor;


Header
------

.. code:: cpp

   #include "tbb/concurrent_hash_map.h"


Description
-----------

A 
``const_accessor`` permits read-only access to a key-value
pair in a 
``concurrent_hash_map``.

Members
-------

.. code:: cpp

   namespace tbb {
           template<typename Key, typename T, typename HashCompare, typename A>
           class concurrent_hash_map<Key,T,HashCompare,A>::const_accessor {
           public:
               // types
               typedef const std::pair<const Key,T> value_type;
        
               // construction and destruction
               const_accessor();
               ~const_accessor();
               
               // inspection
               bool empty() const;
               const value_type& operator*() const;
               const value_type* operator->() const;
        
               // early release
               void release();
           }; 
       }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``bool empty() const``
  \
  **Returns**: True if instance points
  to nothing; false if instance points to a key-value pair.
------------------------------------------------------------------------------------------
\ ``void release()``
  \
  If 
  ``!empty()``, releases the implied lock on the
  pair, and sets instance to point to nothing. Otherwise does nothing.
------------------------------------------------------------------------------------------
\ ``const value_type& operator*() const``
  \
  Raises assertion failure if 
  ``empty()`` and 
  ``TBB_USE_ASSERT`` is defined as nonzero.
  
  **Returns**: Const reference to
  key-value pair.
------------------------------------------------------------------------------------------
\ ``const value_type* operator->() const``
  \
  **Returns**: 
  ``&operator*()``
------------------------------------------------------------------------------------------
\ ``const_accessor()``
  \
  Constructs 
  ``const_accessor`` that points to nothing.
------------------------------------------------------------------------------------------
\ ``~const_accessor``
  \
  If pointing to key-value pair, releases
  the implied lock on the pair.
------------------------------------------------------------------------------------------
= ========================================================================================


accessor
--------

**Summary**

Class that provides read and write access to a
pair in a 
``concurrent_hash_map``.

Syntax
------

.. code:: cpp

    template<typename Key, typename T, typename HashCompare,
       typename Alloc>
    class concurrent_hash_map<Key,T,HashCompare,A>::accessor;


Header
------

.. code:: cpp

   #include "tbb/concurrent_hash_map.h"


Description
-----------

An 
``accessor`` permits read and write access to a key-value
pair in a 
``concurrent_hash_map``. It is derived from a 
``const_accessor``, and thus can be implicitly cast to a 
``const_accessor``.

Members
-------

.. code:: cpp

   namespace tbb {
           template<typename Key, typename T, typename HashCompare, typename Alloc>
           class concurrent_hash_map<Key,T,HashCompare,Alloc>::accessor:
               concurrent_hash_map<Key,T,HashCompare,Alloc>::const_accessor {
           public:
               typedef std::pair<const Key,T> value_type;
               value_type& operator*() const;
               value_type* operator->() const;
           };
       }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``value_type& operator*() const``
  \
  Raises assertion failure if 
  ``empty()`` and 
  ``TBB_USE_ASSERT`` is defined as non-zero.
  
  **Returns**: Reference to key-value
  pair.
------------------------------------------------------------------------------------------
\ ``value_type* operator->() const``
  \
  **Returns**: 
  ``&operator*()``
------------------------------------------------------------------------------------------
= ========================================================================================
