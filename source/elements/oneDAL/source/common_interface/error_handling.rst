.. _error_handling:

==============
Error handling
==============

oneDAL error handling relies on the mechanism of C++ exceptions. If an error
occurs, it shall be propagated at the point of a function call where it is
caught using standard C++ error handling mechanism.

Exception classification
========================

Exception classification in oneDAL is aligned with C++ Standard Library
classification. oneDAL shall introduce abstract classes that define the base
class in the hierarchy of exception classes. Concrete exception classes are
derived from the respective C++ Standard Library exception classes. oneDAL
library shall throw exceptions represented with concrete classes.

In the hierarchy of oneDAL exceptions, ``oneapi::dal::exception`` is the base abstract
class that all other exception classes are derived from.

::

    class oneapi::dal::exception;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``oneapi::dal::exception``
     - The base class of oneDAL exception hierarchy.
     - Yes

All oneDAL exceptions shall be divided into three groups:

- logic errors
- runtime errors
- errors with allocation

::

    class oneapi::dal::logic_error : public oneapi::dal::exception;
    class oneapi::dal::runtime_error : public oneapi::dal::exception;
    class oneapi::dal::bad_alloc :  public oneapi::dal::exception, public std::bad_alloc;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``oneapi::dal::logic_error``
     - Reports violations of preconditions and invariants.
     - Yes
   * - ``oneapi::dal::runtime_error``
     - Reports violations of postconditions and other errors happened during the
       execution of oneDAL functionality.
     - Yes
   * - ``oneapi::dal::bad_alloc``
     - Reports failure to allocate storage.
     - No

All precondition and invariant errors represented by ``oneapi::dal::logic_error``
shall be divided into the following groups:

- invalid argument errors
- domain errors
- out of range errors
- errors with an unimplemented method or algorithm
- unavailable device or data

::

    class oneapi::dal::invalid_argument :  public oneapi::dal::logic_error, public std::invalid_argument;
    class oneapi::dal::domain_error :  public oneapi::dal::logic_error, public std::domain_error;
    class oneapi::dal::out_of_range :  public oneapi::dal::logic_error, public std::out_of_range;
    class oneapi::dal::unimplemented_error :  public oneapi::dal::logic_error, public std::logic_error;
    class oneapi::dal::unavailable_error :  public oneapi::dal::logic_error, public std::logic_error;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``oneapi::dal::invalid_argument``
     - Reports situations when the argument was not been accepted.
     - No
   * - ``oneapi::dal::domain_error``
     - Reports situations when the argument is outside of the domain on which
       the operation is defined. Higher priority than
       ``oneapi::dal::invalid_argument``.
     - No
   * - ``oneapi::dal::out_of_range``
     - Reports situations when the index is out of range. Higher priority
       than ``oneapi::dal::invalid_argument``.
     - No
   * - ``oneapi::dal::unimplemented_error``
     - Reports errors that arise because an algorithm or a method is not
       implemented.
     - No
   * - ``oneapi::dal::unavailable_error``
     - Reports situations when a device or data is not available.
     - No

Errors occured during the execution of oneDAL functionality are represented with
``oneapi::dal::runtime_error``. Two main groups of errors are distinguished:

- destination type range errors
- OS facilities interaction errors

All other errors are reported via ``oneapi::dal::internal_error``.

::

    class oneapi::dal::range_error :  public oneapi::dal::runtime_error, public std::range_error;
    class oneapi::dal::system_error :  public oneapi::dal::runtime_error, public std::system_error;
    class oneapi::dal::internal_error :  public oneapi::dal::runtime_error, public std::runtime_error;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``oneapi::dal::range_error``
     - Reports situations where a result of a computation cannot be represented by the destination type.
     - No
   * - ``oneapi::dal::system_error``
     - Reports errors occurred during interaction with OS facilities.
     - No
   * - ``oneapi::dal::internal_error``
     - Reports all runtime errors that couldn't be assigned to other inheritors.
     - No
