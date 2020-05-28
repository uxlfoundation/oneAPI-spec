.. _error_handling:

==============
Error handling
==============

oneDAL error handling relies on the  mechanism of C++ exceptions. If an error
occurs, it shall be propagated at the point of a function call where it can be
caught using standard C++ error handling mechanism.

Exception classification
========================

Exception classification in onDAL is aligned with C++ STL classification. oneDAL
shall introduce abstract classes defining the base for for hierarchy of
exception classes. Concrete exception classes are derived from respective STL
exception classes. oneDAL library shall throw exceptions represented with
concrete classes.

The root of exception hierarchy is ``onedal::exception``. The rest exception
classes are derived from this class.

::

    class onedal::exception;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``onedal::exception``
     - Base class of oneDAL exception hierarchy.
     - Yes

All errors divide into 3 groups: logic errors, runtime errors and bad allocation.

::

    class onedal::logic_error : public onedal::exception;
    class onedal::runtime_error : public onedal::exception;
    class onedal::bad_alloc :  public onedal::exception, public std::bad_alloc;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``onedal::logic_error``
     - Reports violations of preconditions and invariants.
     - Yes
   * - ``onedal::runtime_error``
     - Reports violations of postconditions and other errors happened during the
       execution of oneDAL functionality.
     - Yes
   * - ``onedal::bad_alloc``
     - Reports failure to allocate storage.
     - No

Precondition and invariant errors that are represented by
``onedal::logic_error`` are divided into subgroups: invalid argument, domain
error, out of range error, unimplemented method or algorithm, unavailable
device or data.

::

    class onedal::invalid_argument :  public onedal::logic_error, public std::invalid_argument;
    class onedal::domain_error :  public onedal::logic_error, public std::domain_error;
    class onedal::out_of_range :  public onedal::logic_error, public std::out_of_range;
    class onedal::unimplemented_error :  public onedal::logic_error, public std::logic_error;
    class onedal::unavailable_error :  public onedal::logic_error, public std::logic_error;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``onedal::invalid_argument``
     - Reports situations when the argument was not been accepted.
     - No
   * - ``onedal::domain_error``
     - Reports situations when the argument is outside of the domain on which
       the operation is defined. Higher priority than
       ``onedal::invalid_argument``.
     - No
   * - ``onedal::out_of_range``
     - Reports situations when the index is out of range. Higher priority
       than ``onedal::invalid_argument``.
     - No
   * - ``onedal::unimplemented_error``
     - Reports errors that arise because an algorithm or a method is not
       implemented.
     - No
   * - ``onedal::unavailable_error``
     - Reports situations when a device or data is not available.
     - No

If an error occurs during function execution after preconditions and invariants
were checked, it is reported via ``ondeal::runtime_error`` inheritors. oneDAL
distinguishes errors happened during interaction with OS facilities and errors
of destination type's range in internal computations, while other errors are
reported via ``onedal::internal_error``.

::

    class onedal::range_error :  public onedal::runtime_error, public std::range_error;
    class onedal::system_error :  public onedal::runtime_error, public std::system_error;
    class onedal::internal_error :  public onedal::runtime_error, public std::runtime_error;

.. list-table::
   :widths: 30 65 5
   :header-rows: 1

   * - Exception
     - Description
     - Abstract
   * - ``onedal::range_error``
     - Reports situations where a result of a computation cannot be represented by the destination type.
     - No
   * - ``onedal::system_error``
     - Reports errors occurred during interaction with OS facilities.
     - No
   * - ``onedal::internal_error``
     - Reports all runtime errors that couldn't be assigned to other inheritors.
     - No
