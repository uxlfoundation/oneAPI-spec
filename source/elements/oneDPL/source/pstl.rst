Extensions to Parallel STL
--------------------------

oneDPL extends Parallel STL with the following APIs.

DPC++ Execution Policy
++++++++++++++++++++++

A DPC++ execution policy specifies where and how an algorithm runs.

.. code:: cpp

  // Defined in <dpstd/execution>

  namespace dpstd {
    namespace execution {

      template <typename KernelName = /*unspecified*/>
      class device_policy;

      device_policy<> dpcpp_default;

      template <typename KernelName = /*unspecified*/>
      device_policy<KernelName>
      make_device_policy( sycl::queue );

      template <typename KernelName = /*unspecified*/>
      device_policy<KernelName>
      make_device_policy( sycl::device );

      template <typename NewKernelName, typename OldKernelName>
      device_policy<NewKernelName>
      make_device_policy( const device_policy<OldKernelName>& = dpcpp_default );
    }
  }

``dpcpp_default`` is a predefined execution policy object to run algorithms on the default DPC++ device.

device_policy class
^^^^^^^^^^^^^^^^^^^

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  class device_policy
  {
  public:
      using kernel_name = KernelName;

      device_policy();
      template <typename OtherName>
      device_policy( const device_policy<OtherName>& );
      explicit device_policy( sycl::queue );
      explicit device_policy( sycl::device );

      sycl::queue queue() const;
      operator sycl::queue() const;
  };

An object of the ``device_policy`` type is associated with a ``sycl::queue`` that is used
to run algorithms on a DPC++ compliant device.

The ``KernelName`` template parameter, also aliased as ``kernel_name`` within the class template,
is to explicitly provide a name for DPC++ kernels executed by an algorithm the policy is passed to. 

.. code:: cpp

  device_policy()

Construct a policy object associated with a queue created with the default device selector.
  
.. code:: cpp

  template <typename OtherName>
  device_policy( const device_policy<OtherName>& policy )

Construct a policy object associated with the same queue as ``policy``, by changing
the kernel name of the given policy to ``kernel_name`` defined for the new policy.

.. code:: cpp

  explicit device_policy( sycl::queue queue )

Construct a policy object associated with the given queue.

.. code:: cpp

  explicit device_policy( sycl::device device )

Construct a policy object associated with a queue created for the given device.

.. code:: cpp

  sycl::queue queue() const

Return the queue the policy is associated with.

.. code:: cpp

  operator sycl::queue() const

Allow implicit conversion of the policy to a ``sycl::queue`` object.

make_device_policy function
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``make_device_policy`` function templates simplify ``device_policy`` creation.

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  device_policy<KernelName>
  make_device_policy( sycl::queue queue )

Return a policy object associated with ``queue``, with a kernel name possibly provided
as the template argument, otherwise unspecified.

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  device_policy<KernelName>
  make_device_policy( sycl::device device )

Return a policy object to run algorithms on ``device``, with a kernel name possibly provided
as the template argument, otherwise unspecified.
  
.. code:: cpp

  template <typename NewKernelName, typename OldKernelName>
  device_policy<NewKernelName>
  make_device_policy( const device_policy<OldKernelName>& policy = dpcpp_default )

Return a policy object constructed from ``policy``, with a new kernel name provided as the template
argument. If no policy object is provided, the new policy is constructed from ``dpcpp_default``.

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
      cl::sycl::buffer<int> buf { 1000 };
      auto buf_begin = dpstd::begin(buf);
      auto buf_end   = dpstd::end(buf);
      auto policy = dpstd::execution::make_device_policy<class Fill>( );
      std::fill(policy, buf_begin, buf_end, 42);
      return 0;
  }
