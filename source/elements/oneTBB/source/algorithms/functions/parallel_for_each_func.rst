=================
parallel_for_each
=================
**[algorithms.parallel_for_each]**

Template function that processes work items in parallel.

.. code:: cpp

    // Defined in header <tbb/parallel_for_each.h>

    namespace tbb {

        template<typename InputIterator, typename Body>
        void parallel_for_each( InputIterator first, InputIterator last, Body body );
        template<typename InputIterator, typename Body>
        void parallel_for_each( InputIterator first, InputIterator last, Body body, task_group_context& group );

        template<typename Container, typename Body>
        void parallel_for_each( Container c, Body body );
        template<typename Container, typename Body>
        void parallel_for_each( Container c, Body body, task_group_context& group );

    } // namespace tbb

Requirements:

* The ``Body`` shall meet the :doc:`parallel_for_each body requirements <../../general/named_requirements/algorithms/par_for_each_body>`.
* The ``InputIterator`` shall meet the `Input Iterator` requiremnts from [input.iterators] ISO C++ Standard section.
* The ``Container`` shall meet the :doc:`Container based sequence requirements <../../general/named_requirements/algorithms/container_based_sequence>`

The ``parallel_for_each`` template has two forms.

The sequence form ``parallel_for_each(first, last, body)`` applies a function object ``body`` over a
sequence [``first,last``). Items may be processed in parallel.

The container form ``parallel_for_each(c, body)`` is equivalent to ``parallel_for_each(std::begin(c), std::end(c), body)``.

The algorithm can be passed a :doc:`task_group_context <../../task_scheduler/task_group_context>`
object so that its tasks are executed in this group. By default the algorithm
is executed in a bound group of its own.

feeder Class
------------

Additional work items can be added by ``body`` if it has a second argument of type ``feeder``.
The function terminates when ``body(x)`` returns for all items ``x`` that were in the input
sequence or added by method ``feeder::add``.

.. toctree::
    :titlesonly:

    feeder.rst


Example
-------

The following code sketches a body with the two-argument form of ``operator()``.

.. code:: cpp

    struct MyBody {
        void operator()(item_t item, parallel_do_feeder<item_t>& feeder ) {
            for each new piece of work implied by item do {
                item_t new_item = initializer;
                feeder.add(new_item);
            }
        }
    };
