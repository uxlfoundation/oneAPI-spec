=======================
filter_t Template Class
=======================


Summary
-------
A filter or composite filter used in conjunction
with function 
``parallel_pipeline``.

Header
------

.. code:: cpp

    #include "tbb/pipeline.h"


Syntax
------

.. code:: cpp

   template<typename T, typename U> class filter_t;
   template<typename T, typename U, typename Func>
   filter_t<T,U> make_filter( filter::mode mode, const Func& f );
   template<typename T, typename V, typename U>
   filter_t<T,U> operator&( const filter_t<T,V>& left, 
                            const filter_t<V,U>& right );


Description
-----------

A ``filter_t`` is a strongly typed filter that specifies
its input and output types. A ``filter_t`` can be constructed from a functor or by composing of two 
``filter_t`` objects with 
``operator&`` . The same ``filter_t`` object can be shared by multiple ``&`` expressions.

Members
-------

.. code:: cpp

   namespace tbb {
       template<typename T, typename U>
       class filter_t {
       public:
           filter_t();
           filter_t( const filter_t<T,U>& rhs );
           template<typename Func>
           filter_t( filter::mode mode, const Func& func );
           void operator=( const filter_t<T,U>& rhs );
           ~filter_t();
           void clear();
       };
   
       template<typename T, typename U, typename Func>
       filter_t<T,U> make_filter( filter::mode mode, const Func& f );
       template<typename T, typename V, typename U>
       filter_t<T,U> operator&( const filter_t<T,V>& left, 
                                const filter_t<V,U>& right );
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``filter _t()``
  \
  Construct an undefined filter.
  
  .. caution::

     The effect of using an undefined filter by 
     ``operator&`` or 
     ``parallel_pipeline`` is undefined.
  
------------------------------------------------------------------------------------------
\ ``filter_t( const filter_t<T,U>& rhs )``
  \
  Construct a copy of 
  *rhs*.
------------------------------------------------------------------------------------------
\ ``template<typename Func> filter_t( filter::mode mode, const Func& f )``
  \
  Construct a 
  ``filter_t`` that uses a copy of functor 
  ``f`` to map an input value 
  *t* of type 
  *T* to an output value 
  *u* of type 
  *U*.
  
  .. note::

     When parallel_pipeline uses the 
     ``filter_t``, it computes 
     *u* by evaluating 
     ``f(t)``, unless 
     *T* is 
     ``void``. In the void case 
     *u* is computed by the expression 
     *u* ``= f(fc)``, where 
     ``fc`` is of type flow_control.
  
------------------------------------------------------------------------------------------
\ ``void operator=( const filter_t<T,U>& rhs )``
  \
  Update 
  ``*this`` to use the functor associated with 
  *rhs*.
------------------------------------------------------------------------------------------
\ ``~filter_t()``
  \
  Destroy the 
  ``filter_t``.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Set 
  ``*this`` to an undefined filter.
------------------------------------------------------------------------------------------
\ ``template<typename T, typename U, typename Func> filter_t<T,U> make_filter(filter::mode mode, const Func& f)``
  \
  **Returns**: 
  ``filter_t<T,U>(mode,f)``
------------------------------------------------------------------------------------------
\ ``template<typename T, typename V, typename U> filter_t<T,U> operator& (const filter_t<T,V>& left, const filter_t<V,U>& right)``
  \
  **Requires**: The output type of 
  *left* must match the input type of 
  *right*.
  
  **Returns**: A ``filter_t`` representing the
  composition of filters 
  *left* and 
  *right*. The composition behaves as if the output value
  of 
  *left* becomes the input value of 
  *right*.
------------------------------------------------------------------------------------------
= ========================================================================================

