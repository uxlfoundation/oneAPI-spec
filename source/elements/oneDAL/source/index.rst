..
  Copyright 2020 Intel Corporation

.. _oneDAL-section:

==============================================
Intel oneAPI Data Analytics Library
==============================================

.. |github| replace:: oneDAL GitHub\* page
.. _github: https://github.com/intel/daal

Intel oneAPI Data Analytics Library
------------------------------------------------------
This document specifies requirements for implementations of Intel oneAPI Data Analytics Library (oneDAL).

oneDAL is a library
that helps speed up big data analysis by providing highly optimized
algorithmic building blocks for all stages of data analytics
(preprocessing, transformation, analysis, modeling, validation, and
decision making) in batch, online, and distributed processing modes of
computation. The current version of oneDAL provides
Data Parallel C++ (DPC++) API extensions to the traditional C++ interface.

For general information, visit |github|.

.. toctree::
   :maxdepth: 3
   :caption: Introduction

   introduction/classical-ml.rst
   introduction/classes.rst
   introduction/building-blocks.rst

.. toctree::
   :maxdepth: 2
   :caption: Programming model

   programming/model.rst
   programming/algoritmics.rst

.. toctree::
   :maxdepth: 2
   :caption: Data management

   data/numeric_tables.rst
   data/structures.rst

.. toctree::
   :maxdepth: 3
   :caption: Algorithms

   algorithms/modes.rst
   algorithms/algorithm_inputs.rst
   algorithms/algorithm_outputs.rst
   algorithms/algorithm_descriptor.rst
   algorithms/algorithm_processing.rst
   algorithms/analysis.rst
   algorithms/unsupervised_learning.rst
   algorithms/supervised_learning.rst

.. toctree::
   :maxdepth: 1
   :caption: Services

   services.rst

.. toctree::
   :maxdepth: 1
   :caption: Bibliography

   bibliography.rst


.. _'full_name': Intel\ |reg|\  oneAPI Data Analytics Library
.. _'shourt_name' : oneDAL
.. _'product': oneDAL
.. _'namespace': daal
.. _'daal_in_code': daal
.. _'base_tk': Intel\ |reg|\  oneAPI Base Toolkit
.. _'dpcpp': Intel\ |reg|\  oneAPI DPC++ Compiler
