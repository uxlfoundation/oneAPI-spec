.. _onemkl_dft_config_packed_format:

PACKED_FORMAT
--------------

The result of the forward real-to-complex transformation is a conjugate-even sequence. When using the ``config_param::CONJUGATE_EVEN_STORAGE`` format, due to the symmetry property, only a part of the complex-valued sequence is stored in memory.  The ``config_param::PACKED_FORMAT`` configuration parameter defines how the data is packed.  Possible values for ``config_param::PACKED_FORMAT`` depend on the values of the ``config_param::CONJUGATE_EVEN_STORAGE`` configuration parameter.

.. tabularcolumns:: l|c|

.. list-table::
     :header-rows: 1
     :class: longtable

     * -   CONJUGATE_EVEN_STORAGE
       -   Supported PACKED_FORMATS
     * -   :ref:`onemkl_dft_conjugate_even_storage_complex_complex`
       -   ``config_value::CCE_FORMAT`` can be used with transforms of any dimension.
     * -   :ref:`onemkl_dft_conjugate_even_storage_complex_real`
       -   one and two-dimensional transforms support ``config_value::CCS_FORMAT``, ``config_value::PACK_FORMAT`` and ``config_value::PERM_FORMAT``.


.. container:: section

   .. _onemkl_dft_config_packed_format_cce:

   .. rubric:: CCE_FORMAT for Any-dimensional Transforms

   This is the format described in :ref:`onemkl_dft_conjugate_even_storage_complex_complex`.



.. container:: section

   .. _onemkl_dft_pack_1d_even:

   .. rubric:: Packed formats for 1D transformation with :math:`n=2L`, even size.

   .. tabularcolumns:: l|c|c|c|c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :class: longtable

        * -   :math:`k=`
          -   0
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-4
          -   n-3
          -   n-2
          -   n-1
          -   n
          -   n+1
        * -   CCS
          -   :math:`R_0`
          -   :math:`0`
          -   :math:`R_1`
          -   :math:`I_1`
          -   :math:`\dots`
          -   :math:`R_{L-2}`
          -   :math:`I_{L-2}`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   :math:`R_L`
          -   :math:`0`
        * -   PACK
          -   :math:`R_0`
          -   :math:`R_1`
          -   :math:`I_1`
          -   :math:`R_2`
          -   :math:`\dots`
          -   :math:`I_{L-2}`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   :math:`R_{L}`
          -   
          -   
        * -   PERM
          -   :math:`R_0`
          -   :math:`R_{L}`
          -   :math:`R_1`
          -   :math:`I_1` 
          -   :math:`\dots`
          -   :math:`R_{L-2}`
          -   :math:`I_{L-2}`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   
          -   


   .. _onemkl_dft_pack_1d_odd:

   .. rubric:: Packed formats for 1D transformation with :math:`n=2L+1`, odd size.

   .. tabularcolumns:: l|c|c|c|c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :class: longtable

        * -   :math:`k=`
          -   0
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-4
          -   n-3
          -   n-2
          -   n-1
          -   n
          -   n+1
        * -   CCS
          -   :math:`R_0`
          -   :math:`0`
          -   :math:`R_1`
          -   :math:`I_1`
          -   :math:`\dots`
          -   :math:`R_{L-2}`
          -   :math:`I_{L-2}`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   :math:`R_L`
          -   :math:`I_L`
        * -   PACK
          -   :math:`R_0`
          -   :math:`R_1`
          -   :math:`I_1`
          -   :math:`R_2`
          -   :math:`\dots`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   :math:`R_{L}`
          -   :math:`I_{L}`
          -
          -
        * -   PERM
          -   :math:`R_0`
          -   :math:`R_1`
          -   :math:`I_1`
          -   :math:`R_2`
          -   :math:`\dots`
          -   :math:`R_{L-1}`
          -   :math:`I_{L-1}`
          -   :math:`R_{L}`
          -   :math:`I_{L}`
          -
          -


