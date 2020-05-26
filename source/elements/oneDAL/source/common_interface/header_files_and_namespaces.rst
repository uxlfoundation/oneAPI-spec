============
Header files
============

==========
Namespaces
==========

oneDAL functionality is represented with a system of C++ namespaces described below:

=======================  =======================================================================================================
namespace                oneDAL content
=======================  =======================================================================================================
``onedal``               The namespace of the library that contains externally exposable data types, processing and service functionality of oneDAL. 
``onedal::%ALGORITHM%``  The namespace of the algorithm. All classes and structures related to that algorithm shall be defined within a particular namespace. To define a specific algorithm, the string %ALGORITHM% should be substituted with its name, for example, ``onedal::kmeans`` or ``onedal::knn``.
``onedal::misc``         The namespace that contains miscellaneous data types and functionality intended to be used by oneDAL algorithms and applications for algorithm customization and optimization on various stages of the analytical pipeline.
``%PARENT%::detail``     The namespace that contains implementation details of the data types and functionality for the parent namespace. The namespace can be on any level in the namespace hierarchy. To define a specific namespace, the string %PARENT% should be substituted with the namespace for which the details are provided, for example, ``onedal::detail`` or ``onedal::kmeans::detail``. The application shall not use any data types nor call any functionality located in the ``detail`` namespaces.
=======================  =======================================================================================================
