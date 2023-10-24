.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_config_data_layouts:

Configuration of Data Layouts
-----------------------------

The DFT interface provides the configuration parameters
``config_param::FWD_STRIDES`` (resp. ``config_param::BWD_STRIDES``) and
``config_param::FWD_DISTANCE`` (resp. ``config_param::BWD_DISTANCE``) to define
the data layouts used in forward (resp. backward) domain. Considering
:math:`M` (:math:`M \geq 1`) :math:`d`-dimensional
:math:`n_{1}\times n_{2} \times\dots\times n_d` data set(s) :math:`X^{m}`
(:math:`0 \leq m < M`) in forward (resp. backward) domain, those configuration
parameters describe that a particular element of multi-index
:math:`\left(k_{1}, k_{2}, \dots, k_d\right)` (see
:ref:`here below<onemkl_dft_data_layout_nonredundant_valid_range>` for the
range of values of such multi-indices), *i.e.*,
:math:`X^{m}_{k_{1}, k_{2}, \dots, k_d }`, is located at index

.. math::
    s_0 + k_1*s_1 + k_2*s_2 + \dots + k_d*s_d + m*l
    :label: eq_idx_data_layout

of the corresponding data container (``sycl::buffer`` or USM pointer) provided
to the compute function, the data type of which is (possibly implicitly
re-interpreted) as documented in the
:ref:`table<onemkl_dft_config_data_element_types>` below. In the index
expression :eq:`eq_idx_data_layout`,

- :math:`s_j`, :math:`0 \leq j \leq d` represents the :ref:`generalized strides and offset<onemkl_dft_fwd_bwd_strides>` within :math:`d`-dimensional data sets in forward (resp. backward) domain, in number of elements of the :ref:`relevant elementary data type<onemkl_dft_config_data_element_types>`;

- :math:`l` represents the :ref:`distance<onemkl_dft_fwd_bwd_distance>` between successive :math:`d`-dimensional data sets in forward (resp. backward) domain, in number of elements of the :ref:`relevant elementary data type<onemkl_dft_config_data_element_types>`;

.. container:: section

   .. _onemkl_dft_config_data_element_types:

   .. rubric:: Elementary data type assumed by descriptors depending on their type and configuration (precision matching the :ref:`descriptor's<onemkl_dft_enum_precision>`)

   .. list-table::
        :header-rows: 1
        :class: longtable

        * -   Descriptor configuration
          -   Element type of forward data
          -   Element type of backward data
        * -   ``COMPLEX`` template :ref:`onemkl_dft_enum_domain` and :ref:`onemkl_dft_complex_storage_complex_complex`
          -   Complex
          -   Complex
        * -   ``COMPLEX`` template :ref:`onemkl_dft_enum_domain` and :ref:`onemkl_dft_complex_storage_real_real`
          -   Real
          -   Real
        * -   ``REAL`` template :ref:`onemkl_dft_enum_domain`, :ref:`onemkl_dft_real_storage_real_real` and :ref:`onemkl_dft_conjugate_even_storage_complex_complex`
          -   Real
          -   Complex


.. _onemkl_dft_fwd_bwd_strides:

.. rubric:: FWD_STRIDE and BWD_STRIDES

The values :math:`s_0, s_1, \dots, s_d` in :eq:`eq_idx_data_layout` here above
are communicated as elements, in that order, of a :math:`(d+1)`-long
``std::vector<std::int64_t>`` value for the configuration parameter
``config_param::FWD_STRIDES`` (resp. ``config_param::BWD_STRIDES``). The element
:math:`s_0` represents an absolute offset (or "displacement") in the data set(s)
while the subsequent element(s) :math:`s_j\ (j > 0)` are generalized strides.

