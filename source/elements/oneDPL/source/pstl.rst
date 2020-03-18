Extensions to Parallel STL
--------------------------

oneDPL extends Parallel STL with the following APIs:

DPC++ Execution Policy
++++++++++++++++++++++

.. code:: cpp

  // Defined in <dpstd/execution>

  namespace dpstd {
    namespace execution {

      template <typename BasePolicy, typename KernelName = /*unspecified*/>
      class device_policy;

      template <typename KernelName, typename Arg>
      device_policy<std::execution::parallel_unsequenced_policy, KernelName>
      make_device_policy( const Arg& );

      device_policy<parallel_unsequenced_policy, /*unspecified*/> default_policy;

    }
  }


A DPC++ execution policy specifies where and how an algorithm runs.
It inherits a standard C++ execution policy and allows specification of an optional
kernel name as a template parameter. 

An object of a :code:`device_policy` type encapsulates a SYCL queue
which runs algorithms on a DPC++ compliant device. You can create a
policy object from a SYCL queue, device, or device selector, as well
as from an existing policy object.

The :code:`make_device_policy` function simplifies :code:`device_policy` creation.

:code:`dpstd::execution::default_policy` is a predefined DPC++ execution policy
object that can run algorithms on a default SYCL device.

Examples::

  using namespace dpstd::execution;

  auto policy_a =
    device_policy<parallel_unsequenced_policy, class PolicyA>{cl::sycl::queue{}};
  std::for_each(policy_a, …);

  auto policy_b = make_device_policy<class PolicyB>(cl::sycl::queue{});
  std::for_each(policy_b, …);

  auto policy_c =
    make_device_policy<class PolicyC>(cl::sycl::device{cl::sycl::gpu_selector{}});
  std::for_each(policy_c, …);

  auto policy_d = make_device_policy<class PolicyD>(cl::sycl::default_selector{});
  std::for_each(policy_d, …);

  // use the predefined dpstd::execution::default_policy policy object
  std::for_each(default_policy, …);

.. USM pointers, and host-side iterators.

Wrappers for SYCL Buffers
++++++++++++++++++++++++++

.. code:: cpp

  // Defined in <dpstd/iterators.h>

  namespace dpstd {

    template <cl::sycl::access::mode = cl::sycl::access::mode::read_write, ... >
    /*unspecified*/ begin(cl::sycl::buffer<...>);

    template <cl::sycl::access::mode = cl::sycl::access::mode::read_write, ... >
    /*unspecified*/ end(cl::sycl::buffer<...>);

  }


:code:`dpstd::begin` and :code:`dpstd::end` are helper functions
for passing SYCL buffers to oneDPL algorithms.
These functions accept a SYCL buffer and return an object
of an unspecified type that satisfies the following requirements:

- Is :code:`CopyConstructible`, :code:`CopyAssignable`, and comparable
  with operators :code:`==` and :code:`!=`

- The following expressions are valid: :code:`a + n`, :code:`a - n`,
  :code:`a - b`, where :code:`a` and :code:`b` are objects of the type,
  and :code:`n` is an integer value

- Provides :code:`get_buffer()` method that returns the SYCL buffer
  passed to :code:`dpstd::begin` or :code:`dpstd::end` function.

Example:

.. code:: cpp

  #include <CL/sycl.hpp>
  #include <dpstd/execution>
  #include <dpstd/algorithm>
  #include <dpstd/iterators.h>

  int main(){
      cl::sycl::queue q;
      cl::sycl::buffer<int> buf { 1000 };
      auto buf_begin = dpstd::begin(buf);
      auto buf_end   = dpstd::end(buf);
      auto policy = dpstd::execution::make_device_policy<class Fill>( q );
      std::fill(policy, buf_begin, buf_end, 42);
      return 0;
  }
