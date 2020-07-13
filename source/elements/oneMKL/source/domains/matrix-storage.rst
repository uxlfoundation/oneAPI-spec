.. _matrix-storage:

Matrix Storage
==============


.. container::


   The oneMKL BLAS and LAPACK routines for DPC++ use several matrix and
   vector storage formats. These are the same formats used in
   traditional Fortran BLAS/LAPACK.


   .. container:: section
      :name: GUID-5DD12E9B-8079-4EFD-8B91-5CF134D55082


      .. rubric:: General Matrix
         :name: general-matrix
         :class: sectiontitle


      A general matrix ``A`` of ``m`` rows and ``n`` columns with
      leading dimension ``lda`` is represented as a one dimensional
      array ``a`` of size of at least ``lda`` \* ``n`` if column major
      layout is used and at least ``lda`` \* ``m`` if row major layout
      is used.  Before entry in any BLAS function using a general
      matrix, the leading ``m`` by ``n`` part of the array ``a`` must
      contain the matrix ``A``. For column (respectively row) major
      layout, the elements of each column (respectively row) are
      contiguous in memory while the elements of each row
      (respectively column) are at distance ``lda`` from the element
      in the same row (respectively column) and the previous column
      (respectively row).


      Visually, the matrix

      
      |image_generic_matrix|


      is stored in memory as an array

      - For column major layout,

      |image_generic_matrix_column_major|

      - For row major layout,

      |image_generic_matrix_row_major|
        
   .. container:: section
      :name: GUID-150ACC6B-BB73-4E6E-A7F7-9CE07707FA0E


      .. rubric:: Triangular Matrix
         :name: triangular-matrix
         :class: sectiontitle


      A triangular matrix ``A`` of ``n`` rows and ``n`` columns with
      leading dimension ``lda`` is represented as a one dimensional
      array ``a``, of a size of at least ``lda`` \* ``n``. When column
      (respectively row) major layout is used, the elements of each
      column (respectively row) are contiguous in memory while the
      elements of each row (respectively column) are at distance
      ``lda`` from the element in the same row (respectively column)
      and the previous column (respectively row).


      Before entry in any BLAS function using a triangular matrix,


      -  If ``upper_lower = uplo::upper``, the leading ``n`` by ``n``
         upper triangular part of the array ``a`` must contain the upper
         triangular part of the matrix ``A``. The strictly lower
         triangular part of the array ``a`` is not referenced. In other
         words, the matrix


         |image_upper_triangular_matrix|


         is stored in memory as the array

         - For column major layout,

         |image_upper_triangular_matrix_column_major|

         - For row major layout,

         |image_upper_triangular_matrix_row_major|

      -  If ``upper_lower = uplo::lower``, the leading ``n`` by ``n``
         lower triangular part of the array ``a`` must contain the lower
         triangular part of the matrix ``A``. The strictly upper
         triangular part of the array ``a`` is not referenced. That is,
         the matrix


         |image_lower_triangular_matrix|


         is stored in memory as the array

         - For column major layout,
         
         |image_lower_triangular_matrix_column_major|

         - For row major layout,

         |image_lower_triangular_matrix_row_major|

   .. container:: section
      :name: GUID-4A6389BD-0396-4C6D-8AA4-C59EDAC7A991


      .. rubric:: Band Matrix
         :name: band-matrix
         :class: sectiontitle


      A general band matrix ``A`` of ``m`` rows and ``n`` columns with
      ``kl`` sub-diagonals, ``ku`` super-diagonals, and leading
      dimension ``lda`` is represented as a one dimensional array
      ``a`` of a size of at least ``lda`` \* ``n`` (respectively
      ``lda`` \* ``m``) if column (respectively row) major layout is
      used.


      Before entry in any BLAS function using a general band matrix,
      the leading (``kl`` + ``ku`` + 1\ ``)`` by ``n`` (respectively
      ``m``) part of the array ``a`` must contain the matrix
      ``A``. This matrix must be supplied column-by-column
      (respectively row-by-row), with the main diagonal of the matrix
      in row ``ku`` (respectively ``kl``) of the array (0-based
      indexing), the first super-diagonal starting at position 1
      (respectively 0) in row (``ku`` - 1) (respectively column
      (``kl`` + 1)), the first sub-diagonal starting at position 0
      (respectively 1) in row (``ku`` + 1) (respectively column
      (``kl`` - 1)), and so on. Elements in the array ``a`` that do
      not correspond to elements in the band matrix (such as the top
      left ``ku`` by ``ku`` triangle) are not referenced.


      Visually, the matrix ``A`` =


      |image_band_matrix|


      is stored in memory as an array

      - For column major layout,
        
      |image_band_matrix_column_major|

      - For row major layout,

      |image_band_matrix_row_major|
      
      The following program segment transfers a band matrix from
      conventional full matrix storage (variable ``matrix``, with
      leading dimension ``ldm``) to band storage (variable ``a``, with
      leading dimension ``lda``):


      - Using matrices stored with column major layout,
        
      ::


         for (j = 0; j < n; j++) {
             k = ku – j;
             for (i = max(0, j – ku); i < min(m, j + kl + 1); i++) {
                 a[(k + i) + j * lda] = matrix[i + j * ldm];
             }
         }

      - Using matrices stored with row major layout,

      ::


         for (i = 0; i < n; i++) {
             k = kl – i;
             for (j = max(0, i – kl); j < min(n, i + ku + 1); j++) {
                 a[(k + j) + i * lda] = matrix[j + i * ldm];
             }
         }
        

   .. container:: section
      :name: GUID-D85FAA87-6868-4DCA-BD38-9C4F4214BD52


      .. rubric:: Triangular Band Matrix
         :name: triangular-band-matrix
         :class: sectiontitle


      A triangular band matrix ``A`` of ``n`` rows and ``n`` columns
      with ``k`` sub/super-diagonals and leading dimension ``lda`` is
      represented as a one dimensional array ``a`` of size at least
      ``lda`` \* ``n``.


      Before entry in any BLAS function using a triangular band matrix,


      - If ``upper_lower = uplo::upper``, the leading (``k`` + 1) by ``n``
        part of the array ``a`` must contain the upper
        triangular band part of the matrix ``A``. When using column
        major layout, this matrix must be supplied column-by-column
        (respectively row-by-row) with the main diagonal of the
        matrix in row (``k``) (respectively column 0) of the array,
        the first super-diagonal starting at position 1
        (respectively 0) in row (``k`` - 1) (respectively column 1),
        and so on. Elements in the array ``a`` that do not correspond
        to elements in the triangular band matrix (such as the top
        left ``k`` by ``k`` triangle) are not referenced.

        Visually, the matrix

        
        |image_upper_triangular_band_matrix|


        is stored as an array


      .. container:: fignone
         :name: GUID-CBD17940-8F30-4779-AEB3-C17E9ADB60EC
                            
                            
         - For column major layout,
                 
           |image_upper_triangular_band_matrix_column_major|

         - For row major layout,

           |image_upper_triangular_band_matrix_row_major|

         The following program segment transfers a band matrix from
         conventional full matrix storage (variable ``matrix``, with
         leading dimension ``ldm``) to band storage (variable ``a``,
         with leading dimension ``lda``):

         - Using matrices stored with column major layout,

         ::


            for (j = 0; j < n; j++) {
                m = k – j;
                for (i = max(0, j – k); i <= j; i++) {
                    a[(m + i) + j * lda] = matrix[i + j * ldm];
                }
            }

         - Using matrices stored with column major layout,

         ::

            for (i = 0; i < n; i++) {
                m = –i;
                for (j = i; j < min(n, i + k + 1); j++) {
                    a[(m + j) + i * lda] = matrix[j + i * ldm];
                }
            }
            

      - If ``upper_lower = uplo::lower``, the leading (``k`` + 1) by ``n``
        part of the array ``a`` must contain the upper triangular
        band part of the matrix ``A``. This matrix must be supplied
        column-by-column with the main diagonal of the matrix in row 0
        of the array, the first sub-diagonal starting at position 0 in
        row 1, and so on. Elements in the array ``a`` that do not
        correspond to elements in the triangular band matrix (such as
        the bottom right ``k`` by ``k`` triangle) are not referenced.

        That is, the matrix


        |image_lower_triangular_band_matrix|


        is stored as the array


      .. container:: fignone
         :name: GUID-D89A1D4C-831C-4D8E-AD9F-0DFB968841E1


         - For column major layout,
           
           |image_lower_triangular_band_matrix_column_major|

         - For row major layout,
           
           |image_lower_triangular_band_matrix_row_major|

         The following program segment transfers a band matrix from
         conventional full matrix storage (variable ``matrix``, with
         leading dimension ``ldm``) to band storage (variable ``a``,
         with leading dimension ``lda``):


         - Using matrices stored with column major layout,
           
         ::


            for (j = 0; j < n; j++) {
                m = –j;
                for (i = j; i < min(n, j + k + 1); i++) {
                    a[(m + i) + j * lda] = matrix[i + j * ldm];
                }
            }

         - Using matrices stored with row major layout,

         ::


            for (i = 0; i < n; i++) {
                m = k – i;
                for (j = max(0, i – k); j <= i; j++) {
                    a[(m + j) + i * lda] = matrix[j + i * ldm];
                }
            }


   .. container:: section
      :name: GUID-41C95365-5CE1-46F9-869C-27647E5ABE2B


      .. rubric:: Packed Triangular Matrix
         :name: packed-triangular-matrix
         :class: sectiontitle


      A triangular matrix ``A`` of ``n`` rows and ``n`` columns is
      represented in packed format as a one dimensional array ``a`` of
      size at least (``n``\ \*(``n`` + 1))/2. All elements in the upper
      or lower part of the matrix ``A`` are stored contiguously in the
      array ``a``.


      Before entry in any BLAS function using a triangular packed
      matrix,


      - If ``upper_lower = uplo::upper``, if column (respectively row)
        major layout is used, the first (``n``\ \*(``n`` + 1))/2
        elements in the array ``a`` must contain the upper triangular
        part of the matrix ``A`` packed sequentially, column by column
        (respectively row by row) so that ``a``\ [0] contains ``A``\
        :sub:`11`, ``a``\ [1] and ``a``\ [2] contain ``A``\ :sub:`12`
        and ``A``\ :sub:`22` (respectively ``A``\ :sub:`13`)
        respectively, and so on. Hence, the matrix


        |image_upper_triangular_pack_matrix|


        is stored as the array

        - For column major layout,

          |image_upper_triangular_pack_matrix_column_major|

        - For row major layout,

          |image_upper_triangular_pack_matrix_row_major|
       

      - If ``upper_lower = uplo::lower``, if column (respectively row)
        major layout is used, the first (``n``\ \*(``n`` + 1))/2
        elements in the array ``a`` must contain the lower triangular
        part of the matrix ``A`` packed sequentially, column by column
        (row by row) so that ``a``\ [0] contains ``A``\ :sub:`11`,
        ``a``\ [1] and ``a``\ [2] contain ``A``\ :sub:`21` and ``A``\
        :sub:`31` (respectively ``A``\ :sub:`22`) respectively, and so
        on. The matrix


         |image14|


         is stored as the array

         - For column major layout,
           
         |image_lower_triangular_pack_matrix_column_major|

         - For row major layout,
           
         |image_lower_triangular_pack_matrix_row_major|


   .. container:: section
      :name: GUID-44CE5D09-0117-46D1-B6EA-333D4550A457


      .. rubric:: Vector
         :name: vector
         :class: sectiontitle


      A vector ``X`` of ``n`` elements with increment ``incx`` is
      represented as a one dimensional array ``x`` of size at least (1 +
      (``n`` - 1) \* abs(``incx``)).


      Visually, the vector


      |image_vector|


      is stored in memory as an array


      .. container:: fignone
         :name: GUID-6929FFA1-5209-4D51-A2B8-CCA373841258


         |image_vector_array|


      **Parent topic:** :ref:`onemkl_dense_linear_algebra`


