.. highlight:: cpp
.. default-domain:: cpp

======================
K-Means initialization
======================

The K-Means initialization algorithm receives :math:`n` feature vectors as input
and chooses :math:`k` initial centroids. After initialization, K-Means algorithm
uses the initialization result to partition input data into :math:`k` clusters.

.. |c_math| replace:: `Computing <kmeans_init_c_math_>`_
.. |c_dense| replace:: `Dense <kmeans_init_c_math_dense_>`_
.. |c_input| replace:: `compute_input <kmeans_init_c_api_input_>`_
.. |c_result| replace:: `compute_result <kmeans_init_c_api_result_>`_
.. |c_op| replace:: `compute(...) <kmeans_init_c_api_>`_

=============== =========================== ======== =========== ============
 **Operation**  **Computational methods**     **Programming Interface**
--------------- --------------------------- ---------------------------------
   |c_math|             |c_dense|            |c_op|   |c_input|   |c_result|
=============== =========================== ======== =========== ============

------------------------
Mathematical formulation
------------------------

.. _kmeans_init_c_math:

Computing
---------

Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional feature vectors and a positive integer :math:`k`, the
problem is to find a set :math:`C = \{ c_1, \ldots, c_k \}` of
:math:`p`-dimensional initial centroids.

.. _kmeans_init_c_math_dense:

Computing method: *dense*
-------------------------

The method choses first :math:`k` feature vectors from the training set
:math:`X`.

-------------
Usage example
-------------

Computing
---------
.. onedal_code:: oneapi::dal::kmeans_init::example::run_compute

---------------------
Programming Interface
---------------------

Descriptor
----------
.. onedal_class:: oneapi::dal::kmeans_init::descriptor

Method tags
-----------
.. onedal_compute_methods:: oneapi::dal::kmeans_init

Computing :expr:`compute(...)`
--------------------------------

.. _kmeans_init_c_api_input:

Input
~~~~~
.. onedal_class:: oneapi::dal::kmeans_init::compute_input

.. _kmeans_init_c_api_result:

Result
~~~~~~
.. onedal_class:: oneapi::dal::kmeans_init::compute_result

.. _kmeans_init_c_api:

Operation
~~~~~~~~~
.. onedal_func:: oneapi::dal::kmeans_init::compute
