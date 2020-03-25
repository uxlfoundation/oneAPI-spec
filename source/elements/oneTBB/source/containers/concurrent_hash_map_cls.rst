==================================
concurrent_hash_map Template Class
==================================


Summary
-------

A template class for an associative container with concurrent access.

Syntax
------

.. code:: cpp

   template < typename Key, typename T,
                 typename HashCompare = tbb_hash_compare<Key>,
                 typename A=tbb_allocator<std::pair<const Key, T> > >
   class concurrent_hash_map;


Header
------

.. code:: cpp

   #include "tbb/concurrent_hash_map.h"


Description
-----------

A ``concurrent_hash_map`` maps keys to values in a way that permits multiple
threads to concurrently access values. The keys are unordered. There is at most one element
in a ``concurrent_hash_map`` for each key. The key may have other elements in
flight but not in the map, as described in Concurrent Operations. The interface resembles
typical STL associative containers, but with some differences critical to supporting
concurrent access. It meets the Container Requirements of the ISO C++ standard. Types
``Key`` and ``T`` must model the CopyConstructible concept. Type
``HashCompare`` specifies how keys are hashed and compared for equality. It
must model the HashCompare concept in the table below.

= ========================================================================================
\ HashCompare Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``HashCompare::HashCompare( const HashCompare& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``HashCompare::~HashCompare()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``bool HashCompare::equal( const Key& j, const Key& k ) const``
  \
  True if keys are equal.
------------------------------------------------------------------------------------------
\ ``size_t HashCompare::hash( const Key& k ) const``
  \
  Hashcode for key.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   As for most hash tables, if two keys are equal, they must hash to the same hash code. That is,
   for a given HashCompare instance ``h`` and any two keys ``j``
   and ``k``, the following assertion must hold:
   ``"!h.equal(j,k) || h.hash(j)==h.hash(k)"``. The importance of this property
   is the reason that ``concurrent_hash_map`` makes key equality and hashing
   function combined in a single object instead of being separate objects. The hash
   code of a key must not change while the hash table is non-empty.

.. caution::

   Good performance depends on having good pseudo-randomness in the low-order bits of the
   hash code.


Example
-------

When keys are pointers, simply casting the pointer to a hash code may cause poor performance
because the low-order bits of the hash code will be always zero if the pointer points to a
type with alignment restrictions. A way to remove this bias is to divide the cast pointer
by the size of the type, as indicated below in
``bold italic font``.

.. code:: cpp

   size_t MyHashCompare::hash( Key* key ) const {
       return reinterpret_cast<size_t>(key) / sizeof(Key);
   }


Members
-------

In the following synopsis, methods shown in
``bold font``
may be concurrently invoked.

.. code:: cpp

   namespace tbb {
       template<typename Key, typename T, typename HashCompare,
                   typename Alloc = tbb_allocator<std::pair<const Key, T> > >
       class concurrent_hash_map {
           public:
               // types
               typedef Key key_type;
               typedef T mapped_type;
               typedef std::pair<const Key, T> value_type;
               typedef size_t size_type;
               typedef ptrdiff_t difference_type;
               typedef value_type* pointer;
               typedef const value_type* const_pointer;
               typedef value_type& reference;
               typedef Alloc allocator_type;
   
               // whole-table operations
               explicit concurrent_hash_map( const allocator_type& a=allocator_type() );
               explicit concurrent_hash_map( const HashCompare& compare, const allocator_type& a=allocator_type() );
               concurrent_hash_map( size_type n, const allocator_type&a = allocator_type() );
               concurrent_hash_map( size_type n, const HashCompare& compare, const allocator_type& a=allocator_type() );
               concurrent_hash_map( const concurrent_hash_map& );
               concurrent_hash_map( const concurrent_hash_map&, const allocator_type& );
               template<typename InputIterator>
               concurrent_hash_map( InputIterator first, InputIterator last,
                                    const allocator_type& a = allocator_type() );
               template<typename InputIterator>
               concurrent_hash_map( InputIterator first, InputIterator last,
                                    const HashCompare& compare, const allocator_type& a=allocator_type() );
               // Supported since C++11
               concurrent_hash_map( concurrent_hash_map&& );
               concurrent_hash_map( concurrent_hash_map&&, const allocator_type& );
               concurrent_hash_map( std::initializer_list<value_type> il,
                                    const allocator_type& a = allocator_type() );
               concurrent_hash_map( std::initializer_list<value_type> il,
                                    const HashCompare& compare, const allocator_type& a=allocator_type() );
               ~concurrent_hash_map();
               concurrent_hash_map operator=( const concurrent_hash_map& );
               // Supported since C++11
               concurrent_hash_map& operator=( concurrent_hash_map&& );
               concurrent_hash_map operator=( std::initializer_list<value_type> il );
               void rehash( size_type n = 0 );
               void clear();
               allocator_type get_allocator() const;
   
               // concurrent access
               class const_accessor;
               class accessor;
   
               // concurrent operations on a table
               bool find( const_accessor& result, const Key& key ) const;
               bool find( accessor& result, const Key& key );
               bool insert( const_accessor& result, const Key& key );
               bool insert( accessor& result, const Key& key );
               bool insert( const_accessor& result, const value_type& value );
               bool insert( accessor& result, const value_type& value );
               bool insert( const value_type& value );
               template<typename I>
               void insert( I first, I last );
               // Supported since C++11
               void insert( std::initializer_list<value_type> il );
               bool erase( const Key& key );
               bool erase( const_accessor& item_accessor );
               bool erase( accessor& item_accessor );
   
               // parallel iteration
               typedef implementation-defined range_type;
               typedef implementation-defined const_range_type;
               range_type range( size_t grainsize = 1 );
               const_range_type range( size_t grainsize = 1 ) const;
   
               // capacity
               size_type size() const;
               bool empty() const;
               size_type max_size() const;
               size_type bucket_count() const;
   
               // iterators
               typedef implementation-defined iterator;
               typedef implementation-defined const_iterator;
               iterator begin();
               iterator end();
               const_iterator begin() const;
               const_iterator end() const;
               std::pair<iterator, iterator> equal_range( const Key& key );
               std::pair<const_iterator, const_iterator> equal_range( const Key& key ) const;
           };
   
           template<typename Key, typename T, typename HashCompare, typename A1, typename A2>
           bool operator==( const concurrent_hash_map<Key,T,HashCompare,A1>& a,
                            const concurrent_hash_map<Key,T,HashCompare,A2>& b);
   
           template<typename Key, typename T, typename HashCompare, typename A1, typename A2>
           bool operator!=( const concurrent_hash_map<Key,T,HashCompare,A1>& a,
                            const concurrent_hash_map<Key,T,HashCompare,A2>& b );
   
           template<typename Key, typename T, typename HashCompare, typename A>
           void swap( concurrent_hash_map<Key,T,HashCompare,A>& a,
                      concurrent_hash_map<Key,T,HashCompare,A>& b );
       }

Where possible, constructors of ``concurrent_hash_map`` support class template argument deduction for C++17. For example

.. code:: cpp

   std::vector<std::pair<int, std::string>> v {{1, "one"}, {2, "two"}};
   tbb::concurrent_hash_map hmap {v.begin(), v.end()};

declares ``hmap`` as ``tbb::concurrent_hash_map<int, std::string, tbb::tbb_hash_compare<int>, tbb::tbb_allocator<std::pair<const int, std::string>>>``.

Exception Safety
----------------

The following functions must not throw exceptions:

* The hash function
* The destructors for types ``Key`` and ``T``.

The following holds true:

* If an exception happens during an insert operation, the operation has no effect.
* If an exception happens during an assignment operation, the container may be in a state
  where only some of the items were assigned, and methods ``size()`` and
  ``empty()`` may return invalid answers.


See also:

* :doc:`tbb_hash_compare <tbb_hash_compare_cls>`
* :doc:`concurrent_unordered_map <concurrent_unordered_map_cls>`
* :doc:`concurrent_unordered_set <concurrent_unordered_set_cls>`

.. toctree::

   concurrent_hash_map_cls/whole_table_operations.rst
   concurrent_hash_map_cls/concurrent_access.rst
   concurrent_hash_map_cls/concurrent_operations_hash.rst
   concurrent_hash_map_cls/parallel_iteration_container.rst
   concurrent_hash_map_cls/capacity_map_cls.rst
   concurrent_hash_map_cls/iterators_hash_map_cls.rst
   concurrent_hash_map_cls/global_funcs.rst