.. |image_generic_matrix| image:: equations/generic_matrix.png
   :class: img-middle
.. |image_generic_matrix_column_major| image:: equations/generic_matrix_column_major.png
.. |image_generic_matrix_row_major| image:: equations/generic_matrix_row_major.png
.. |image_upper_triangular_matrix| image:: equations/upper_triangular_matrix.png
   :class: img-middle
.. |image_upper_triangular_matrix_column_major| image:: equations/upper_triangular_matrix_column_major.png
.. |image_upper_triangular_matrix_row_major| image:: equations/upper_triangular_matrix_row_major.png
.. |image_lower_triangular_matrix| image:: equations/lower_triangular_matrix.png
   :class: img-middle
.. |image_lower_triangular_matrix_column_major| image:: equations/lower_triangular_matrix_column_major.png
.. |image_lower_triangular_matrix_row_major| image:: equations/lower_triangular_matrix_row_major.png
.. |image_band_matrix| image:: equations/band_matrix.png
   :class: img-middle
.. |image_band_matrix_column_major| image:: equations/band_matrix_column_major.png
.. |image_band_matrix_row_major| image:: equations/band_matrix_row_major.png
.. |image_upper_triangular_band_matrix| image:: equations/upper_triangular_band_matrix.png
   :class: img-middle
