.. _hw-acceleration:

==================================
Working with Hardware Acceleration
==================================

-----------------------------------
Working with Multiple Media Devices
-----------------------------------

If your system has multiple graphics adapters you may need hints on which
adapter is better suited to process a particular workload. The SDK provides
the helper API to select the most suitable adapter for your workload based on
the provide workload description. The following example shows workload
initialization on a discrete adapter:

.. literalinclude:: snippets/prg_hw.cpp
   :language: c++
   :start-after: /*beg1*/
   :end-before: /*end1*/
   :lineno-start: 1

The example shows that after obtaining the adapter list with
:cpp:func:`MFXQueryAdapters`, further initialization of :cpp:type:`mfxSession`
is performed in the regular way. The specific adapter selected using
the :cpp:enumerator:`MFX_IMPL_HARDWARE`, :cpp:enumerator:`MFX_IMPL_HARDWARE2`,
:cpp:enumerator:`MFX_IMPL_HARDWARE3`, or :cpp:enumerator:`MFX_IMPL_HARDWARE4`
values of :cpp:type:`mfxIMPL`.

The following example shows the use of :cpp:func:`MFXQueryAdapters` for querying
the most suitable adapter for a particular encode workload:

.. literalinclude:: snippets/prg_hw.cpp
   :language: c++
   :start-after: /*beg2*/
   :end-before: /*end2*/
   :lineno-start: 1

See the :cpp:func:`MFXQueryAdapters` description for adapter priority rules.

-------------------------
Working with Video Memory
-------------------------

To fully utilize the SDK acceleration capability, the application should support
OS specific infrastructures. If using Microsoft\* Windows\*, the application
should support Microsoft DirectX\*. If using Linux\*, the application should
support the VA API for Linux.

The hardware acceleration support in an application consists of video memory
support and acceleration device support.

Depending on the usage model, the application can use video memory at different
stages in the pipeline. Three major scenarios are shown in the following
illustration:

.. graphviz::

  digraph {
    rankdir=LR;
    labelloc="t";
    label="SDK Functions interconnection";
    F1 [shape=octagon label="SDK Function"];
    F2 [shape=octagon label="SDK Function"];
    F1->F2 [ label="Video Memory" ];
  }

.. graphviz::

  digraph {
    rankdir=LR;
    labelloc="t";
    label="Video memory as output";
    F3 [shape=octagon label="SDK Function"];
    F4 [shape=octagon label="Application" fillcolor=lightgrey];
    F3->F4 [ label="Video Memory" ];
  }

.. graphviz::

  digraph {
    rankdir=LR;
    labelloc="t";
    label="Video memory as input";
    F5 [shape=octagon label="Application"];
    F6 [shape=octagon label="SDK Function"];
    F5->F6 [ label="Video Memory" ];
  }

The application must use the ``IOPattern`` field of the :cpp:struct:`mfxVideoParam`
structure to indicate the I/O access pattern during initialization. Subsequent
SDK function calls must follow this access pattern. For example, if an SDK
function operates on video memory surfaces at both input and output, the
application must specify the access pattern `IOPattern` at initialization in
:cpp:enumerator:`MFX_IOPATTERN_IN_VIDEO_MEMORY` for input and
:cpp:enumerator:`MFX_IOPATTERN_OUT_VIDEO_MEMORY` for output. This particular I/O
access pattern must not change inside the **Init** **-** **Close** sequence.

Initialization of any hardware accelerated SDK component requires the
acceleration device handle. This handle is also used by the SDK component to
query hardware capabilities. The application can share its device with the SDK
by passing the device handle through the :cpp:func:`MFXVideoCORE_SetHandle`
function. It is recommended to share the handle before any actual usage of the SDK.

---------------------------------------------
Working with Microsoft DirectX\* Applications
---------------------------------------------

The SDK supports two different infrastructures for hardware acceleration on the
Microsoft Windows OS: Direct3D\* 9 DXVA2 and Direct3D 11 Video API. If Direct3D 9
DXVA2 is used for hardware acceleration, the application should use the
IDirect3DDeviceManager9 interface as the acceleration device handle. If the
Direct3D 11 Video API is used for hardware acceleration, the application should
use the ID3D11Device interface as the acceleration device handle.

