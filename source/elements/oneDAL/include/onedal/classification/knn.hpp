#include <cstdint>
#include "onedal/table.hpp"

namespace onedal::classification::knn {

namespace method {
   struct bruteforce {};
   struct kd_tree {};
   using by_default = bruteforce;
} // namespace method

template <typename Float = float,
          typename Method = method::by_default>
class desc {
public:
   desc();

   std::int64_t get_class_count() const;

   /// Retuns the number of neighbors :math:`k`
   std::int64_t get_neighbor_count() const;

   desc& set_class_count(std::int64_t);
   desc& set_neighbor_count(std::int64_t);
};

class model {
public:
   model();
};

class train_input {
public:
   train_input(const table& data = table(),
               const table& labels = table());

   train_input& set_data(const table&);
   train_input& set_labels(const table&);
};

class train_result {
public:
   train_result();

   const model& get_model() const;
};

class infer_input {
public:
   infer_input(const model& model = model(),
               const table& data = table());

   infer_input& set_model(const model&);
   infer_input& set_data(const table&);
};

class infer_result {
public:
   infer_result();

   const table& get_labels() const;
};

} // namespace onedal::classification::knn