The default values set for the forward and backward strides correspond to the
data layout configurations for unbatched, in-place transforms using unit stride
along the leading dimension with no offset (and minimal padding in forward
domain in case of descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`,
aligning with the :ref:`requirements for in-place
transforms<onemkl_dft_data_layout_requirements>`). In other words, the default
values are :math:`s_0 = 0`, :math:`s_d = 1` and, for multi-dimensional
transforms, *i.e.*, if :math:`d > 1`,

- :math:`s_{d-1} = n_{d}` for descriptors of ``COMPLEX`` template :ref:`onemkl_dft_enum_domain`;

- :math:`s_{d-1} = \alpha \left(\lfloor \frac{n_{d}}{2} \rfloor + 1\right)`, wherein :math:`\alpha = 2` (resp. :math:`\alpha = 1`) for forward (resp. backward) strides, of descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`;

and :math:`s_k = n_{k+1} * s_{k+1}` for :math:`1 \leq k < d - 1` if :math:`d > 2`.

.. _onemkl_dft_fwd_bwd_distance:

.. rubric:: FWD_DISTANCE and BWD_DISTANCE

The value :math:`l` in :eq:`eq_idx_data_layout` here above is communicated as an
``std::int64_t`` value for the configuration parameter
``config_param::FWD_DISTANCE`` (resp. ``config_param::BWD_DISTANCE``). This
configuration parameter is irrelevant for unbatched transforms, *i.e.*, for
descriptors set to handle a
:ref:`number of transforms<onemkl_dft_config_number_of_transforms>` equal to
:math:`1` (default value). The configuration parameters
``config_param::FWD_DISTANCE`` and ``config_param::BWD_DISTANCE`` must be set
for descriptors configured to compute more than one transform, *i.e.*, if the
:ref:`number of transforms<onemkl_dft_config_number_of_transforms>` is larger
than :math:`1`. The default values for ``config_param::FWD_DISTANCE`` and
``config_param::BWD_DISTANCE`` are :math:`0` regardless of the descriptor's
nature.

.. _onemkl_dft_data_layout_requirements:

.. rubric:: General consistency requirements

In general, the distance and strides must be set so that every index value
:eq:`eq_idx_data_layout` corresponds to a *unique* (relevant) data point in the
data set under consideration. In other words, there must not be one index value
as expressed in :eq:`eq_idx_data_layout` corresponding to two different
:math:`(d+1)`-tuples :math:`(m, k_{1}, k_{2}, \dots, k_d)` within valid range,
*i.e.*, such that

.. _onemkl_dft_data_layout_nonredundant_valid_range:

- :math:`0 \leq m < M` wherein :math:`M` is the :ref:`number of transforms<onemkl_dft_config_number_of_transforms>`;

- :math:`0 \leq k_j < n_j`, :math:`1 \leq j < d` if :math:`d > 1` ;

- :math:`0 \leq k_d < n_d`, for descriptors of ``COMPLEX`` template :ref:`onemkl_dft_enum_domain` or for forward data of descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`;

- :math:`0 \leq k_d \leq \lfloor\frac{n_d}{2}\rfloor`, for backward data of descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`.

Additionally, for in-place transforms (``PLACEMENT=INPLACE``), the forward and
backward data layouts must be configured *consistently* with one another: the
memory address(es) of leading element(s) along the last dimension must be
identical in forward and backward domain. Specifically, considering any
:math:`(d+1)`-tuple :math:`(m, k_{1}, k_{2}, \dots, k_{d-1}, 0)` within valid
range (as developed above), the memory address of the element of corresponding
index value :eq:`eq_idx_data_layout` in forward domain (considering the
:ref:`implicitly assumed type<onemkl_dft_config_data_element_types>` in forward
domain) must be identical to the memory address of the element of corresponding
index value :eq:`eq_idx_data_layout` in backward domain (considering the
:ref:`implicitly assumed type<onemkl_dft_config_data_element_types>` in
backward domain). Equivalently,

- for descriptors such that the :ref:`assumed elemementary type<onemkl_dft_config_data_element_types>` is identical in forward and backward domains, the offset, stride(s) (and distances, if relevant) must be equal in forward and backward domain;
- for descriptors assuming :ref:`different elemementary types<onemkl_dft_config_data_element_types>` in forward and backward domain, let :math:`\beta` and :math:`\gamma` be the sizes of the :ref:`elementary data type assumed<onemkl_dft_config_data_element_types>` in forward and backward domain, respectively (:math:`\beta \neq \gamma`). Then,

    - offsets must satisfy :math:`\beta s^{\text{fwd}}_{0} = \gamma s^{\text{bwd}}_{0}`;
    - if :math:`d > 1`, strides must satisfy :math:`\beta s^{\text{fwd}}_{j} = \gamma s^{\text{bwd}}_{j}, \forall 1 \leq j < d`;
    - if :math:`M > 1`, distances must satisfy :math:`\beta l^{\text{fwd}} = \gamma l^{\text{bwd}}`.

.. _onemkl_dft_io_strides_deprecated:

.. rubric:: INPUT_STRIDES and OUTPUT_STRIDES (deprecated)

The deprecated ``config_param::INPUT_STRIDES`` (resp.
``config_param::OUTPUT_STRIDES``) configuration parameter operates similarly to
the ``config_param::FWD_STRIDES`` (resp. ``config_param::BWD_STRIDES``)
parameter specified :ref:`here above<onemkl_dft_fwd_bwd_strides>`, when
configuring a descriptor for a *forward* DFT. When configuring a descriptor for
a *backward* (inverse) DFT, the deprecated ``config_param::INPUT_STRIDES`` (resp.
``config_param::OUTPUT_STRIDES``) configuration parameter operates similarly to
the ``config_param::BWD_STRIDES`` (resp. ``config_param::FWD_STRIDES``)
parameter specified :ref:`here above<onemkl_dft_fwd_bwd_strides>`.

If specifying the data layout strides using these deprecated configuration
parameters and if the strides differ in forward and backward domain, the
descriptor *must* be re-configured and re-committed for computing the DFT in the
:ref:`reverse direction<onemkl_dft_formula>` as shown below.

.. code-block:: cpp

   // ...
   desc.set_value(config_param::INPUT_STRIDES,  fwd_domain_strides);
   desc.set_value(config_param::OUTPUT_STRIDES, bwd_domain_strides);
   desc.commit(queue);
   compute_forward(desc, ...);
   // ...
   desc.set_value(config_param::INPUT_STRIDES,  bwd_domain_strides);
   desc.set_value(config_param::OUTPUT_STRIDES, fwd_domain_strides);
   desc.commit(queue);
   compute_backward(desc, ...);

Setting either of ``config_param::FWD_STRIDES`` or ``config_param::BWD_STRIDES``
triggers any previously-set values for ``config_param::INPUT_STRIDES`` or
``config_param::OUTPUT_STRIDES`` to be wiped out, and vice versa. As a
consequence, mix-and-matching either of ``config_param::INPUT_STRIDES`` or
``config_param::OUTPUT_STRIDES`` with either of ``config_param::FWD_STRIDES`` or
``config_param::BWD_STRIDES`` is **not** to be supported and would result in an
exception being thrown at commit time due to invalid configuration, if attempted.

The ``config_param::INPUT_STRIDES`` and ``config_param::OUTPUT_STRIDES``
parameters are deprecated. A warning message "{IN,OUT}PUT_STRIDES are deprecated:
please use {F,B}WD_STRIDES, instead." is to be reported to applications using
these configuration parameters.

**Parent topic** :ref:`onemkl_dft_enums`
