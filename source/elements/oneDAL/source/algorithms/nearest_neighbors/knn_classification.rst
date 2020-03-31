.. highlight:: cpp

=========================================
k-Nearest Neighbors Classification (k-NN)
=========================================

:math:`k`-NN classification algorithm infers the class for the new feature
vector by computing majority vote of the :math:`k` nearest samples from the
training set.

.. |math_train| replace:: `Mathematical formulation <math_train_>`_
.. |math_infer| replace:: `Mathematical formulation <math_infer_>`_
.. |api_train| replace:: `Programming Interface <api_train_>`_
.. |api_infer| replace:: `Programming Interface <api_infer_>`_

+------------------------------------------------+
|    Operations supported by :math:`k`-NN        |
+---------------+----------------+---------------+
| **Training**  |  |math_train|  |  |api_train|  |
+---------------+----------------+---------------+
| **Inference** |  |math_infer|  |  |api_infer|  |
+---------------+----------------+---------------+


------------------------
Mathematical formulation
------------------------

.. _math_train:

Training
--------

Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional feature vectors, the vector of class labels :math:`y` and
a positive integer :math:`k`, where :math:`y_i \in \{ 0, \ldots, c-1 \}`,
:math:`1 \leq i \leq n`, :math:`c` is the number of classes and :math:`k` is
number of nearest neighbors specified by the user. The problem is to build a
model that allow efficient distance computation between the feature vectors in
:math:`X` and :math:`X'` for the inference operation.


Brute-force method
~~~~~~~~~~~~~~~~~~

The training operation for brute-force :math:`k`-NN produces the model that
simply stores the unchained training set :math:`X`. The training operation may
precompute some values required for efficient distance computation by the
inference operation.


k-d tree method
~~~~~~~~~~~~~~~



.. _math_infer:

Inference
---------
Given the test set :math:`X' = \{ x_1', \ldots, x_n' \}` of
:math:`p`-dimensional feature vectors, the user defined number of nearest
neighbors :math:`k` and the model produced by the training operation.




---------------------
Programming Interface
---------------------

Computational methods
---------------------
::

   namespace method {
      struct bruteforce {};
      struct kd_tree {};
      using by_default = brutforce;
   } // namespace method

.. namespace:: onedal::knn_classification::method
.. type:: by_default

   Alias tag-type for ..






---------------------
Programming Interface
---------------------
Methods
-------

Descriptor
----------
.. onedal_class:: classification::knn::desc

Model
-----
.. onedal_class:: classification::knn::model


.. _api_train:

Training
--------
Input
~~~~~
.. onedal_class:: classification::knn::train_input

Result
~~~~~~
.. onedal_class:: classification::knn::train_result


.. _api_infer:

Inference
---------
Input
~~~~~
.. onedal_class:: classification::knn::infer_input

Result
~~~~~~
.. onedal_class:: classification::knn::infer_result
=======
