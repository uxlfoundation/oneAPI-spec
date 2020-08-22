.. highlight:: cpp
.. default-domain:: cpp

===================================
Principal Components Analysis (PCA)
===================================

.. TODO: we either need to refer to the literature that describe the algorithm
.. (in present daal docs we do not always do that) or specify somewhere a single
.. source that contain all such descriptions and add more refs in individual algos
.. when necessary. It would help avoid different interpretation of the possible
.. minor differences and precisely say-we rely on that specific scheme

Principal Component Analysis (PCA) is an algorithm for exploratory data analysis
and dimensionality reduction. PCA transforms a set of feature vectors of
possibly correlated features to a new set of uncorrelated features, called
principal components. Principal components are the directions of the largest
variance, that is, the directions where the data is mostly spread out.

Given the training set :math:`X = \{ x_1, \ldots, x_n \}` of
:math:`p`-dimensional feature vectors and the number of principal components
:math:`r`, the problem is to compute :math:`r` principal directions
(:math:`p`-dimensional eigenvectors) for the training set. The eigenvectors can
be grouped into the :math:`r \times p` matrix :math:`T` that contains one
eigenvector in each row.

oneDAL specifies two methods for PCA computation:

#. `Covariance-based method`_
#. `SVD-based method`_

-----------------------
Covariance-based method
-----------------------
[TBD]

----------------
SVD-based method
----------------
[TBD]

-------------------
Sign-flip technique
-------------------
Eigenvectors computed by some eigenvalue solvers are not uniquely defined due to
sign ambiguity. To get the deterministic result, a sign-flip technique should be
applied. One of the sign-flip techniques proposed in [Bro07]_ requires the
following modification of matrix :math:`T`:

.. math::
   \hat{T}_i = T_i \cdot \mathrm{sgn}(\max_{1 \leq j \leq p } |{T}_{ij}|), \quad 1 \leq i \leq r,

where :math:`T_i` is :math:`i`-th row, :math:`T_{ij}` is the element in the
:math:`i`-th row and :math:`j`-th column, :math:`\mathrm{sgn}(\cdot)` is the
signum function,

.. math::
   \mathrm{sgn}(x) =
      \begin{cases}
         -1, & x < 0, \\
          0, & x = 0, \\
          1, & x > 0.
      \end{cases}

.. note::
   The sign-flip technique described above is an example. oneDAL spec does not
   require implementation of this sign-flip technique. Implementer can choose an
   arbitrary technique that modifies the eigenvectors' signs.


-------------
Usage example
-------------
::

   oneapi::dal::pca::model run_training(const oneapi::dal::table& data) {

      const auto pca_desc = oneapi::dal::pca::desc<float>{}
         .set_component_count(5)
         .set_deterministic(true);

      const auto result = oneapi::dal::train(pca_desc, data);

      print_table("means", result.get_means());
      print_table("variances", result.get_variances());
      print_table("eigenvalues", result.get_eigenvalues());
      print_table("eigenvectors", result.get_model().get_eigenvectors());

      return result.get_model();
   }


::

   oneapi::dal::table run_inference(const oneapi::dal::pca::model& model,
                               const oneapi::dal::table& new_data) {

      const auto pca_desc = oneapi::dal::pca::desc<float>{}
         .set_component_count(model.get_component_count());

      const auto result = oneapi::dal::infer(pca_desc, model, new_data);

      print_table("labels", result.get_transformed_data());
   }


---
API
---
Methods
-------
::

   namespace method {
      struct cov {};
      struct svd {};
      using by_default = cov;
   } // namespace method


.. namespace:: oneapi::dal::pca::method

.. struct:: cov

   Tag-type that denotes `Covariance-based method`_.


.. struct:: svd

   Tag-type that denotes `SVD-based method`_.


.. type:: by_default = cov

   Alias tag-type for the `Covariance-based method`_.


Descriptor
----------
::

   template <typename Float = float,
             typename Method = method::by_default>
   class desc {
   public:
      desc();

      int64_t get_component_count() const;
      bool get_deterministic() const;

      desc& set_component_count(int64_t);
      desc& set_deterministic(bool);
   };

.. namespace:: oneapi::dal::pca

.. class:: template<typename Float = float, \
                    typename Method = method::by_default> \
           desc

   :tparam Float: The floating-point type that the algorithm uses for
                  intermediate computations. Can be :expr:`float` or :expr:`double`.

   :tparam Method: Tag-type that specifies an implementation of PCA algorithm.
                   Can be :expr:`method::cov`, :expr:`method::svd` or
                   :expr:`method::by_default`.

   .. function:: desc()

      Creates a new instance of the descriptor with the default attribute
      values.


   .. member:: std::int64_t component_count = 0

      The number of principal components :math:`r`. If it is zero, the algorithm
      computes the eigenvectors for all features, :math:`r = p`.

      Getter & Setter
         | ``std::int64_t get_component_count() const``
         | ``desc& set_component_count(std::int64_t)``

      Invariants
         | :expr:`component_count >= 0`


   .. member:: bool set_deterministic = true

      Specifies whether the algorithm applies the `Sign-flip technique`_ or uses
      a deterministic eigenvalues solver. If it is `true`, directions of the
      eigenvectors must be deterministic.

      Getter & Setter
         | ``bool get_deterministic() const``
         | ``desc& set_deterministic(bool)``


