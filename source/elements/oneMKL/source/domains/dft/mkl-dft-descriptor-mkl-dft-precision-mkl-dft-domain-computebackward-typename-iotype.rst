.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-computebackward-typename-iotype:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>::computeBackward<typename IOType>
======================================================================================================


.. container::


   Computes the backward FFT.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::ErrCode descriptor.computeBackward         (cl::sycl::buffer<IOType, 1> &inout , cl::sycl::event\* event =         nullptr) 

         .. cpp:function::  onemkl::dft::ErrCode descriptor.computeBackward         (cl::sycl::buffer<IOType, 1> &in , cl::sycl::buffer<IOType, 1>         &out , cl::sycl::event\* event = nullptr) 

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         The onemkl::dft::Descriptor<onemkl::dft::Precision,
         onemkl::dft::Domain>::computeBackward<typename IOType> function
         accepts the descriptor handle parameter and one or more data
         parameters. Given a successfully configured and committed
         descriptor, this function computes the backward FFT, that is,
         the
         `transform <https://software.intel.com/en-us/onemkl-developer-reference-c-fourier-transform-functions#FORMULA>`__
         with the minus sign in the exponent, δ = -1.


         The FFT descriptor must be properly configured prior to the
         function call.


         The number of the data parameters that the function requires
         may vary depending on the configuration of the descriptor. This
         variation is accommodated by variable parameters.


         Function calls needed to configure an FFT descriptor for a
         particular call to an FFT computation function are summarized
         in `Configuring and Computing an FFT in
         C/C++ <https://software.intel.com/en-us/onemkl-developer-reference-c-configuring-and-computing-an-fft-in-c-c>`__.


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
            * -     inout, in    
              -     cl::sycl::buffer<IOType, 1>    
              -     Sycl buffer containing an array of length no less          than specified at onemkl::dft::Descriptor<onemkl::dft::Precision,         onemkl::dft::Domain>::init call.   




         The suffix in parameter names corresponds to the value of the
         configuration parameter onemkl::dft::ConfigParam::PLACEMENT as
         follows:


         -  inout to DFTI_INPLACE


         -  in to DFTI_NOT_INPLACE


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
            * -     inout, out    
              -     cl::sycl::buffer<IOType, 1>    
              -     Sycl buffer containing an array of length no less          than specified at onemkl::dft::Descriptor<onemkl::dft::Precision,         onemkl::dft::Domain>::init call.   
            * -     Event    
              -     cl::sycl::event\*    
              -     If no event pointer is passed, then it defaults to          nullptr. If a non-nullptr value is passed, it is set to the         event associated with the enqueued computation job.   
            * -     Status    
              -     onemkl::dft::ErrCode    
              -     Function completion status.    




         The suffix in parameter names corresponds to the value of the
         configuration parameter onemkl::dft::PLACEMENT as follows:


         -  inout to DFTI_INPLACE


         -  out to DFTI_NOT_INPLACE


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
               * -  onemkl::dft::ErrCode::MEMORY_ERROR 
                 -     Internal memory allocation failed.    




   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Fourier Transform
         Functions <fourier-transform-functions.html>`__


   .. container::

