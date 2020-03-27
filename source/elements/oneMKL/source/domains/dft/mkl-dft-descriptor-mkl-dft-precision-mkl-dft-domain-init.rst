.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-init:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>::Init
==========================================================================


.. container::


   Allocates the descriptor data structure and initializes it with
   default configuration values.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::ErrCode descriptor.init (dimension )         

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         This function allocates memory for the descriptor data
         structure and instantiates it with all the default
         configuration settings for the precision, forward domain, and
         dimensions of the transform. This function does not perform any
         significant computational work, such as computation of twiddle
         factors. The function
         `onemkl::dft::Descriptor::commit <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-commit.html>`__
         does this work after the function
         `onemkl::dft::Descriptor::setValue <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-setvalue.html>`__
         has set values of all necessary parameters.


         The interface supports a single std::int64_t input for 1-D
         transforms, and an ``std::vector`` for N-D transforms.


         The function returns onemkl::dft::ErrCode::NO_ERROR when it
         completes successfully.


         .. rubric:: Input Parameters: 1-Dimensional
            :name: input-parameters-1-dimensional
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     dimension    
              -     std::int64_t    
              -     Dimension of the transform 1-D transform.    




      .. container:: section
         :name: GUID-E04D8261-79E2-4282-A499-CC437D91378F


         .. rubric:: Input Parameters: N-Dimensional
            :name: input-parameters-n-dimensional
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     dimensions    
              -     std::vector<std::int64_t>    
              -     Dimensions of the transform.    




      .. container:: section
         :name: GUID-AD3394E9-6864-4509-A178-6BA8CFB88A2C


         .. rubric:: Output Parameters
            :name: output-parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     status    
              -     onemkl::dft::ErrCode    
              -     Function completion status.    




      .. container:: section
         :name: GUID-3D8228F8-5900-441B-AE87-B63DDB82E9BA


         .. rubric:: Return Values
            :name: return-values
            :class: sectiontitle


         The function returns a value indicating whether the operation
         was successful or not, and why.


         .. container:: tablenoborder


            .. list-table:: 
               :header-rows: 1

               * -  Return Value 
                 -  Description 
               * -  onemkl::dft::ErrCode::NO_ERROR 
                 -     The operation was successful.    
               * -                  onemkl::dft::ErrCode::INCONSISTENT_CONFIGURATION/                  onemkl::dft::ErrCode::INVALID_CONFIGURATION   
                 -     An input value provided is invalid.    
               * -  onemkl::dft::ErrCode::UNIMPLEMENTED 
                 -     Functionality requested is not             implemented.   
               * -  onemkl::dft::ErrCode::MEMORY_ERROR 
                 -     Internal memory allocation failed.    




   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Fourier Transform
         Functions <fourier-transform-functions.html>`__


   .. container::

