.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft_config_storage_formats:

Storage Formats
---------------

Depending on the value of the :ref:`onemkl_dft_enum_domain` template value, the
implementation of the DFT may support different storage schemes for data
sequences in forward and/or backward domain.

In any case, the data elements are expected to be within contiguous memory
blocks and defined with generalized strides therein
(see :ref:`onemkl_dft_config_data_layouts`). For multiple transforms, all data
sets should be located within the same memory block, and they should be placed
at the same distance from each other
(see :ref:`onemkl_dft_num_dft_fwd_and_bwd_distance`).

.. _onemkl_dft_complex_storage:

COMPLEX_STORAGE
+++++++++++++++

For the :ref:`onemkl_dft_enum_domain` template parameter with value ``COMPLEX``,
data sequences are non-redundant complex sequences in both forward and backward
domains. In this case, the configuration parameter ``COMPLEX_STORAGE``
determines how the data is organized in memory, in both forward and backward
domain. This configuration parameter may take one of the two following values:
``COMPLEX_COMPLEX`` (default) or ``REAL_REAL``.

.. _onemkl_dft_complex_storage_complex_complex:

.. rubric:: COMPLEX_COMPLEX value for configuration parameter COMPLEX_STORAGE

For descriptors of ``COMPLEX`` template :ref:`onemkl_dft_enum_domain` with
``config_param::COMPLEX_STORAGE`` set to ``config_value::COMPLEX_COMPLEX``,
forward- and backward-domain data sequences are read/stored from/in a single
data container (device-accessible USM allocation or ``sycl::buffer``). Any
relevant element :math:`z^{m}_{k_1, k_2,\dots ,k_d}` of the :math:`m`-th
:math:`d`-dimensional sequence is accessed/stored from/in the data container
provided at compute time at the index value expressed in eq.
:eq:`eq_idx_data_layout` (from :ref:`this page<onemkl_dft_config_data_layouts>`)
of that data container whose elementary data type is (possibly implicitly
re-interpreted as) ``std::complex<float>`` (resp. ``std::complex<double>``) for
descriptors operating in single (resp. double)
:ref:`precision<onemkl_dft_enum_precision>`.

The following snippet illustrates the usage of ``config_value::COMPLEX_COMPLEX``
storage for the in-place, single-precision (fp32), calculation of :math:`M`
three-dimensional :math:`n_1 \times n_2 \times n_3` complex transforms, using
identical (default) strides and distances in forward and backward domains, with
USM allocations.

.. code-block:: cpp

    namespace dft = oneapi::mkl::dft;
    dft::descriptor<dft::precision::SINGLE, dft::domain::COMPLEX> desc({n1, n2, n3});
    std::vector<std::int64_t> strides({0, n2*n3, n3, 1});
    std::int64_t dist = n1*n2*n3;
    std::complex<float> *AZ = (std::complex<float> *) malloc_device(2*sizeof(float)*n1*n2*n3*M, queue);
    desc.set_value(dft::config_param::FWD_STRIDES, strides);
    desc.set_value(dft::config_param::BWD_STRIDES, strides);
    desc.set_value(dft::config_param::FWD_DISTANCE, dist);
    desc.set_value(dft::config_param::BWD_DISTANCE, dist);
    desc.set_value(dft::config_param::NUMBER_OF_TRANSFORMS, M);
    desc.set_value(dft::config_param::COMPLEX_STORAGE, dft::config_value::COMPLEX_COMPLEX);
    desc.commit(queue);

    // initialize forward-domain data such that z{m;k1,k2,k3}
    //   = AZ[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]
    compute_forward(desc, AZ); // complex-to-complex in-place DFT
    // in backward domain: z{m;k1,k2,k3}
    //   = AZ[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]


.. _onemkl_dft_complex_storage_real_real:

.. rubric:: REAL_REAL value for configuration parameter COMPLEX_STORAGE

For descriptors of ``COMPLEX`` template :ref:`onemkl_dft_enum_domain`
with ``config_param::COMPLEX_STORAGE`` set to ``config_value::REAL_REAL``,
forward- and backward-domain data sequences are read/stored from/in two different
data containers (device-accessible USM allocation or ``sycl::buffer``)
encapsulating the real and imaginary parts, separately. The real (resp.
imaginary) part of any relevant complex element
:math:`z^{m}_{k_1, k_2,\dots ,k_d}` within the :math:`m`-th
:math:`d`-dimensional sequence is accessed/stored from/in a data container
provided at compute time at the index value expressed in eq.
:eq:`eq_idx_data_layout` (from :ref:`this page<onemkl_dft_config_data_layouts>`)
of that data container whose elementary data type is ``float`` (resp. ``double``)
for descriptors operating in single (resp. double)
:ref:`precision<onemkl_dft_enum_precision>`.

