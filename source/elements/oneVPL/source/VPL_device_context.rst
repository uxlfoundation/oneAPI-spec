:class:`vpl::DeviceContext` represents device's driver context and 
command queue for VPL operations. Depending on the operating systems and workloads, the low level
device contexts can be VAAPI, DX, OCL, GL for media, compute and rendering operations.
This class hides the low level contexts, while exposing 
sufficient information to enable context sharing for different :class:`vpl::Workstream`
operations.

This class provides the following functions:

1. :func:`vpl::DeviceContext::DeviceContext`: create a new device context on a device
2. :func:`vpl::DeviceContext::AddWorkstream`: add a workstream sharing the device context
3. :func:`vpl::DeviceContext::RemoveWorkstream`: remove a workstream for the device context

The device context is usually created implicitly inside the :class:`vpl::Workstream` constructor.
Application programmers can also create it explicitly and pass the context to multiple workstreams.