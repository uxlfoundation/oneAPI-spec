=====
graph
=====
**[flow_graph.graph]**

Class that serves as a handle to a flow graph of nodes and edges.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        class graph {
        public:
            graph();
            graph(task_group_context& context);
            ~graph();

            void wait_for_all();

            bool is_cancelled();
            bool exception_thrown();
            void reset(reset_flags f = rf_reset_protocol);
        };

    } // namespace flow
    } // namespace tbb

reset_flags enumeration
-----------------------

.. toctree::
    :titlesonly:

    reset_flags_enum.rst

Member functions
----------------

.. cpp:function:: graph(task_group_context& group )

    Constructs a graph with no nodes. If ``group`` is specified, the
    graph tasks are executed in this group. By default, the graph is
    executed in a bound context of its own.

.. cpp:function:: ~graph()

    Calls ``wait_for_all`` on the graph, then destroys the graph.

.. cpp:function:: void wait_for_all()

    Blocks execution until all tasks associated with the graph have completed.

.. cpp:function:: void reset(reset_flags f = rf_reset_protocol)

    Resets the graph according to the specified flags.
    Flags to ``reset()`` can be combined with bitwise-``or``.

.. cpp:function:: bool is_cancelled()

    Returns: ``true`` if the graph was cancelled during the last call to
    ``wait_for_all()``; ``false``, otherwise.

.. cpp:function:: bool exception_thrown()

    Returns: ``true`` if during the last call to ``wait_for_all()`` an
    exception was thrown; ``false``, otherwise.
