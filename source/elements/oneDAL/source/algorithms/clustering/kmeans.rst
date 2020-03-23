.. highlight:: cpp
.. default-domain:: cpp

=======
K-Means
=======

The K-Means algorithm partitions :math:`n` samples into :math:`k` *clusters*
minimizing some criterion. Each cluster is characterized by a representative
point, called *a centroid*.

Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional samples and a positive integer :math:`k`, the problem is
to find a set :math:`C = \{ c_1, \ldots, c_k \}` of :math:`p`-dimensional
centroids that minimize the objective function

.. math::
   \Phi_{X}(C) = \sum_{i = 1}^n d^2(x_i, C),

where :math:`d^2(x_i, C)` is the squared Euclidean distance from :math:`x_i`
to the closest center in :math:`C`,

.. math::
   d^2(x_i, C) = \min_{1 \leq j \leq k} \| x_i - c_j \|^2, \quad 1 \leq i \leq k.

Expression :math:`\|\cdot\|` denotes :math:`L_2` norm.

.. note::
   In the general case, :math:`d` may be an arbitrary distance function. Current
   version of the oneDAL spec defines only Euclidean distance case.


--------------
Lloyd's method
--------------

The Lloyd's method [Lloyd82]_ consists in iterative updates of centroids by
applying the alternating *Assignment* and *Update* steps, where :math:`t`
denotes a number of the current iteration, e.g., :math:`C^{(t)} = \{ c_1^{(t)},
\ldots, c_k^{(t)} \}` is the set of centroids at the :math:`t`-th iteration. The
method requires the initial centroids :math:`C^{(1)}` to be specified.

**(1) Assignment step:** Each sample :math:`x_i` is assigned to the nearest centroid.

.. math::
   y_i^{(t)} = \mathrm{arg}\min_{1 \leq j \leq k} \| x_i - c_j^{(t)} \|^2, \quad 1 \leq i \leq n.

Each observation from the training set :math:`X` is assigned to exactly one
centroid such that :math:`X` is partitioned to :math:`k` disjoint sets
(clusters)

.. math::
   S_j^{(t)} = \big\{ \; x_i \in X : \; y_i^{(t)} = j \; \big\}, \quad 1 \leq j \leq k.

**(2) Update step:** Recalculate centroids by averaging samples assigned to each
cluster.

.. math::
   c_j^{(t + 1)} = \frac{1}{|S_j^{(t)}|} \sum_{x \in S_j^{(t)}} x, \quad 1 \leq j \leq k.

The steps (1) and (2) are performed until the following **stop condition**,

.. math::
   \sum_{j=1}^k \big\| c_j^{(t)} - c_j^{(t+1)} \big\|^2 < \varepsilon,

is satisfied or number of iterations exceeds the maximal value :math:`T` defined
by the user.

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


::

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

Methods
-------
::

   namespace method {
      struct lloyd {};
      using by_default = lloyd;
   } // namespace method

.. namespace:: onedal::kmeans::method
.. struct:: lloyd

   Tag-type that denotes `Lloyd's method`_.


.. type:: by_default = lloyd

   Alias tag-type for the Lloyd's method.


Descriptor
----------
::

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

.. namespace:: onedal::kmeans
.. class:: template<typename Float = float, \
                    typename Method = method::by_default> \
           desc

   :tparam Float: The floating-point type that the algorithm uses for
                  intermediate computations. Can be :expr:`float` or :expr:`double`.

   :tparam Method: Tag-type that specifies variant of K-Means algorithm. Can be
                   :expr:`method::lloyd` or :expr:`method::by_default`.

   .. function:: desc()

      Creates new instance of descriptor with the default attribute values.

   .. member:: std::int64_t cluster_count = 2

      The number of clusters :math:`k`.

      Getter & Setter
         | ``std::int64_t get_cluster_count() const``
         | ``desc& set_cluster_count(std::int64_t)``

      Invariants
         | :expr:`cluster_count > 0`


   .. member:: std::int64_t max_iteration_count = 100

      The maximum number of iterations :math:`T`.

      Getter & Setter
         | ``std::int64_t get_max_iteration_count() const``
         | ``desc& set_max_iteration_count(std::int64_t)``

      Invariants
         | :expr:`max_iteration_count >= 0`


   .. member:: double accuracy_threshold = 0.0

      The threshold :math:`\varepsilon` for the stop condition.

      Getter & Setter
         | ``double get_accuracy_threshold() const``
         | ``desc& set_accuracy_threshold(double)``

      Invariants
         | :expr:`accuracy_threshold >= 0.0`


Model
-----
::

   class model {
   public:
      model();

      const table& get_centroids() const;
      int64_t get_cluster_count() const;
   };

.. class:: model

   .. function:: model()

      Creates model with default attribute values.


   .. member:: table centroids = table()

      :math:`k \times p` table with the cluster centroids. Each row of the table
      stores one centroid.

      Getter
         | ``const table& get_centroids() const``


   .. member:: std::int64_t cluster_count = 0

      Number of clusters :math:`k` in the trained model.

      Getter
         | ``std::int64_t get_cluster_count() const``

      Invariants
         | :expr:`cluster_count == centroids.row_count`


Training :expr:`onedal::train(...)`
-----------------------------------
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

