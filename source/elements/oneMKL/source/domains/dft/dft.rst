.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_dft:

Discrete Fourier Transform Functions
------------------------------------

oneMKL provides a DPC++ interface to :math:`d`-dimensional :math:`\left(d \in
\mathbb{Z}_{>0}\right)` Discrete Fourier Transforms (DFTs).

.. _onemkl_dft_definitions:

Definitions
+++++++++++

Let :math:`w^{m}_{k_1, k_2, \ldots, k_d}` be the entry of multi-index
:math:`\left(k_1, k_2, \ldots, k_d\right) \in \mathbb{Z}^d` in the
:math:`m`-th sequence of a set :math:`w` of :math:`M` :math:`d`-dimensional
periodic discrete sequences of period(s) (or "length(s)")
:math:`n_1 \times n_2 \times \dots \times n_d`
(:math:`M \in \mathbb{Z}_{>0}`, :math:`m \in \lbrace 0, 1, \ldots, M-1\rbrace`
and
:math:`n_{\ell} \in \mathbb{Z}_{>0}, \forall \ell \in \lbrace 1, \ldots, d \rbrace`).

For every :math:`m \in \lbrace 0, 1, \ldots, M - 1 \rbrace`, the DFT of sequence
:math:`w^{m}` is the :math:`d`-dimensional
:math:`n_1 \times n_2 \times \dots \times n_d` periodic discrete sequence
:math:`z^{m}` whose entries are defined as

.. _onemkl_dft_formula:

.. math::
    z^{m}_{k_1, k_2,\ldots, k_d} = \sigma \displaystyle\sum_{j_d=0}^{n_d-1}\dots\displaystyle\sum_{j_2=0}^{n_2-1}\displaystyle\sum_{j_1=0}^{n_1-1} w^{m}_{j_1, j_2,\dots,j_d} \exp \left[ \delta 2\pi \imath \left( \sum_{\ell=1}^{d} \frac{j_{\ell}k_{\ell}}{n_{\ell}} \right) \right] \ \forall \left(k_1, \ldots, k_d\right) \in \mathbb{Z}^{d}
    :label: eq_dft_definition

where :math:`\imath^2 = -1` and :math:`\sigma` is a scale factor.
In :eq:`eq_dft_definition`, :math:`\delta` determines one of the two
"directions" of the DFT: :math:`\delta=-1` defines the "forward DFT" while
:math:`\delta=+1` defines the "backward DFT".

The domain of input (resp. output) discrete sequences for a forward (resp.
backward) DFT is referred to as "forward domain". Conversely, the domain of
output (resp. input) discrete sequences for forward (resp. backward) DFT is
referred to as "backward domain".

oneMKL supports single-precision (fp32) and double-precision (fp64)
floating-point arithmetic for the calculation of DFTs, using two types of
forward domains:

- the set of complex :math:`d`-dimensional periodic sequences, referred to as
  "complex forward domain";
- the set of real :math:`d`-dimensional periodic sequences, referred to as
  "real forward domain".

Similarly, we refer to DFTs of complex (resp. real) forward domain as "complex
DFTs" (resp. "real DFTs"). Regardless of the type of forward domain, the
backward domain's data sequences are always complex.

The calculation of the same DFT for several, *i.e.*, :math:`M > 1`, data sets of
the same type of forward domain, using the same precision is referred to as a
"batched DFT".

.. _onemkl_dft_finite_range_of_indices:

Finite range of indices
+++++++++++++++++++++++