Model
-----
::

   class model {
   public:
      model();

      const table& get_eigenvectors() const;
      int64_t get_component_count() const;
   };

.. class:: model

   .. function:: model()

      Creates a model with the default attribute values.


   .. member:: table eigenvectors = table()

      :math:`r \times p` table with the eigenvectors. Each row contains one
      eigenvector.

      Getter
         | ``const table& get_eigenvectors() const``


   .. member:: std::int64_t component_count = 0

      The number of components :math:`r` in the trained model.

      Getter
         | ``std::int64_t get_component_count() const``

      Invariants
         | :expr:`component_count == eigenvectors.row_count`



Training :expr:`oneapi::dal::train(...)`
----------------------------------------
Input
~~~~~
::

   class train_input {
   public:
      train_input();
      train_input(const table& data);

      const table& get_data() const;

      train_input& set_data(const table&);
   };

.. class:: train_input

   .. function:: train_input()

      Creates an input for the training operation with the default attribute
      values.


   .. function:: train_input(const table& data)

      Creates an input for the training operation with the given :expr:`data`.


   .. member:: table data = table()

      :math:`n \times p` table with the training data, where each row stores one
      feature vector.

      Getter & Setter
         | ``const table& get_data() const``
         | ``train_input& set_data(const table&)``


Result
~~~~~~
::

   class train_result {
   public:
      train_result();

      const model& get_model() const;
      const table& get_means() const;
      const table& get_variances() const;
      const table& get_eigenvalues() const;
   };

.. class:: train_result

   .. function:: train_result()

      Creates a result of the training operation with the default attribute
      values.


   .. member:: pca::model model = pca::model()

      The trained PCA model.

      Getter
         | ``const model& get_model() const``


   .. member:: table means = table()

      :math:`1 \times r` table that contains mean value for the first :math:`r`
      features.

      Getter
         | ``const table& get_means() const``


   .. member:: table variances = table()

      :math:`1 \times r` table that contains variance for the first :math:`r`
      features.

      Getter
         | ``const table& get_variances() const``


   .. member:: table eigenvalues = table()

      :math:`1 \times r` table that contains eigenvalue for for the first
      :math:`r` features.

      Getter
         | ``const table& get_eigenvalues() const``


Operation semantics
~~~~~~~~~~~~~~~~~~~
.. namespace:: oneapi::dal
.. function:: template <typename Descriptor> \
              pca::train_result train(const Descriptor& desc, \
                                      const pca::train_input& input)

   :tparam Descriptor: PCA algorithm descriptor :expr:`pca::desc`.

   Preconditions
      | :expr:`input.data.is_empty == false`
      | :expr:`input.data.column_count >= desc.component_count`

   Postconditions
      | :expr:`result.means.row_count == 1`
      | :expr:`result.means.column_count == desc.component_count`
      | :expr:`result.variances.row_count == 1`
      | :expr:`result.variances.column_count == desc.component_count`
      | :expr:`result.variances >= 0.0`
      | :expr:`result.eigenvalues.row_count == 1`
      | :expr:`result.eigenvalues.column_count == desc.component_count`
      | :expr:`result.model.eigenvectors.row_count == 1`
      | :expr:`result.model.eigenvectors.column_count == desc.component_count`


Inference :expr:`oneapi::dal::infer(...)`
-----------------------------------------
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

.. namespace:: oneapi::dal::pca

.. class:: infer_input

   .. function:: infer_input()

      Creates an input for the inference operation with the default attribute
      values.


   .. function:: infer_input(const pca::model& model)

      Creates an input for the inference operation with the given :expr:`model`,
      the other attributes get default values.


   .. function:: infer_input(const pca::model& model, const table& data)

      Creates an input for the inference operation with the given :expr:`model`
      and :expr:`data`.


   .. member:: table data = table()

      :math:`n \times p` table with the data to be projected to the :math:`r`
      principal components previously extracted from a training set.

      Getter & Setter
         | ``const table& get_data() const``
         | ``infer_input& set_data(const table&)``


   .. member:: pca::model model = pca::model()

      The trained PCA model (see :expr:`pca::model`).

      Getter & Setter
         | ``const pca::model& get_model() const``
         | ``infer_input& set_model(const pca::model&)``


Result
~~~~~~
::

   class infer_result {
   public:
      infer_result();

      const table& get_transformed_data() const;
   };


.. class:: infer_result

   .. function:: infer_result()

      Creates a result of the inference operation with the default attribute
      values.


   .. member:: table transformed_data = table()

      :math:`n \times r` table that contains data projected to the :math:`r`
      principal components.

      Getter
         | ``const table& get_transformed_data() const``


Operation semantics
~~~~~~~~~~~~~~~~~~~
.. namespace:: oneapi::dal
.. function:: template <typename Descriptor> \
              pca::infer_result infer(const Descriptor& desc, \
                                      const pca::infer_input& input)

   :tparam Descriptor: PCA algorithm descriptor :expr:`pca::desc`.

   Preconditions
      | :expr:`input.data.is_empty == false`
      | :expr:`input.model.eigenvectors.row_count == desc.component_count`
      | :expr:`input.model.eigenvectors.column_count = input.data.column_count`

   Postconditions
      | :expr:`result.transformed_data.row_count == input.data.row_count`
      | :expr:`result.transformed_data.column_count == desc.component_count`