.. class:: train_input

   .. function:: train_input()

      Creates input for the training operation with the default attribute
      values.


   .. function:: train_input(const table& data)

      Creates input for the training operation with the given :expr:`data`, the
      other attributes get default values.


   .. function:: train_input(const table& data, const table& initial_centroids)

      Creates input for the training operation with the given data and
      :expr:`initial_centroids`.


   .. member:: table data = table()

      :math:`n \times p` table with the data to be clustered, where each row
      stores one sample.

      Getter & Setter
         | ``const table& get_data() const``
         | ``train_input& set_data(const table&)``


   .. member:: table initial_centroids = table()

      :math:`k \times p` table with the initial centroids, where each row
      stores one centroid.

      Getter & Setter
         | ``const table& get_initial_centroids() const``
         | ``train_input& set_initial_centroids(const table&)``


Result
~~~~~~
::

   class train_result {
   public:
      train_result();

      const model& get_model() const;
      const table& get_labels() const;
      int64_t get_iteration_count() const;
      double get_objective_function_value() const;
   };

.. class:: train_result

   .. function:: train_result()

      Creates result of the training operation with the default attribute
      values.


   .. member:: kmeans::model model = kmeans::model()

      The trained K-means model.

      Getter
         | ``const model& get_model() const``


   .. member:: table labels = table()

      :math:`n \times 1` table with assignments of cluster indices to samples in
      the input data.

      Getter
         | ``const table& get_labels() const``


   .. member:: std::int64_t iteration_count = 0

      Actual number of iterations performed by the algorithm.

      Invariants
         | :expr:`iteration_count >= 0`


   .. member:: double objective_function_value = 0.0

      The value of the objective function :math:`\Phi_X(C)`, where :math:`C` is
      :expr:`model.centroids` (see :expr:`kmeans::model::centroids`).

      Invariants
         | :expr:`objective_function_value >= 0.0`


Operation semantics
~~~~~~~~~~~~~~~~~~~
.. namespace:: onedal
.. function:: template <typename Descriptor> \
              kmeans::train_result train(const Descriptor& desc, \
                                         const kmeans::train_input& input)

   :tparam Descriptor: K-Means algorithm descriptor :expr:`kmeans::desc`.

   Preconditions
      | :expr:`input.data.is_empty == false`
      | :expr:`input.initial_centroids.is_empty == false`
      | :expr:`input.initial_centroids.row_count == desc.cluster_count`
      | :expr:`input.initial_centroids.column_count == input.data.column_count`

   Postconditions
      | :expr:`result.labels.is_empty == false`
      | :expr:`result.labels.row_count == input.data.row_count`
      | :expr:`result.model.centroids.is_empty == false`
      | :expr:`result.model.clusters.row_count == desc.cluster_count`
      | :expr:`result.model.clusters.column_count == input.data.column_count`
      | :expr:`result.iteration_count <= desc.max_iteration_count`


Inference :expr:`onedal::infer(...)`
------------------------------------

Input
~~~~~
::

   class infer_input {
   public:
      infer_input();
      infer_input(const model& m);
      infer_input(const model& m, const table& data);

      const model& get_model() const;
      const table& get_data() const;

      infer_input& set_model(const model&);
      infer_input& set_data(const table&);
   };

.. namespace:: onedal::kmeans
.. class:: infer_input

   .. function:: infer_input()

      Creates input for the inference operation with the default attribute
      values.


   .. function:: infer_input(const kmeans::model& model)

      Creates input for the inference operation with the given :expr:`model`, the
      other attributes get default values.


   .. function:: infer_input(const kmeans::model& model, const table& data)

      Creates input for the inference operation with the given :expr:`model` and
      :expr:`data`.


   .. member:: table data = table()

      :math:`n \times p` table with the data to be assigned to the clusters,
      where each row stores one sample.

      Getter & Setter
         | ``const table& get_data() const``
         | ``infer_input& set_data(const table&)``


   .. member:: kmeans::model model = kmeans::model()

      The trained K-Means model (see :expr:`kmeans::model`).

      Getter & Setter
         | ``const kmeans::model& get_model() const``
         | ``infer_input& set_model(const kmeans::model&)``


Result
~~~~~~
::

   class infer_result {
   public:
      infer_result();

      const table& get_labels() const;
      double get_objective_function_value() const;
   };


.. class:: infer_result

   .. function:: infer_result()

      Creates result of the inference operation with the default attribute
      values.


   .. member:: table labels = table()

      :math:`n \times 1` table with assignments of cluster indices to samples in
      the input data.

      Getter
         | ``const table& get_labels() const``


   .. member:: double objective_function_value = 0.0

      The value of the objective function :math:`\Phi_X(C)`, where :math:`C` is
      defined by the corresponding :expr:`infer_input::model::centroids`.

      Invariants
         | :expr:`objective_function_value >= 0.0`


Operation semantics
~~~~~~~~~~~~~~~~~~~
.. namespace:: onedal
.. function:: template <typename Descriptor> \
              kmeans::infer_result infer(const Descriptor& desc, \
                                         const kmeans::infer_input& input)

   :tparam Descriptor: K-Means algorithm descriptor :expr:`kmeans::desc`.

   Preconditions
      | :expr:`input.data.is_empty == false`
      | :expr:`input.model.centroids.is_empty == false`
      | :expr:`input.model.centroids.row_count == desc.cluster_count`
      | :expr:`input.model.centroids.column_count == input.data.column_count`

   Postconditions
      | :expr:`result.labels.is_empty == false`
      | :expr:`result.labels.row_count == input.data.row_count`