The following snippet illustrates the usage of ``config_value::REAL_REAL``
storage for the in-place, single-precision (fp32), calculation of :math:`M`
three-dimensional :math:`n_1 \times n_2 \times n_3` complex transforms, using
identical (default) strides and distances in forward and backward domains, with
USM allocations.

.. code-block:: cpp

    namespace dft = oneapi::mkl::dft;
    dft::descriptor<dft::precision::SINGLE, dft::domain::COMPLEX> desc({n1, n2, n3});
    std::vector<std::int64_t> strides({0, n2*n3, n3, 1});
    std::int64_t dist = n1*n2*n3;
    float *AR = (float *) malloc_device(sizeof(float)*n1*n2*n3*M, queue); // data container for real parts
    float *AI = (float *) malloc_device(sizeof(float)*n1*n2*n3*M, queue); // data container for imaginary parts
    desc.set_value(dft::config_param::FWD_STRIDES, strides);
    desc.set_value(dft::config_param::BWD_STRIDES, strides);
    desc.set_value(dft::config_param::FWD_DISTANCE, dist);
    desc.set_value(dft::config_param::BWD_DISTANCE, dist);
    desc.set_value(dft::config_param::NUMBER_OF_TRANSFORMS, M);
    desc.set_value(dft::config_param::COMPLEX_STORAGE, dft::config_value::REAL_REAL);
    desc.commit(queue);

    // initialize forward-domain data such that the real part of z{m;k1,k2,k3}
    //   = AR[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]
    // and the imaginary part of z{m;k1,k2,k3}
    //   = AI[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]
    compute_forward(desc, AR, AI); // complex-to-complex in-place DFT
    // in backward domain: the real part of z{m;k1,k2,k3}
    //   = AR[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]
    // and the imaginary part of z{m;k1,k2,k3}
    //   = AI[ strides[0] + k1*strides[1] + k2*strides[2] + k3*strides[3] + m*dist ]

.. _onemkl_dft_real_and_conjugate_even_storage:

REAL_STORAGE and CONJUGATE_EVEN_STORAGE
+++++++++++++++++++++++++++++++++++++++

When forward-domain data sequences are real (*i.e.*, for descriptors whose
:ref:`onemkl_dft_enum_domain` template parameter is set to ``REAL``), only
roughly half the backward-domain (complex) data is relevant to DFT calculations:
using the notations from the definition presented :ref:`here<onemkl_dft_formula>`,
if :math:`w_{j_1, j_2, \dots, j_d}` are all real, then the resulting
:math:`z_{k_1, k_2, \dots, k_d}` is a complex sequence which satisfies
:math:`z^{*}_{k_1, k_2, \dots, k_d} = z_{n_1 - k_1, n_2 - k_2, \dots, n_d - k_d}`
where :math:`z^{*}` represents the conjugate of :math:`z`.  Therefore, the
non-redundant sequence :math:`z_{k_1, k_2, \dots, k_d}` wherein
:math:`0\leq k_d \leq \lfloor\frac{n_d}{2}\rfloor` and
:math:`0\leq k_j < n_j, \forall 1\leq j < d` if :math:`d > 1` suffices to
determine the entire backward-domain data sequences, unambiguously. Descriptors
of ``REAL`` template :ref:`onemkl_dft_enum_domain` require (and produce)
only those non-redundant parts of the backward-domain data.

For descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`, the
configuration parameter ``REAL_STORAGE`` determines how the forward-domain data
sequences are organized in memory while the configuration parameter
``CONJUGATE_EVEN_STORAGE`` determines how the backward-domain data sequences
are organized in memory. The possible value for ``REAL_STORAGE`` is
``REAL_REAL`` (default) and the possible value for ``CONJUGATE_EVEN_STORAGE`` is
``COMPLEX_COMPLEX`` (default).

.. _onemkl_dft_real_storage_real_real:

.. rubric:: REAL_REAL value for configuration parameter REAL_STORAGE

For descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`
with ``config_param::REAL_STORAGE`` set to ``config_value::REAL_REAL``,
forward-domain data sequences are read/stored from/in a single data container
(device-accessible USM allocation or ``sycl::buffer``). Any relevant real
element :math:`z^{m}_{k_1, k_2,\dots ,k_d}` within the :math:`m`-th
:math:`d`-dimensional sequence is accessed/stored from/in the data container
provided at compute time at the index value expressed in eq.
:eq:`eq_idx_data_layout` (from :ref:`this page<onemkl_dft_config_data_layouts>`)
of that data container whose elementary data type is (possibly implicitly
re-interpreted as) ``float`` (resp. ``double``) for descriptor operating in
single (resp. double) :ref:`precision<onemkl_dft_enum_precision>`.

