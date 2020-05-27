============
Header files
============

oneDAL public identifiers are represented in the following header files:

.. list-table::
   :widths:  10 50
   :header-rows: 1

   * - header file
     - description
   * - ``onedal/onedal.hpp```
     - Main header file of oneDAL library.
   * - ``onedal/algo/%ALGORITHM%/%ALGORITM%.hpp``
     - An algorithm header file for a particular algorithm.
       The string %ALGORITHM% should be substituted with the name of the algorithm, for example, ``kmeans`` or ``knn``.

   * - ``onedal/algo/misc/%FUNCTIONALITY%/%FUNCTIONALITY%.hpp``
     -  A header file for miscellaneous data types and functionality intended to be used by oneDAL algorithms and applications for algorithm customization and optimization on various stages
        of the analytical pipeline.
        The string %FUNCTIONALITY% should be substituted with the functionality name, for example, ``mt19937`` or ``cross_enthropy_loss``.

   * - ``onedal/util/%UTILITY%.hpp```
     - A header file for auxiliary functionality intended to be used for design of classes and implementation of methods such as memory allocators or type traits. 
       The string %UTILITY% should be substituted with the auxiliary functionality name, for example, ``usm_allocator`` or ``type_traits``. 



==========
Namespaces
==========

oneDAL functionality is represented with a system of C++ namespaces described below:

.. list-table::
   :widths:  10 50
   :header-rows: 1

   * - namespace
     - oneDAL content
   * - ``onedal``
     - The namespace of the library that contains externally exposable data types, processing and service functionality of oneDAL.
   * - ``onedal::%ALGORITHM%``
     - The namespace of the algorithm.
       All classes and structures related to that algorithm shall be defined within a particular namespace.

       To define a specific algorithm, the string %ALGORITHM% should be substituted with its name,
       for example, ``onedal::kmeans`` or ``onedal::knn``.

   * - ``onedal::misc``
     - The namespace that contains miscellaneous data types and functionality intended to be used by oneDAL algorithms
       and applications for algorithm customization and optimization on various stages of the analytical pipeline.
   * - ``%PARENT%::detail``
     - The namespace that contains implementation details of the data types and functionality for the parent namespace.
       The namespace can be on any level in the namespace hierarchy.

       To define a specific namespace, the string %PARENT% should be substituted with the namespace for which the details are provided,
       for example, ``onedal::detail`` or ``onedal::kmeans::detail``.

       The application shall not use any data types nor call any functionality located in the ``detail`` namespaces.
