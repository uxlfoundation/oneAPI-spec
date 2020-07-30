.. _onemkl_rng_nondeterministic:

nondeterministic
================

Non-deterministic random number generator.

.. _onemkl_rng_nondeterministic_description:

.. rubric:: Description

Implementation defined generator with non-deterministic source of randomness(e.g. a hardware device).

.. _onemkl_rng_nondeterministic_description_syntax:

class nondeterministic
----------------------

.. rubric:: Syntax

.. code-block:: cpp

    class nondeterministic {
    public:
        nondeterministic(sycl::queue& queue);
        nondeterministic (const nondeterministic& other);
        nondeterministic& operator=(const nondeterministic& other);
        ~nondeterministic();
    };

.. cpp:class:: oneapi::mkl::rng::nondeterministic

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `nondeterministic(sycl::queue& queue)`_
          - Constructor for the particular device
        * - `nondeterministic(const nondeterministic& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`nondeterministic(sycl::queue& queue)`:

    .. cpp:function:: nondeterministic::nondeterministic(sycl::queue& queue)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.


    .. _`nondeterministic(const nondeterministic& other)`:

    .. cpp:function:: nondeterministic::nondeterministic(const nondeterministic& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``nondeterministic`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one. Note: needed only to change the queue.

.. container:: section

    .. rubric:: Subsequence selection functions support

    .. list-table::
        :header-rows: 1

        * - Routine
          - Support
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::uint64_t num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Note supported
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::initializer_list\<std::uint64_t\> num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Not supported
        * - :ref:`oneapi::mkl::rng::leapfrog(EngineType& engine, std::uint64_t idx, std::uint64_t stride)<onemkl_rng_leapfrog>`
          - Not supported
   
**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
