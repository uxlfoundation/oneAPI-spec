#include <cstdint>
#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::knn {

namespace method {
   /// Tag-type that denotes `brute-force <knn_t_math_brute_force_>`_ computational
   /// method.
   struct bruteforce {};

   /// Tag-type that denotes `k-d tree <knn_t_math_kd_tree>`_ computational method.
   struct kd_tree {};

   /// Alias tag-type for `brute-force <knn_t_math_brute_force_>`_ computational
   /// method.
   using by_default = bruteforce;
} // namespace method

namespace task {
   /// Tag-type that parametrizes entities used for solving classification
   /// problem.
   struct classification {};

   /// Alias tag-type for classification task.
   using by_default = classification;
} // namespace task

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::bruteforce` or :expr:`method::kd_tree`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::classification`.
template <typename Float = float,
          typename Method = method::by_default,
          typename Task = task::by_default>
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

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::classification`.
template <typename Task = task::by_default>
class model {
public:
   /// Creates a new instance of the class with the default property values.
   model();
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::classification`.
template <typename Task = task::by_default>
class train_input {
public:
   /// Creates a new instance of the class with the given :literal:`data`
   /// and :literal:`labels` property values
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

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::classification`.
template <typename Task = task::by_default>
class train_result {
public:
   /// Creates a new instance of the class with the default property values.
   train_result();

   /// The trained $k$-NN model
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;
};

/// Runs the training operation for $k$-NN classifier. For more details see
/// :expr:`oneapi::dal::train`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::bruteforce` or :expr:`method::kd_tree`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::classification`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the training operation
/// @return result Result of the training operation
///
/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.labels.has_data == true`
/// @pre :expr:`input.data.row_count == input.labels.row_count`
/// @pre :expr:`input.labels.column_count == 1`
/// @pre :expr:`input.labels[i] >= 0`
/// @pre :expr:`input.labels[i] < desc.class_count`
template <typename Float, typename Method, typename Task>
train_result<Task> train(const descriptor<Float, Method, Task>& desc,
                         const train_input<Task>& input);

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::classification`.
template <typename Task = task::by_default>
class infer_input {
public:
   /// Creates a new instance of the class with the given :literal:`model`
   /// and :literal:`data` property values
   infer_input(const model<Task>& m = model<Task>{},
               const table& data = table{});

   /// The trained $k$-NN model
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;
   infer_input& set_model(const model&);

   /// The dataset for inference $X'$
   /// @remark default = table{}
   const table& get_data() const;
   infer_input& set_data(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::classification`.
template <typename Task = task::by_default>
class infer_result {
public:
   /// Creates a new instance of the class with the default property values.
   infer_result();

   /// The predicted labels
   /// @remark default = table{}
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
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::classification`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the inference operation
/// @return   result Result of the inference operation
///
/// @pre  :expr:`input.data.has_data == true`
/// @post :expr:`result.labels.row_count == input.data.row_count`
/// @post :expr:`result.labels.column_count == 1`
/// @post :expr:`result.labels[i] >= 0`
/// @post :expr:`result.labels[i] < desc.class_count`
template <typename Float, typename Method, typename Task>
infer_result<Task> infer(const descriptor<Float, Method, Task>& desc,
                         const infer_input<Task>& input);

} // namespace oneapi::dal::knn

namespace oneapi::dal::knn::example {

knn::model<> run_training(const table& data,
                          const table& labels) {
   const std::int64_t class_count = 10;
   const std::int64_t neighbor_count = 5;
   const auto knn_desc = knn::descriptor<float>{class_count, neighbor_count};

   const auto result = train(knn_desc, data, labels);

   return result.get_model();
}

table run_inference(const knn::model<>& model,
                    const table& new_data) {
   const std::int64_t class_count = 10;
   const std::int64_t neighbor_count = 5;
   const auto knn_desc = knn::descriptor<float>{class_count, neighbor_count};

   const auto result = infer(knn_desc, model, new_data);

   print_table("labels", result.get_labels());
}

} // oneapi::dal::knn::example
