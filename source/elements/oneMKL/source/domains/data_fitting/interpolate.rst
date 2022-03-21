.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _interpolate:

Interpolate Function
====================

Interpolate function performs computations of function and derivatives values at interpolation sites.

If the sites do not belong to interpolation interval ``[a, b)``, the library uses:

  - interpolant :math:`I_0` coefficients computed for interval :math:`[x_0, x_1)` for the
    computations at the sites to the left of ``a``.
  - interpolant :math:`I_{n-2}` coefficients computed for interval
    :math:`[x_{n-2}, x_{n-1})` for the computations at the sites to the right of ``b``.

Interpolation algorithm depends on interpolant's type (e.g., for a cubic spline,
the evaluation of a third-order polynomial is performed to obtain the resulting interpolant value).

Header File
-----------

.. code:: cpp

  #include<oneapi/mkl/experimental/data_fitting.hpp>

Namespace
---------

.. code:: cpp

  oneapi::mkl::experimental::data_fitting

Syntax
------

.. code:: cpp

  template <typename Interpolant>
  sycl::event interpolate(
      Interpolant& interpolant,
      typename Interpolant::value_type* sites,
      std::int64_t n_sites,
      typename Interpolant::value_type* results,
      const std::vector<sycl::event>& dependencies,
      interpolate_hint ResultHint = interpolate_hint::funcs_sites_ders,
      site_hint SiteHint = site_hint::non_uniform); // (1)

  template <typename Interpolant>
  sycl::event interpolate(
      Interpolant& interpolant,
      typename Interpolant::value_type* sites,
      std::int64_t n_sites,
      typename Interpolant::value_type* results,
      std::bitset<32> derivatives_indicator,
      const std::vector<sycl::event>& dependencies = {},
      interpolate_hint ResultHint = interpolate_hint::funcs_sites_ders,
      site_hint SiteHint = site_hint::non_uniform); // (2)

  template <typename Interpolant>
  sycl::event interpolate(
      sycl::queue& queue,
      const Interpolant& interpolant,
      typename Interpolant::value_type* sites,
      std::int64_t n_sites,
      typename Interpolant::value_type* results,
      const std::vector<sycl::event>& dependencies,
      interpolate_hint ResultHint = interpolate_hint::funcs_sites_ders,
      site_hint SiteHint = site_hint::non_uniform); // (3)

  template <typename Interpolant>
  sycl::event interpolate(
      sycl::queue& queue,
      const Interpolant& interpolant,
      typename Interpolant::value_type* sites,
      std::int64_t n_sites,
      typename Interpolant::value_type* results,
      std::bitset<32> derivatives_indicator,
      const std::vector<sycl::event>& dependencies = {},
      interpolate_hint ResultHint = interpolate_hint::funcs_sites_ders,
      site_hint SiteHint = site_hint::non_uniform); // (4)

For all functions users can provide ``SiteHint`` and ``ResultHint`` to specify
the layout of ``sites`` and ``results`` respectively.
If ``results`` layout doesn't satisfy ``ResultHint`` and/or
``sites`` layout doesn't satisfy ``SiteHint``, behavior is undefined.
Returns the SYCL event of the submitted task.

#. Performs computations of function values only using the SYCL queue
   associated with ``interpolant``.
#. Performs computations of certain derivatives
   (function values is considered as a zero derivative) which are indicated in
   ``derivatives_indicator`` (each bit corresponds to certain derivative starting from lower bit)
   using the SYCL queue associated with ``interpolant``.
#. Performs computations of function values only using ``queue`` as an input argument
   that should be created from the same context and device as the SYCL queue
   associated with ``interpolant``.
#. Performs computations of certain derivatives
   (function values is considered as a zero derivative) which are indicated in
   ``derivatives_indicator`` (each bit corresponds to certain derivative starting from lower bit)
   using ``queue`` as an input argument that should be created from
   the same context and device as the SYCL queue associated with ``interpolant``.
