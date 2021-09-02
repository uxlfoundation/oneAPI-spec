.. SPDX-FileCopyrightText: 2019-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=======================
collaborative_once_flag
=======================
**[algorithms.collaborative_call_once.collaborative_once_flag]**

Helper structure for ``collaborative_call_once``.

``collaborative_once_flag`` is passed to ``collaborative_call_once`` as the first argument and serves to resolve
which of the multiple callers under this flag will be the *Winner* and which will collaborate.

.. code:: cpp

    // Defined in header <tbb/collaborative_call_once.h>

    namespace tbb {
        
        class collaborative_once_flag {
        public:
            collaborative_once_flag();
            collaborative_once_flag(const collaborative_once_flag&) = delete;
        };
    } // namespace tbb

Member functions
----------------

.. cpp:function:: collaborative_once_flag()

    Constructs an ``collaborative_once_flag`` object. The initial state indicates that no function has been called.
