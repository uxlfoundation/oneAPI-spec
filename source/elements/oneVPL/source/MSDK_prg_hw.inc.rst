Working with multiple Intel media devices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If your system has multiple Intel Gen Graphics adapters you may need hints on which adapter suits better
to process some particular workload. The SDK provides helper API to select best suitable adapter for your workload
based on passed workload description. Example below showcases workload initialization on discrete adapter:

.. code-block:: c++

   mfxU32 num_adapters_available;

   // Query number of Intel Gen Graphics adapters available on system
   mfxStatus sts = MFXQueryAdaptersNumber(&num_adapters_available);
   MSDK_CHECK_STATUS(sts, "MFXQueryAdaptersNumber failed");

   // Allocate memory for response
   std::vector<mfxAdapterInfo> displays_data(num_adapters_available);
   mfxAdaptersInfo adapters = { displays_data.data(), mfxU32(displays_data.size()), 0u };

   // Query information about all adapters (mind that first parameter is NULL)
   sts = MFXQueryAdapters(nullptr, &adapters);
   MSDK_CHECK_STATUS(sts, "MFXQueryAdapters failed");

   // Find dGfx adapter in list of adapters
   auto idx_d = std::find_if(adapters.Adapters, adapters.Adapters + adapters.NumActual,
       [](const mfxAdapterInfo info)
   {
      return info.Platform.MediaAdapterType == mfxMediaAdapterType::MFX_MEDIA_DISCRETE;
   });

   // No dGfx in list
   if (idx_d == adapters.Adapters + adapters.NumActual)
   {
      printf("Warning: No dGfx detected on machine\n");
      return -1;
   }

   mfxU32 idx = static_cast<mfxU32>(std::distance(adapters.Adapters, idx));

   // Choose correct implementation for discrete adapter
   switch (adapters.Adapters[idx].Number)
   {
   case 0:
      impl = MFX_IMPL_HARDWARE;
      break;
   case 1:
      impl = MFX_IMPL_HARDWARE2;
      break;
   case 2:
      impl = MFX_IMPL_HARDWARE3;
      break;
   case 3:
      impl = MFX_IMPL_HARDWARE4;
      break;

   default:
      // Try searching on all display adapters
      impl = MFX_IMPL_HARDWARE_ANY;
      break;
   }

   // Initialize mfxSession in regular way with obtained implementation

As you see in this example, after obtaining adapter list with MFXQueryAdapters further initialization of mfxSession
is performed in regular way. Particular adapter choice is performed with :cpp:enumerator:`MFX_IMPL_HARDWARE`,..., :cpp:enumerator:`MFX_IMPL_HARDWARE4` values
of :cpp:type:`mfxIMPL`.

Example below showcases usage of MFXQueryAdapters for querying best suitable adapter for particular encode
workload (see MFXQueryAdapters description for adapter priority rules):

.. code-block:: c++

   mfxU32 num_adapters_available;

   // Query number of Intel Gen Graphics adapters available on system
   mfxStatus sts = MFXQueryAdaptersNumber(&num_adapters_available);
   MSDK_CHECK_STATUS(sts, "MFXQueryAdaptersNumber failed");

   // Allocate memory for response
   std::vector<mfxAdapterInfo> displays_data(num_adapters_available);
   mfxAdaptersInfo adapters = { displays_data.data(), mfxU32(displays_data.size()), 0u };

   // Fill description of Encode workload
   mfxComponentInfo interface_request = { MFX_COMPONENT_ENCODE, Encode_mfxVideoParam };

   // Query information about suitable adapters for Encode workload described by Encode_mfxVideoParam
   sts = MFXQueryAdapters(&interface_request, &adapters);

   if (sts == MFX_ERR_NOT_FOUND)
   {
      printf("Error: No adapters on machine capable to process desired workload\n");
      return -1;
   }

   MSDK_CHECK_STATUS(sts, "MFXQueryAdapters failed");

   // Choose correct implementation for discrete adapter. Mind usage of index 0, this is best suitable adapter from MSDK perspective
   switch (adapters.Adapters[0].Number)
   {
   case 0:
      impl = MFX_IMPL_HARDWARE;
      break;
   case 1:
      impl = MFX_IMPL_HARDWARE2;
      break;
   case 2:
      impl = MFX_IMPL_HARDWARE3;
      break;
   case 3:
      impl = MFX_IMPL_HARDWARE4;
      break;

   default:
      // Try searching on all display adapters
      impl = MFX_IMPL_HARDWARE_ANY;
      break;
   }

   // Initialize mfxSession in regular way with obtained implementation

