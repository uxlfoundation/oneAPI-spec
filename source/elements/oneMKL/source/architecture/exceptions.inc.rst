.. _onemkl_exceptions:

Exceptions and Error Handling
------------------------------

oneMKL error handling relies on the mechanism of C++ exceptions. Should error occur, it will be propagated at the point of a function call where it is caught using standard C++ error handling mechanism.

.. _onemkl_exception_classification:

Exception classification
++++++++++++++++++++++++

Exception classification in oneMKL is aligned with C++ Standard Library classification. oneMKL introduces class that defines the base class in the hierarchy of oneMKL exception classes. All oneMKL routines throw exceptions inherited from this base class.
In the hierarchy of oneMKL exceptions, ``oneapi::mkl::exception`` is the base class inherited from ``std::exception`` class. All other oneMKL exception classes are derived from this base class.

This specification does not require implementations to perform error-checking. However, if an implementation does provide error-checking, it shall use the following exception classes. Additional implementation-specific exception classes can be used for exceptional conditions not fitting any of these classes.

.. _onemkl_common_exceptions:

Common exceptions
*****************

.. csv-table::
    :header: "Exception class", "Description"
    :widths: 40, 60

    ".. _onemkl_exception:

    ``oneapi::mkl::exception``", "Reports general unspecified problem"
    ".. _onemkl_exception_unsupported_device:

    ``oneapi::mkl::unsupported_device``", "Reports a problem when the routine is not supported on a specific device"
    ".. _onemkl_exception_host_bad_alloc:

    ``oneapi::mkl::host_bad_alloc``", "Reports a problem that occurred during memory allocation on the host"
    ".. _onemkl_exception_device_bad_alloc:

    ``oneapi::mkl::device_bad_alloc``", "Reports a problem that occurred during memory allocation on a specific device"
    ".. _onemkl_exception_unimplemented:

    ``oneapi::mkl::unimplemented``", "Reports a problem when a specific routine has not been implemented for the specified parameters"
    ".. _onemkl_exception_invalid_argument:

    ``oneapi::mkl::invalid_argument``", "Reports problem when arguments to the routine were rejected"
    ".. _onemkl_exception_uninitialized:

    ``oneapi::mkl::uninitialized``", "Reports problem when a handle (descriptor) has not been initialized"
    ".. _onemkl_exception_computation_error:

    ``oneapi::mkl::computation_error``", "Reports any computation errors that have ccurred inside a oneMKL routine"
    ".. _onemkl_exception_batch_error:

    ``oneapi::mkl::batch_error``", "Reports errors that have occurred inside a batch oneMKL routine"


.. _onemkl_lapack_specific_exceptions:

LAPACK specific exceptions
**************************

.. csv-table::
    :header: "Exception class", "Description"
    :widths: 40, 60

    ".. _onemkl_lapack_exception:

    ``oneapi::mkl::lapack::exception``", "Reports general errors that occur inside a LAPACK routine"
    ".. _onemkl_lapack_batch_exception:

    ``oneapi::mkl::lapack::batch_exception``", "Reports general errors that occur inside a LAPACK batch routine"

