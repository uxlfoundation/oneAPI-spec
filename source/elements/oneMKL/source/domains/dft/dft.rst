.. _onemkl_dft:

Fourier Transform Functions
---------------------------

.. container::


   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain> <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain.html>`__
      Creates an empty descriptor for the templated precision and
      forward domain.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::Init <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-init.html>`__
      Allocates the descriptor data structure and initializes it with
      default configuration values.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::setValue <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-setvalue.html>`__
      Sets one particular configuration parameter with the specified
      configuration value.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::getValue <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-getvalue.html>`__
      Gets the configuration value of one particular configuration
      parameter.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::commit <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-commit.html>`__
      Performs all initialization for the actual FFT computation.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::computeForward<typename
      IOType> <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computeforward-typename-iotype.html>`__
      Computes the forward FFT.
   -  `onemkl::dft::Descriptor<onemkl::dft::Precision,
      onemkl::dft::Domain>::computeBackward<typename
      IOType> <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computebackward-typename-iotype.html>`__
      Computes the backward FFT.

**Parent topic:** :ref:`onemkl_domains`

.. toctree::
    :hidden:

    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-init
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-setvalue
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-getvalue
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-commit
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computeforward-typename-iotype
    mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computebackward-typename-iotype

