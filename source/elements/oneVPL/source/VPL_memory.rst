Memory representation and memory allocation are important parts of
VPL API. By default:

- Each workstream is responsible to allocate its output memory objects 
  and passes the memory objects to its consumer workstreams.
- For performance, memory objects are passed asynchronously to consumers
  before its producer finishes writing to the objects. Hence, a consumer
  workstream must first acquire a read access right before reading the 
  data from the memory object.   
- Each memory objects may have multiple consumer workstreams. Hence a 
  consumer workstream should avoid modifying its input memory objects.
  If a consumer workstream needs to modify an input memory object, 
  it must first acquire a write access right to avoid corrupting 
  the memory object.

VPL Memory API provides sharing of 1D buffers and 2D images across
different frameworks (e.g. SYCL, OpenCL, VAAPI, DXVA2) and different
devices (CPU, GPU).  Buffer sharing across the decode, compute and
encode pipeline is important for both performance and portability.

The buffer sharing mechanisms can be classified into 3 types:

1. *Direct* sharing when access is granted to the primary object's
   representation in physical memory, but this happens via different
   framework specific logical memory objects (like VAAPI surface or
   OpenCL memory). That's the case when handle from one framework can
   be converted to the handle of another framework. For example, via
   OpenCL VAAPI Sharing Extension.
2. *Mapping* when object is being mapped to the device memory and
   framework handle is generated. That's a typical case for CPU (HOST)
   access to the video memory. Underneath implementation might
   significantly vary and result in a kind of direct access or
   accessing a copy of the memory object with the set of associated
   copy and on-the-fly conversion operations. For example, OpenCL
   provides two sets of functions: clEnqueueReadBuffer,
   clEnqueueWriteBuffer for copying, and clEnqueueMapBuffer for direct
   mapping between CPU and OpenCL device.
3. *Coherent* sharing when memory object has unified addressing the
   physical memory and the underlying hardware and software system
   layers assures coherency between these representations as in a
   unified shared memory mode.

The Memory API aims to provide a sharing mechanism with the highest
performance. From this perspective, the library uses "direct" sharing
whenever possible. However, currently, there are a lot of various
restrictions coming from all over the software stack which makes
"direct" sharing unavailable:

1. Framework restrictions where some color formats are not supported,
   or lack of capability to import certain memory handle
2. Underlying driver implementation (or even HW) restrictions

As oneAPI software stack evolves, we intend to eliminate the *direct*
sharing restrictions in the underlying frameworks and drivers through
API extension and implementation enhancement.

The current VPL Memory Library provides the following *direct* sharing
capabilities:

* Sharing of CPU (HOST) allocated memory on Linux (via userptr):

  * With VAAPI driver
  * With OpenCL driver and SYCL
* Sharing of VAAPI allocated memory:
  
  * With OpenCL, SYCL
* Exporting dmabuf handle:
  
  * From VAAPI memory object

Recall that oneAPI platform is a host and a collection of devices; and
each device has an associated command queue.  Operations on the
devices are executed through submitting tasks to devices’ command
queues.  In the application domain of video processing pipeline, each
device may have multiple command queues corresponding to the media
driver, OpenCL and SYCL compute drivers and 3D graphics drivers.  For
Intel’s GPU on Linux, a VAAPI driver executes tasks for video
decoding, post processing and encoding, an OpenCL driver executes
tasks for compute such as DL inference, and an OpenGL driver executes
tasks for 3D rendering. Buffers and images allocated by these drivers
are initially only accessible in the context of their corresponding
command queues.  To share a buffer between a source and a sink command
queues, VPL Memory library must extract the buffer address from the
source command queue context, map the address to the sink command
queue context, such that, tasks in the sink command queue can now read
or write to the buffer.  We call this <command_queue,buffer> pair a
memory handler. Memory handlers are encapsulated in the
:cpp:class:`vplm::memory` class hierarchy.
    
To share a buffer to a device driver command queue context, just
simply constructs a new memory handler of the corresponding derived
class from the base :cpp:class:`vplm::memory` object.  For instance,
the code above converts a CPU allocated memory to a GPU VAAPI surface
for media processing.

In addition to the buffer sharing API in vplm::\*:memory
subclass constructors, VPL Memory API also provides:

* API to import memory already allocated by the application external
  to VPL Memory library
* API to allocate memory

The memory import and allocation functions are defined in
:func:`vplm::cpu::make_memory`, :func:`vplm::opencl::make_memory`,
:func:`vplm::sycl::make_memory`, and :func:`vplm::vaapi::make_memory`.

