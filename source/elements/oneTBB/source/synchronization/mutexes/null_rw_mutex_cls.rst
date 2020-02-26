===================
null_rw_mutex Class
===================


Summary
-------

Class that models ``ReaderWriterMutex`` Concept but
does nothing.

Syntax
------

.. code:: cpp

   class null_rw_mutex;


Header
------

.. code:: cpp

   #include "tbb/null_rw_mutex.h"


Description
-----------

A ``null_rw_mutex`` models the ReaderWriterMutex Concept syntactically, but does nothing. It is useful for instantiating a template that expects a ReaderWriterMutex, but no mutual exclusion is actually needed for that instance.

Members
-------

See ReaderWriterMutex concept.

See also:

* :doc:`ReaderWriterMutex Concept <readerwritermutex_concept>`
