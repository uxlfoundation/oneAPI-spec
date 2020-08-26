#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::kmeans_init {

namespace method {
   /// Tag-type that denotes `Default dense`_.
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

   /// Creates new instance of descriptor with the default attribute values.
   descriptor();

   /// The number of clusters $k$
   /// @invariant :expr:`cluster_count > 0`
   std::int64_t get_cluster_count() const;
   descriptor& set_cluster_count(std::int64_t);

};

class compute_input {
public:

   /// Creates input for the computing operation with the default attribute values.
   /// @remark default = table{}
   compute_input();

   /// Creates input for the computing operation with the given data,
   /// the other attributes get default values.
   compute_input(const table& data = table{});

   /// The computing set $X$
   /// @remark default = table{}
   const table& get_data() const;
   train_input& set_data(const table&);
};

class compute_result {
public:

   compute_result();

   /// The initial centroids
   /// @remark default = table{}
   table get_centroids() const;
};

/// Runs the computing operation for KMeans initialization. For more details see
/// :expr:`oneapi::dal::compute`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation
/// of K-Means Initialization algorithm.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the training operation
/// @return result Result of the training operation
///
/// @pre  :expr:`input.data.has_data == true`
/// @pre  :expr:`input.data.row_count == desc.cluster_count`
/// @post :expr:`result.centroids.has_data == true`
/// @post :expr:`result.centroids.row_count == desc.cluster_count`
/// @post :expr:`result.centroids.column_count == input.data.column_count`
template <typename Float, typename Method>
train_result compute(const descriptor<Float, Method>& desc,
                   const train_input& input);


} // namespace oneapi::dal:kmeans_init
