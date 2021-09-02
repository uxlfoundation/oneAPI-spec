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

    namespace tbb {

        template<typename Func, typename... Args>
        void collaborative_call_once(collaborative_once_flag& flag, Func&& func, Args&&... args);

    } // namespace tbb

Requirements:

* ``Func`` type must meet the ``Function Objects``
  requirements from the [function.objects] ISO C++ Standard section.

Executes the ``Func`` object under same ``collaborative_once_flag`` only once, even if called concurrently.
But it's allowed for other threads that also called ``collaborative_call_once`` under same
``collaborative_once_flag`` to join nested parallelism inside the ``Func`` object.

All threads that called ``collaborative_call_once`` compete to be the *Winner*, threads that fail to become
the *Winner* become *Moonlighters*. *Moonlighters* can *collaborate* with the *Winner* by joining nested parallelism.

If the invocation of the ``Func`` object was successful, the flag is considered spent and can no longer be reused.
If the invocation throws an exception, it is rethrown only by the *Winner*. The flag remains in its initial state,
so *Moonlighters* will try to become the winner again.

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
