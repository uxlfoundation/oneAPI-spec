.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-setvalue:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>::setValue
==============================================================================


.. container::


   Sets one particular configuration parameter with the specified
   configuration value.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::ErrCode descriptor.setValue         (onemkl::dft::ConfigParam param , ...) 

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         This function sets one particular configuration parameter with
         the specified configuration value. Each configuration parameter
         is a named constant, and the configuration value must have the
         corresponding type, which can be a named constant or a native
         type. For available configuration parameters and the
         corresponding configuration values, see `Config
         Params <https://software.intel.com/en-us/onemkl-developer-reference-c-dftisetvalue>`__.


         .. rubric:: Note
            :class: NoteTipHead


         An important addition to the configuration options for DPC++
         FFT interface is onemkl::dft::FWD_DISTANCE,
         onemkl::dft::BWD_DISTANCE. The FWD_DISTANCE describes the distance
         between different FFTs for the forward domain while
         BWD_DISTANCE describes the distance between different FFTs for
         the backward domain. It is required for all R2C or C2R
         transforms to use FWD_DISTANCE and BWD_DISTANCE instead of
         INPUT_STRIDE and OUTPUT_STRIDE, respectively.


         The onemkl::dft::setValue function cannot be used to change
         configuration parameters onemkl::dft::ConfigParam::FORWARD_DOMAIN,
         onemkl::dft::ConfigParam::PRECISION, DFTI_DIMENSION since these
         are a part of the template. Likewise,
         onemkl::dft::ConfigParam::LENGTHS is set with the function call
         onemkl::dft::Descriptor<onemkl::dft::Precision,
         onemkl::dft::Domain>::init.


         All calls to setValue must be done after init, and before
         commit. This is because the handle may have been moved to an
         offloaded device after commit.


         Function calls needed to configure an FFT descriptor for a
         particular call to an FFT computation function are summarized
         in
         `DftiSetValue <https://software.intel.com/en-us/onemkl-developer-reference-c-dftisetvalue#7E6778F1-D80D-4CED-82F4-90CF4600FA57>`__.


         The function returns onemkl::dft::ErrCode::NO_ERROR when it
         completes successfully. See `Status Checking
         Functions <https://software.intel.com/en-us/onemkl-developer-reference-c-status-checking-functions>`__
         for more information on the returned status.


         .. rubric:: Input Parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     param    
              -     onemkl::dft::ConfigParam    
              -     Configuration parameter.    
            * -     value    
              -     Depends on the configuration parameter    
              -     Configuration value.    




      .. container:: section
         :name: GUID-AD3394E9-6864-4509-A178-6BA8CFB88A2C


         .. rubric:: Output Parameters
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




   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Fourier Transform
         Functions <fourier-transform-functions.html>`__


   
