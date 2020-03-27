.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-commit:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>::commit
============================================================================


.. container::


   Performs all initialization for the actual FFT computation.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::ErrCode descriptor.Commit         (cl::sycl::queue &in ) 

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         This function completes initialization of a previously created
         descriptor, which is required before the descriptor can be used
         for FFT computations. The cl::sycl::queue may be associated
         with a host, CPU, or GPU device. Typically, committing the
         descriptor performs all initialization that is required for the
         actual FFT computation on the given device. The initialization
         done by the function may involve exploring different
         factorizations of the input length to find the optimal
         computation method.


         .. rubric:: Note
            :name: note
            :class: NoteTipHead


         All calls to the onemkl::dft::Descriptor<onemkl::dft::Precision,
         onemkl::dft::Domain>::setValue function to change configuration
         parameters of a descriptor need to happen after
         onemkl::dft::Descriptor<onemkl::dft::Precision,
         onemkl::dft::Domain>::init and before
         onemkl::dft::Descriptor<onemkl::dft::Precision,
         onemkl::dft::Domain>::commit. Typically, a committal function call
         is immediately followed by a computation function call (see
         `FFT Compute
         Functions <mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computeforward-typename-iotype.html>`__).


         The function returns onemkl::dft::ErrCode::NO_ERROR when it
         completes successfully. See `Status Checking
         Functions <https://software.intel.com/en-us/onemkl-developer-reference-c-status-checking-functions>`__
         for more information on the returned status.


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     deviceQueue    
              -     cl::sycl::queue    
              -     Sycl queue for a host, CPU, or GPU device.    




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
               * -  onemkl::dft::ErrCode::BAD_DESCRIPTOR 
                 -     DFTI handle provided is invalid.    
               * -                  onemkl::dft::ErrCode::INCONSISTENT_CONFIGURATION/                  onemkl::dft::ErrCode::INVALID_CONFIGURATION   
                 -     An input value provided is invalid.    
               * -  onemkl::dft::ErrCode::UNIMPLEMENTED 
                 -     Functionality requested is not             implemented.   
               * -  onemkl::dft::ErrCode::MKL_INTERNAL_ERROR 
                 -     Internal MKL error.    




   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Fourier Transform
         Functions <fourier-transform-functions.html>`__


   .. container::

