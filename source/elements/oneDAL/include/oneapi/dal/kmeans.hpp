#include <cstdint>
#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::kmeans {

namespace method {
   /// Tag-type that denotes `Lloyd's <kmeans_t_math_lloyd_>`_ computational
   /// method.
   struct lloyd {};

   /// Alias tag-type for `Lloyd's <kmeans_t_math_lloyd_>`_ computational
   /// method.
   using by_default = lloyd;
} // namespace method

namespace task {
   /// Tag-type that parametrizes entities used for solving
   /// :capterm:`clustering problem <clustering>` .
   struct clustering {};

   /// Alias tag-type for custering task.
   using by_default = clustering;
} // namespace task

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::lloyd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::clustering`.
template <typename Float = float,
          typename Method = method::by_default,
          typename Task = task::by_default>
class descriptor {
public:
   /// Creates a new instance of the class with the given :literal:`cluster_count`
   explicit descriptor(std::int64_t cluster_count = 2);

   /// The number of clusters $k$
   /// @invariant :expr:`cluster_count > 0`
   /// @remark default = 2
   int64_t get_cluster_count() const;
   descriptor& set_cluster_count(int64_t);

   /// The maximum number of iterations $T$
   /// @invariant :expr:`max_iteration_count >= 0`
   /// @remark default = 100
   int64_t get_max_iteration_count() const;
   descriptor& set_max_iteration_count(int64_t);

   /// The threshold $\\varepsilon$ for the stop condition
   /// @invariant :expr:`accuracy_threshold >= 0.0`
   /// @remark default = 0.0
   double get_accuracy_threshold() const;
   descriptor& set_accuracy_threshold(double);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class model {
public:
   /// Creates a new instance of the class with the default property values.
   model();

   /// $k \\times p$ table with the cluster centroids. Each row of the
   /// table stores one centroid.
   /// @remark default = table{}
   const table& get_centroids() const;

   /// Number of clusters $k$ in the trained model.
   /// @invariant :expr:`cluster_count == centroids.row_count`
   /// @remark default = 0
   int64_t get_cluster_count() const;
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class train_input {
public:
   /// Creates a new instance of the class with the given :literal:`data` and
   /// :literal:`initial_centroids`
   train_input(const table& data = table{},
               const table& initial_centroids = table{});

   /// $n \\times p$ table with the data to be clustered, where each row
   /// stores one feature vector.
   const table& get_data() const;
   train_input& set_data(const table&);

   /// $k \\times p$ table with the initial centroids, where each row
   /// stores one centroid.
   const table& get_initial_centroids() const;
   train_input& set_initial_centroids(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class train_result {
public:
   /// Creates a new instance of the class with the default property values.
   train_result();

   /// The trained K-means model
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;

   /// $n \\times 1$ table with the labels $y_i$ assigned to the
   /// samples $x_i$ in the input data, $1 \\leq 1 \\leq n$.
   /// @remark default = table{}
   const table& get_labels() const;

   /// The number of iterations performed by the algorithm.
   /// @remark default = 0
   /// @invariant :expr:`iteration_count >= 0`
   int64_t get_iteration_count() const;

   /// The value of the objective function $\\Phi_X(C)$, where $C$ is
   /// :expr:`model.centroids` (see :expr:`kmeans::model::centroids`).
   /// @invariant :expr:`objective_function_value >= 0.0`
   double get_objective_function_value() const;
};

/// Runs the training operation for K-Means clustering. For more details see
/// :expr:`oneapi::dal::train`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::lloyd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::clustering`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the training operation
/// @return result   Result of the training operation
///
/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.initial_centroids.row_count == desc.cluster_count`
/// @pre :expr:`input.initial_centroids.column_count == input.data.column_count`
/// @post :expr:`result.labels.row_count == input.data.row_count`
/// @post :expr:`result.labels.column_count == 1`
/// @post :expr:`result.labels[i] >= 0`
/// @post :expr:`result.labels[i] < desc.cluster_count`
/// @post :expr:`result.iteration_count <= desc.max_iteration_count`
/// @post :expr:`result.model.clusters.row_count == desc.cluster_count`
/// @post :expr:`result.model.clusters.column_count == input.data.column_count`
template <typename Float, typename Method, typename Task>
train_result<Task> train(const descriptor<Float, Method, Task>& desc,
                         const train_input<Task>& input);

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class infer_input {
public:
   /// Creates a new instance of the class with the given :literal:`model` and
   /// :literal:`data`
   infer_input(const model<Task>& m = model<Task>{},
               const table& data = table{});

   /// $n \\times p$ table with the data to be assigned to the clusters,
   /// where each row stores one feature vector.
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;
   infer_input& set_model(const model<Task>&);

   /// The trained K-Means model
   /// @remark default = table{}
   const table& get_data() const;
   infer_input& set_data(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class infer_result {
public:
   /// Creates a new instance of the class with the default property values.
   infer_result();

   /// $n \\times 1$ table with assignments labels to feature
   /// vectors in the input data.
   /// @remark default = table{}
   const table& get_labels() const;

   /// The value of the objective function $\\Phi_X(C)$, where $C$ is
   /// defined by the corresponding :expr:`infer_input::model::centroids`.
   /// @invariant :expr:`objective_function_value >= 0.0`
   /// @remark default = 0.0
   double get_objective_function_value() const;
};

/// Runs the inference operation for K-Means clustering. For more details see
/// :expr:`oneapi::dal::infer`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::lloyd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::clustering`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the inference operation
/// @return result   Result of the inference operation
///

/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.model.centroids.row_count == desc.cluster_count`
/// @pre :expr:`input.model.centroids.column_count == input.data.column_count`
/// @post :expr:`result.labels.row_count == input.data.row_count`
/// @post :expr:`result.labels.column_count == 1`
/// @post :expr:`result.labels[i] >= 0`
/// @post :expr:`result.labels[i] < desc.cluster_count`
template <typename Float, typename Method, typename Task>
infer_result<Task> infer(const descriptor<Float, Method, Task>& desc,
                         const infer_input<Task>& input);

} // namespace oneapi::dal::kmeans

namespace oneapi::dal::kmeans::example {

kmeans::model<> run_training(const table& data,
                             const table& initial_centroids) {
   const auto kmeans_desc = kmeans::descriptor<float>{}
      .set_cluster_count(10)
      .set_max_iteration_count(50)
      .set_accuracy_threshold(1e-4);

   const auto result = train(kmeans_desc, data, initial_centroids);

   print_table("labels", result.get_labels());
   print_table("centroids", result.get_model().get_centroids());
   print_value("objective", result.get_objective_function_value());

   return result.get_model();
}

table run_inference(const kmeans::model<>& model,
                    const table& new_data) {
   const auto kmeans_desc = kmeans::descriptor<float>{}
      .set_cluster_count(model.get_cluster_count());

   const auto result = infer(kmeans_desc, model, new_data);

   print_table("labels", result.get_labels());
}

} // oneapi::dal::kmeans::example
