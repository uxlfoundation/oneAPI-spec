==========
Algorithms
==========

Most parallel algorithms provided by oneAPI Threading Building Blocks are generic. They operate on all
types that model the necessary concepts. Parallel algorithms may be nested. For
example, the body of a ``parallel_for`` can invoke another ``parallel_for``.

.. caution::

   When the body of an outer parallel algorithm invokes another parallel
   algorithm, it may cause the outer body to be re-entered for a different
   iteration of the outer algorithm.
   
   For example, if the outer body holds a global lock while calling an
   inner parallel algorithm, the body will deadlock if the re-entrant invocation
   attempts to acquire the same global lock. This ill-formed example is a special
   case of a general rule that code should not hold a lock while calling code
   written by another author.

.. toctree::

   algorithms/splittable_concept.rst
   algorithms/range_concept.rst
   algorithms/partitioners.rst

   algorithms/parallel_for_func.rst
   algorithms/parallel_reduce_func.rst
   algorithms/parallel_deterministic_reduce_func.rst
   algorithms/parallel_scan_func.rst

   algorithms/parallel_do_func.rst
   algorithms/parallel_for_each_func.rst

   algorithms/parallel_invoke_func.rst
   algorithms/variadic_parallel_invoke_func.rst
   algorithms/parallel_pipeline_func.rst
   algorithms/parallel_sort_func.rst
