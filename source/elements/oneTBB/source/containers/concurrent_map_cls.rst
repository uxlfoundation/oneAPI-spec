=======================================================
concurrent_map and concurrent_multimap Template Classes
=======================================================


Summary
-------

Template classes for ordered associative containers which support concurrent insertion and
traversal (supported since C++11).

Syntax
------

.. code:: cpp

   template <typename Key,
             typename Element,
             typename Compare = std::less<Key>,
             typename Allocator = tbb::tbb_allocator<std::pair<const Key, Element> > >
   class concurrent_map;

.. code:: cpp

   template <typename Key,
             typename Element,
             typename Compare = std::less<Key>,
             typename Allocator = tbb::tbb_allocator<std::pair<const Key, Element> > >
   class concurrent_multimap;


Header
------

.. code:: cpp

   #define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
   #include "tbb/concurrent_map.h"


Description
-----------

``concurrent_map`` and ``concurrent_multimap``
support concurrent insertion and traversal, but not concurrent erasure.
They have semantics similar to the ``std::map`` and
``std::multimap`` respectively, except as follows:

* The ``erase`` and ``extract`` methods are prefixed with
  ``unsafe_``, to indicate that they are not concurrency safe.
* Return values of the ``insert`` and ``emplace`` methods might differ
  from the C++ standard. In particular the methods of ``concurrent_multimap``
  may return ``std::pair<iterator,bool>``, with the Boolean value in the pair
  being always ``true``.
* For ``concurrent_map``, ``insert`` and
  ``emplace`` methods may create a temporary item that is destroyed
  if another thread inserts an item with the same key concurrently.
* Like ``std::list``, insertion of new items does *not* invalidate any
  iterators, nor does it change the order of items already in the map. Insertion and traversal may
  be concurrent.
* Reverse iterators are not supported: ``reverse_iterator``
  and ``const_reverse_iterator`` member types, ``rbegin()`` and ``rend()``
  methods are not available.


Members of both concurrent_map and concurrent_multimap
------------------------------------------------------

In the following synopsis, methods shown in
``bold fond``
may be concurrently invoked.

.. code:: cpp

   public:
       // types
       using key_type = Key;
       using mapped_type = Element;
       using value_type = std::pair<const Key, Element>;
       using key_compare = Compare;
       using allocator_type = Allocator;
       using reference = value_type&
       using const_reference = const value_type&
       using pointer = std::allocator_traits<Allocator>::pointer;
       using const_pointer = std::allocator_traits<Allocator>::const_pointer;
       using size_type = implementation-defined;
       using difference_type = implementation-defined;
       using iterator = implementation-defined;
       using const_iterator = implementation-defined;
       using node_type = implementation-defined;
   
       class value_compare {
       public:
           bool operator()(const value_type& lhs, const value_type& rhs) const;
   
           protected:
               value_compare(key_compare c);
               key_compare comp;
       };
   
       allocator_type get_allocator() const;
   
       // size and capacity
       bool empty const;
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
       template<typename P>
       std::pair<iterator, bool> insert(P&& x);
       std::pair<iterator, bool> insert(value_type&& x);
   
       iterator insert(const_iterator hint, const value_type& x);
       template<typename P>
       iterator insert(const_iterator hint, P&& x);
       iterator insert(const_iterator hint, value_type&& x);
   
       template<typename InputIterator>
       void insert(InputIterator first, InputIterator last);
       void insert(std::initializer_list<value_type> il);
   
       std::pair<iterator, bool> insert(node_type&& nh);
       iterator insert(const_iterator hint, node_type&& nh);
   
       template<typename... Args>
       std::pair<iterator, bool> emplace(Args&&... args);
       template<typename... Args>
       iterator emplace_hint(const_iterator hint, Args&&... args);
   
       template<typename SrcCompare>
       void merge(concurrent_map<Key, Element, SrcCompare, Allocator>& source);
       template<typename SrcCompare>
       void merge(concurrent_map<Key, Element, SrcCompare, Allocator>&& source);
       template<typename SrcCompare>
       void merge(concurrent_multimap<Key, Element, SrcCompare, Allocator>& source);
       template<typename SrcCompare>
       void merge(concurrent_multimap<Key, Element, SrcCompare, Allocator>&& source);
   
       iterator unsafe_erase(const_iterator position);
       iterator unsafe_erase(iterator position);
       iterator unsafe_erase(const_iterator first, const_iterator last);
   
       size_type unsafe_erase(const key_type& k);
   
       template<typename K>
       size_type unsafe_erase(const K& k);
   
       node_type unsafe_extract(const_iterator position);
       node_type unsafe_extract(const key_type& k);
   
       void clear();
   
       // observers
       key_compare key_comp() const;
       value_compare value_comp() const;
   
       // lookup
       iterator find(const key_type& k);
       const_iterator find(const key_type& k) const;
       template<typename K>
       iterator find(const K& k);
       template<typename K>
       const_iterator find(const K& k);
   
       bool contains(const key_type& k);
       template<typename K>
       bool contains(const K& k);
   
       size_type count(const key_type& k) const;
       template<typename K>
       size_type count(const K& k);
   
       std::pair<iterator, iterator> equal_range(const key_type& k);
       std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
   
       template<typename K>
       std::pair<iterator, iterator> equal_range(const K& k);
       template<typename K>
       std::pair<const_iterator, const_iterator> equal_range(const K& k);
   
       iterator lower_bound(const key_type& k);
       const_iterator lower_bound(const key_type& k) const;
   
       template<typename K>
       iterator lower_bound(const K& k);
       template<typename K>
       const_iterator lower_bound(const K& k);
   
       iterator upper_bound(const key_type& k);
       const_iterator upper_bound(const key_type& k) const;
   
       template<typename K>
       iterator upper_bound(const K& k);
       template<typename K>
       const_iterator upper_bound(const K& k) const;
   
       // parallel iteration
       using range_type = implementation-defined;
       using const_range_type = implementation-defined;
       range_type range();
       const_range_type range() const;


