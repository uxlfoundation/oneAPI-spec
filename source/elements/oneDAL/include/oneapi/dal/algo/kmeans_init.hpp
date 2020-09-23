#include "oneapi/dal/table/common.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::kmeans_init {

namespace method {
   /// Tag-type that denotes `dense <kmeans_init_c_math_dense_>`_
   /// computational method.
   struct dense {};

   using by_default = dense;
} // namespace method

namespace task {
   /// Tag-type that parameterizes entities used for obtaining the initial K-Means centroids.
   struct init {};

   /// Alias tag-type for the initialization task.
   using by_default = init;
} // namespace task

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation
///                of K-Means Initialization algorithm.
/// @tparam Task   Tag-type that specifies the type of the problem to solve. Can
///                be :expr:`task::init`.
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
   std::int64_t get_cluster_count() const;
   descriptor& set_cluster_count(std::int64_t);

};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::init`.
template <typename Task = task::by_default>
class compute_input {
public:

   /// Creates a new instance of the class with the given :literal:`data`.
   compute_input(const table& data = table{});

   /// An $n \\times p$ table with the data to be clustered, where each row
   /// stores one feature vector.
   /// @remark default = table{}
   const table& get_data() const;
   compute_input& set_data(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::clustering`.
template <typename Task = task::by_default>
class compute_result {
public:

   /// Creates a new instance of the class with the default property values.
   compute_result();

   /// A $k \\times p$ table with the initial centroids. Each row of the
   /// table stores one centroid.
   /// @remark default = table{}
   const table& get_centroids() const;
};

/// Runs the computing operation for K-Means initialization. For more details,
/// see :expr:`oneapi::dal::compute`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
///
/// @tparam Method Tag-type that specifies an implementation of K-Means
///                Initialization algorithm.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::init`.
///
/// @param[in] desc  The descriptor of the algorithm
/// @param[in] input Input data for the computing operation
/// @return result The result of the computing operation
///
/// @pre  :expr:`input.data.has_data == true`
/// @pre  :expr:`input.data.row_count == desc.cluster_count`
/// @post :expr:`result.centroids.has_data == true`
/// @post :expr:`result.centroids.row_count == desc.cluster_count`
/// @post :expr:`result.centroids.column_count == input.data.column_count`
template <typename Float, typename Method, typename Task>
compute_result<Task> compute(const descriptor<Float, Method, Task>& desc,
                   const compute_input<Task>& input);


} // namespace oneapi::dal:kmeans_init

namespace oneapi::dal::kmeans_init::example {

table run_compute(const table& data) {
   const auto kmeans_desc = kmeans_init::descriptor<float,
                                                    kmeans_init::method::dense>{}
      .set_cluster_count(10)

   const auto result = compute(kmeans_desc, data);

   print_table("centroids", result.get_centroids());

   return result.get_centroids();
}

} // oneapi::dal::kmeans_init::example
