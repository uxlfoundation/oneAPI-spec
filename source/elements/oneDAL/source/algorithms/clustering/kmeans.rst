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


API
---

Descriptor
++++++++++
.. code-block:: c++

   namespace onedal::kmeans {

   namespace method {
   struct lloyd {};
   using by_default = lloyd;
   } // namespace method

   template <typename Float = float,
             typename Method = method::by_default>
   class desc {
   public:
      double get_gamma() const;
      double get_accuracy_threshold() const;
      std::int64_t get_cluster_count() const;
      std::int64_t get_max_iteration_count() const;

      desc& set_gamma(double);
      desc& set_accuracy_threshold(double);
      desc& set_cluster_count(std::int64_t);
      desc& set_max_iteration_count(std::int64_t);
   };

   } // namespace onedal::kmeans


Model
+++++
.. code-block:: c++

   class model {
   public:
      const table& get_centroids() const;
   };


Training
++++++++

Input
~~~~~
.. code-block:: c++

   namespace onedal::kmeans {

   class train_input {
   public:
      train_input();
      train_input(const table& data);
      train_input(const table& data, const table& initial_centroids);

      train_input& set_data(const table&);
      train_input& set_initial_centroids(const table&);
   };

   } // namespace onedal::kmeans


Result
~~~~~~
.. code-block:: c++

   namespace onedal::kmeans {

   class train_result {
   public:
      const model& get_model() const;
      const table& get_labels() const;
      std::int64_t get_iteration_count() const;
      double get_objective_function_value() const;
   };

   } // namespace onedal::kmeans


Usage example
~~~~~~~~~~~~~

.. code-block:: c++

   int main() {
      auto kmeans_desc = onedal::kmeans::desc{}
         .set_cluster_count(10);

      onedal::train(kmeans_desc, x_train, x_train_centroids);
   }


Inference
+++++++++

Input
~~~~~
.. code-block:: c++

   namespace onedal::kmeans {

   class infer_input {
   public:
      infer_input();
      infer_input(const model& m);
      infer_input(const model& m, const table& data);

      infer_input& set_model(const model&);
      infer_input& set_data(const table&);
   };

   } // namespace onedal::kmeans


Result
~~~~~~
.. code-block:: c++

   namespace onedal::kmeans {

   class infer_result {
   public:
      const table& get_labels() const;
   };

   } // namespace onedal::kmeans




