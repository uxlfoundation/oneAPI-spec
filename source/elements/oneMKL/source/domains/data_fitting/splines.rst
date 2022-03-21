.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _splines:

Splines
=======

Header File
-----------

.. code:: cpp

  #include<oneapi/mkl/experimental/data_fitting.hpp>

Namespace
---------

.. code:: cpp

  oneapi::mkl::experimental::data_fitiing

Common API for All Spline Types
-------------------------------

.. code:: cpp

  template <
    typename FpType,
    typename SplineType,
    int Dimensions = 1>
  class spline {
  public:
      using value_type = FpType;
      using spline_type = SplineType;

      spline(
        const sycl::queue& queue,
        std::int64_t ny = 1,
        bool were_coeffs_computed = false);

      spline(
        const sycl::device& device,
        const sycl::context& context,
        std::int64_t ny = 1,
        bool were_coeffs_computed = false);

      ~spline();

      spline(const spline<FpType, SplineType, Dimensions>& other) = delete;
      spline(spline<FpType, SplineType, Dimensions>&& other) = delete;
      spline<FpType, SplineType, Dimensions>& operator=(
          const spline<FpType, SplineType, Dimensions>& other) = delete;
      spline<FpType, SplineType, Dimensions>& operator=(
          spline<FpType, SplineType, Dimensions>&& other) = delete;

      spline& set_partitions(
        FpType* input_data,
        std::int64_t nx,
        partition_hint PartitionHint = partition_hint::non_uniform);

      spline& set_function_values(
        FpType* input_data,
        function_hint FunctionHint = function_hint::row_major);

      spline& set_coefficients(
        FpType* data,
        coefficient_hint CoeffHint = coefficient_hint::row_major);

      bool is_initialized() const;

      std::int64_t get_required_coeffs_size() const;

      sycl::event construct(const std::vector<sycl::event>& dependencies = {});
  };

An instance of ``spline<T, ST, N>`` create the ``N``-dimensional spline
that operates with the ``T`` data type. ``ST`` is a type of spline.
``T`` can only be ``float`` or ``double``.

.. list-table::
   :header-rows: 1

   * - Constructor
     - Description
   * - ``spline(const sycl::queue& queue, std::int64_t ny = 1, bool were_coeffs_computed = false);``
     - Create an object with the ``queue`` SYCL queue and ``ny`` number of functions.
       If spline coeficients were already computed, provide ``true`` as a 3-rd argument.
       ``were_coeffs_computed == false`` by default.
       It means that it needs to call ``construct`` to compute spline coefficients.
   * - ``spline(const sycl::device& device, const sycl::context& context, std::int64_t ny = 1, bool were_coeffs_computed = false);``
     - Create an object using the ``device`` SYCL device, the ``context`` context
       and ``ny`` number of functions.
       If spline coeficients were already computed, provide ``true`` as a 3-rd argument.
       ``were_coeffs_computed == false`` by default.
       It means that it needs to call ``construct`` to compute spline coefficients.

.. list-table::
   :header-rows: 1

   * - Member function
     - Description
   * - ``spline& set_partitions(FpType* input_data, std::int64_t nx, partition_hint PartitionHint = partition_hint::non_uniform);``
     - Set partition values that are specified by the ``input_data`` memory pointer and ``nx`` partition values.
       Users can provide ``PartitionHint`` to specify the layout of data.
       Default layout is ``non_uniform``.
       If ``uniform`` is specified, ``nx`` must be equal to ``2`` and
       ``input_data`` must contain only 2 values corresponding to the left and the right borders
       of the sub-interval defined by the partition.
       Otherwise, behavior is undefined.
       If ``input_data`` layout doesn't satisfy ``PartitionHint``, behavior is undefined.
       Returns a reference to the spline object for which partitions are set.

       Example, for ``uniform``. Let :math:`\left\{ i \right\}_{i=1,\dots,n}` be a partition.
       So, ``input_data`` must contain only 2 values: 1, ``n``.
   * - ``spline& set_function_values(FpType* input_data, function_hint FunctionHint = storage_hint::row_major);``
     - Set function values that are specified by the ``input_data`` memory pointer.
       Number of function values must be ``ny * nx`` elements.
       Users can provide a ``FunctionHint`` to specify the layout of data with a default value of ``row_major``.
       If ``input_data`` layout doesn't satisfy ``FunctionHint``, behavior is undefined.
       Returns a reference to the spline object for which function values are set.
   * - ``spline& set_coefficients(FpType* data, coefficient_hint CoeffHint = storage_hint::row_major);``
     - Set coefficients that are specified by the ``data`` memory pointer.
       Number of coefficients in the memory must equals to the return value of ``get_required_coeffs_size()``.
       Users can provide a ``CoeffHint`` to specify the layout of data with a default value of ``row_major``.
       If ``data`` layout doesn't satisfy ``CoeffHint``, behavior is undefined.
       If ``were_coeffs_computed == false``, ``data`` will be rewritten during ``construct``.
       Returns a reference to the spline object for which coefficients are set.
   * - ``bool is_initialized() const;``
     - Returns ``true`` if all required data are set (for example, partitions, function values, coefficients).
   * - ``std::int64_t get_required_coeffs_size() const;``
     - Returns amount of memory that is required for coefficients storage.
   * - ``sycl::event construct(const std::vector<sycl::event>& dependencies = {});``
     - Constructs the spline (calculates spline coefficients if ``were_coeffs_computed == false``).
       The function submits a SYCL kernel and returns the SYCL event to wait on to ensure computation is complete.
       ``dependencies`` is a list of SYCL events to wait for before starting computations.

There are some splines that requires internal conditions and boundary conditions to be set.
For such spline types, the following member functions must be called.

.. code:: cpp

  spline& set_internal_conditions(
    FpType* input_data);

  spline& set_boundary_conditions(
    bc_type BCType = bc_type::free_end,
    FpType input_value = {});

.. list-table::
   :header-rows: 1

   * - Member function
     - Description
   * - ``spline& set_internal_conditions(FpType* input_data);``
     - Set internal conditions that are specified by the ``input_data`` memory pointer.
       Number of internal condition values must equals to ``nx - 2``.
       Returns a reference to the spline object for which internal conditions are set.
   * - ``spline& set_boundary_conditions(bc_type BCType = bc_type::free_end, FpType input_value = {});``
     - Set the ``input_value`` boundary condition corresponding to ``BCType``.
       Default value for ``input_value`` is empty since some boundary conditions doesn't require value to be provided.
       Returns a reference to the spline object for which boundary condition value is set.

.. note::
   copy/move constructor and copy/move assignment operators are deleted
   since the ``spline`` class is just a wrapper over memory that users provide.
   Memory management responsibility is on user's side.

Supported Spline Types
----------------------

Currently, the DPC++ Data Fitting APIs support the following spline types
(follow the corresponding links to deep-dive into the details):

:ref:`linear`

:ref:`cubic`

.. toctree::
   :maxdepth: 1
   :hidden:

   linear
   cubic
