#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::kmeans_init {

namespace method {
   /// Tag-type that denotes `dense <kmeans_init_c_math_dense_>`_
   /// computational method.
   struct dense {};

   using by_default = dense;
} // namespace method

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method – Tag-type that specifies an implementation
/// of K-Means Initialization algorithm.
template <typename Float = float,
          typename Method = method::by_default>
class descriptor {
public:

   /// Creates a new instance of the descriptor with the default attribute
   /// values.
   explicit descriptor(std::int64_t cluster_count = 2);

   /// The number of clusters $k$
   /// @invariant :expr:`cluster_count > 0`
   /// @remark default = 2
   std::int64_t get_cluster_count() const;
   descriptor& set_cluster_count(std::int64_t);

};

class compute_input {
public:

   /// Creates input for the computing operation with the given data,
   /// the other attributes get default values.
   compute_input(const table& data = table{});

   /// The training set $X$
   /// @remark default = table{}
   const table& get_data() const;
   compute_input& set_data(const table&);
};

class compute_result {
public:

   /// Creates a new instance of the class with the default property values.
   compute_result();

   /// The initial centroids
   /// @remark default = table{}
   const table& get_centroids() const;
};

/// Runs the computing operation for KMeans initialization. For more details,
/// see :expr:`oneapi::dal::compute`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
/// intermediate computations. Can be :expr:`float` or :expr:`double`. @tparam
/// Method Tag-type that specifies an implementation of K-Means Initialization
/// algorithm.
///
/// @param[in] desc  The descriptor of the algorithm @param[in] input Input data
/// for the computing operation @return result The result of the computing
/// operation
///
/// @pre  :expr:`input.data.has_data == true` @pre  :expr:`input.data.row_count
/// == desc.cluster_count` @post :expr:`result.centroids.has_data == true` @post
/// :expr:`result.centroids.row_count == desc.cluster_count` @post
/// :expr:`result.centroids.column_count == input.data.column_count`
template <typename Float, typename Method>
compute_result compute(const descriptor<Float, Method>& desc,
                   const compute_input& input);


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
