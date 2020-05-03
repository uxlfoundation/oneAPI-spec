#include <cstdint>
#include "onedal/table.hpp"
#include "onedal/train.hpp"

namespace onedal::knn {

namespace method {
   struct bruteforce {};
   struct kd_tree {};
   using by_default = bruteforce;
} // namespace method


/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be `float` or `double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be `method::bruteforce` or `method::kd_tree`.
template <typename Float = float,
          typename Method = method::by_default>
class descriptor {
public:
   /// Creates a new instance of the class with the given `class_count`,
   /// `neighbor_count` property values
   explicit descriptor(std::int64_t class_count,
                       std::int64_t neighbor_count);

   /// The number of classes $c$
   /// @invariant class_count > 1
   std::int64_t get_class_count() const;
   descriptor& set_class_count(std::int64_t);

   /// The number of neighbors $k$
   /// @invariant neighbor_count > 0
   std::int64_t get_neighbor_count() const;
   descriptor& set_neighbor_count(std::int64_t);
};

class model {
public:
   /// Creates a new instance of class with the default property values.
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
/// `onedal::train`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be `float` or `double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be `method::bruteforce` or `method::kd_tree`.
///
/// @param[in] desc  Descriptor for the algorithm
/// @param[in] input Input values for the algorithm
/// @return result Result of the training
///
/// @pre input.data.is_empty == false
/// @post result.model.is_empty == false
/// @post result.model.is_empty == false
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

} // namespace onedal::knn

namespace onedal::knn::example {

knn::model run_training(const table& data, const table& labels) {
}

} // onedal::knn::example
