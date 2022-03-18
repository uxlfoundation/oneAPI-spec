.. _cubic:

Cubic Splines
=============

Cubic splines are splines whose degree is equal to 3.

Cubic splines are described by the following polynomial

.. math::
  P_i\left( x \right) = c_{1,i}+ c_{2,i}\left( x - x_i \right) + c_{3,i}{\left( x - x_i \right)}^2+ c_{4,i}{\left( x - x_i \right)}^3,

where

.. math::
  x \in \left[ x_i, x_{i+1} \right),

.. math::
  i = 1,\dots , n-1.

There are many different kinds of cubic splines: Hermite, natural, Akima, Bessel.
However, the current version of DPC++ API supports only one type: Hermite.

Header File
-----------

.. code:: cpp

  #include<oneapi/mkl/experimental/data_fitting.hpp>

Namespace
---------

.. code:: cpp

  oneapi::mkl::experimental::data_fitiing

Hermite Spline
--------------

The coefficients of Hermite spline are calculated using the following formulas:

.. math::
  c_{1,i} = f\left( x_i \right),

.. math::
  c_{2,i} = s_i,

.. math::
  c_{3,i} = \left( \left[ x_i, x_{i+1} \right]f - s_i \right)  / \left( \Delta x_i \right) - c_{4,i}\left( \Delta x_i \right),

.. math::
  c_{4,i} = \left( s_i + s_{i+1} - 2\left[ x_i, x_{i+1} \right]f \right) / {\left( \Delta x_i \right)}^2,

.. math::
  s_i = f^{\left( 1 \right)}\left( x_i \right).

The following boundary conditions are supported for Hermite spline:

 - Free end (:math:`f^{(2)}(x_1) = f^{(2)}(x_n) = 0`).
 - Periodic.
 - First derivative.
 - Second Derivative.

Syntax
^^^^^^

.. code:: cpp

  namespace cubic_spline {
    struct hermite {};
  }

Example
^^^^^^^

To create a cubic Hermite spline object use the following:

.. code:: cpp

  spline<float, cubic_spline::hermite> val(
    /*SYCL queue object*/q,
    /*number of spline functions*/ny
  );

Follow the :ref:`examples` section to see more complicated examples.