.. container:: section

   .. _onemkl_dft_config_packed_format_1d_ccs:

   .. rubric:: CCS_FORMAT for One-Dimensional Transforms

   For a one-dimensional size-``n`` conjugate-even sequence being stored in a CCS packed format, we require ``n+2`` elements in the array.
   The real and imaginary parts of the complex-valued conjugate-even sequence, :math:`z_k`, are located in a real valued array as seen in :ref:`onemkl_dft_pack_1d_even` and :ref:`onemkl_dft_pack_1d_odd`. The whole conjugate-even sequence can be reconstructed as follows (using USM pointers) :

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n
      datatype * AC; // sizeof(datatype)*(n+2)

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::CCS_FORMAT);

      // ...

      // on input: R(k) = AR[k]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output:
      // for k=0, n/2:      Z{k} = AC[2*k+0]         + i*AC[2*k+1]
      // for k=n/2+1, n-1:  Z{k} = AC[2*(n-k)%n + 0] - i*AC{2*(n-k)%n + 1] 


.. container:: section

   .. _onemkl_dft_config_packed_format_1d_pack:

   .. rubric:: PACK_FORMAT for One-Dimensional Transforms

   For a one-dimensional size-``n`` conjugate-even sequence being stored in a PACK packed format, we require ``n`` elements in the array.
   The real and imaginary parts of the complex-valued conjugate-even sequence, :math:`z_k`, are located in a real valued array as seen in :ref:`onemkl_dft_pack_1d_even` and :ref:`onemkl_dft_pack_1d_odd`. The whole conjugate-even sequence can be reconstructed as follows (using USM pointers) :

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n
      datatype * AC; // sizeof(datatype)*n

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::PACK_FORMAT);

      // ...

      // on input: R{k} = AR[k]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output: Z{k} = re + i*im  where
      // if (k==0) {
      //   re =  AC[0];
      //   im =  0;
      // } else if (k==n-k) {
      //   re =  AC[2*k-1];
      //   im =  0;
      // } else if (k<=n-2) {
      //   re =  AC[2*k-1];
      //   im =  AC[2*k-0];
      // } else {
      //   re =  AC[2*(n-k)-1];
      //   im = -AC[2*(n-k)-0];
      // }

.. container:: section

   .. _onemkl_dft_config_packed_format_1d_perm:

   .. rubric:: PERM_FORMAT for One-Dimensional Transforms

   For a one-dimensional size-``n`` conjugate-even sequence being stored in a PERM packed format, we require ``n`` elements in the array.
   The real and imaginary parts of the complex-valued conjugate-even sequence, :math:`z_k`, are located in a real valued array as seen in :ref:`onemkl_dft_pack_1d_even` and :ref:`onemkl_dft_pack_1d_odd`. The whole conjugate-even sequence can be reconstructed as follows (using USM pointers) :

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n
      datatype * AC; // sizeof(datatype)*n

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::PACK_FORMAT);

      // ...

      // on input: R{k} = AR[k]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output: Z{k} = re + i*im  where
      // if (k==0) {
      //   re =  AC[0];
      //   im =  0;
      // } else if (k==n-k) {
      //   re =  AC[1];
      //   im =  0;
      // } else if (k<=n-2) {
      //   re =  AC[2*k+0 - n%2];
      //   im =  AC[2*k+1 - n%2];
      // } else {
      //   re =  AC[2*(n-k)+0 - n%2];
      //   im = -AC[2*(n-k)+1 - n%2];
      // }