Working with video memory
~~~~~~~~~~~~~~~~~~~~~~~~~

To fully utilize the SDK acceleration capability, the application should support OS specific infrastructures,
Microsoft* DirectX* for Micorosoft* Windows* and VA API for Linux*. 

The hardware acceleration support in application consists of video memory support and acceleration device support.

Depending on usage model, the application can use video memory on different stages of pipeline. Three major scenarios
are illustrated below:

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

The application must use the **IOPattern** field of the mfxVideoParam structure to indicate the I/O access pattern during
initialization. Subsequent SDK function calls must follow this access pattern. For example, if an SDK function operates on
video memory surfaces at both input and output, the application must specify the access pattern **IOPattern** at initialization
in MFX_IOPATTERN_IN_VIDEO_MEMORY for input and MFX_IOPATTERN_OUT_VIDEO_MEMORY for output. This particular I/O access pattern
must not change inside the **Init** … **Close** sequence.

Initialization of any hardware accelerated SDK component requires the acceleration device handle. This handle is also
used by SDK component to query HW capabilities. The application can share its device with the SDK by passing device handle
through the MFXVideoCORE_SetHandle function. It is recommended to share the handle before any actual usage of the SDK.

Working with Microsoft* DirectX* Applications
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK supports two different infrastructures for hardware acceleration on Microsoft* Windows* OS, “Direct3D 9 DXVA2” and
“Direct3D 11 Video API”. In the first one the application should use the IDirect3DDeviceManager9 interface as the acceleration
device handle, in the second one - ID3D11Device interface. The application should share one of these interfaces with
the SDK through the MFXVideoCORE_SetHandle function. If the application does not provide it, then the SDK creates its own
internal acceleration device. This internal device could not be accessed by the application and as a result, the SDK input and
output will be limited to system memory only. That in turn will reduce SDK performance. If the SDK fails to create a valid
acceleration device, then SDK cannot proceed with hardware acceleration and returns an error status to the application.

The application must create the Direct3D9* device with the flag **D3DCREATE_MULTITHREADED**. Additionally the flag
**D3DCREATE_FPU_PRESERVE** is recommended. This influences floating-point calculations, including PTS values.

The application must also set multithreading mode for Direct3D11* device. Example below illustrates how to do it:

.. code-block:: c++

   ID3D11Device            *pD11Device;
   ID3D11DeviceContext     *pD11Context;
   ID3D10Multithread       *pD10Multithread;

   pD11Device->GetImmediateContext(&pD11Context);
   pD11Context->QueryInterface(IID_ID3D10Multithread, &pD10Multithread);
   pD10Multithread->SetMultithreadProtected(true);

During hardware acceleration, if a Direct3D* “device lost” event occurs, the SDK operation terminates with the return
status MFX_ERR_DEVICE_LOST. If the application provided the Direct3D* device handle, the application must reset
the Direct3D* device.

When the SDK decoder creates auxiliary devices for hardware acceleration, it must allocate the list of Direct3D* surfaces
for I/O access, also known as the surface chain, and pass the surface chain as part of the device creation command.
In most cases, the surface chain is the frame surface pool mentioned in the Frame Surface Locking section.

