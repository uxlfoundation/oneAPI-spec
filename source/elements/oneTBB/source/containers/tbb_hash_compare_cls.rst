======================
tbb_hash_compare Class
======================


Summary
-------

Hash support class to use with associative containers
provided by oneAPI Threading Building Blocks.

Syntax
------


.. code:: cpp

   template<typename Key> struct tbb_hash_compare;


Description
-----------

A ``tbb_hash_compare<Key>`` is the default for
the ``HashCompare`` argument of template class
``concurrent_hash_map``.
For your own types, you can define template specializations of
``tbb_hash_compare``

There are built-in definitions of ``tbb_hash_compare`` for the following Key types:

* Types that are convertible to
  a ``size_t`` by ``static_cast<T>``
* Pointer types
* ``std::basic_string``
* ``std::pair<K1,K2>``
  where ``K1`` and ``K2``
  are hashed using ``tbb_hasher``.


Members
-------

.. code:: cpp

   namespace tbb {
       template<typename Key>
       struct tbb_hash_compare {
           static size_t hash(const Key& k) {
               /*implementation defined*/
           }
           static bool equal(const Key& k1, const Key& k2) {
               return k1==k2;
           }
       };
   }


See also:

* :doc:`concurrent_hash_map Template Class <concurrent_hash_map_cls>`
* :doc:`concurrent_unordered_map and concurrent_unordered_multimap Template Classes <concurrent_unordered_map_cls>`
* :doc:`concurrent_unordered_set and concurrent_unordered_multiset Template Classes <concurrent_unordered_set_cls>`
