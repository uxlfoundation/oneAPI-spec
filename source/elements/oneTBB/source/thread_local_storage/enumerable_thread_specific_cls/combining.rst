=========
Combining
=========

The methods in this section iterate across the entire container sequentially in the calling thread.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template<typename BinaryFunc> T combine(BinaryFunc f)``
  \
  **Requires**: Parameter
  ``f`` should be an associative
  binary functor with the signature
  ``T(T,T)`` or ``T(const T&,const T&)``.
  
  **Effects**: Computes reduction over all
  elements using binary functor ``f``.
  If there are no elements, creates the result
  using the same rules as for creating a thread-local element.
  
  **Returns**: Result of the reduction.
------------------------------------------------------------------------------------------
\ ``template<typename UnaryFunc> void combine_each(UnaryFunc f)``
  \
  **Requires**: Parameter
  ``f`` should be a unary functor with the signature
  ``void(T)`` or
  ``void(T&)`` or
  ``void(const T&)``.
  
  **Effects**: Evaluates
  ``f(x)`` for each instance
  ``x`` of
  ``T`` in
  ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================
