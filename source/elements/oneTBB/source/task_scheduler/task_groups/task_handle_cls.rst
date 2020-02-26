==========================
task_handle Template Class
==========================


Summary
-------

Template class used to wrap a function object in conjunction with class ``structured_task_group``.

Description
-----------

Class ``task_handle`` is used primarily in conjunction with class ``structured_task_group``. For sake of uniformity, class ``task_group`` also accepts ``task_handle`` arguments.

Members
-------

.. code:: cpp

   template<typename Func>
   class task_handle {
   public:
       task_handle( const Func& );
       task_handle( Func&& ); // supported since C++11
       void operator()() const;
   };


See also:

* :doc:`make_task Function Template <make_task_func>`