.. container:: section

   .. _onemkl_dft_config_packed_format_2d_ccs:

   .. rubric:: CCS_FORMAT for Multi-dimensional Transforms

   The ``config_value::CCS_FORMAT`` for multi-dimensional transformations is defined as a Cartesian product of the one-dimensional case in each dimension using row-major layout and zero based indexing.  For example, the 2-dimensional :math:`m\times n` conjugate-even sequence in a real array for CCS packed format requires an array of size :math:`(m+2)(n+2)`.  There are four resulting configurations for 2D depending on if each dimension is even or odd.  The following figures show two such variants, with both dimensions being even and both being odd.  The other variants can be looked up in the literature but the 2D formula for how to construct the general complex-valued conjugate-even sequence from CCS packed format is provided below.  

   .. rubric:: CCS_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K` and :math:`n=2L`. (n/u=not used)

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-1
          -   n
          -   n+1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`0`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`\dots`
          -   :math:`I_{0,L-1}`
          -   :math:`R_{0,L}`
          -   :math:`0`
        * -   1
          -   :math:`0`
          -   :math:`0`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`\dots`
          -   :math:`I_{1,L-1}`
          -   :math:`0`
          -   :math:`0`
        * -   2
          -   :math:`R_{1,0}`
          -   :math:`0`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`\dots`
          -   :math:`I_{2,L-1}`
          -   :math:`R_{1,L}`
          -   :math:`0`
        * -   3
          -   :math:`I_{1,0}`
          -   :math:`0`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`\dots`
          -   :math:`I_{3,L-1}`
          -   :math:`I_{1,L}`
          -   :math:`0`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-2
          -   :math:`R_{K-1,0}`
          -   :math:`0`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`\dots`
          -   :math:`I_{m-2,L-1}`
          -   :math:`R_{K-1,L}`
          -   :math:`0`
        * -   m-1
          -   :math:`I_{K-1,0}`
          -   :math:`0`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`\dots`
          -   :math:`I_{m-1,L-1}`
          -   :math:`I_{K-1,L}`
          -   :math:`0`
        * -   m
          -   :math:`R_{K,0}`
          -   :math:`0`
          -   n/u
          -   n/u
          -   n/u
          -   n/u
          -   :math:`R_{K,L}`
          -   :math:`0`
        * -   m+1
          -   :math:`0`
          -   :math:`0`
          -   n/u
          -   n/u
          -   n/u
          -   n/u
          -   :math:`0`
          -   :math:`0`


   .. rubric:: CCS_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K+1` and :math:`n=2L+1`. (n/u = not used)

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-1
          -   n
          -   n+1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`0`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`\dots`
          -   :math:`I_{0,L-1}`
          -   :math:`R_{0,L}`
          -   :math:`I_{0,L}`
        * -   1
          -   :math:`0`
          -   :math:`0`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`\dots`
          -   :math:`I_{1,L-1}`
          -   :math:`R_{1,L}`
          -   :math:`I_{1,L}`
        * -   2
          -   :math:`R_{1,0}`
          -   :math:`0`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`\dots`
          -   :math:`I_{2,L-1}`
          -   :math:`R_{2,L}`
          -   :math:`I_{2,L}`
        * -   3
          -   :math:`I_{1,0}`
          -   :math:`0`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`\dots`
          -   :math:`I_{3,L-1}`
          -   :math:`R_{3,L}`
          -   :math:`I_{3,L}`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-2
          -   :math:`R_{K-1,0}`
          -   :math:`0`
          -   :math:`R_{m-3,1}`
          -   :math:`I_{m-3,1}`
          -   :math:`\dots`
          -   :math:`I_{m-3,L-1}`
          -   :math:`R_{m-3,L}`
          -   :math:`I_{m-3,L}`
        * -   m-1
          -   :math:`I_{K-1,0}`
          -   :math:`0`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`\dots`
          -   :math:`I_{m-2,L-1}`
          -   :math:`R_{m-2,L}`
          -   :math:`I_{m-2,L}`
        * -   m
          -   :math:`R_{K,0}`
          -   :math:`0`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`\dots`
          -   :math:`I_{m-1,L-1}`
          -   :math:`R_{m-1,L}`
          -   :math:`I_{m-1,L}`
        * -   m+1
          -   :math:`I_{K,0}`
          -   :math:`0`
          -   n/u
          -   n/u
          -   n/u
          -   n/u
          -   n/u
          -   n/u



   The real and imaginary parts of the complex-valued conjugate-even sequence :math:`z_{k_1,k_2}` are located in a real-valued array, AC, in ``config_value::CCS_FORMAT`` and can be used to reconstruct the whole sequence as follows:

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n1*n2
      datatype * AC; // sizeof(datatype)*(n1+2)*(n2+2)

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::CCS_FORMAT);

      // ...

      // on input: R{k1,k2} = AR[(n2+2)*k1+k2]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output: Z{k1,k2} = re + i*im  where
      // if (k1==0) {
      //    if (k2 <= n2/2) {
      //       re =  AC[2*k2+0];
      //       im =  AC[2*k2+1];
      //    } else {
      //       re =  AC[2*(n2-k2)+0];
      //       im = -AC[2*(n2-k2)+1];
      //    }
      // } else if (k2==0) {
      //    if (k1 <= n1/2) {
      //       re =  AC[(2*k1+0)*(n2+2)];
      //       im =  AC[(2*k1+1)*(n2+2)];
      //    } else {
      //       re =  AC[(2*(n1-k1)+0)*(n2+2)];
      //       im = -AC[(2*(n1-k1)+1)*(n2+2)];
      //    }
      // } else if (k2==n2-k2) {
      //    if (k1 <= n1/2) {
      //       re =  AC[(2*k1+0)*(n2+2) + 2*(n2/2)];
      //       im =  AC[(2*k1+1)*(n2+2) + 2*(n2/2)];
      //    } else {
      //       re =  AC[(2*(n1-k1)+0)*(n2+2) + 2*(n2/2)];
      //       im = -AC[(2*(n1-k1)+1)*(n2+2) + 2*(n2/2)];
      //    }
      // } else if (k2 <= n2/2) {
      //   re =  AC[k1*(n2+2) + 2*k2+0];
      //   im =  AC[k1*(n2+2) + 2*k2+1];
      // } else {
      //   re =  AC[(n1-k1)*(n2+2)+2*(n2-k2)+0];
      //   im = -AC[(n1-k1)*(n2+2)+2*(n2-k2)+1];
      // }


