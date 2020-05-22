.. _mkl-rng-bits:

onemkl::rng::bits
=================


.. container::


   Generates bits of underlying engine (BRNG) integer reccurents.


   .. container:: section
      :name: GUID-C153356E-A495-466B-93DF-6104814C143E


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::

           template<typename T = std::uint32_t, method Method = standard>
             class bits {}

         .. rubric:: Include Files
            :class: sectiontitle


         -  ``mkl_sycl.hpp``


         .. rubric:: Description
            :class: sectiontitle


         The onemkl::rng::bits class object is used to generate integer
         random values. Each integer can be treated as a vector of
         several bits. In a truly random generator, these bits are
         random, while in pseudorandom generators this randomness can be
         violated. For example, a drawback of linear congruential
         generators is that lower bits are less random than higher bits
         (for example, see
         [`Knuth81 <bibliography.html>`__]).
         For this reason, exercise care when using this function.
         Typically, in a 32-bit LCG only 24 higher bits of an integer
         value can be considered random. See `VS
         Notes <bibliography.html>`__
         for details.


         .. rubric:: Input Parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     T    
              -     \ ``std::uint32_t``\     
              -     Integer type     




   .. container:: familylinks


      .. container:: parentlink


         **Parent
         topic:** `Distributions <distributions.html>`__


   
