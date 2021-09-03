.. SPDX-FileCopyrightText: 2019-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=======================
collaborative_call_once
=======================
**[algorithms.collaborative_call_once]**

Function template that executes function exactly once.

.. code:: cpp

    // Defined in header <tbb/collaborative_call_once.h>

    namespace oneapi {
        namespace tbb {

            template<typename Func, typename... Args>
            void collaborative_call_once(collaborative_once_flag& flag, Func&& func, Args&&... args);

        } // namespace tbb
    } // namespace oneapi

Requirements:

* ``Func`` type must meet the ``Function Objects``
  requirements from the [function.objects] ISO C++ Standard section.

Executes the ``Func`` object only once, even if called concurrently. It allows other threads
blocked on the same ``collaborative_once_flag`` to join oneTBB parallel construction called
inside the ``Func`` object.

In case of the exception thrown from the ``Func`` object, the thread calling the ``Func`` object 
receives this exception. One of the threads blocked on the same ``collaborative_once_flag``
calls the ``Func`` object again. 

collaborative_once_flag Class
-----------------------------

Helper class that ``collaborative_call_once`` uses to perform a call only once and to connect the *Winner*
and *Moonlighters* for a collaboration.

.. toctree::
    :titlesonly:

    collaborative_once_flag_cls.rst


Example
-------

The following example sketches a class in which the "Lazy initialization" pattern is implemented on the field
"cachedProperty"

.. code:: cpp

    #include "tbb/collaborative_call_once.h"

    extern double foo(int i);

    class LazyData {
        tbb::collaborative_once_flag flag;
        double cachedProperty;
    public:
        double getProperty() {
            tbb::collaborative_call_once(flag, [&] {
                // serial part
                std::atomic<double> result;

                // parallel part where threads can collaborate
                tbb::parallel_for(0, 1000, [&] (int r) {
                    result += foo(r);
                });

                // continue serial part
                cachedProperty = result;
            });

            return cachedProperty;
        }
    };
