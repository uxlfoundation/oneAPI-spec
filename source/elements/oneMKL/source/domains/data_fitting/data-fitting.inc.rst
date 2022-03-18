.. _data-fitting:

Data Fitting
============

oneMKL provides spline-based interpolation capabilities that can be used for
spline construction (Linear, Cubic, Quadratic etc.),
to perform cell-search operations, and to approximate functions,
function derivatives, or integrals.

APIs are experimental. It means that no API or ABI backward compatibility are guaranteed.

APIs are based on SYCL USM (Unfied Shared Memory) input data.

Routines
--------

Splines:
    :ref:`splines`
Interpolate function:
    :ref:`interpolate`

.. toctree::
   :maxdepth: 1
   :hidden:

   data_fitting/terms
   data_fitting/splines
   data_fitting/interpolate
   data_fitting/examples
