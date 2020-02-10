Engine
------

*Engine* is abstraction of a computational device: a CPU, a specific GPU card in
the system, etc. Most primitives are created to execute computations on one
specific engine. The only exceptions are reorder primitives that transfer data
between two different engines.

.. doxygenstruct:: dnnl::engine
   :project: oneDNN
   :members:


