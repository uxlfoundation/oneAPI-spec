==================================
Construction, Copy, and Assignment
==================================

.. caution::

   These operations must not be invoked concurrently on the same vector.

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``concurrent_vector( const allocator_type& a = allocator_type() )``
  \
  Constructs an empty vector using optionally specified allocator instance.
------------------------------------------------------------------------------------------
\ ``concurrent_vector( size_type n, const_reference t=T(), const allocator_type& a = allocator_type() );``
  \
  Constructs a vector of ``n`` copies of
  ``t``, using optionally specified allocator instance. If
  ``t`` is not specified, each element is default-constructed
  instead of copied.
------------------------------------------------------------------------------------------
\ ``template<typename InputIterator> concurrent_vector( InputIterator first, InputIterator last, const allocator_type& a = allocator_type() )``
  \
  Constructs a vector that is a copy of the sequence
  ``[first,last)``, making only ``N`` calls to the
  copy constructor of ``T``, where ``N`` is the distance
  between ``first`` and ``last``.
------------------------------------------------------------------------------------------
\ ``concurrent_vector( std::initializer_list<T> il, const allocator_type &a = allocator_type() )``
  \
  Supported since C++11. Equivalent to
  ``concurrent_vector( il.begin(), il.end(), a)`` .
------------------------------------------------------------------------------------------
\ ``concurrent_vector( const concurrent_vector& src )``
  \
  Constructs a copy of ``src``.
------------------------------------------------------------------------------------------
\ ``concurrent_vector( const concurrent_vector& src, const allocator_type& a )``
  \
  Constructs a new vector by copying content from
  ``src`` using allocator ``a``.
------------------------------------------------------------------------------------------
\ ``template<class M> concurrent_vector( const concurrent_vector<T,M>& src, const allocator_type& a = allocator_type() )``
  \
  Constructs a new vector by copying content from
  ``src`` using allocator ``a``.
------------------------------------------------------------------------------------------
\ ``concurrent_vector(concurrent_vector&& src )``
  \
  Supported since C++11. Constructs a new vector by moving content from
  ``src``. ``src`` is left in an
  unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_vector( concurrent_vector&& src, const allocator_type& a )``
  \
  Supported since C++11. Constructs a new vector by moving content from
  ``src`` using allocator ``a``.
  ``src`` is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_vector& operator=( const concurrent_vector& src )``
  \
  Assigns the contents of ``src`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_vector& operator=(concurrent_vector&& src)``
  \
  Supported since C++11. Moves data from ``src`` to
  ``*this``. ``src`` is left in an
  unspecified state, but can be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``template<typename M> concurrent_vector& operator=( const concurrent_vector<T, M>& src )``
  \
  Assigns the contents of ``src`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_vector& operator=( std::initializer_list<T> il )``
  \
  Supported since C++11. Sets ``*this`` to contain data from
  ``il``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``void assign( size_type n, const_reference t )``
  \
  Assigns ``n`` copies of ``t`` to ``*this``.
------------------------------------------------------------------------------------------
\ ``template<class InputIterator> void assign( InputIterator first, InputIterator last )``
  \
  Assigns the contents of the sequence ``[first,last)``, making only
  ``N`` calls to the copy constructor of ``T``, where
  ``N`` is the distance between ``first`` and ``last``.
------------------------------------------------------------------------------------------
\ ``void assign( std::initializer_list<T> il )``
  \
  Supported since C++11. Equivalent to
  ``assign(il.begin(), il.end())``.
------------------------------------------------------------------------------------------
= ========================================================================================
