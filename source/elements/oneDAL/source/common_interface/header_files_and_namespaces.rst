===========================
Header files and namespaces
===========================

onedal Namespace
-------------

Namespace
``onedal`` contains public service funcitons and classes 
similar to shared pointers and malloc/free functions.

Algorithm Namespaces
--------------------

Every algorithm owns a separate namespacec inside
``onedal`` namespace. Examples are ``onedal::kmeans`` 
and ``onedal::knn``.
All applications of the algorithm to particular problem types 
are inside the algorithm namespace.

onedal::misc Namespace
----------------------

``onedal::misc`` namespace contains auxiliary algorithms and auxiliary functionality
which are used in other algorithms or expected to be used
by a user for customization of algorithms. All compatibility garantees are 
provided for ``onedal::misc`` namespace.

onedal::vx Namespace
----------------------

Namespaces of the form
``onedal::vx`` define public identifiers that
the library injects into namespace
``onedal`` or nested namespaces. The numeral
``x`` corresponds to an internal version number
that serves to prevent accidental linkage of incompatible definitions. User
code should never directly reference namespaces prefixed with
``onedal::kmeans::vx``, for example. Instead, reference names via
parent namespace which is ``onedal::kmeans`` in the example.

detail Namespaces
-----------------------

Namespace ``detail`` can appear on every level. 
``onedal::detail`` and ``onedal::kmeans::detail`` are the examples.
Such namespaces include source code to be used internally in oneDAL and be shipped as is
without any compatibility guarantee.
Your code should never directly reference any ``detail`` namespace.
Indirect reference via a public 
``typedef`` provided by the header files is permitted.