Creating memory objects
-----------------------

An application can use the VPL Memory Library to create a memory
object for one of the supported frameworks. For example, the following
code allocates memory in system memory (we count CPU (HOST) as one of
the frameworks):

.. code:: cpp

  #include <om++.h>

  vplm::cpu::memory yuv_image = vplm::cpu::make_memory(1920, 1080, VPLM_PIXEL_FORMAT_NV12);

or it can allocate memory externally and request the VPL Memory
Library to manage it as in the following example for VAAPI:

.. code:: cpp
	  
  #include <om++.h>
  #include <om_vaapi++.h>

  VADisplay dpy;
  VASurfaceID id;
  vaCreateSurfaces(dpy, VA_RT_FORMAT_RGB32, 1920, 1080, &id, 1, attribs, num_attribs);

  vplm::vaapi::memory rgb_image = vplm::vaapi::make_surface(dpy, id);

In either case, it ends up with the framework specific C++ object (in
our examples :cpp:class:`vplm::cpu::memory` or
:cpp:class:`vplm::vaapi::memory`), and hence, have access to the
framework specific API defined by VPL Memory for this object. For
example, the following code will access CPU allocated image (via
:cpp:class:`vplm::cpu_image` representation):

.. code:: cpp

  vplm::cpu_image image;
  yuv_image.map(VPLM_ACCESS_MODE_READ, image);

  // do something with the image since you have access to data pointers:
  printf("Y data pointer: %p\n", image.data(0));

  yuv_image.unmap(image);

Helper Class for Simplifying Image Data Access
----------------------------------------------

In the examples above we directly used a memory object to access its
data. While this is possible, there is a simpler way. Most frameworks
require a program to acquire and release access to data. For the CPU
access example, we saw calls to map and unmap to acquire/release
access to the data. Using the :cpp:class:`vplm::cpu_image` helper
class eliminates the need to map and unmap:

.. code:: cpp

  {
    vplm::cpu::image cpu_image(yuv_image, VPLM_ACCESS_MODE_READ);

    // do something with the image since you have access to data pointers:
    printf("Y data pointer: %p\n", image.data(0));
  }
  
This helper class issues acquire and release operations to mark
start/stop data access in constructor and destructor.  Another
"feature" of these helper classes is that they accept base
memory object (:cpp:class:`vplm::memory`) in constructors. This means that we can
use helper classes to make implicit conversion between different
framework objects. For example, with the following we will map our
VAAPI image on to CPU:

.. code:: cpp
	  
  {
    vplm::cpu::image cpu_image(rgb_image, VPLM_ACCESS_MODE_WRITE);

    // do something with the image since you have access to data pointers:
    printf("R data pointer: %p\n", image.data(0));
  }

Usage example
The following example summarize the key usage scenario:

.. code:: cpp
	  
  #include <om++.h>
  #include <om_vaapi++.h>

  VADisplay dpy = init_vaapi();
  VASurfaceID id = create_per_my_needs(); // calls vaCreateSurfaces inside

  vplm::cpu::memory yuv_image = vplm::cpu::make_memory(1920, 1080, VPLM_PIXEL_FORMAT_NV12);
  vplm::vaapi::memory rgb_image = vplm::vaapi::make_surface(dpy, id);

  {
    vplm::cpu::image cpu_image(yuv_image, VPLM_ACCESS_MODE_WRITE);

    // do something with the image since you have access to data pointers:
    printf("Y data pointer: %p\n", image.data(0));
    // for example, write data into the surface
  }

  {
    vplm::vaapi::image vaapi_cpu_image(dpy, yuv_image);
    vplm::vaapi::image vaapi_rgb_image(dpy, rgb_image); // just for consistency

    // do something with surfaces via VAAPI since we have access to them
    // for example, convert yuv which we just wrote on CPU to rgb format
    convert_yuv_to_rgb(vaapi_cpu_image.id(), vaapi_rgb_image.id())
  }

  {
    vplm::cpu::image cpu_image(rgb_image, VPLM_ACCESS_MODE_READ);

    // now we can read from the CPU data which we got in rgb image after VAAPI conversion:
    printf("R data pointer: %p\n", image.data(0));
  }

The VPL API defines 4 different helper classes, one for each supported device context: 
:cpp:class:`vplm::cpu::image`
:cpp:class:`vplm::opencl::image`,
:cpp:class:`vplm::sycl::memory` and
:cpp:class:`vplm::vaapi::image`.
