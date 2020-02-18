================
null_mutex Class
================


Summary
-------

Class that models Mutex Concept buts does nothing.

Syntax
------

.. code:: cpp

   class null_mutex;


Header
------

.. code:: cpp

   #include "tbb/null_mutex.h"


Description
-----------

A ``null_mutex`` models the Mutex Concept syntactically, but does nothing. It is useful for instantiating a template that expects a Mutex, but no mutual exclusion is actually needed for that instance.

Members
-------

See Mutex Concept.

See also:

* :doc:`Mutex Concept <mutex_concept>`