In general, given the periodicity of the discrete data considered in any DFT,
ranges of indices :math:`\left(k_1, \ldots, k_d\right) \in \mathbb{Z}^{d}` such
that :math:`0\leq k_{\ell} < n_{\ell}, \forall \ell \in \lbrace 1, \ldots, d
\rbrace` suffice to determine any relevant :math:`d`-dimensional sequence
unambiguously (for any valid :math:`m`). In case of real DFTs, the data
sequences in backward domain can be fully determined from a smaller range of
indices. Indeed, if all entries of :math:`w` are real in
:eq:`eq_dft_definition`, then the entries of :math:`z` are complex and, for any
valid :math:`m`,
:math:`\left(z^{m}_{k_1, k_2, \dots, k_d}\right)^{*} = z^{m}_{n_1 - k_1, n_2 - k_2, \dots, n_d - k_d}`
:math:`\forall \left(k_1, k_2, \ldots, k_d\right) \in \mathbb{Z}^{d}` where
:math:`\lambda^{*}` represents the conjugate of complex number :math:`\lambda`.
This conjugate symmetry relation makes roughly half the data redundant in
backward domain: in case of real DFTs, the data sequences in backward domain can
be fully determined even if one of the :math:`d` indices :math:`k_{\ell}` is
limited to the range
:math:`0\leq k_{\ell} \leq \lfloor \frac{n_{\ell}}{2}\rfloor`. In oneMKL, the
index :math:`k_d`, *i.e.*, the last dimension's index, is restricted as such for
capturing an elementary set of non-redundant entries of data sequences belonging
to the backward domain of real DFTs.

.. _onemkl_dft_elementary_range_of_indices:

Elementary range of indices
~~~~~~~~~~~~~~~~~~~~~~~~~~~

In other words, oneMKL expects and produces a set of :math:`M`
:math:`d`-dimensional *finite* data sequences
:math:`\left(\cdot \right)^{m}_{k_1, k_2,\ldots, k_d}` with integer indices 
:math:`m` and
:math:`k_{\ell}\ \left(\ell \in \lbrace 1, \ldots, d \rbrace\right)` in the
elementary range

- :math:`0 \leq m < M`;
- :math:`0 \leq k_j < n_j,\ \forall j \in \lbrace1, \ldots, d - 1\rbrace`, if :math:`d > 1`;
- :math:`0 \leq k_d < n_d`, except for backward domain's data sequences of real DFTs;
- :math:`0 \leq k_d \leq \lfloor\frac{n_d}{2}\rfloor`, for backward domain's data sequences of real DFTs.

.. _onemkl_dft_additional_constraints_in_bwd_domain_for_real_dft:

Additional constraints for data in backward domain of real DFTs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Finally, note that the conjugate symmetry relation further constrains some of
the entries (or pairs thereof) in the backward domain's data sequences for real
DFTs. Specifically, for any of the :math:`M` sequences,

- the imaginary part must be :math:`0` for any entry of multi-index
  :math:`\left(k_1, k_2, \ldots, k_d\right)` such that
  :math:`k_{\ell} \equiv \left(n_{\ell} - k_{\ell}\right) \pmod {n_{\ell}}, \forall \ell \in \lbrace{1, \ldots, d\rbrace}`,
  *e.g.*, entry of multi-index :math:`\left(0, 0, \ldots, 0\right)`;
- pairs of entries of multi-indices :math:`\left(k_1, k_2, \ldots, k_d\right)`
  and :math:`\left(j_1, j_2, \ldots, j_d\right)` such that
  :math:`k_{\ell} \equiv \left(n_{\ell} - j_{\ell}\right) \pmod {n_{\ell}}, \forall \ell \in \lbrace{1, \ldots, d\rbrace}`
  must be complex conjugates of one another, *e.g.*, entries of multi-indices
  :math:`\left(1, 0, \ldots, 0\right)` and
  :math:`\left(n_1 - 1, 0, \ldots, 0\right)` must be complex conjugates (note
  that this case falls back to the above constraint if :math:`n_1 = 2`).

.. note::
  The behavior of oneMKL is undefined for real backward DFT if the input data
  does not satisfy those constraints. oneMKL considers it the user's
  responsibility to guarantee that these constraints are satisfied by the input
  data for real backward DFTs.

.. _onemkl_dft_recommended_usage:

Recommended usage
+++++++++++++++++

