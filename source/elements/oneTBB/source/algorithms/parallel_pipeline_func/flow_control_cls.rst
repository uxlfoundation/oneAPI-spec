==================
flow_control Class
==================


Summary
-------
Enables the first filter in a composite filter to indicate when the
end of input has been reached.

Header
------

.. code:: cpp

   #include "tbb/pipeline.h" 


Syntax
------

.. code:: cpp

   class flow_control;


Description
-----------

Template function ``parallel_pipeline`` passes a ``flow_control`` object``fc`` to the input functor of a ``filter_t``. When the input functor
reaches the end of its input, it should invoke ``fc.stop()`` and return a
dummy value.

Members
-------

.. code:: cpp

   namespace tbb {
       class flow_control {
       public:
           void stop();
       };
   }