The application should share one of these interfaces with the SDK through the
:cpp:func:`MFXVideoCORE_SetHandle` function. If the application does not provide the
interface, then the SDK creates its own internal acceleration device. This
internal device is not accessible by the application and as a result, the SDK
input and output will be limited to system memory only. This will reduce SDK
performance. If the SDK fails to create a valid acceleration device, then the
SDK cannot proceed with hardware acceleration and returns an error status to the
application.

The application must create the Direct3D 9 device with the flag
``D3DCREATE_MULTITHREADED``. The flag ``D3DCREATE_FPU_PRESERVE`` is also
recommended. This influences floating-point calculations, including PTS values.

The application must also set multi-threading mode for the Direct3D 11 device.
The following example shows how to set multi-threading mode for a Direct3D 11
device:

.. code-block:: c++
   :lineno-start: 1

   ID3D11Device            *pD11Device;
   ID3D11DeviceContext     *pD11Context;
   ID3D10Multithread       *pD10Multithread;

   pD11Device->GetImmediateContext(&pD11Context);
   pD11Context->QueryInterface(IID_ID3D10Multithread, &pD10Multithread);
   pD10Multithread->SetMultithreadProtected(true);

During hardware acceleration, if a Direct3D “device lost” event occurs, the SDK
operation terminates with the :cpp:enumerator:`mfxStatus::MFX_ERR_DEVICE_LOST`
return status. If the application provided the Direct3D device handle, the
application must reset the Direct3D device.

When the SDK decoder creates auxiliary devices for hardware acceleration, it
must allocate the list of Direct3D surfaces for I/O access, also known as the
surface chain, and pass the surface chain as part of the device creation command.
In most cases, the surface chain is the frame surface pool mentioned in the
:ref:`Frame Surface Locking <frame-surface-lock>` section.

The application passes the surface chain to the SDK component Init function
through an SDK external allocator callback. See the
:ref:`Memory Allocation and External Allocators <mem-alloc-ext-alloc>` section
for details.

Only the decoder Init function requests the external surface chain from the
application and uses it for auxiliary device creation. Encoder and VPP Init
functions may only request internal surfaces. See the
:ref:`ExtMemFrameType enumerator <extmemframetype>` for more details about
different memory types.

Depending on configuration parameters, the SDK requires different surface types.
It is strongly recommended to call the :cpp:func:`MFXVideoENCODE_QueryIOSurf` function,
:cpp:func:`MFXVideoDECODE_QueryIOSurf` function, or :cpp:func:`MFXVideoVPP_QueryIOSurf`
function to determine the appropriate type.

See the
:ref:`SDK Support for Direct3D 9 Surface Types and Color Formats table <direct3d9-support-table>`
for detailed information about Direct3D 9 support.

.. _direct3d9-support-table:

.. table:: SDK Support for Direct3D 9 Surface Types and Color Formats

   ============= =============================== ===================== ======================= ===================
   Class         Input Surface Type              Input Color Format    Output Surface Type     Output Color Format
   ============= =============================== ===================== ======================= ===================
   DECODE        Not Applicable                  Not Applicable        Decoder Render Target   NV12
   DECODE (JPEG)                                                       Decoder Render Target   RGB32, YUY2
   VPP           Decoder/Processor Render Target Listed in ColorFourCC Decoder Render Target   NV12
   VPP                                                                 Processor Render Target RGB32
   ENCODE        Decoder Render Target           NV12                  Not Applicable          Not Applicable
   ENCODE (JPEG) Decoder Render Target           RGB32, YUY2, YV12
   ============= =============================== ===================== ======================= ===================

.. note:: In table SDK Support for Direct3D 9 Surface Types and Color Formats,
          “Decoder Render Target” corresponds to the ``DXVA2_VideoDecoderRenderTarget``
          type and “Processor Render Target” corresponds to
          ``DXVA2_VideoProcessorRenderTarget``.

See the
:ref:`SDK Support for Direct3D 11 Surface Types and Color Formats table <direct3d11-support-table>`
for detailed information about Direct3D 11 support.

.. _direct3d11-support-table:

