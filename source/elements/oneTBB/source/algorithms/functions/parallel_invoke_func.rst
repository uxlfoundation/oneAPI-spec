===============
parallel_invoke
===============
**[algortihms.parallel_invoke]**

Template function that evaluates several functions in parallel.

.. code:: cpp

    // Defined in header <tbb/parallel_invoke.h>

    namespace tbb {

        template<typename... Functions>
        void parallel_invoke(Functions&&... fs);

    } // namespace tbb

Requirements:

* All members of ``Functions`` parameter pack shall meet ``Function Objects``
  requiremnts from [function.objects] ISO C++ Standard section or be a pointer to a function.
* Last member of ``Functions`` parameter pack may be a ``task_group_context&`` type.

Evaluates each member passed to ``parrallel_invoke`` possibly in parallel. Return values are ignored.

The algoritm can accept a :doc:`task_group_context <../../task_scheduler/task_group_context>` object
so that the algorithm’s tasks are executed in this group. By default the algorithm is executed in a bound group of its own.

Example
-------

The following example evaluates ``f()``, ``g()``, ``h()``, and ``bar(1)`` in parallel.

.. code:: cpp

    #include "tbb/parallel_invoke.h"

    extern void f();
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

        tbb::parallel_invoke(f, g, h, []{bar(1);});
    }
