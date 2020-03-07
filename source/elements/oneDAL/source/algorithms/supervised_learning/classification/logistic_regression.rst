Logistic Regression
===================

.. toctree::
   :glob:
   :maxdepth: 4


Logistic regression is a method for modeling the relationships
between one or more explanatory variables and a categorical variable
by expressing the posterior statistical distribution of the
categorical variable via linear functions on observed data. If the
categorical variable is binary, taking only two values, "0" and "1",
the logistic regression is simple, otherwise, it is multinomial.


Details
*******

Given n feature vectors of n p-dimensional feature vectors a vector
of class labels :math:`y = (y_1,\ldots{},y_n )`, where :math:`y_i \in \{0, 1, \ldots, K-1\}` and :math:`K` is the number of classes, describes the
class to which the feature vector :math:`x_i` belongs, the problem is to
train a logistic regression model.

The logistic regression model is the set of vectors :math:`\beta =\left\{ {\beta }_{0}=\left({\beta }_{00}\dots {\beta }_{0p}\right), {..\beta }_{K-1}=\left({\beta }_{K-10}\dots {\beta }_{K-1p}\right)\right\}` that gives the posterior probability

	.. math::
		 {P\left\{y=k|x\right\}= p}_{k}\left(x, \beta \right)=\mathrm{ }\frac{{e}^{{f}_{k}\left(x, \beta \right)}}{\sum _{i=0}^{K-1}{e}^{{f}_{i}\left(x, \beta \right)}}, \text{where} {f}_{k}\left(x, \beta \right)= {\beta }_{k0}+ \sum _{j=1}^{p}{\beta }_{kj}*{x}_{j}

for a given feature vector :math:`x = (x_1, \ldots, x_p)` and class
label :math:`y \in \{0, 1, \ldots, K - 1\}` for each :math:`k = 0, \ldots, K-1`.

If the categorical variable is binary, the model is defined as a single vector :math:`{\beta }_{0}=\left({\beta }_{00}\dots {\beta }_{0p}\right)` that determines the posterior probability

.. math::

		 P\left\{y=1|x\right\}= \mathrm{\sigma }\left(x,\mathrm{ }\mathrm{\beta }\right)=\frac{1}{1+ {e}^{-f\left(x, \beta \right)}}

		 P\left\{y=0|x\right\}=1- P\left\{y=1|x\right\}


Parameters
****************


   * - Parameter
     - Default Value
     - Description
   * - algorithmFPType
     - float
     - The floating-point type that the algorithm uses for intermediate computations. Can be float or double.
   * - method
     - defaultDense
     - The computation method used by the logistic regression. The only
       training method supported so far is the default dense method.
   * - nClasses
     - Not applicable.
     - The number of classes. A required parameter.
   * - interceptFlag
     - True
     - A flag that indicates a need to compute :math:`\theta_j`
   * - penaltyL1
     - :math:`0`
     - L1 regularization coefficient
   * - penaltyL2
     - :math:`0`
     - L2 regularization coefficient
   * - optimizationSolver
     - SGD solver
     - All iterative solvers are available as optimization procedures to use at
       the training stage:
       -  SGD (Stochastic Gradient Descent Algorithm)
       -  ADAGRAD (Adaptive Subgradient Method)
       -  LBFGS (Limited-Memory Broyden-Fletcher-Goldfarb-Shanno Algorithm)
       -  SAGA (Stochastic Average Gradient Accelerated Method)

APIs
*******

APIs description