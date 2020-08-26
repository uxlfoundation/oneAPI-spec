.. highlight:: cpp
.. default-domain:: cpp

======================
K-Means initialization
======================

The K-Means initialization algorithm gets :math:`n` feature vectors as input and
chooses :math:`k` initial centroids. After initialization, K-Means algorithm
uses the initialization result to partition input data into :math:`k` clusters.

Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional feature vectors and a positive integer :math:`k`, the
problem is to find a set :math:`C = \{ c_1, \ldots, c_k \}` of
:math:`p`-dimensional initial centroids.

-------------
Default dense
-------------

Method choses first :math:`k` feature vectors from the training set :math:`X`

-------------
Usage example
-------------
::

   onedal::table run_compute(const onedal::table& data) {
      const auto kmeans_desc = onedal::kmeans_init::descriptor<float,
                                                               kmeans_init::method::random_dense>{}
         .set_cluster_count(10)

      const auto result = onedal::compute(kmeans_desc, data);

      print_table("centroids", result.get_centroids());

      return result.get_centroids()
   }

---
API
---

Computational methods
---------------------
.. onedal_compute_methods:: oneapi::dal::kmeans_init

Descriptor
----------
.. onedal_class:: oneapi::dal::kmeans_init::descriptor

Input
-----
.. onedal_class:: oneapi::dal::kmeans_init::compute_input

Result
------
.. onedal_class:: oneapi::dal::kmeans_init::compute_result

Operation
---------
.. onedal_func:: oneapi::dal::kmeans_init::compute