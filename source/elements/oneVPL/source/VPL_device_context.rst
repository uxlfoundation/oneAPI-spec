:class:`vpl::DeviceContext` defines a device's driver context and 
command queue for VPL operations. Depending on the underlying operating systems and workstream operations, 
the low level device contexts can be VAAPI, DX, OCL, GL for media, compute and rendering operations.
This class hides the details of the low level contexts, while enabling context sharing among several workstreams.

This class provides the following functions:

1. :func:`vpl::DeviceContext::DeviceContext`: create a new device context on a device
2. :func:`vpl::DeviceContext::AddWorkstream`: add a workstream sharing the device context
3. :func:`vpl::DeviceContext::RemoveWorkstream`: remove a workstream for the device context

The device context is usually created implicitly inside the :class:`vpl::Workstream` constructor.
Application programmers can also create it explicitly to share the context with multiple workstreams.