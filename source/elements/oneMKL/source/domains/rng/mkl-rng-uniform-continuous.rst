.. _mkl-rng-uniform-continuous:

onemkl::rng::uniform (Continuous)
=================================


.. container::


   Generates random numbers with uniform distribution.


   .. container:: section
      :name: GUID-6D277E22-1F56-4721-838C-CDCF9F1CEBE1


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = float, method Method =      standard>
          class uniform {
          public:
            uniform(): uniform((T)0.0, (T)1.0){}
            uniform(Ta, T b)
            uniform(const uniform<T, Method>& other)
            T a() const
            T b() const
            uniform<T, Method>& operator=(const uniform<T,      Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  ``mkl_sycl.hpp``


      .. rubric:: Description
         :class: sectiontitle


      The class object is used in onemkl::rng::generate function to provide
      random numbers uniformly distributed over the interval [``a``,
      ``b``), where ``a``, ``b`` are the left and right bounds of the
      interval, respectively, and ``a``, ``b∈R`` ; ``a`` < ``b``.


      The probability density function is given by:


      | 
      | |image0|


      The cumulative distribution function is as follows:


      | 
      | |image1|


      .. rubric:: Input Parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     a    
           -     \ ``T (float, double)``\     
           -     Left bound ``a``\     
         * -     b    
           -     \ ``T (float, double)``\     
           -     Right bound ``b``\     




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-8AD223ED-624A-4390-9514-D8EF20BD04EE-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-0A8E6C61-9171-4584-927A-83AC482ADC4D-low.gif
   :class: .eq

