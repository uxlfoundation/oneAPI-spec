=========================
combinable Template Class
=========================


Summary
-------

Template class for holding thread-local values
during a parallel computation that will be merged into a final value.

Syntax
------

.. code:: cpp

   template<typename T> class combinable;


Header
------

.. code:: cpp

   #include "tbb/combinable.h"


Description
-----------

A
``combinable<T>`` provides each thread with its own
instance of type ``T``.

Members
-------

.. code:: cpp

   namespace tbb {
       template <typename T>
       class combinable {
       public:
           combinable();
   
           template <typename FInit>
           explicit combinable(FInit finit);
   
           combinable(const combinable& other);
           // Supported since C++11
           combinable(combinable&& other);
   
           ~combinable();
   
           combinable& operator=( const combinable& other);
           // Supported since C++11
           combinable& operator=( combinable&& other);
   
           void clear();
   
           T& local();
           T& local(bool & exists);
   
           template<typename BinaryFunc> T combine(BinaryFunc f);
           template<typename UnaryFunc> void combine_each(UnaryFunc f);
       };
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``combinable()``
  \
  Constructs
  ``combinable`` such that thread-local
  instances of
  ``T`` will be default-constructed.
------------------------------------------------------------------------------------------
\ ``template<typename FInit> explicit combinable(FInit finit)``
  \
  Constructs
  ``combinable`` such that thread-local
  elements will be created by copying the result of
  *finit()*.
  
  .. caution::

     The expression *finit()* must be safe to evaluate
     concurrently by multiple threads. It is evaluated each time
     a new thread-local element is created.
  
------------------------------------------------------------------------------------------
\ ``combinable( const combinable& other );``
  \
  Constructs a copy of
  *other*, so that it has copies of each element in
  *other* with the same thread mapping.
------------------------------------------------------------------------------------------
\ ``combinable( combinable&& other );``
  \
  Supported since C++11. Constructs ``combinable`` by moving
  the content of *other* intact. *other* is left
  in an unspecified state but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``~combinable()``
  \
  Destroys all elements in ``*this``.
------------------------------------------------------------------------------------------
\ ``combinable& operator=( const combinable& other )``
  \
  Sets ``*this`` to be a copy of
  *other*.
------------------------------------------------------------------------------------------
\ ``combinable& operator=( combinable&& other )``
  \
  Supported since C++11. Moves the content of *other* to
  ``*this`` intact. *other* is left
  in an unspecified state but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Removes all elements from ``*this``.
------------------------------------------------------------------------------------------
\ ``T& local()``
  \
  If an element does not exist for the current thread, creates it.
  
  **Returns**: Reference to thread-local element.
------------------------------------------------------------------------------------------
\ ``T& local( bool& exists )``
  \
  Similar to
  ``local()``, except that
  *exists* is set to true if an element was already
  present for the current thread; false otherwise.
  
  **Returns**: Reference to thread-local element.
------------------------------------------------------------------------------------------
\ ``template<typename BinaryFunc>T combine(BinaryFunc f)``
  \
  **Requires**: Parameter
  *f* should be an associative
  binary functor with the signature ``T(T,T)``
  or ``T(const T&,const T&)``.
  
  **Effects**: Computes a reduction over
  all elements using binary functor *f*. All evaluations
  of *f* are done sequentially in the calling thread.
  If there are no elements, creates the result
  using the same rules as for creating a new element.
  
  **Returns**: Result of the reduction.
------------------------------------------------------------------------------------------
\ ``template<typename UnaryFunc> void combine_each(UnaryFunc f)``
  \
  **Requires**: Parameter
  *f* should be a unary functor with the signature
  ``void(T)`` or ``void(T&)`` or
  ``void(const T&)``.
  
  **Effects**: Evaluates
  *f(x)* for each thread-local element
  *x* in ``*this``. All evaluations
  are done sequentially in the calling thread.
------------------------------------------------------------------------------------------
= ========================================================================================

.. note::

   Methods of ``class combinable`` are not thread-safe,
   except for ``local``.