.. container:: section

   .. _onemkl_dft_config_packed_format_2d_pack:

   .. rubric:: PACK_FORMAT for Multi-Dimensional Transforms

   The ``config_value::PACK_FORMAT`` for multi-dimensional transformations is also defined as a Cartesian product of the one-dimensional case in each dimension using a row-major layout and zero-based indexing.  For example, the 2-dimensional :math:`m\times n` conjugate-even sequence in a real array for PACK packed format requires an array of size :math:`(m)(n)`.  There are four resulting configurations for 2D depending on if each dimension is even or odd.  The following figures show two such variants, the first with each dimension being even, the second with dimensions even-by-odd.  The other variants can be looked up in the literature but the 2D formula for how to construct the general complex-valued conjugate-even sequence from the ``config_value::PACK_FORMAT`` is provided below.

   .. rubric:: PACK_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K` and :math:`n=2L`

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-2
          -   n-1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`R_{0,2}`
          -   :math:`\dots`
          -   :math:`I_{0,L-1}`
          -   :math:`R_{0,L}`
        * -   1
          -   :math:`R_{1,0}`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`R_{1,2}`
          -   :math:`\dots`
          -   :math:`I_{1,L-1}`
          -   :math:`R_{1,L}`
        * -   2
          -   :math:`I_{1,0}`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`R_{2,2}`
          -   :math:`\dots`
          -   :math:`I_{2,L-1}`
          -   :math:`I_{1,L}`
        * -   3
          -   :math:`R_{2,0}`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`R_{3,2}`
          -   :math:`\dots`
          -   :math:`I_{3,L-1}`
          -   :math:`R_{2,L}`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-2
          -   :math:`I_{K-1,0}`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`R_{m-2,2}`
          -   :math:`\dots`
          -   :math:`I_{m-2,L-1}`
          -   :math:`I_{K-1,L}`
        * -   m-1
          -   :math:`R_{K,0}`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`R_{m-1,2}`
          -   :math:`\dots`
          -   :math:`I_{m-1,L-1}`
          -   :math:`R_{K,L}`


   .. rubric:: PACK_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K` and :math:`n=2L+1`

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-3
          -   n-2
          -   n-1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`R_{0,2}`
          -   :math:`\dots`
          -   :math:`I_{0,L-1}`
          -   :math:`R_{0,L}`
          -   :math:`I_{0,L}`
        * -   1
          -   :math:`R_{1,0}`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`R_{1,2}`
          -   :math:`\dots`
          -   :math:`I_{1,L-1}`
          -   :math:`R_{1,L}`
          -   :math:`I_{1,L}`
        * -   2
          -   :math:`I_{1,0}`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`R_{2,2}`
          -   :math:`\dots`
          -   :math:`I_{2,L-1}`
          -   :math:`R_{2,L}`
          -   :math:`I_{2,L}`
        * -   3
          -   :math:`R_{2,0}`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`R_{3,2}`
          -   :math:`\dots`
          -   :math:`I_{3,L-1}`
          -   :math:`R_{3,L}`
          -   :math:`I_{3,L}`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-2
          -   :math:`I_{K-1,0}`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`R_{m-2,2}`
          -   :math:`\dots`
          -   :math:`R_{m-2,L-1}`
          -   :math:`R_{m-2,L}`
          -   :math:`I_{m-2,L}`
        * -   m-1
          -   :math:`R_{K,0}`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`R_{m-1,2}`
          -   :math:`\dots`
          -   :math:`I_{m-1,L-1}`
          -   :math:`R_{m-1,L}`
          -   :math:`I_{m-1,L}`

   The real and imaginary parts of the complex-valued conjugate-even sequence :math:`z_{k_0,k_1}` are located in a real-valued array, AC, in ``config_param::PACK_FORMAT`` and can be used to reconstruct the whole sequence as follows:

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n1*n2
      datatype * AC; // sizeof(datatype)*n1*n2

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::PACK_FORMAT);

      // ...

      // on input: R{k1,k2} = AR[n2*k1+k2]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output: Z{k1,k2} = re + i*im  where
      // if (k1==0) {
      //    if (k2 == 0) {
      //       re =  AC[0];
      //       im =  0;
      //    } else if (k2 == n2-k2) {
      //       re =  AC[2*k2-1];
      //       im =  0;
      //    } else if (k2 <= n2/2) {
      //       re =  AC[2*k2-1];
      //       im =  AC[2*k2-0];
      //    } else {
      //       re =  AC[2*(n2-k2)-1];
      //       im = -AC[2*(n2-k2)-0];
      //    }
      // } else if (k2==0) {
      //    if (k1 == n1-k1) {
      //       re =  AC[(n1-1)*n2];
      //       im =  0;
      //    } else if (k1 <= n1/2) {
      //       re =  AC[(2*k1-1)*n2];
      //       im =  AC[(2*k1-0)*n2];
      //    } else {
      //       re =  AC[(2*(n1-k1)-1)*n2];
      //       im = -AC[(2*(n1-k1)-0)*n2];
      //    }
      // } else if (k2==n2-k2) {
      //    if (k1 == n1-k1) {
      //       re =  AC[n1*n2 - 1];
      //       im =  0;
      //    } else if (k1 <= n1/2) {
      //       re =  AC[(2*k1-1)*n2 + n2-1];
      //       im =  AC[(2*k1-0)*n2 + n2-1];
      //    } else {
      //       re =  AC[(2*(n1-k1)-1)*n2 + n2-1];
      //       im = -AC[(2*(n1-k1)-0)*n2 + n2-1];
      //    }
      // } else if (k2 <= n2/2) {
      //   re =  AC[k1*n2 + 2*k2-1];
      //   im =  AC[k1*n2 + 2*k2-0];
      // } else {
      //   re =  AC[(n1-k1)*n2+2*(n2-k2)-1];
      //   im = -AC[(n1-k1)*n2+2*(n2-k2)-0];
      // }