The desired (batched) DFT to be computed is entirely defined by an object
``desc`` of the :ref:`descriptor<onemkl_dft_descriptor>` class. The desired type
of forward domain and precision are determined at ``desc``'s construction time
by the specialization values chosen for the self-explanatory template parameters
``prec`` (of type :ref:`onemkl_dft_enum_precision`) and ``dom`` (of type
:ref:`onemkl_dft_enum_domain`), respectively. The transform size 
:math:`n_1 \times n_2 \times \dots \times n_d` is also set at construction time
as a required argument to the class constructor. Other configuration details for
the (batched) DFT under consideration may be specified by invoking the
:ref:`onemkl_dft_descriptor_set_value` member function of ``desc`` for every
relevant configuration setting (*e.g.*, the number :math:`M` of sequences to
consider in case of a batched DFT). Once configured as desired, the
:ref:`onemkl_dft_descriptor_commit` member function of ``desc``, requiring a
``sycl::queue`` object ``Q``, may be invoked. The successful completion of the
latter makes ``desc`` committed to the desired (batched) DFT *as configured*, for
the particular device and context encapsulated by ``Q``. The
:ref:`onemkl_dft_compute_forward` (resp. :ref:`onemkl_dft_compute_backward`)
function may then be called and provided with ``desc`` to enqueue operations
relevant to the desired forward (resp. backward) DFT calculations with
user-provided, device-accessible data.

.. note::
  Objects of the :ref:`descriptor<onemkl_dft_descriptor>` class

  - must be successfully committed prior to providing them to any compute
    function;
  - must be re-committed to account for any change in configuration after
    it was already successfully committed;
  - deliver best performance for DFT calculations when created, configured and
    committed outside applications' hotpath(s) that use them multiple times for
    identically-configured (batched) DFTs. :ref:`onemkl_dft_compute_forward`
    and/or :ref:`onemkl_dft_compute_backward` should be the only oneMKL DFT-related
    routines invoked in programs' hotpaths.

Summary table
~~~~~~~~~~~~~

The table below summarizes the object and functions relevant to computing DFTs
(all defined in the ``oneapi::mkl::dft`` namespace).

.. _onemkl_dft_summary_table:
.. container::


   .. container:: tablenoborder

      .. 

      .. list-table:: 
         :header-rows: 1
         :widths: 33 64   

         * -     Routines and Objects
           -     Description     
         * -     :ref:`descriptor<onemkl_dft_descriptor>`
           -     A class whose instances define a specific (batched) DFT(s) to
                 be calculated.
         * -     :ref:`descriptor::set_value<onemkl_dft_descriptor_set_value>`
           -     A member function of the
                 :ref:`descriptor<onemkl_dft_descriptor>` class to set (writable)
                 :ref:`configuration parameters<onemkl_dft_enum_config_param>`
                 for an instance of that class.
         * -     :ref:`descriptor::get_value<onemkl_dft_descriptor_get_value>`
           -     A member function of the
                 :ref:`descriptor<onemkl_dft_descriptor>` class to query
                 :ref:`configuration parameters<onemkl_dft_enum_config_param>`
                 from any instance of that class.
         * -     :ref:`descriptor::commit<onemkl_dft_descriptor_commit>`
           -     A member function of the
                 :ref:`descriptor<onemkl_dft_descriptor>` class to commit an
                 instance of that class to the (batched) DFT calculations it
                 defines, on a given queue.
         * -     :ref:`onemkl_dft_compute_forward`
           -     A function requiring a successfully-committed object of the
                 :ref:`descriptor<onemkl_dft_descriptor>` class to compute a
                 forward (batched) DFT, as defined by that object.
         * -     :ref:`onemkl_dft_compute_backward`
           -     A function requiring a successfully-committed object of the
                 :ref:`descriptor<onemkl_dft_descriptor>` class to compute a
                 backward (batched) DFT, as defined by that object.


**Parent topic:** :ref:`onemkl_domains`

.. toctree::
    :hidden:

    descriptor
    enums_and_config_params
    compute_forward
    compute_backward

