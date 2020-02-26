===========================================================================
concurrent_unordered_map and concurrent_unordered_multimap Template Classes
===========================================================================


Summary
-------

Template classes for associative containers which support concurrent insertion and
traversal.

Syntax
------

.. code:: cpp

   template <typename Key,
             typename Element,
             typename Hasher = tbb_hash<Key>,
             typename Equality = std::equal_to<Key>,
             typename Allocator = tbb::tbb_allocator<std::pair<const Key, Element> > >
   class concurrent_unordered_map;

.. code:: cpp

   template <typename Key,
             typename Element,
             typename Hasher = tbb_hash<Key>,
             typename Equality = std::equal_to<Key>,
             typename Allocator = tbb::tbb_allocator<std::pair<const Key, Element> > >
   class concurrent_unordered_multimap;


Header
------

.. code:: cpp

   #include "tbb/concurrent_unordered_map.h"


Description
-----------

``concurrent_unordered_map`` and ``concurrent_unordered_multimap``
support concurrent insertion and traversal, but not concurrent erasure. The interfaces have
no visible locking. They may hold locks internally, but never while calling user-defined
code. They have semantics similar to ``std::unordered_map`` and
``std::unordered_multimap`` respectively, except as follows:

* The ``erase`` and ``extract`` methods are prefixed with
  ``unsafe_``, to indicate that they are not concurrency safe.
* Bucket methods are prefixed with ``unsafe_`` as a reminder that they are
  not concurrency safe with respect to insertion.
* Return values of the ``insert`` and ``emplace`` methods might differ
  from the C++ standard. In particular, the methods of ``concurrent_unordered_multimap``
  may return ``std::pair<iterator,bool>``, with the Boolean value in the pair
  being always ``true``.
* For ``concurrent_unordered_map``, ``insert`` and
  ``emplace`` methods may create a temporary item that is destroyed
  if another thread inserts an item with the same key concurrently.
* Like ``std::list``, insertion of new items does *not* invalidate any
  iterators, nor does it change the order of items already in the map. Insertion and traversal may
  be concurrent.
* Insertion methods called concurrently with ``equal_range`` may cause non-equal
  items to be inserted at the end of the range. However, the first in the pair of iterators
  returned by ``equal_range`` will nonetheless point to the first item in the range.

The following table lists the key differences between classes
``concurrent_unordered_map`` and ``concurrent_hash_map`` and
``concurrent_unordered_multimap``.

================================= ==============================
Class                             Key Difference
================================= ==============================
``concurrent_hash_map``           Permits concurrent erasure, and has built-in locking
--------------------------------- ------------------------------
``concurrent_unordered_map``      * Permits concurrent traversal and insertion, no visible locking, closely
                                    resembles the C++11 unordered_map.
                                  * Has the ``[]`` and ``at`` accessors.
                                  
--------------------------------- ------------------------------
``concurrent_unordered_multimap`` * More than one ``<key,value>`` pair with the same
                                    ``key`` value may be inserted in
                                    ``concurrent_unordered_multimap``.
                                  * ``find`` returns the first ``<key,value>``
                                    pair with a matching key at the point the search is made, though concurrent
                                    accesses to the container may insert other pairs with the same key before the
                                    one returned.
                                  
================================= ==============================

.. caution::

   As with any form of hash table, keys that are equal must have the same hash code, and the
   ideal hash function distributes keys uniformly across the hash code space.


Members of both concurrent_unordered_map and concurrent_unordered_multimap
--------------------------------------------------------------------------

In the following synopsis, methods shown in
``bold font``
may be concurrently invoked. For example, three different threads can concurrently call
methods ``insert``, ``begin``, and ``size``. Their
results might be non-deterministic. For example, the result from size might correspond to
before or after the insertion.

