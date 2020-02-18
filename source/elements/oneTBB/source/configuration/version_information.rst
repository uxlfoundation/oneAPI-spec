===================
Version Information
===================

oneAPI Threading Building Blocks has
macros, an environment variable, and a function that reveal version and
run-time information.

Version Macros
--------------

The header 
``tbb/tbb_stddef.h`` defines macros related to versioning,
as described below. You should not redefine these macros.

.. table:: Version Macros

   ==================================== =============================================
   **Macro**                            **Description of Value**
   ==================================== =============================================
   ``TBB_INTERFACE_VERSION``            Current interface version. The value is a
                                        decimal numeral of the form 
                                        ``xyyy`` where 
                                        ``x`` is the major version number and 
                                        ``y`` is the minor version number.
   ------------------------------------ ---------------------------------------------
   ``TBB_INTERFACE_VERSION_MAJOR``      ``TBB_INTERFACE_VERSION/1000;`` that is, the
                                        major version number.
   ------------------------------------ ---------------------------------------------
   ``TBB_COMPATIBLE_INTERFACE_VERSION`` Oldest major interface version still
                                        supported.
   ==================================== =============================================


TBB_VERSION Environment Variable
--------------------------------

Set the environment variable 
``TBB_VERSION`` to 
``1`` to cause the library to print information on 
``stderr``. Each line is of the form 
``“TBB: tag value”``, where 
*tag* and 
*value* are described below.

.. table:: Output from TBB_VERSION

   ===================== ==============================
   **Tag**               **Description of Value**
   ===================== ==============================
   ``VERSION``           TBB product version number.
   --------------------- ------------------------------
   ``INTERFACE_VERSION`` Value of macro 
                         ``TBB_INTERFACE_VERSION`` when library was
                         compiled.
   --------------------- ------------------------------
   ``BUILD_``...         Various information about the machine
                         configuration on which the library was built.
   --------------------- ------------------------------
   ``TBB_USE_ASSERT``    Setting of macro 
                         ``TBB_USE_ASSERT``
   --------------------- ------------------------------
   ``ALLOCATOR``         Underlying allocator for 
                         ``tbb::tbb_allocator``. It is 
                         ``scalable_malloc`` if the TBB malloc
                         library was successfully loaded; 
                         ``malloc`` otherwise.
   ===================== ==============================

.. caution::

   This output is implementation specific and may
   change at any time.

.. note::

   For Microsoft Windows Store* applications, setting TBB_VERSION variable
   to 1 will have no effect due to platform limitations.


TBB_runtime_interface_version Function
--------------------------------------

**Summary**

Function that returns the interface version of the
TBB library that was loaded at runtime.

Syntax
------


.. code:: cpp

   extern "C" int TBB_runtime_interface_version();

Header
------


.. code:: cpp

   #include "tbb/tbb_stddef.h"


Description
-----------

The value returned by 
``TBB_runtime_interface_version()`` may differ from the
value of 
``TBB_INTERFACE_VERSION`` obtained at compile time. This
can be used to identify whether an application was compiled against a
compatible version of the TBB headers.

In general, the run-time value 
``TBB_runtime_interface_version()`` must be greater than
or equal to the compile-time value of TBB_INTERFACE_VERSION. Otherwise the
application may fail to resolve all symbols at run time.
