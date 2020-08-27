#include <cstdint>
#include "oneapi/dal/table.hpp"
#include "oneapi/dal/train.hpp"

namespace oneapi::dal::pca {

namespace method {
   /// Tag-type that denotes `Covariance <pca_t_math_cov_>`_ computational
   /// method.
   struct cov {};

   /// Tag-type that denotes `SVD <pca_t_math_svd_>`_ computational method.
   struct svd {};

   /// Alias tag-type for `Covariance <pca_t_math_cov_>`_ computational
   /// method.
   using by_default = cov;
} // namespace method

namespace task {
   /// Tag-type that parametrizes entities used for solving dimensionality
   /// reduction problem.
   struct dim_reduction {};

   /// Alias tag-type for dimensionality reduction task.
   using by_default = dim_reduction;
} // namespace task

/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::cov` or :expr:`method::svd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::dim_reduction`.
template <typename Float = float,
          typename Method = method::by_default,
          typename Task = task::by_default>
class descriptor {
public:
   /// Creates a new instance of the class with the given :literal:`component_count`
   /// property value
   explicit descriptor(std::int64_t component_count = 0);

   /// The number of principal components $r$. If it is zero, the algorithm
   /// computes the eigenvectors for all features, $r = p$.
   /// @remark default = 0
   /// @invariant :expr:`component_count >= 0`
   int64_t get_component_count() const;
   descriptor& set_component_count(int64_t);

   /// Specifies whether the algorithm applies the `Sign-flip technique`_.
   /// If it is `true`, directions of the eigenvectors must be deterministic.
   /// @remark default = true
   bool get_deterministic() const;
   descriptor& set_deterministic(bool);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::dim_reduction`.
template <typename Task = task::by_default>
class model {
public:
   /// Creates a new instance of the class with the default property values.
   model();

   /// $r \\times p$ table with the eigenvectors. Each row contains one
   /// eigenvector.
   /// @remark default = table{}
   const table& get_eigenvectors() const;

   /// The number of components $r$ in the trained model.
   /// @invariant :expr:`component_count == eigenvectors.row_count`
   /// @remark default = 0
   int64_t get_component_count() const;
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::dim_reduction`.
template <typename Task = task::by_default>
class train_input {
public:
   /// Creates a new instance of the class with the given :literal:`data`
   /// property value
   train_input(const table& data = table{});

   /// $n \\times p$ table with the training data, where each row stores one
   /// feature vector.
   /// @remark default = table{}
   const table& get_data() const;
   train_input& set_data(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::dim_reduction`.
template <typename Task = task::by_default>
class train_result {
public:
   /// Creates a new instance of the class with the default property values.
   train_result();

   /// The trained PCA model
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;

   /// $1 \\times r$ table that contains mean value for the first $r$
   /// features.
   /// @remark default = table{}
   const table& get_means() const;

   /// $1 \\times r$ table that contains variance for the first $r$
   /// features.
   /// @remark default = table{}
   const table& get_variances() const;

   /// $1 \\times r$ table that contains eigenvalue for for the first
   /// $r$ features.
   /// @remark default = table{}
   const table& get_eigenvalues() const;

   /// $r \\times p$ table with the eigenvectors. Each row contains one
   /// eigenvector.
   /// @remark default = table{}
   /// @invariant :expr:`eigenvectors == model.eigenvectors`
   const table& get_eigenvectors() const;
};

/// Runs the training operation for PCA. For more details see
/// :expr:`oneapi::dal::train`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::cov` or :expr:`method::svd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::dim_reduction`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the training operation
/// @return result   Result of the training operation
///
/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.data.column_count >= desc.component_count`
/// @post :expr:`result.means.row_count == 1`
/// @post :expr:`result.means.column_count == desc.component_count`
/// @post :expr:`result.variances.row_count == 1`
/// @post :expr:`result.variances.column_count == desc.component_count`
/// @post :expr:`result.variances[i] >= 0.0`
/// @post :expr:`result.eigenvalues.row_count == 1`
/// @post :expr:`result.eigenvalues.column_count == desc.component_count`
/// @post :expr:`result.model.eigenvectors.row_count == 1`
/// @post :expr:`result.model.eigenvectors.column_count == desc.component_count`
template <typename Float, typename Method, typename Task>
train_result<Task> train(const descriptor<Float, Method, Task>& desc,
                         const train_input<Task>& input);

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::dim_reduction`.
template <typename Task = task::by_default>
class infer_input {
public:
   /// Creates a new instance of the class with the given :literal:`model`
   /// and :literal:`data` property values
   infer_input(const model<Task>& m = model<Task>{},
               const table& data = table{});

   /// The trained PCA model
   /// @remark default = model<Task>{}
   const model<Task>& get_model() const;
   infer_input& set_model(const model&);

   /// The dataset for inference $X'$
   /// @remark default = table{}
   const table& get_data() const;
   infer_input& set_data(const table&);
};

/// @tparam Task Tag-type that specifies type of the problem to solve. Can
///              be :expr:`task::dim_reduction`.
template <typename Task = task::by_default>
class infer_result {
public:
   /// Creates a new instance of the class with the default property values.
   infer_result();

   /// $n \\times r$ table that contains data projected to the $r$
   /// principal components.
   /// @remark default = table{}
   const table& get_transformed_data() const;
};

/// Runs the inference operation for PCA. For more details see
/// :expr:`oneapi::dal::infer`.
///
/// @tparam Float  The floating-point type that the algorithm uses for
///                intermediate computations. Can be :expr:`float` or
///                :expr:`double`.
/// @tparam Method Tag-type that specifies an implementation of algorithm. Can
///                be :expr:`method::cov` or :expr:`method::svd`.
/// @tparam Task   Tag-type that specifies type of the problem to solve. Can
///                be :expr:`task::dim_reduction`.
///
/// @param[in] desc  Descriptor of the algorithm
/// @param[in] input Input data for the inference operation
/// @return result   Result of the inference operation
///
/// @pre :expr:`input.data.has_data == true`
/// @pre :expr:`input.model.eigenvectors.row_count == desc.component_count`
/// @pre :expr:`input.model.eigenvectors.column_count = input.data.column_count`
/// @post :expr:`result.transformed_data.row_count == input.data.row_count`
/// @post :expr:`result.transformed_data.column_count == desc.component_count`
template <typename Float, typename Method, typename Task>
infer_result<Task> infer(const descriptor<Float, Method, Task>& desc,
                         const infer_input<Task>& input);

} // namespace oneapi::dal::pca

namespace oneapi::dal::pca::example {

pca::model<> run_training(const table& data) {
   const auto pca_desc = pca::descriptor<float>{}
      .set_component_count(5)
      .set_deterministic(true);

   const auto result = train(pca_desc, data);

   print_table("means", result.get_means());
   print_table("variances", result.get_variances());
   print_table("eigenvalues", result.get_eigenvalues());
   print_table("eigenvectors", result.get_eigenvectors());

   return result.get_model();
}

table run_inference(const pca::model<>& model,
                    const table& new_data) {
   const auto pca_desc = pca::descriptor<float>{}
      .set_component_count(model.get_component_count());

   const auto result = infer(pca_desc, model, new_data);

   print_table("labels", result.get_transformed_data());
}

} // oneapi::dal::pca::example
