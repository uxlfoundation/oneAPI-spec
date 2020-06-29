The following sections address a few aspects of supporting switchable graphics and multiple monitors configurations.

Switchable Graphics
~~~~~~~~~~~~~~~~~~~

Switchable Graphics refers to the machine configuration that multiple graphic devices are available (integrated device for power saving and discrete
devices for performance.) Usually at one time or instance, one of the graphic devices drives display and becomes the active device, and others become
inactive. There are different variations of software or hardware mechanisms to switch between the graphic devices. In one of the switchable graphics
variations, it is possible to register an application in an affinity list to certain graphic device so that the launch of the application
automatically triggers a switch. The actual techniques to enable such a switch are outside the scope of this document. This document discusses the
implication of switchable graphics to the SDK and the SDK applications.

As the SDK performs hardware acceleration through Intel graphic device, it is critical that the SDK can access to the Intel graphic device in the
switchable graphics setting. If possible, it is recommended to add the application to the Intel graphic device affinity list. Otherwise,
the application must handle the following cases:

- By the SDK design, during the SDK library initialization, the function :cpp:func:`MFXInit` searches for Intel graphic devices. If a SDK
  implementation is successfully loaded, the function :cpp:func:`MFXInit` returns :cpp:enumerator:`MFX_ERR_NONE` and the :cpp:func:`MFXQueryIMPL`
  function returns the actual implementation type. If no SDK implementation is loaded, the function :cpp:func:`MFXInit` returns
  :cpp:enumerator:`MFX_ERR_UNSUPPORTED`. In the switchable graphics environment, if the application is not in the Intel graphic device affinity
  list, it is possible that the Intel graphic device is not accessible during the SDK library initialization. The fact that the :cpp:func:`MFXInit`
  function returns :cpp:enumerator:`MFX_ERR_UNSUPPORTED` does not mean that hardware acceleration is not possible permanently. The user may switch
  the graphics later and by then the Intel graphic device will become accessible. It is recommended that the application initialize the SDK library
  right before the actual decoding, video processing, and encoding operations to determine the hardware acceleration capability.
- During decoding, video processing, and encoding operations, if the application is not in the Intel graphic device affinity list, the previously
  accessible Intel graphic device may become inaccessible due to a switch event. The SDK functions will return :cpp:enumerator:`MFX_ERR_DEVICE_LOST`
  or :cpp:enumerator:`MFX_ERR_DEVICE_FAILED`, depending on when the switch occurs and what stage the SDK functions operate. The application needs to
  handle these errors and exits gracefully.

Multiple Monitors
~~~~~~~~~~~~~~~~~

Multiple monitors refer to the machine configuration that multiple graphic devices are available. Some of the graphic devices connect to a display,
they become active and accessible under the Microsoft* DirectX* infrastructure. For those graphic devices not connected to a display, they are
inactive. Specifically, under the Microsoft Direct3D9* infrastructure, those devices are not accessible.

The SDK uses the adapter number to access to a specific graphic device. Usually, the graphic device that drives the main desktop becomes the primary
adapter. Other graphic devices take subsequent adapter numbers after the primary adapter. Under the Microsoft Direct3D9 infrastructure,
only active adapters are accessible and thus have an adapter number.

The SDK extends the implementation type :cpp:type:`mfxIMPL` as follows:

====================================    ====================================================
Implementation Type                     Definition
====================================    ====================================================
:cpp:enumerator:`MFX_IMPL_HARDWARE`     The SDK should initialize on the primary adapter
:cpp:enumerator:`MFX_IMPL_HARDWARE2`    The SDK should initialize on the 2nd graphic adapter
:cpp:enumerator:`MFX_IMPL_HARDWARE3`    The SDK should initialize on the 3rd graphic adapter
:cpp:enumerator:`MFX_IMPL_HARDWARE4`    The SDK should initialize on the 4th graphic adapter
====================================    ====================================================

The application can use the above definitions to instruct the SDK library to initializes on a specific graphic device. The application can also
use the following definitions for automatic detection:

=======================================   ======================================================================================================
Implementation Type                       Definition
=======================================   ======================================================================================================
:cpp:enumerator:`MFX_IMPL_HARDWARE_ANY`   The SDK should initialize on any graphic adapter
:cpp:enumerator:`MFX_IMPL_AUTO_ANY`       The SDK should initialize on any graphic adapter. If not successful, load the software implementation.
=======================================   ======================================================================================================

If the application uses the Microsoft* DirectX* surfaces for I/O, it is critical that the application and the SDK works on the same graphic device.
It is recommended that the application use the following procedure:

- The application uses the :cpp:func:`MFXInit` function to initialize the SDK library, with option :cpp:enumerator:`MFX_IMPL_HARDWARE_ANY` or
  :cpp:enumerator:`MFX_IMPL_AUTO_ANY`. The :cpp:func:`MFXInit` function returns :cpp:enumerator:`MFX_ERR_NONE` if successful.
- The application uses the :cpp:func:`MFXQueryIMPL` function to check the actual implementation type. The implementation type
  :cpp:enumerator:`MFX_IMPL_HARDWARE` ,..., :cpp:enumerator:`MFX_IMPL_HARDWARE4` indicates the graphic adapter the SDK works on.
- The application creates the Direct3D* device on the respective graphic adapter, and passes it to the SDK through the :cpp:func:`MFXVideoCORE_SetHandle`
  function.

Finally, similar to the switchable graphics cases, it is possible that the user disconnects monitors from the graphic devices or remaps the primary
adapter thus causes interruption. If the interruption occurs during the SDK library initialization, the :cpp:func:`MFXInit` function may return
:cpp:enumerator:`MFX_ERR_UNSUPPORTED`. This means hardware acceleration is currently not available. It is recommended that the application
initialize the SDK library right before the actual decoding, video processing, and encoding operations to determine the hardware acceleration
capability.

If the interruption occurs during decoding, video processing, or encoding operations, the SDK functions will return
:cpp:enumerator:`MFX_ERR_DEVICE_LOST` or :cpp:enumerator:`MFX_ERR_DEVICE_FAILED`. The application needs to handle these errors and exit gracefully.