.. code:: cpp

   public:
       // types
       typedef Key key_type;
       typedef Element mapped_type;
       typedef std::pair<const Key, Element> value_type;
       typedef Hasher hasher;
       typedef Equality key_equal;
       typedef Allocator allocator_type;
       typedef typename allocator_type::pointer pointer;
       typedef typename allocator_type::const_pointer const_pointer;
       typedef typename allocator_type::reference reference;
       typedef typename allocator_type::const_reference const_reference;
       typedef implementation-defined size_type;
       typedef implementation-defined difference_type;
       typedef implementation-defined iterator;
       typedef implementation-defined const_iterator;
       typedef implementation-defined local_iterator;
       typedef implementation-defined const_local_iterator;
       typedef implementation-defined node_type;
   
       allocator_type get_allocator() const;
   
       // size and capacity
       bool empty() const;
       size_type size() const;
       size_type max_size() const;
   
       // iterators
       iterator begin();
       const_iterator begin() const;
       iterator end();
       const_iterator end() const;
       const_iterator cbegin() const;
       const_iterator cend() const;
   
       // modifiers
       std::pair<iterator, bool> insert(const value_type& x);
       iterator insert(const_iterator hint, const value_type& x);
       template<class InputIterator>
       void insert(InputIterator first, InputIterator last);
       // Supported since C++11
       std::pair<iterator, bool> insert(value_type&& x);
       iterator insert(const_iterator hint, value_type&& x);
       void insert(std::initializer_list<value_type> il);
       std::pair<iterator, bool> insert(node_type&& nh);
       iterator insert(const_iterator hint, node_type&& nh);
       template<typename... Args>
       std::pair<iterator, bool> emplace(Args&&... args);
       template<typename... Args>
       iterator emplace_hint(const_iterator hint, Args&&... args);
   
       // Supported since C++11
       template<typename SrcHash, typename SrcEquality>
       void merge(concurrent_unordered_multimap<Key, T, SrcHash, SrcEquality, Allocator>& source);
       template<typename SrcHash, typename SrcEquality>
       void merge(concurrent_unordered_multimap<Key, T, SrcHash, SrcEquality, Allocator>&& source);
       template<typename SrcHash, typename SrcEquality>
       void merge(concurrent_unordered_map<Key, T, SrcHash, SrcEquality, Allocator>& source);
       template<typename SrcHash, typename SrcEquality>
       void merge(concurrent_unordered_map<Key, T, SrcHash, SrcEquality, Allocator>&& source);
   
       // Supported since C++11
       node_type unsafe_extract(const_iterator where);
       node_type unsafe_extract(const key_type& key);
   
       iterator unsafe_erase(const_iterator position);
       size_type unsafe_erase(const key_type& k);
       iterator unsafe_erase(const_iterator first, const_iterator last);
       void clear();
   
       // observers
       hasher hash_function() const;
       key_equal key_eq() const;
   
       // lookup
       iterator find(const key_type& k);
       const_iterator find(const key_type& k) const;
       size_type count(const key_type& k) const;
       std::pair<iterator, iterator> equal_range(const key_type& k);
       std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
   
       // parallel iteration
       typedef implementation-defined range_type;
       typedef implementation-defined const_range_type;
       range_type range();
       const_range_type range() const;
   
       // bucket interface - for debugging
       size_type unsafe_bucket_count() const;
       size_type unsafe_max_bucket_count() const;
       size_type unsafe_bucket_size(size_type n);
       size_type unsafe_bucket(const key_type& k) const;
       local_iterator unsafe_begin(size_type n);
       const_local_iterator unsafe_begin(size_type n) const;
       local_iterator unsafe_end(size_type n);
       const_local_iterator unsafe_end(size_type n) const;
       const_local_iterator unsafe_cbegin(size_type n) const;
       const_local_iterator unsafe_cend(size_type n) const;
   
       // hash policy
       float load_factor() const;
       float max_load_factor() const;
       void max_load_factor(float z);
       void rehash(size_type n);


Members of concurrent_unordered_map
-----------------------------------

In the following synopsis, methods in bold may be concurrently invoked.

.. code:: cpp

   public:
       // construct/destroy/copy
       explicit concurrent_unordered_map(size_type n = implementation-defined,
       const hasher& hf = hasher(),
       const key_equal& eql = key_equal(),
       const allocator_type& a = allocator_type());
       concurrent_unordered_map(size_type n, const allocator_type& a);
       concurrent_unordered_map(size_type n, const hasher& hf, const allocator_type& a);
       template <typename InputIterator>
       concurrent_unordered_map(InputIterator first, InputIterator last,
                                 size_type n = implementation-defined,
                                 const hasher& hf = hasher(),
                                 const key_equal& eql = key_equal(),
                                 const allocator_type& a = allocator_type());
       template <typename InputIterator>
       concurrent_unordered_map(InputIterator first, InputIterator last,
                                 size_type n, const allocator_type& a);
       template <typename InputIterator>
       concurrent_unordered_map(InputIterator first, InputIterator last,
                                 size_type n, const hasher& hf, const allocator_type& a);
       concurrent_unordered_map(const concurrent_unordered_map&);
       explicit concurrent_unordered_map(const allocator_type&);
       concurrent_unordered_map(const concurrent_unordered_map&, const allocator_type&);
       // Supported since C++11
       concurrent_unordered_map(concurrent_unordered_map&&);
       concurrent_unordered_map(concurrent_unordered_map&&, const allocator_type&);
       concurrent_unordered_map(std::initializer_list<value_type> il,
                                 size_type n = implementation-defined,
                                 const hasher& hf = hasher(),
                                 const key_equal& eql = key_equal(),
                                 const allocator_type& a = allocator_type());
       concurrent_unordered_map(std::initializer_list<value_type> il,
                                 size_type n, const allocator_type& a);
       concurrent_unordered_map(std::initializer_list<value_type> il,
                                 size_type n, const hasher& hf, const allocator_type& a);
   
       ~concurrent_unordered_map();
   
       concurrent_unordered_map& operator=(const concurrent_unordered_map&);
       // Supported since C++11
       concurrent_unordered_map& operator=(concurrent_unordered_map&&);
       concurrent_unordered_map& operator=(std::initializer_list<value_type> il);
   
       void swap(concurrent_unordered_map&);
   
       mapped_type& operator[](const key_type& k);
       mapped_type& at( const key_type& k );
       const mapped_type& at(const key_type& k) const;


