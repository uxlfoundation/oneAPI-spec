==========================================
parallel_invoke Variadic Template Function
==========================================


Summary
-------

An implementation of ``parallel_invoke`` that uses C++11 variadic templates
to evaluate an arbitrary number of functions in parallel.

Header
------

.. code:: cpp

   #define TBB_PREVIEW_VARIADIC_PARALLEL_INVOKE 1
   #include "tbb/parallel_invoke.h"
      


Syntax
------

.. code:: cpp

   template<typename Func0, typename Func1, typename... Functions>
   void parallel_invoke(Func0&& f0, Func1&& f1, Functions&&... f);
      


Description
-----------

This implementation of ``parallel_invoke`` uses C++11 variadic templates
to accept an arbitrary number of arguments (subject to limitations by a particular compiler).
If ``TBB_PREVIEW_VARIADIC_PARALLEL_INVOKE`` is set to non-zero,
this implementation replaces the default implementation limited by 10 arguments.

See also:

* :doc:`parallel_invoke Template Function <parallel_invoke_func>`
