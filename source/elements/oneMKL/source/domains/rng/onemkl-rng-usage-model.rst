.. _onemkl-rng-usage-model:

oneMKL RNG Usage Model
======================


.. container::


   A typical algorithm for random number generators is as follows:


   #. Create and initialize the object for basic random number
      generator.


      -  Use the skip_ahead or leapfrog function if it is required (used
         in parallel with random number generation for Host and CPU
         devices).


   #. Create and initialize the object for distribution generator.


   #. Call the generate routine to get random numbers with appropriate
      statistical distribution.


   The following example demonstrates generation of random numbers that
   is output of basic generator (engine) PHILOX4X32X10. The seed is
   equal to 777. The generator is used to generate 10,000 normally
   distributed random numbers with parameters ``a`` = 5 and ``sigma``\ =
   2. The purpose of the example is to calculate the sample mean for
   normal distribution with the given parameters.


   .. container:: tbstyle(tblExampleStandard)


      .. rubric:: Example of RNG Usage
         :name: example-of-rng-usage
         :class: sectiontitle


      **Buffer API**


      ::


         #include <iostream>
         #include <vector>


         #include “CL/sycl.hpp”
         #include “mkl_rng_sycl.hpp”


         int main() {
             cl::sycl::queue queue;
             

             const size_t n = 10000; 
             std::vector<double> r(n);


             onemkl::rng::philox4x32x10 engine(queue, SEED); // basic random number generator object
             onemkl::rng::gaussian<double, onemkl::rng::box_muller2> distr(5.0, 2.0); //  distribution object


             {
                  //create buffer for random numbers
                  cl::sycl::buffer<double, 1> r_buf(r.data(), cl::sycl::range<1>{n}); 
                  

                  onemkl::rng::generate(distr, engine, n, r_buf); // perform generation


             }
             

             double s = 0.0;
             for(int i = 0; i < n; i++) {
                 s += r[i];
             }
             s /= n;


             std::cout << “Average = ” << s << std::endl;
             

             return 0;
         }


      **USM API**


      ::


         #include <iostream> 
         #include <vector>
         #include “CL/sycl.hpp”
         #include “mkl_rng_sycl.hpp”


         int main() {
           cl::sycl::queue queue;


           const size_t n = 10000;


           // create USM allocator
           cl::sycl::usm_allocator<double, cl::sycl::usm::alloc::shared> allocator(queue.get_context(), queue.get_device());


           // create vector woth USM allocator
           std::vector<double, cl::sycl::usm_allocator<double, cl::sycl::usm::alloc::shared>> r(n, allocator);


           onemkl::rng::philox4x32x10 engine(queue, SEED); // basic random number generator object
           onemkl::rng::gaussian<double, onemkl::rng::box_muller2> distr(5.0, 2.0); // distribution object


           auto event = onemkl::rng::generate(distr, engine, n, r.data()); // perform generation
           // cl::sycl::event object is returned by generate function for synchronisation
           event.wait(); // synchronization can be also done by queue.wait()


           double s = 0.0;
           for(int i = 0; i < n; i++) {
           s += r[i];


           std::cout << “Average = ” << s << std::endl;
             

           return 0;
         }


      You can also use USM with raw pointers by using the
      cl::sycl::malloc_shared function.


      **Parent topic:** :ref:`onemkl_rng`

