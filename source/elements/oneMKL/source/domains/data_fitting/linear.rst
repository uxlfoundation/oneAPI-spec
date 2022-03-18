.. _linear:

Linear Spline
=============

Linear spline is a spline whose degree is equal to 1.

It's described by the following polynomial

.. math::
  P_i\left( x \right) = c_{1,i} + c_{2,i}\left( x - x_i \right),

where

.. math::
  x \in \left[ x_i, x_{i+1} \right),

.. math::
  c_{1,i} = f\left( x_i \right),

.. math::
  c_{2,i} = \left[ x_i, x_{i+1} \right]f,

.. math::
  i = 1, \dots, n-1.

Header File
-----------

.. code:: cpp

  #include<oneapi/mkl/experimental/data_fitting.hpp>

Namespace
---------

.. code:: cpp

  oneapi::mkl::experimental::data_fitiing

Syntax
------

.. code:: cpp

  namespace linear_spline {
    struct default_type {};
  }

Example
-------

To create a linear spline object use the following:

.. code:: cpp

  spline<float, linear_spline::default_type> val(
    /*SYCL queue object*/q,
    /*number of spline functions*/ny
  );

Follow the :ref:`examples` section to see more complicated examples.