The application passes the surface chain to the SDK component Init function through an SDK external allocator callback.
See the Memory Allocation and External Allocators section for details.

Only decoder Init function requests external surface chain from the application and uses it for auxiliary device creation.
Encoder and VPP Init functions may only request internal surfaces. See the ExtMemFrameType enumerator for more details about
different memory types.

Depending on configuration parameters, SDK requires different surface types. It is strongly recommended to call
one of the MFXVideoENCODE_QueryIOSurf, MFXVideoDECODE_QueryIOSurf or MFXVideoVPP_QueryIOSurf functions to determine
the appropriate type.

Supported SDK Surface Types and Color Formats for Direct3D9:

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

.. note:: “Decoder Render Target” corresponds to **DXVA2_VideoDecoderRenderTarget** type.
.. note:: “Processor Render Target” corresponds to **DXVA2_VideoProcessorRenderTarget**.

Supported SDK Surface Types and Color Formats for Direct3D11:

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

.. note:: “Decoder Render Target” corresponds to **D3D11_BIND_DECODER** flag.
.. note:: “Processor Render Target” corresponds to **D3D11_BIND_RENDER_TARGET**.
.. note:: that NV12 is the major encoding and decoding color format.
.. note:: Additionally, JPEG/MJPEG decoder supports RGB32 and YUY2 output.
.. note:: JPEG/MJPEG encoder supports RGB32 and YUY2 input for Direct3D9/Direct3D11 and YV12 input for Direct3D9 only.
.. note:: VPP supports RGB32 output.

Working with VA API Applications
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK supports single infrastructure for hardware acceleration on Linux* - “VA API”. The application should use
the VADisplay interface as the acceleration device handle for this infrastructure and share it with the SDK through
the MFXVideoCORE_SetHandle function. Because the SDK does not create internal acceleration device on Linux, the application
must always share it with the SDK. This sharing should be done before any actual usage of the SDK, including capability
query and component initialization. If the application fails to share the device, the SDK operation will fail.

Obtaining VA display from X Window System:

.. code-block::

   Display   *x11_display;
   VADisplay va_display;

   x11_display = XOpenDisplay(current_display);
   va_display  = vaGetDisplay(x11_display);

   MFXVideoCORE_SetHandle(session, MFX_HANDLE_VA_DISPLAY, (mfxHDL) va_display);

Obtaining VA display from Direct Rendering Manager:

.. code-block::

   int card;
   VADisplay va_display;

   card = open("/dev/dri/card0", O_RDWR); /* primary card */
   va_display = vaGetDisplayDRM(card);
   vaInitialize(va_display, &major_version, &minor_version);

   MFXVideoCORE_SetHandle(session, MFX_HANDLE_VA_DISPLAY, (mfxHDL) va_display);

When the SDK decoder creates hardware acceleration device, it must allocate the list of video memory surfaces for
I/O access, also known as the surface chain, and pass the surface chain as part of the device creation command.
The application passes the surface chain to the SDK component Init function through an SDK external allocator callback.
See the Memory Allocation and External Allocators section for details.

.. todo:: Add link to "Allocation and External Allocators"

Only decoder Init function requests external surface chain from the application and uses it for device creation.
Encoder and VPP Init functions may only request internal surfaces. See the **ExtMemFrameType** enumerator for more
details about different memory types.

.. note:: The VA API does not define any surface types and the application can use either MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET
   or MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET to indicate data in video memory.

Supported SDK Surface Types and Color Formats for VA API:

============= =====================    ===================
SDK Class     SDK Function Input       SDK Function Output
============= =====================    ===================
DECODE        Not Applicable           NV12
DECODE (JPEG)                          RGB32, YUY2
VPP           Listed in ColorFourCC    NV12, RGB32
ENCODE        NV12                     Not Applicable
ENCODE (JPEG) RGB32, YUY2, YV12
============= =====================    ===================
