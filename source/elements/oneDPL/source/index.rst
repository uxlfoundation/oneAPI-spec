..
  Copyright 2020 Intel Corporation

.. _oneDPL-section:

====================
oneDPL |dpl_version|
====================

The |dpl_full_name| (oneDPL) provides the functionality
specified in the C++ standard, with extensions to support data parallelism
and offloading to devices, and with extensions to simplify its usage for 
implementing data parallel algorithms.

The library is comprised of the following components:

- The C++ standard library.  (See `C++ Standard`_.)  oneDPL
  defines a subset of the C++ standard library which you can use with
  buffers and data parallel kernels.  (See `Supported C++
  Standard Library APIs and Algorithms`_.)

- Parallel STL. (See `Supported C++ Standard Library APIs and
  Algorithms`_.)  oneDPL extends Parallel STL with execution
  policies and companion APIs for running algorithms on oneAPI
  devices.  (See `Extensions to Parallel STL`_.)

- Extensions. An additional set of library classes and functions that
  are known to be useful in practice but are not (yet) included into
  C++ or SYCL specifications. (See `Specific API of oneDPL`_.)

Namespaces
----------

oneDPL uses :code:`namespace std` for the `Supported C++ Standard
Library APIs and Algorithms`_ including Parallel STL algorithms
and the subset of the standard C++ library for kernels,
and uses :code:`namespace dpstd` for its extended functionality.

Supported C++ Standard Library APIs and Algorithms
---------------------------------------------------

For all C++ algorithms accepting execution policies (as defined by C++17),
oneDPL provides an implementation supporting
:code:`dpstd::execution::device_policy` and SYCL buffers (via :code:`dpstd::begin/end`).
(See `Extensions to Parallel STL`_.)

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


Specific API of oneDPL
----------------------

.. code:: cpp

  namespace dpstd {

  // Declared in <dpstd/iterators.h>

    template <typename Integral>
    class counting_iterator;

    template <typename... Iterators>
    class zip_iterator;
    template <typename... Iterators>
    zip_iterator<Iterators...> make_zip_iterator(Iterators...);

    template <typename UnaryFunc, typename Iterator>
    class transform_iterator;
    template <typename UnaryFunc, typename Iterator>
    transform_iterator<UnaryFunc, Iterator> make_transform_iterator(Iterator, UnaryFunc);


  // Declared in <dpstd/functional>

    struct identity;

  // Defined in <dpstd/algorithm>

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T, typename BinaryPredicate>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init, BinaryPredicate binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename T, typename BinaryPredicate, typename BinaryOp>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              T init, BinaryPredicate binary_pred, BinaryOp binary_op);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename BinaryPred>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              BinaryPred binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputValueIt,
             typename BinaryPred, typename BinaryOp>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                              InputValueIt values_first, OutputValueIt values_result,
                              BinaryPred binary_pred, BinaryOp binary_op);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt, typename BinaryPred>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result,
                      BinaryPred binary_pred);

    template<typename Policy, typename InputKeyIt, typename InputValueIt, typename OutputKeyIt,
             typename OutputValueIt, typename BinaryPred, typename BinaryOp>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
                      InputValueIt values_first, OutputKeyIt keys_result, OutputValueIt values_result,
                      BinaryPred binary_pred, BinaryOp binary_op);

  }

.. _`C++ Standard`: https://isocpp.org/std/the-standard