Members of concurrent_unordered_multimap
----------------------------------------

.. code:: cpp

   public:
       // construct/destroy/copy
       explicit concurrent_unordered_multimap(size_type n = implementation-defined,
                                              const hasher& hf = hasher(),
                                              const key_equal& eql = key_equal(),
                                              const allocator_type& a = allocator_type());
       concurrent_unordered_multimap(size_type n, const allocator_type& a);
       concurrent_unordered_multimap(size_type n, const hasher& hf, const allocator_type& a);
       template <typename InputIterator>
       concurrent_unordered_multimap( InputIterator first, InputIterator last,
                                      size_type n = implementation-defined,
                                      const hasher& hf = hasher(),
                                      const key_equal& eql = key_equal(),
                                      const allocator_type& a = allocator_type());
       template <typename InputIterator>
       concurrent_unordered_multimap( InputIterator first, InputIterator last,
                                      size_type n, const allocator_type& a);
       template <typename InputIterator>
       concurrent_unordered_multimap( InputIterator first, InputIterator last,
                                      size_type n, const hasher& hf, const allocator_type& a);
       concurrent_unordered_multimap(const concurrent_unordered_multimap&);
       explicit concurrent_unordered_multimap(const allocator_type&);
       concurrent_unordered_multimap(const concurrent_unordered_multimap&, const allocator_type&);
       // Supported since C++11
       concurrent_unordered_multimap(concurrent_unordered_multimap&&);
       concurrent_unordered_multimap(concurrent_unordered_multimap&&, const allocator_type&);
       concurrent_unordered_multimap(std::initializer_list<value_type> il,
                                     size_type n = implementation-defined,
                                     const hasher& hf = hasher(),
                                     const key_equal& eql = key_equal(),
                                     const allocator_type& a = allocator_type());
       concurrent_unordered_multimap(std::initializer_list<value_type> il,
                                     size_type n, const allocator_type& a);
       concurrent_unordered_multimap(std::initializer_list<value_type> il,
                                     size_type n, const hasher& hf, const allocator_type& a);
   
       ~concurrent_unordered_multimap();
   
       concurrent_unordered_multimap& operator=(const concurrent_unordered_multimap&);
       // Supported since C++11
       concurrent_unordered_multimap& operator=(concurrent_unordered_multimap&&);
       concurrent_unordered_multimap& operator=(std::initializer_list<value_type> il);
   
       void swap(concurrent_unordered_multimap&);

Where possible, constructors of ``concurrent_unordered_map`` and ``concurrent_unordered_multimap`` support class template argument deduction for C++17. For example

.. code:: cpp

   std::vector<std::pair<int, std::string>> v {{1, "one"}, {2, "two"}};
   tbb::concurrent_unordered_map cu_map {v.begin(), v.end()};

declares ``cu_map`` as ``tbb::concurrent_unordered_map<int, std::string, tbb::tbb_hash<int>, std::equal_to<int>, tbb::tbb_allocator<std::pair<const int, std::string>>>``.

See also:

* :doc:`Node handles <node_handles_cls>`
* :doc:`concurrent_unordered_set <concurrent_unordered_set_cls>`
* :doc:`concurrent_hash_map <concurrent_hash_map_cls>`

.. toctree::

   concurrent_unordered_map_cls/construct_destroy_copy_map_cls.rst
   concurrent_unordered_map_cls/size_and_capacity_map_cls.rst
   concurrent_unordered_map_cls/container_iterators_map_cls.rst
   concurrent_unordered_map_cls/modifiers_map_cls.rst
   concurrent_unordered_map_cls/observers_map_cls.rst
   concurrent_unordered_map_cls/lookup_map_cls.rst
   concurrent_unordered_map_cls/parallel_iteration_map_cls.rst
   concurrent_unordered_map_cls/bucket_interface_map_cls.rst
   concurrent_unordered_map_cls/hash_policy_map_cls.rst
