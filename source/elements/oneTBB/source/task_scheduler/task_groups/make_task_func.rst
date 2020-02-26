===========================
make_task Template Function
===========================


Summary
-------

Template function for creating a ``task_handle``
from a function or functor.

Syntax
------

.. code:: cpp

   // Supported until C++11
   template<typename Func> 
   task_handle<Func> make_task( const Func& f );
   
   // Supported since C++11
   template<typename TFunc> 
   task_handle<Func> make_task( TFunc&& f );

**Returns:** ``task_handle<Func>(f)``

Since C++11, the type *Func* is obtained by removing
reference and const/volatile qualifiers remained after deduction of type *TFunc*.

See also:

* :doc:`task_handle Template Class <task_handle_cls>`