.. |image_upper_triangular_band_matrix_column_major| image:: equations/upper_triangular_band_matrix_column_major.png
.. |image_upper_triangular_band_matrix_row_major| image:: equations/upper_triangular_band_matrix_row_major.png
.. |image_lower_triangular_band_matrix| image:: equations/lower_triangular_band_matrix.png
   :class: img-middle
.. |image_lower_triangular_band_matrix_column_major| image:: equations/lower_triangular_band_matrix_column_major.png
.. |image_lower_triangular_band_matrix_row_major| image:: equations/lower_triangular_band_matrix_row_major.png
.. |image_upper_triangular_pack_matrix| image:: equations/upper_triangular_pack_matrix.png
   :class: img-middle
.. |image_upper_triangular_pack_matrix_column_major| image:: equations/upper_triangular_pack_matrix_column_major.png
.. |image_upper_triangular_pack_matrix_row_major| image:: equations/upper_triangular_pack_matrix_row_major.png
   :class: img-middle
.. |image14| image:: equations/GUID-B9AEF80A-AD5F-4B59-9F21-60672FB15ee9.png
   :class: img-middle
.. |image_lower_triangular_pack_matrix_column_major| image:: equations/GUID-B9AEF80A-AD5F-4B59-9F21-60672FB15e10.png
.. |image_lower_triangular_pack_matrix_row_major| image:: equations/lower_triangular_pack_matrix_row_major.png
   :class: img-middle
.. |image_vector| image:: equations/vector.png
   :class: img-middle
.. |image_vector_array| image:: equations/vector_array.png

