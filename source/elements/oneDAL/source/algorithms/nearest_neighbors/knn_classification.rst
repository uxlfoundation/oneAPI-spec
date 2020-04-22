.. highlight:: cpp
.. default-domain:: cpp

=========================================
k-Nearest Neighbors Classification (k-NN)
=========================================

:math:`k`-NN classification algorithm infers the class for the new feature
vector by computing majority vote of the :math:`k` nearest observations from the
training set.

.. |t_math| replace:: `Training <t_math_>`_
.. |t_api| replace:: `API <t_api_>`_
.. |t_brute_f| replace:: `Brute-force <t_math_brute_force_>`_
.. |t_kd_tree| replace:: `k-d tree <t_math_kd_tree_>`_
.. |t_input| replace:: `train_input <t_api_input_>`_
.. |t_result| replace:: `train_result <t_api_result_>`_
.. |t_op| replace:: `train(...) <t_api_>`_

.. |i_math| replace:: `Inference <i_math_>`_
.. |i_api| replace:: `API <i_api_>`_
.. |i_brute_f| replace:: `Brute-force <i_math_brute_force_>`_
.. |i_kd_tree| replace:: `k-d tree <i_math_kd_tree_>`_
.. |i_input| replace:: `infer_input <i_api_input_>`_
.. |i_result| replace:: `infer_result <i_api_result_>`_
.. |i_op| replace:: `infer(...) <i_api_>`_


=============== ============= ============= ======== =========== ============
 **Operation**  **Computational methods**     **Programming Interface**
--------------- --------------------------- ---------------------------------
   |t_math|      |t_brute_f|   |t_kd_tree|   |t_op|   |t_input|   |t_result|
   |i_math|      |i_brute_f|   |i_kd_tree|   |i_op|   |i_input|   |i_result|
=============== ============= ============= ======== =========== ============

------------------------
Mathematical formulation
------------------------

.. _t_math:

Training
--------
Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional feature vectors, the vector of class labels :math:`y` and
a positive integer :math:`k`, where :math:`y_i \in \{ 0, \ldots, c-1 \}`,
:math:`1 \leq i \leq n`, :math:`c` is the number of classes and :math:`k` is the
number of nearest neighbors specified by the user. The problem is to build a
model that allows efficient distance computation between the feature vectors in
:math:`X` and :math:`X'` at the inference stage.


.. _t_math_brute_force:

Training method: *brute-force*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The training operation produces the model that simply stores all the
feature vectors from the initial training set :math:`X`.


.. _t_math_kd_tree:

Training method: *k-d tree*
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The training operation builds a :math:`k`-:math:`d` tree that partitions the
training set :math:`X` (for more details, see :ref:`kd_tree`).


.. _i_math:

Inference
---------
Given the set :math:`X' = \{ x_1', \ldots, x_m' \}` of :math:`p`-dimensional
feature vectors, the user-defined number of nearest neighbors :math:`k`, and the
model produced by the training operation, the problem is to predict the label
:math:`y_j'` for each :math:`x_j'`, :math:`1 \leq j \leq m`, by performing the
following steps:

#. Identify the set :math:`N(x_j') \subseteq X` of the :math:`k` feature vectors
   in the training set that are nearest to :math:`x_j'` with respect to the
   Euclidean distance.

#. Estimate the conditional probability for the :math:`l`-th class as the
   fraction of vectors in :math:`N(x_j')` whose labels :math:`y_j` are equal to
   :math:`l`:

   .. math::
      :label: p_predict

      P(y_j' = l \; | \; x_j') = \frac{1}{| N(x_j') |}
      \Big| \big\{ x_r \in N(x_j') : y_r = l \big\} \Big|,
      \quad 1 \leq j \leq m, \; 0 \leq l < c.

#. Predict the class that has the highest probability for the feature vector
   :math:`x_j'`:

   .. math::
      :label: y_predict

      y_j' = \mathrm{arg}\max_{0 \leq l < c} P(y_j' = l \; | \; x_j'),
      \quad 1 \leq j \leq m.


.. _i_math_brute_force:

Inference method: *brute-force*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The inference operation determines the set :math:`N(x_j')` of the nearest
feature vectors by iterating over all the pairs :math:`(x_j', x_i)` in the
implementation defined order, :math:`1 \leq i \leq n`, :math:`1 \leq j \leq m`.
The final prediction is computed according to the equations :eq:`p_predict` and
:eq:`y_predict`.


.. _i_math_kd_tree:

Inference method: *k-d tree*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The inference operation traverses the :math:`k`-:math:`d` tree to find feature
vectors associated with a leaf node that are closest to :math:`x_j'`, :math:`1
\leq j \leq m`. The set :math:`\tilde{n}(x_j')` of the currently-known nearest
:math:`k`-th neighbors is progressively updated during tree traversal. The
search algorithm limits exploration of the nodes for which the distance between
the :math:`x_j'` and respective part of the feature space is not less than the
distance between :math:`x_j'` and the most distant feature vector from
:math:`\tilde{n}(x_j')`. Once tree traversal is finished, :math:`\tilde{n}(x_j')
\equiv N(x_j')`. The final prediction is computed according to the equations
:eq:`p_predict` and :eq:`y_predict`.


---------------------
Programming Interface
---------------------

Computational methods
---------------------
.. namespace:: onedal::knn_classification::method

::

   namespace method {
      struct bruteforce {};
      struct kd_tree {};
      using by_default = bruteforce;
   } // namespace method


.. type:: bruteforce

   Tag-type that denotes `brute-force <t_math_brute_force_>`_ computational
   method.


.. type:: kd_tree

   Tag-type that denotes `k-d tree <t_math_kd_tree>`_ computational method.


.. type:: by_default = bruteforce

   Alias tag-type for `brute-force <t_math_brute_force_>`_ computational method.


Descriptor
----------
.. onedal_class:: knn_classification::desc

Model
-----
.. onedal_class:: knn_classification::model


.. _t_api:

Training :expr:`train(...)`
--------------------------------
.. _t_api_input:

Input
~~~~~
.. onedal_class:: knn_classification::train_input


.. _t_api_result:

Result
~~~~~~
.. onedal_class:: knn_classification::train_result


Operation semantics
~~~~~~~~~~~~~~~~~~~
.. onedal_func:: knn_classification::train


.. _i_api:

Inference ``infer(...)``
------------------------
.. _i_api_input:

Input
~~~~~
.. onedal_class:: knn_classification::infer_input


.. _i_api_result:

Result
~~~~~~
.. onedal_class:: knn_classification::infer_result
