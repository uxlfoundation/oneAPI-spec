.. _math_notations:

======================
Mathematical Notations
======================

.. list-table::
   :widths: 15 85
   :header-rows: 1

   * - Notation
     - Definition

   * - :math:`n`
     - Number of :term:`feature vectors <Feature vector>` in a :term:`training
       set <Training set>`.

   * - :math:`m`
     - Number of feature vectors in a :term:`inference set <Inference set>`.

   * - :math:`p`
     - Number of features in a :term:`dataset <Dataset>`.

   * - :math:`a \times b`
     - Denotes that the corresponding matrix (dataset) has :math:`a` rows
       (observations) and :math:`b` columns (features).

   * - :math:`|A|`
     - If :math:`A` is a set, this denotes cardinality of a set, i.e., the
       number of elements in the set :math:`A`. If :math:`A` is a real number,
       this denotes an absolute value of :math:`A`.

   * - :math:`\|x\|`
     - The :math:`L_2`-norm for a vector :math:`x \in \mathbb{R}^d`,

       .. math::
          \|x\| =  \sqrt{ x_1^2 + x_2^2 + \dots + x_d^2 }.

   * - :math:`\mathrm{sgn}(x)`
     - Sign function of a number :math:`x \in \mathbb{R}`.

       .. math::
          \mathrm{sgn}(x) =
             \begin{cases}
                -1, & x < 0, \\
                0, & x = 0, \\
                1, & x > 0.
             \end{cases}

   * - :math:`x_i`
     - In the context of algorithm description, typically denotes the
       :math:`i`-th feature vector of *a training set*.

   * - :math:`x'_i`
     - In the context of algorithm description, typically denotes the
       :math:`i`-th feature vector of *a inference set*.

   * - :math:`y_i`
     - In the context of algorithm description, typically denotes the
       :math:`i`-th :term:`response <Response>` of a training set given a
       priori.

   * - :math:`y'_i`
     - In the context of algorithm description, typically denotes the
       :math:`i`-th response that needs to predicted by an inference algorithm
       given the feature vector :math:`x'_i` from inference set .
