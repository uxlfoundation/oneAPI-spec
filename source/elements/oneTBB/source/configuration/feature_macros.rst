==============
Feature Macros
==============

Macros in this section control optional features in
the library.

TBB_DEPRECATED_* macros
-----------------------

The macros starting with
``TBB_DEPRECATED`` control deprecated features that would
otherwise conflict with non-deprecated use. Define it to be 1
to keep using an earlier version of API or behavior.


TBB_USE_EXCEPTIONS macro
------------------------

The macro 
``TBB_USE_EXCEPTIONS`` controls whether the library
headers use exception-handling constructs such as 
``try``, 
``catch``, and 
``throw``. The headers do not use these constructs when 
``TBB_USE_EXCEPTIONS=0``.

For the Microsoft Windows*, Linux*, and macOS*
operating systems, the default value is 1 if exception handling constructs are
enabled in the compiler, and 0 otherwise.

.. caution::

   The runtime library may still throw an exception
   when 
   ``TBB_USE_EXCEPTIONS=0``.


C++11 Support
-------------

To enable functionality that requires C++11, you need to use a compiler that
supports C++11 mode, and compile your code with this mode set. C++11
support is off by default in the compiler. 

In some cases TBB headers cannot correctly detect availability of
necessary C++11 features in a C++ standard library. For example, when
GNU libstdc++ library is used with a compiler that does not set GCC version
macros (__GNUC__ etc.) or, like Clang, sets them to a version that does not
match the version of libstdc++.

The macro ``TBB_USE_GLIBCXX_VERSION`` can be used to specify
the proper version of GNU libstdc++ if the detection fails. Define the value 
of the macro equal to ``Major*10000 + Minor*100 + Patch``,
where Major.Minor.Patch is the actual GCC/libstdc++ version (if unknown,
it can be obtained with ``'gcc -dumpversion'`` command).
For example, if you use libstdc++ from GCC 4.9.2, define
``TBB_USE_GLIBCXX_VERSION=40902``.

See also:

* :doc:`Exceptions <../exceptions>`