Members of concurrent_map
-------------------------

In the following synopsis, methods shown in
``bold fond``
may be concurrently invoked.

.. code:: cpp

   public:
       // construct/destroy/copy
       concurrent_map();
       explicit concurrent_map(const key_compare& comp, const allocator_type& a = allocator_type());
       explicit concurrent_map(const allocator_type& a);
   
       template<typename InputIterator>
       concurrent_map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                      const allocator_type& a = allocator_type());
       template<typename InputIterator>
       concurrent_map(InputIterator first, InputIterator last, const allocator_type& a);
   
       concurrent_map(const concurrent_map& other);
       concurrent_map(const concurrent_map& other, const allocator_type& a);
       concurrent_map(concurrent_map&& other);
       concurrent_map(concurrent_map&& other, const allocator_type& a);
   
       concurrent_map(std::initializer_list<value_type> il, const key_compare& comp = key_compare(),
                      const allocator_type& a = allocator_type());
       concurrent_map(std::initializer_list<value_type> il, const allocator_type& a);
   
       ~concurrent_map();
   
       concurrent_map& operator=(const concurrent_map& other);
       concurrent_map& operator=(concurrent_map&& other);
       concurrent_map& operator=(std::initializer_list<value_type> il);
   
       void swap(concurrent_map& other);
   
       mapped_type& operator[](const key_type& k);
       mapped_type& operator[](key_type&& k);
       mapped_type& at(const key_type& k);
       const mapped_type& at(const key_type& k) const;


Members of concurrent_multimap
------------------------------

.. code:: cpp

   public:
       // construct/destroy/copy
       concurrent_multimap();
       explicit concurrent_multimap(const key_compare& comp, const allocator_type& a = allocator_type());
       explicit concurrent_multimap(const allocator_type& a);
   
       template<typename InputIterator>
       concurrent_multimap(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                           const allocator_type& a = allocator_type());
       template<typename InputIterator>
       concurrent_multimap(InputIterator first, InputIterator last, const allocator_type& a);
   
       concurrent_multimap(const concurrent_multimap& other);
       concurrent_multimap(const concurrent_multimap& other, const allocator_type& a);
       concurrent_multimap(concurrent_multimap&& other);
       concurrent_multimap(concurrent_multimap&& other, const allocator_type& a);
   
       concurrent_multimap(std::initializer_list<value_type> il, const key_compare& comp = key_compare(),
                           const allocator_type& a = allocator_type());
       concurrent_multimap(std::initializer_list<value_type> il, const allocator_type& a);
   
       ~concurrent_multimap();
   
       void swap(concurrent_multimap& other);

Where possible, constructors of ``concurrent_map`` and ``concurrent_multimap``
support class template argument deduction for C++17. For example:

.. code:: cpp

   std::vector<std::pair<int, std::string>> v {{1, "one"}, {2, "two"}};
   tbb::concurrent_map m{v.begin(), v.end()};

declares ``m`` as ``tbb::concurrent_map<int, std::string, std::less<int>, tbb::tbb_allocator<std::pair<const int, std::string>>>``.

See also:

* :doc:`Node handles <node_handles_cls>`
* :doc:`concurrent_set <concurrent_set_cls>`
* :doc:`concurrent_unordered_map <concurrent_unordered_map_cls>`
* :doc:`concurrent_hash_map <concurrent_hash_map_cls>`

.. toctree::

   concurrent_map_cls/construct_destroy_copy_map_cls.rst
   concurrent_map_cls/size_and_capacity_map_cls.rst
   concurrent_map_cls/iterators_map_cls.rst
   concurrent_map_cls/modifiers_map_cls.rst
   concurrent_map_cls/observers_map_cls.rst
   concurrent_map_cls/lookup_map_cls.rst
   concurrent_map_cls/parallel_iteration_map_cls.rst