.. container:: section

   .. _onemkl_dft_config_packed_format_2d_perm:

   .. rubric:: PERM_FORMAT for Multi-dimensional Transforms

   The ``config_value::PERM_FORMAT`` for multi-dimensional transformations is also defined as a cartesian product of the one-dimensional case in each dimension and using a row-major layout and zero-based indexing.  For example, the 2-dimensional :math:`m\times n` conjugate-even sequence in a real array for PACK packed format requires an array of size :math:`(m)(n)`. There are four resulting configurations depending on if each dimension is even or odd.  The following figures show two such variants, first with each dimension even, then with dimensions odd-by-even.  The other variants for can be looked up in the literature but the 2D formula for how to construct the general complex-valued conjugate-even sequence from the ``config_value::PERM_FORMAT`` is provided below.


   .. rubric:: PERM_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K` and :math:`n=2L`

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-2
          -   n-1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`R_{0,L}`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`\dots`
          -   :math:`R_{0,L-1}`
          -   :math:`I_{0,L-1}`
        * -   1
          -   :math:`R_{K,0}`
          -   :math:`R_{1,L}`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`\dots`
          -   :math:`R_{1,L-1}`
          -   :math:`I_{1,L-1}`
        * -   2
          -   :math:`R_{1,0}`
          -   :math:`R_{2,L}`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`\dots`
          -   :math:`R_{2,L-1}`
          -   :math:`I_{2,L-1}`
        * -   3
          -   :math:`I_{1,0}`
          -   :math:`I_{2,L}`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`\dots`
          -   :math:`R_{3,L-1}`
          -   :math:`I_{3,L-1}`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-2
          -   :math:`R_{K-1,0}`
          -   :math:`R_{K-1,L}`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`\dots`
          -   :math:`R_{m-2,L-1}`
          -   :math:`I_{m-2,L-1}`
        * -   m-1
          -   :math:`I_{K-1,0}`
          -   :math:`I_{K-1,L}`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`\dots`
          -   :math:`R_{m-1,L-1}`
          -   :math:`I_{m-1,L-1}`



   .. rubric:: PERM_FORMAT for a two-dimensional :math:`m\times n` transformation with :math:`m=2K+1` and :math:`n=2L`

   .. tabularcolumns:: |c|c|c|c|c|c|c|c|

   .. list-table::
        :header-rows: 1
        :stub-columns: 1
        :class: longtable

        * -   :math:`k_1\backslash k_2`
          -   :math:`0`
          -   1
          -   2
          -   3
          -   :math:`\dots`
          -   n-2
          -   n-1
        * -   :math:`0`
          -   :math:`R_{0,0}`
          -   :math:`R_{0,L}`
          -   :math:`R_{0,1}`
          -   :math:`I_{0,1}`
          -   :math:`\dots`
          -   :math:`R_{0,L-1}`
          -   :math:`I_{0,L-1}`
        * -   1
          -   :math:`R_{1,0}`
          -   :math:`R_{1,L}`
          -   :math:`R_{1,1}`
          -   :math:`I_{1,1}`
          -   :math:`\dots`
          -   :math:`R_{1,L-1}`
          -   :math:`I_{1,L-1}`
        * -   2
          -   :math:`I_{1,0}`
          -   :math:`I_{1,L}`
          -   :math:`R_{2,1}`
          -   :math:`I_{2,1}`
          -   :math:`\dots`
          -   :math:`R_{2,L-1}`
          -   :math:`I_{2,L-1}`
        * -   3
          -   :math:`R_{2,0}`
          -   :math:`R_{2,L}`
          -   :math:`R_{3,1}`
          -   :math:`I_{3,1}`
          -   :math:`\dots`
          -   :math:`R_{3,L-1}`
          -   :math:`I_{3,L-1}`
        * -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
          -   :math:`\dots`
        * -   m-3
          -   :math:`I_{K-1,0}`
          -   :math:`I_{K-1,L}`
          -   :math:`R_{m-3,1}`
          -   :math:`I_{m-3,1}`
          -   :math:`\dots`
          -   :math:`R_{m-3,L-1}`
          -   :math:`I_{m-3,L-1}`
        * -   m-2
          -   :math:`R_{K,0}`
          -   :math:`R_{K,L}`
          -   :math:`R_{m-2,1}`
          -   :math:`I_{m-2,1}`
          -   :math:`\dots`
          -   :math:`R_{m-2,L-1}`
          -   :math:`I_{m-2,L-1}`
        * -   m-1
          -   :math:`I_{K,0}`
          -   :math:`I_{K,L}`
          -   :math:`R_{m-1,1}`
          -   :math:`I_{m-1,1}`
          -   :math:`\dots`
          -   :math:`R_{m-1,L-1}`
          -   :math:`I_{m-1,L-1}`



   The real and imaginary parts of the complex-valued conjugate-even sequence :math:`z_{k_0,k_1}` are located in a real-valued array, AC, in ``config_param::PACK_FORMAT`` and can be used to reconstruct the whole sequence as follows:

   .. code-block:: cpp

      datatype * AR; // sizeof(datatype)*n1*n2
      datatype * AC; // sizeof(datatype)*n1*n2

      // ...

      descr.set_value(config_param::PACKED_FORMAT, config_value::PERM_FORMAT);

      // ...

      // on input: R{k1,k2} = AR[n2*k1+k2]
      compute_forward(descr, AR, AC); // real-to-complex FFT
      // on output: Z{k1,k2} = re + i*im  where
      // if (k1==0) {
      //    if (k2 == 0) {
      //       re =  AC[0];
      //       im =  0;
      //    } else if (k2 == n2-k2) {
      //       re =  AC[1];
      //       im =  0;
      //    } else if (k2 <= n2/2) {
      //       re =  AC[2*k2+0 - n2%2];
      //       im =  AC[2*k2+1 - n2%2];
      //    } else {
      //       re =  AC[2*(n2-k2)+0 - n2%2];
      //       im = -AC[2*(n2-k2)+1 - n2%2];
      //    }
      // } else if (k2==0) {
      //    if (k1 == n1-k1) {
      //       re =  AC[n2];
      //       im =  0;
      //    } else if (k1 <= n1/2) {
      //       re =  AC[(2*k1+0 - n1%2)*n2];
      //       im =  AC[(2*k1+1 - n1%2)*n2];
      //    } else {
      //       re =  AC[(2*(n1-k1)-1)*n2];
      //       im = -AC[(2*(n1-k1)-0)*n2];
      //    }
      // } else if (k2==n2-k2) {
      //    if (k1 == n1-k1) {
      //       re =  AC[n1*n2 - 1];
      //       im =  0;
      //    } else if (k1 <= n1/2) {
      //       re =  AC[(2*k1-1)*n2 + n2-1];
      //       im =  AC[(2*k1-0)*n2 + n2-1];
      //    } else {
      //       re =  AC[(2*(n1-k1)-1)*n2 + n2-1];
      //       im = -AC[(2*(n1-k1)-0)*n2 + n2-1];
      //    }
      // } else if (k2 <= n2/2) {
      //   re =  AC[k1*n2 + 2*k2-1];
      //   im =  AC[k1*n2 + 2*k2-0];
      // } else {
      //   re =  AC[(n1-k1)*n2+2*(n2-k2)-1];
      //   im = -AC[(n1-k1)*n2+2*(n2-k2)-0];
      // }



**Parent topic:** :ref:`onemkl_dft_enums`


