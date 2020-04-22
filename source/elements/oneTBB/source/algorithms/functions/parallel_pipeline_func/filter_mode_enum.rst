===========
filter_mode
===========
**[algorithms.parallel_pipeline.filter_mode]**

A ``filter_mode`` enumeration represents an execution mode of a ``filter`` in a ``parallel_pipeline`` algorithm.

Its enumerated values and their meanings are as follows:

* A ``parallel`` filter can process multiple items in parallel and in no particular order.
* A ``serial_out_of_order`` filter processes items one at a time, and in no particular order.
* A ``serial_in_order`` filter processes items one at a time. The order in which items are processed
  is implicitly set by the first `serial_in_order` filter and respected by all other such filters in the pipeline.

.. code:: cpp

    // Defined in header <tbb/parallel_pipeline.h>

    namespace tbb {

        enum class filter_mode {
            parallel = /*implementation-defined*/,
            serial_in_order = /*implementation-defined*/,
            serial_out_of_order = /*implementation-defined*/
        };

    }
