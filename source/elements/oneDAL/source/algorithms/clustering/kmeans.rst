.. highlight:: cpp

=======
K-Means
=======

K-Means is a clustering algorithm that partitions :math:`n` observations into
:math:`k` clusters minimizing some criterion within each cluster. Each cluster
is characterized by a representative point, called *a centroid*, and a cluster
radius.

Given the set :math:`X = \{ x_1, \ldots, x_n \}` of :math:`p`-dimensional
feature vectors and a positive integer :math:`k`, the problem is to find a set
:math:`C = \{ c_1, \ldots, c_k \}` of :math:`p`-dimensional vectors that
minimize the objective function

.. math::
   \Phi_{X}(C)=\sum_{x_i \in X}d(x_i, C),

where :math:`d(x_i, C)` is the distance from :math:`x_i` to the closest center
in :math:`C`.


-------------
Usage example
-------------
::

   onedal::kmeans::model run_training(const onedal::table& data,
                                      const onedal::table& initial_centroids) {

      const auto kmeans_desc = onedal::kmeans::desc<float>{}
         .set_cluster_count(10)
         .set_max_iteration_count(50)
         .set_accuracy_threshold(1e-4);

      const auto result = onedal::train(kmeans_desc, data, initial_centroids);

      print_table("labels", result.get_labels());
      print_table("centroids", result.get_model().get_centroids());
      print_value("objective", result.get_objective_function_value());

      return result.get_model();
   }

   onedal::table run_inference(const onedal::kmeans::model& model,
                               const onedal::table& new_data) {

      const auto kmeans_desc = onedal::kmeans::desc<float>{}
         .set_cluster_count(model.get_cluster_count());

      const auto result = onedal::infer(kmeans_desc, model, new_data);

      print_table("labels", result.get_labels());
   }


---
API
---

Descriptor
----------
::

   namespace method {
      struct lloyd {};
      using by_default = lloyd;
   } // namespace method

   template <typename Float = float,
             typename Method = method::by_default>
   class desc {
   public:
      desc();

      int64_t get_cluster_count() const;
      int64_t get_max_iteration_count() const;
      double get_accuracy_threshold() const;

      desc& set_cluster_count(int64_t);
      desc& set_max_iteration_count(int64_t);
      desc& set_accuracy_threshold(double);
   };

cluster_count ``int64_t`` ``default = 2``
   The number of clusters.

   Invariants
      | ``cluster_count > 0``

max_iterations ``int64_t`` ``default = 100``
   The maximum number of iterations.

   Invariants
      | ``max_iterations > 0``

accuracy_threshold ``double`` ``default = 0.0``
   The threshold for termination.

   Invariants
      | ``accuracy_threshold >= 0.0``


Model
-----
::

   class model {
   public:
      const table& get_centroids() const;
      int64_t get_cluster_count() const;
   };

centroids ``table`` ``[read-only]``
   :math:`[\text{cluster_count} \times \text{feature_count}]` table with the
   cluster centroids. Each row of the table stores one centroid.

   Invariants
      | ``centroids.is_empty() == false``

cluster_count, ``int64_t`` ``[read-only]``
   Number of clusters in the trained model.

   Invariants
      | ``cluster_count == centroids.get_row_count()``


Training ``onedal::train(...)``
-------------------------------
Input
~~~~~
::

   class train_input {
   public:
      train_input();
      train_input(const table& data);
      train_input(const table& data, const table& initial_centroids);

      const table& get_data() const;
      const table& get_initial_centroids() const;

      train_input& set_data(const table&);
      train_input& set_initial_centroids(const table&);
   };

data ``table`` ``default = table()``
   :math:`[\text{observation_count} \times \text{feature_count}]` table with the data
   to be clustered, where each row stores one observation.

initial_centroids ``table`` ``default = table()``
   :math:`[\text{cluster_count} \times \text{feature_count}]` table with the
   initial centroids, where each row stores one centroid.

Result
~~~~~~
::

   class train_result {
   public:
      const model& get_model() const;
      const table& get_labels() const;
      int64_t get_iteration_count() const;
      double get_objective_function_value() const;
   };

model ``kmeans::model`` ``[read-only]``
   The trained K-means model.

labels ``table`` ``[read-only]``
   :math:`[\text{observation_count} \times 1]` table with assignments of cluster
   indices to feature vectors in the input data.

   Invariants
      | ``labels.is_empty() == false``

iteration_count ``int64_t`` ``[read-only]``
   Actual number of iterations performed by the algorithm.

   Invariants
      | ``iteration_count > 0``

objective_function_value ``double`` ``[read-only]``
   The value of the objective function.

   Invariantss
      | ``objective_function_value >= 0.0``


Operation semantics
~~~~~~~~~~~~~~~~~~~
::

   kmeans::train_result train(const kmeans::desc&, const kmeans::train_input&);

**Preconditions**
   | ``input.get_data().is_empty() == false``
   | ``input.get_initial_centroids().is_empty() == false``
   | ``input.get_data().get_column_count() == input.get_initial_centroids().get_column_count()``

**Postconditions**
   | ``result.get_labels().get_row_count() == input.get_data().get_row_count()``
   | ``result.get_model().get_clusters().get_row_count() == desc.get_cluster_count()``
   | ``result.get_model().get_clusters().get_column_count() == input.get_data().get_column_count()``


Inference ``onedal::infer(...)``
--------------------------------

Input
~~~~~
::

   class infer_input {
   public:
      infer_input();
      infer_input(const model& m);
      infer_input(const model& m, const table& data);

      infer_input& set_model(const model&);
      infer_input& set_data(const table&);
   };


Result
~~~~~~
::

   class infer_result {
   public:
      const table& get_labels() const;
   };

