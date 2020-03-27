.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>
====================================================================


.. container::


   Creates an empty descriptor for the templated precision and forward
   domain.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::Descriptor<PRECISION , DOMAIN>         descriptor

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         This constructor initializes members to default values and does
         not throw exceptions. Note that the precision and domain are
         determined via templating.


         .. rubric:: Template Parameters
            :name: template-parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     PRECISION     
              -      onemkl::dft::Precision    
              -      onemkl::dft::Precision::SINGLE or          onemkl::dft::Precision::DOUBLE are supported precisions. Double         precision has limited GPU support and full CPU and Host         support.   
            * -     DOMAIN     
              -      onemkl::dft::Domain    
              -     onemkl::dft::Domain::REAL or onemkl::dft::Domain::COMPLEX          are supported forward domains.   




   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Fourier Transform
         Functions <fourier-transform-functions.html>`__


   .. container::