.. _onemkl_dft_conjugate_even_storage_complex_complex:

.. rubric:: COMPLEX_COMPLEX value for configuration parameter CONJUGATE_EVEN_STORAGE

For descriptors of ``REAL`` template :ref:`onemkl_dft_enum_domain`
with ``config_param::CONJUGATE_EVEN_STORAGE`` set to
``config_value::COMPLEX_COMPLEX``, backward-domain data sequences are
read/stored from/in a single data container (device-accessible USM allocation or
``sycl::buffer``) encapsulating the non-redundant parts of the complex data
sequences. Any relevant element :math:`z^{m}_{k_1, k_2,\dots ,k_d}` within the
:math:`m`-th :math:`d`-dimensional sequence wherein
:math:`0\leq k_d \leq \lfloor\frac{n_d}{2}\rfloor` (and
:math:`0\leq k_j < n_j, \forall 1\leq j < d` if :math:`d > 1`) is
accessed/stored from/in the data container provided at compute time at the
index value expressed in eq. :eq:`eq_idx_data_layout` (from
:ref:`this page<onemkl_dft_config_data_layouts>`) of that data container whose
elementary data type is (possibly implicitly re-interpreted as)
``std::complex<float>`` (resp. ``std::complex<double>``) for descriptors
operating in single (resp. double) :ref:`precision<onemkl_dft_enum_precision>`.

.. _onemkl_dft_real_example:

.. rubric:: Illustration of storage formats for real transforms

The following snippet illustrates the usage of ``config_value::REAL_REAL``
for ``config_param::REAL_STORAGE`` along with ``config_value::COMPLEX_COMPLEX``
for ``config_param::CONJUGATE_EVEN_STORAGE`` for the in-place, single-precision
(fp32), calculation of :math:`M` three-dimensional
:math:`n_1 \times n_2 \times n_3` real transforms, using default strides in
forward and backward domains, with USM allocations.

.. code-block:: cpp

    namespace dft = oneapi::mkl::dft;
    dft::descriptor<dft::precision::SINGLE, dft::domain::REAL> desc({n1, n2, n3});
    // Note: integer divisions here below
    std::vector<std::int64_t> fwd_strides({0, 2*n2*(n3/2 + 1), 2*(n3/2 + 1), 1});
    std::vector<std::int64_t> bwd_strides({0,   n2*(n3/2 + 1),   (n3/2 + 1), 1});
    std::int64_t fwd_dist = 2*n1*n2*(n3/2 + 1);
    std::int64_t bwd_dist =   n1*n2*(n3/2 + 1);
    float *data = (float *) malloc_device(sizeof(float)*fwd_dist*M, queue); // data container
    desc.set_value(dft::config_param::FWD_STRIDES, fwd_strides);
    desc.set_value(dft::config_param::BWD_STRIDES, bwd_strides);
    desc.set_value(dft::config_param::FWD_DISTANCE, fwd_dist);
    desc.set_value(dft::config_param::BWD_DISTANCE, bwd_dist);
    desc.set_value(dft::config_param::NUMBER_OF_TRANSFORMS, M);
    desc.set_value(dft::config_param::REAL_STORAGE, dft::config_value::REAL_REAL);
    desc.set_value(dft::config_param::CONJUGATE_EVEN_STORAGE, dft::config_value::COMPLEX_COMPLEX);
    desc.commit(queue);

    // initialize forward-domain data such that real z{m;k1,k2,k3}
    //   = data[ fwd_strides[0] + k1*fwd_strides[1] + k2*fwd_strides[2] + k3*fwd_strides[3] + m*fwd_dist ]
    compute_forward(desc, data); // real-to-complex in-place DFT
    // in backward domain, the implicitly-assumed type is complex so, considering
    //   std::complex<float>* complex_data = static_cast<std::complex<float>*>(data);
    //   we have the complex value z{m;k1,k2,k3}
    //   = complex_data[ bwd_strides[0] + k1*bwd_strides[1] + k2*bwd_strides[2] + k3*bwd_strides[3] + m*bwd_dist ]
    //   for 0 <= k3 <= n3/2.
    //   If n3/2 < k3 < n3, z{m;k1,k2,k3} = std::conj(z{m;n1-k1,n2-k2,n3-k3})

**Parent topic** :ref:`onemkl_dft_enums`
