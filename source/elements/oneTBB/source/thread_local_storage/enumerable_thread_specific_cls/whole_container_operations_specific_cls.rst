==========================
Whole Container Operations
==========================

**Safety**

These operations must not be invoked concurrently
on the same instance of 
``enumerable_thread_specific``.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``enumerable_thread_specific()``
  \
  Constructs an 
  ``enumerable_thread_specific`` where each thread-local
  element will be default-constructed.
------------------------------------------------------------------------------------------
\ ``template<typename Finit> explicit enumerable_thread_specific( Finit finit )``
  \
  Constructs an
  ``enumerable_thread_specific`` such that any
  thread-local element will be created by copying the result of 
  ``finit()``.
  
  .. note::

     The expression 
     ``finit()`` must be safe to evaluate
     concurrently by multiple threads. It is evaluated each time a thread-local
     element is created.
     
     C++11 and beyond: this constructor 
     is only available (i.e. participates in overload resolution)
     if ``finit()`` is a valid expression.
  
------------------------------------------------------------------------------------------
\ ``explicit enumerable_thread_specific( const T& exemplar )``
  
  ``explicit enumerable_thread_specific( T&& exemplar )``
  \
  Constructs an 
  ``enumerable_thread_specific`` where each thread-local
  element will be copy-constructed from 
  ``exemplar``.
  
  .. note::

     C++11 and beyond: move constructor of
     ``T`` can be used to store ``exemplar``
     internally, however thread-local elements are always copy-constructed.
  
------------------------------------------------------------------------------------------
\ ``template <typename... Args> enumerable_thread_specific( Args&&... args );``
  \
  Supported since C++11. Constructs 
  ``enumerable_thread_specific`` such that any
  thread-local element will be constructed by invoking
  ``T(args...)``.
  
  .. note::

     This constructor does not participate in overload resolution
     if the type of the first argument in ``args...`` is ``T``,
     or ``enumerable_thread_specific<T>``, or ``foo()``
     is a valid expression for a value ``foo`` of that type.
  
------------------------------------------------------------------------------------------
\ ``enumerable_thread_specific ( const enumerable_thread_specific& other )``
  
  ``template<typename Alloc, ets_key_usage_type Cachetype> enumerable_thread_specific( const enumerable_thread_specific <T, Alloc, Cachetype>& other )``
  \
  Constructs an ``enumerable_thread_specific``
  as a copy of ``other``. The values are
  copy-constructed from the values in 
  ``other`` and have same thread
  correspondence.
------------------------------------------------------------------------------------------
\ ``enumerable_thread_specific ( enumerable_thread_specific&& other )``
  \
  Supported since C++11. Constructs an ``enumerable_thread_specific``
  by moving the content of ``other`` intact.
  ``other`` is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``template<typename Alloc, ets_key_usage_type Cachetype> enumerable_thread_specific( enumerable_thread_specific <T, Alloc, Cachetype>&& other )``
  \
  Supported since C++11. Constructs an ``enumerable_thread_specific``
  using per-element move construction from the values in ``other``, and
  keeping their thread correspondence.
  ``other`` is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``~enumerable_thread_specific()``
  \
  Destroys all elements in 
  ``*this``. Destroys any native TLS keys that
  were created for this instance.
------------------------------------------------------------------------------------------
\ ``enumerable_thread_specific& operator=( const enumerable_thread_specific& other );``
  \
  Copies the content of 
  ``other`` to ``*this``.
------------------------------------------------------------------------------------------
\ ``template<typename Alloc, ets_key_usage_type Cachetype> enumerable_thread_specific& operator=( const enumerable_thread_specific<T, Alloc, Cachetype>& other );``
  \
  Copies the content of 
  ``other`` to ``*this``.
  
  .. note::

     The allocator and key usage
     specialization is unchanged by this call.
  
------------------------------------------------------------------------------------------
\ ``enumerable_thread_specific& operator=( enumerable_thread_specific&& other );``
  \
  Supported since C++11. Moves the content of 
  ``other`` to ``*this`` intact. 
  ``other`` is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``template<typename Alloc, ets_key_usage_type Cachetype> enumerable_thread_specific& operator=( enumerable_thread_specific<T, Alloc, Cachetype>&& other );``
  \
  Supported since C++11. Moves the content of ``other``
  to ``*this`` using per-element move construction
  and keeping thread correspondence.
  ``other`` is left in an unspecified state, but can be safely destroyed.
  
  .. note::

     The allocator and key usage
     specialization is unchanged by this call.
  
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Destroys all elements in 
  ``*this``. Destroys and then recreates any
  native TLS keys used in the implementation.
  
  .. note::

     In the current implementation, there is
     no performance advantage of using clear instead of destroying and
     reconstructing an 
     ``enumerable_thread_specific``.
  
------------------------------------------------------------------------------------------
= ========================================================================================
