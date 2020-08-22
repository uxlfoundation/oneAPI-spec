#include <cstdint>
#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::knn {

namespace method {
   /// Tag-type that denotes `brute-force <t_math_brute_force_>`_ computational
   /// method.
   struct bruteforce {};

   /// Tag-type that denotes `k-d tree <t_math_kd_tree>`_ computational method.
   struct kd_tree {};

   /// Alias tag-type for `brute-force <t_math_brute_force_>`_ computational
   /// method.
   using by_default = bruteforce;
} // namespace method

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::bruteforce` or :expr:`method::kd_tree`.
template <typename Float = float,
          typename Method = method::by_default>
class descriptor {
public:
   /// Creates a new instance of the class with the given :literal:`class_count`
   /// and :literal:`neighbor_count` property values
   explicit descriptor(std::int64_t class_count,
                       std::int64_t neighbor_count);

   /// The number of classes $c$
   /// @invariant :expr:`class_count > 1`
   std::int64_t get_class_count() const;
   descriptor& set_class_count(std::int64_t);

   /// The number of neighbors $k$
   /// @invariant :expr:`neighbor_count > 0`
   std::int64_t get_neighbor_count() const;
   descriptor& set_neighbor_count(std::int64_t);
};

class model {
public:
   /// Creates a new instance of the class with the default property values.
   model();
};

class train_input {
public:
   train_input(const table& data = table{},
               const table& labels = table{});

   /// The training set $X$
   /// @remark default = table{}
   const table& get_data() const;
   train_input& set_data(const table&);

   /// Vector of labels $y$ for the training set $X$
   /// @remark default = table{}
   const table& get_labels() const;
   train_input& set_labels(const table&);
};

class train_result {
public:
   train_result();

   /// The trained $k$-NN model
   /// @remark default = model{}
   const model& get_model() const;
};

/// Runs the training operation for $k$-NN classifier. For more details see
/// :expr:`oneapi::dal::train`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::bruteforce` or :expr:`method::kd_tree`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the training operation
/// @return result Result of the training operation
///
/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.labels.has_data == true`
/// @pre :expr:`input.data.rows == input.labels.rows`
/// @pre :expr:`input.data.columns == 1`
/// @pre :expr:`input.labels[i] >= 0`
/// @pre :expr:`input.labels[i] < desc.class_count`
template <typename Float, typename Method>
train_result train(const descriptor<Float, Method>& desc,
                   const train_input& input);


class infer_input {
public:
   infer_input(const model& m = model{},
               const table& data = table{});

   /// The trained $k$-NN model
   /// @remark default = model{}
   const model& get_model() const;
   infer_input& set_model(const model&);

   /// The dataset for inference $X'$
   /// @remark default = table{}
   const table& get_data() const;
   infer_input& set_data(const table&);
};

class infer_result {
public:
   infer_result();

   /// The predicted labels
   /// @remark default = model{}
   const table& get_labels() const;
};

/// Runs the inference operation for $k$-NN classifier. For more details see
/// :expr:`oneapi::dal::infer`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::bruteforce` or
///                :expr:`method::kd_tree`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the inference operation
/// @return result Result of the inference operation
///
/// @pre  :expr:`input.data.has_data == true`
/// @post :expr:`result.labels.rows == input.data.rows`
/// @post :expr:`result.labels.columns == 1`
/// @post :expr:`result.labels[i] >= 0`
/// @post :expr:`result.labels[i] < desc.class_count`
template <typename Float, typename Method>
infer_result infer(const descriptor<Float, Method>& desc,
                   const infer_input& input);

} // namespace oneapi::dal::knn

namespace oneapi::dal::knn::example {

knn::model run_training(const table& data, const table& labels) {
}

} // oneapi::dal::knn::example
