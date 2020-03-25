.. _mkl-rng-uniform_bits:

onemkl::rng::uniform_bits
======================


.. container::


   Generates uniformly distributed bits in 32/64-bit chunks.


   .. container:: section
      :name: GUID-C153356E-A495-466B-93DF-6104814C143E


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::uint32_t, method      Method = standard>

      .. cpp:function::  class uniform_bits {}

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  ``mkl_sycl.hpp``


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::uniform_bits class object is used to generate
      uniformly distributed bits in 32/64-bit chunks. It is designed to
      ensure each bit in the 32/64-bit chunk is uniformly distributed.
      It is not supported not for all engines. See `VS
      Notes <bibliography.html>`__
      for details.


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     T    
           -     \ ``std::uint32_t / std::uint64_t``\     
           -     Chunk size     




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::

