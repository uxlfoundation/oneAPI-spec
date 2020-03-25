.. _mkl-dft-descriptor-mkl-dft-precision-mkl-dft-domain-getvalue:

onemkl::dft::Descriptor<onemkl::dft::Precision, onemkl::dft::Domain>::getValue
=====================================================================


.. container::


   Gets the configuration value of one particular configuration
   parameter.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  onemkl::dft::ErrCode descriptor.getValue         (onemkl::dft::ConfigParam param , ...) 

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_dfti_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         This function gets the configuration value of one particular
         parameter. Each configuration parameter is a named constant,
         and the configuration value must have the corresponding type,
         which can be a named constant or a native type. For available
         configuration parameters and the corresponding configuration
         values, see
         `DftiGetValue <https://software.intel.com/en-us/onemkl-developer-reference-c-dftigetvalue#BC7944B8-F01C-40C4-8EAA-6C3422C9C838>`__


         .. rubric:: Note
            :name: note
            :class: NoteTipHead


         All calls to getValue must be done after init, and before
         commit. This is because the handle may have been moved to an
         offloaded device after commit.


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
            * -     param    
              -     enum DFTI_CONFIG_PARAM    
              -     Configuration parameter.    
            * -     value_ptr    
              -     Depends on the configuration parameter    
              -     Pointer to configuration value.    




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
            * -     value    
              -     Depends on the configuration parameter    
              -     Configuration value.    
            * -     status    
              -     std::int64_t    
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


   .. container::

