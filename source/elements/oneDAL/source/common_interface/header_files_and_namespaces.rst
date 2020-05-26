============
Header files
============

==========
Namespaces
==========

The functionality of oneDAL library is represented with a system of the C++ namespaces described below:

=======================  =======================================================================================================
namespace                oneDAL content
=======================  =======================================================================================================
``onedal``               The namespace of the library that contains externally exposable data types, processing and service functionality of oneDAL. 
``onedal::%ALGORITHM%``  The namespace of the algorithm. All classes and structures related to that algorithm shall be defined within the namespace. The string %ALGORITHM% shall be substituted to define specific algorithm, for example, ``onedal::kmeans``, ``onedal::knn``. 
``onedal::misc``         The namespace that contains miscellaneous data types and functionality intended to be used by oneDAL algorithms and applications for algorithm customization and optimization on various stages of the analytical pipeline.
``%PARENT%::detail``     The namespace that contains implementation details of the data types and functionality for parent namespace. The namespace can be on any level of namespace hierarchy. The string %PARENT% shall be substituted to define specific namespace, for example, ``onedal::detail``, ``onedal::kmeans::detail``. The application shall not use any data types nor call any functionality located in ``detail`` namespaces.
=======================  =======================================================================================================
