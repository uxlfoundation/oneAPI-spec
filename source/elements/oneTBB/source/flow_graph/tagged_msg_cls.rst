=========================
tagged_msg Template Class
=========================


Summary
-------

A template class composed of a tag and a message. The message is a value that can be one of several defined types.

Syntax
------

.. code:: cpp

   template<typename TagType, typename T0, typename T1...typename TN>
    class tagged_msg;


Header
------

.. code:: cpp

    #include "tbb/flow_graph.h"


Description
-----------

The ``tagged_msg`` template class is intended 
for messages whose type is determined at run time. A message of one of the types 
``T0, T1 ...TN``  is tagged with a tag of type 
``TagType``. The tag then may serve to identify the message. 
In the flow graph ``tagged_msg`` is used as the output of 
``indexer_node``.

.. note::

   ``tagged_msg`` employs 
   tuples in its implementation so a limitation on how many types a tuple can hold, will apply to 
   ``tagged_msg`` as well.


Example
-------

.. code:: cpp

   #include<iostream>
   #include "tbb/flow_graph.h"
   
   typedef tbb::flow::tagged_msg<size_t, int, char, double> tagged_msg_type;
   
   void print_type_and_value(const tagged_msg_type &tm) {
       if (tm.tag()==1 && tm.is_a<int>()) 
           std::cout << "Type is an int, value is : " << tm.cast_to<int>() << std::endl;
       else if (tm.tag()==2 && tbb::flow::is_a<char>(tm)) 
           std::cout << "Type is a char, value is : " << tbb::flow::cast_to<char>(tm) << std::endl;
       else if (tm.tag()==3 && tm.is_a<double>()) 
           std::cout << "Type is a double, value is : " << tm.cast_to<double>() << std::endl;
       else std::cout << "Invalid tag or type" << std::endl;
   }
   
   int main() {
       print_type_and_value(tagged_msg_type(1, 8));
       print_type_and_value(tagged_msg_type(2, 'c'));
       print_type_and_value(tagged_msg_type(3, 23.78));
       print_type_and_value(tagged_msg_type(4, 12));
       
       return 0;
   }

In this example the function ``print_type_and_value`` takes a 
``tagged_msg`` with tag type 
``size_t`` capable of holding a value of either an 
``int``, 
a ``char`` or a ``double`` 
and prints the type and the value stored. ``tagged_msg`` objects with different 
tags and value types are passed to the function, where the tag is used to identify and retrieve the value.  
Retrieval of a value is done using either the template method 
``tagged_msg::cast_to`` or the ``tbb::flow::cast_to`` template function.

The following output is generated when the example is run:		

.. code:: cpp

    
   Type is an int, value is : 8
   Type is a char, value is : c
   Type is a double, value is : 23.78
   Invalid tag or type


Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
       template<typename TagType, typename T0, typename T1...typename TN>
       class tagged_msg {
       public:
           template<typename T, typename R>
           tagged_msg(T const &index, R const &val);
   
           TagType tag() const;
   
           template<typename V>
           const V& cast_to() const;
   
           template<typename V>
           bool is_a() const; 
   
       };
   
       //The following functions simplify the use of tagged_msg in template contexts
   
       template<typename V, typename T>
       const V& cast_to(T const &t);
   
       template<typename V, typename T>
       bool is_a(T const &t);
   }
   }

The following table provides additional information on the  members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template<typename T, typename R> tagged_msg(T const &index, R const &value)``
  \
  Constructs a 
  ``tagged_msg`` with tag
  ``index`` and value
  ``val``.
------------------------------------------------------------------------------------------
\ ``TagType tag() const``
  \
  Returns the current tag.
------------------------------------------------------------------------------------------
\ ``template<typename V> const V& cast_to() const``
  \
  Returns the value stored in the ``tagged_msg``. If the value is not of type   
  ``V`` an std::runtime_error exception is thrown.
------------------------------------------------------------------------------------------
\ ``template<typename V> bool is_a() const``
  \
  Returns true if  
  ``V``
  is the type of the value held by the ``tagged_msg``.
  Returns false otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================

The free-standing template functions ``cast_to`` and 
``is_a`` applied to a ``tagged_msg`` 
object are equivalent to the calls of the corresponding methods of that object.

See also:

* :doc:`indexer_node Template Class <indexer_node_cls>`
