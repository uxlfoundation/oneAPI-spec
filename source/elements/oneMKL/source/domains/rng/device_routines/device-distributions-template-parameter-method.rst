.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_uniform_continuous_distributions_method:

Distributions Template Parameter Method
=======================================

.. tabularcolumns:: |\Y{0.4}|\Y{0.2}|\Y{0.4}|

.. list-table::
   :header-rows: 1
   :class: longtable

   * -  Method Type
     -  Distributions
     -  Math Description

   * -  ``uniform_method::standard``
        ``uniform_method::accurate``
     -  ``uniform``
     -   Standard method. Currently there is only one method for these functions. ``uniform_method::accurate`` checks for additional ``s`` and ``d`` data types. For ``integer`` data types, it uses ``d`` as a ``BRNG`` data type (``s`` ``BRNG`` data type is used in ``uniform_method::standard`` method on GPU).
   * -  ``gaussian_method::box_muller2``
     -  ``gaussian``
     -  Generates normally distributed random numbers x1 and x2 thru the pair of uniformly distributed numbers u1 and u2 according to   the formulas: \ :math:`x_1 = \sqrt{-2 \ln u_1} \sin {2 \pi u_2}`\       \ :math:`x_2 = \sqrt{-2 \ln u_1} \cos {2 \pi u_2}`\       Lognormal   distribution: generated normally distributed random numbers x1 and x2   are converted to lognormal distribution.
   * -  ``exponential_method::icdf``
        ``exponential_method::icdf_accurate``
     -  ``exponential``
     -  Inverse cumulative distribution function (ICDF) method.
   * -  ``lognormal_method::box_muller2``
     -  ``lognormal``
     -  Normally distributed random numbers x1 and x2 are produced through the pair of uniformly distributed numbers u1 and u2 according to the formulas: \ :math:`x_1 = -2 \ln u_1 \sin {2 \pi u_2}`\       \ :math:`x_2 = -2 \ln u_1 \cos {2 \pi u_2}`\   Then x1 and x2 are converted to lognormal distribution.
   * -  ``bernoulli_method::icdf``
     -  ``bernoulli``
     -  Inverse cumulative distribution function (ICDF) method.
   * -  ``poisson_method::devroye``
     -  ``poisson``
     -  Acceptance/rejection method for ``λ≥ 27`` with decomposition into four regions:

        Two parallelograms

        Triangle

        Left exponential tail

        Right exponenetial tail

`NOTE:` Methods provided for exposition purposes. 
