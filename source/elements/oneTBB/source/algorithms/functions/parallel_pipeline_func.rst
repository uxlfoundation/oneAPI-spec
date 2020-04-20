==========================
parallel_pipeline Function
==========================

Strongly-typed interface for pipelined execution.

.. code:: cpp

    // Defined in header <tbb/parallel_pipeline.h>

    namespace tbb {

    void parallel_pipeline( size_t max_number_of_live_tokens, const filter_t<void,void>& filter_chain );
    void parallel_pipeline( size_t max_number_of_live_tokens, const filter_t<void,void>& filter_chain, task_group_context& group] );

    } // namespace tbb

A `parallel_pipeline` algorithm represents pipelined application of a series of filters to a stream of items.
Each filter operates in a particular mode: parallel, serial in-order, or serial out-of-order (MacDonald 2004).

To build and run a pipeline from functors *g*\ :sub:`0`, *g*\ :sub:`1`, *g*\ :sub:`2`, ..., *g*\ :sub:`n`, write:

.. code:: cpp

   parallel_pipeline( max_number_of_live_tokens,
                      make_filter<void,I1>(mode0,g0) &
                      make_filter<I1,I2>(mode1,g1) &
                      make_filter<I2,I3>(mode2,g2) &
                      ...
                      make_filter<In,void>(moden,gn) );

In general, functor *g*\ :sub:`i` should define its ``operator()`` to map objects of type
*I*\ :sub:`i` to objects of type *I*\ :sub:`i+1`. Functor *g*\ :sub:`0` is a special case, because
it notifies the pipeline when the end of the input stream is reached. Functor *g*\ :sub:`0` must
be defined such that for a *flow_control* object *fc*, the expression *g*\ :sub:`0` (*fc* ) either
returns the next value in the input stream, or if at the end of the input stream, invokes *fc.stop()*
and returns a dummy value.

Each `filter_t` should be instantiated by a special way...(TODO)

The number of items processed in parallel depends upon the structure of the pipeline and number of available threads.
At most *max_number_of_live_tokens* set the threshold for number of concurrently processed tokens.

If the *group* argument is specified, pipeline's tasks are executed in this group. By default the algorithm
is executed in a bound group of its own.

Example
-------

The following example uses ``parallel_pipeline`` compute the root-mean-square of a sequence defined
by [ *first* , *last* ). The example is only for demonstrating syntactic mechanics. It is not as a
practical way to do the calculation because parallel overhead would be vastly higher than useful
work. Operator `&` requires that the output type of its first ``filter_t`` argument matches the input
type of its second ``filter_t`` argument.

.. code:: cpp

    float RootMeanSquare( float* first, float* last ) {
        float sum=0;
        parallel_pipeline( /*max_number_of_live_token=*/16,       
            make_filter<void,float*>(
                filter::serial,
                [&](flow_control& fc)-> float*{
                    if( first<last ) {
                        return first++;
                     } else {
                        fc.stop();
                        return NULL;
                    }
                }    
            ) &
            make_filter<float*,float>(
                filter::parallel,
                [](float* p){return (*p)*(*p);} 
            ) &
            make_filter<float,void>(
                filter::serial,
                [&](float x) {sum+=x;}
            )
        );
        return sqrt(sum);
    }


See the oneAPI Threading Building Blocks Tutorial for a non-trivial example of ``parallel_pipeline``.

filter_t Template Class
-----------------------

.. toctree::

    parallel_pipeline_func/filter_t_cls.rst

flow_control Class
------------------

.. toctree::

   parallel_pipeline_func/flow_control_cls.rst

See also:

* :doc:`task_group_context <../../task_scheduler/task_group_context>`
