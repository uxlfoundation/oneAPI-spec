=================================
parallel_invoke Template Function
=================================


Summary
-------
Template function that evaluates several functions in parallel.

Header
------

.. code:: cpp

   #include "tbb/parallel_invoke.h"


Syntax
------

.. code:: cpp

   template<typename Func0, typename Func1>
   void parallel_invoke(const Func0& f0, const Func1& f1);
   
   template<typename Func0, typename Func1, typename Func2>
   void parallel_invoke(const Func0& f0, const Func1& f1, const Func2& f2);
   template<typename Func0, typename Func1, ..., typename Func9>
   void parallel_invoke(const Func0& f0, const Func1& f1, ..., const Func9& f9);


Description
-----------

The expression parallel_invoke(f\ :sub:`0`,f\ :sub:`1`,...,f\ :sub:`k`) evaluates
f\ :sub:`0`(), f\ :sub:`1`(), ..., f\ :sub:`k`() possibly in parallel. There can be from 2
to 10 arguments. Each argument must have a type for which ``operator()`` is
defined. Typically the arguments are either function objects or pointers to functions. Return
values are ignored.

Example
-------

The following example evaluates ``f(), g(),`` and
``h()`` in parallel. Notice how ``g`` and ``h`` are
function objects that can hold local state.

.. code:: cpp

   #include "tbb/parallel_invoke.h"
   
   using namespace tbb;
   
   void f();
   extern void bar(int);
   
   class MyFunctor {
       int arg;
   public:
       MyFunctor(int a) : arg(a) {}
       void operator()() const {bar(arg);}
   };
   
   void RunFunctionsInParallel() {
       MyFunctor g(2);
       MyFunctor h(3);
       tbb::parallel_invoke(f, g, h );
   }
     


Example with Lambda Expressions
-------------------------------

Here is the previous example rewritten with C++11 lambda expressions, which generate function objects.

.. code:: cpp

   #include "tbb/parallel_invoke.h"
   
   using namespace tbb;
   
   void f();
   extern void bar(int);
   
   void RunFunctionsInParallel() {
       tbb::parallel_invoke(f, []{bar(2);}, []{bar(3);} );
   }
     