.. table:: SDK Support for Direct3D 11 Surface Types and Color Formats

   ============= =============================== ===================== ================================ ===================
   Class         Input Surface Type              Input Color Format    Output Surface Type              Output Color Format
   ============= =============================== ===================== ================================ ===================
   DECODE        Not Applicable                  Not Applicable        Decoder Render Target            NV12
   DECODE (JPEG)                                                       Decoder/Processor Render Target  RGB32, YUY2
   VPP           Decoder/Processor Render Target Listed in ColorFourCC Processor Render Target          NV12
   VPP                                                                 Processor Render Target          RGB32
   ENCODE        Decoder/Processor Render Target NV12                  Not Applicable                   Not Applicable
   ENCODE (JPEG) Decoder/Processor Render Target RGB32, YUY2
   ============= =============================== ===================== ================================ ===================

.. note:: In table SDK Support for Direct3D 11 Surface Types and Color Formats,
          “Decoder Render Target” corresponds to the ``D3D11_BIND_DECODER`` flag
          and “Processor Render Target” corresponds to ``D3D11_BIND_RENDER_TARGET``.

.. note:: Note the following encoding and decoding color format support:

          * NV12 is the major encoding and decoding color format.
          * The JPEG/MJPEG decoder supports RGB32 and YUY2 output.
          * The JPEG/MJPEG encoder supports RGB32 and YUY2 input for Direct3D 9
            and Direct3D 11 and YV12 input for Direct3D 9 only.
          * VPP supports RGB32 output.


--------------------------------
Working with VA API Applications
--------------------------------

The SDK supports the VA API infrastructure for hardware acceleration on Linux.
The application should use the VADisplay interface as the acceleration device
handle for this infrastructure and share it with the SDK through the
:cpp:func:`MFXVideoCORE_SetHandle` function. Because the SDK does not create an internal
acceleration device on Linux, the application must always share it with the SDK.
This sharing should be done before any actual usage of the SDK, including
capability query and component initialization. If the application fails to share
the device, the SDK operation will fail.

The following example shows how to obtain the VA display from X Window System:

.. code-block::
   :lineno-start: 1

   Display   *x11_display;
   VADisplay va_display;

   x11_display = XOpenDisplay(current_display);
   va_display  = vaGetDisplay(x11_display);

   MFXVideoCORE_SetHandle(session, MFX_HANDLE_VA_DISPLAY, (mfxHDL) va_display);

The following example shows how to obtain the VA display from the Direct
Rendering Manager:

.. code-block::
   :lineno-start: 1

   int card;
   VADisplay va_display;

   card = open("/dev/dri/card0", O_RDWR); /* primary card */
   va_display = vaGetDisplayDRM(card);
   vaInitialize(va_display, &major_version, &minor_version);

   MFXVideoCORE_SetHandle(session, MFX_HANDLE_VA_DISPLAY, (mfxHDL) va_display);

When the SDK decoder creates a hardware acceleration device, it must allocate
the list of video memory surfaces for I/O access, also known as the surface chain,
and pass the surface chain as part of the device creation command. The
application passes the surface chain to the SDK component Init function through
an SDK external allocator callback. See the
:ref:`Memory Allocation and External Allocators <mem-alloc-ext-alloc>` section
for details.

Only the decoder Init function requests external surface chain from the
application and uses it for device creation. Encoder and VPP Init functions may
only request internal surfaces. See the
:ref:`ExtMemFrameType enumerator <extmemframetype>` for more details about
different memory types.

.. note:: The VA API does not define any surface types and the application can
          use either MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET
          or MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET to indicate data in video
          memory.


See the :ref:`SDK Support for VA API Surface Types and Color Formats table <va-api-support-table>`
for detailed information about VA API support.

.. _va-api-support-table:

.. table:: SDK Support for VA API Surface Types and Color Formats

   ============= =====================    ===================
   SDK Class     SDK Function Input       SDK Function Output
   ============= =====================    ===================
   DECODE        Not Applicable           NV12
   DECODE (JPEG)                          RGB32, YUY2
   VPP           Listed in ColorFourCC    NV12, RGB32
   ENCODE        NV12                     Not Applicable
   ENCODE (JPEG) RGB32, YUY2, YV12
   ============= =====================    ===================
