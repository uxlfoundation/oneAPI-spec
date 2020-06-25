There are two models of memory managment in SDK implementations: internal and external. 

External memory managment
~~~~~~~~~~~~~~~~~~~~~~~~~
In external memory model the application must allocate sufficient memory for input and output parameters and buffers, and de-allocate it 
when SDK functions complete their operations.
During execution, the SDK functions use callback functions to the application to manage memory for video frames through
external allocator interface mfxFrameAllocator.

If an application needs to control the allocation of video frames, it can use callback functions through the
mfxFrameAllocator interface. If an application does not specify an allocator, an internal allocator is used.
However, if an application uses video memory surfaces for input and output, it must specify the hardware acceleration
device and an external frame allocator using mfxFrameAllocator.

The external frame allocator can allocate different frame types:

- in system memory
- in video memory, as “decoder render targets” or “processor render targets.” See the section
  Working with hardware acceleration for additional details.

The external frame allocator responds only to frame allocation requests for the requested memory type and
returns MFX_ERR_UNSUPPORTED for all others. The allocation request uses flags, part of memory type field,
to indicate which SDK class initiates the request, so the external frame allocator can respond accordingly.

Simple external frame allocator:

.. code-block:: c++

   typedef struct {
      mfxU16 width, height;
      mfxU8 *base;
   } mid_struct;

   mfxStatus fa_alloc(mfxHDL pthis, mfxFrameAllocRequest *request, mfxFrameAllocResponse *response) {
      if (!(request->type&MFX_MEMTYPE_SYSTEM_MEMORY))
         return MFX_ERR_UNSUPPORTED;
      if (request->Info->FourCC!=MFX_FOURCC_NV12)
         return MFX_ERR_UNSUPPORTED;
      response->NumFrameActual=request->NumFrameMin;
      for (int i=0;i<request->NumFrameMin;i++) {
         mid_struct *mmid=(mid_struct *)malloc(sizeof(mid_struct));
         mmid->width=ALIGN32(request->Info->Width);
         mmid->height=ALIGN32(request->Info->Height);
         mmid->base=(mfxU8*)malloc(mmid->width*mmid->height*3/2);
         response->mids[i]=mmid;
      }
      return MFX_ERR_NONE;
   }

   mfxStatus fa_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr) {
      mid_struct *mmid=(mid_struct *)mid;
      ptr->pitch=mmid->width;
      ptr->Y=mmid->base;
      ptr->U=ptr->Y+mmid->width*mmid->height;
      ptr->V=ptr->U+1;
      return MFX_ERR_NONE;
   }

   mfxStatus fa_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr) {
      if (ptr) ptr->Y=ptr->U=ptr->V=ptr->A=0;
      return MFX_ERR_NONE;
   }

   mfxStatus fa_gethdl(mfxHDL pthis, mfxMemId mid, mfxHDL *handle) {
      return MFX_ERR_UNSUPPORTED;
   }

   mfxStatus fa_free(mfxHDL pthis, mfxFrameAllocResponse *response) {
      for (int i=0;i<response->NumFrameActual;i++) {
         mid_struct *mmid=(mid_struct *)response->mids[i];
         free(mmid->base); free(mid);
      }
      return MFX_ERR_NONE;
   }


For system memory, it is highly recommended to allocate memory for all
planes of the same frame as a single buffer (using one single malloc call).

Internal memory managment
~~~~~~~~~~~~~~~~~~~~~~~~~
In the internal memory managment model SDK provides interface functions for frames allocation:

:cpp:func:`MFXMemory_GetSurfaceForVPP`

:cpp:func:`MFXMemory_GetSurfaceForEncode`

:cpp:func:`MFXMemory_GetSurfaceForDecode`

which are used together with :cpp:struct:`mfxFrameSurfaceInterface` for surface managment. 
The surface returned by these function is reference counted objecte and the application has to call
:cpp:member:`mfxFrameSurfaceInterface::Release` after finishing all operations with the surface.
In this model the application doesn't need to create and set external allocator to SDK.
Another possibility to obtain internally allocated surface is to call :cpp:func:`MFXVideoDECODE_DecodeFrameAsync`
with working surface equal to NULL (see :ref:`Simplified decoding procedure <simplified-decoding-procedure>`). In such situation 
Decoder will allocate new refcountable :cpp:struct:`mfxFrameSurface1`
and return to the user. All assumed contracts with user are similar with such in functions MFXMemory_GetSurfaceForXXX.

mfxFrameSurfaceInterface
~~~~~~~~~~~~~~~~~~~~~~~~
Starting from API version 2.0 SDK support :cpp:struct:`mfxFrameSurfaceInterface`. 
This interface is a set of callback functions to manage lifetime of allocated surfaces, get access to pixel data, 
and obtain native handles and device abstractions (if suitable). It's recommended to use
mfxFrameSurface1::mfxFrameSurfaceInterface if presents instead of directly accessing :cpp:struct:`mfxFrameSurface1` structure members 
or call external allocator callback functions if set.

The following example demonstrates the usage of :cpp:struct:`mfxFrameSurfaceInterface` for memory sharing:

.. code-block:: c++


    // let decode frame and try to access output optimal way.
    sts = MFXVideoDECODE_DecodeFrameAsync(session, NULL, NULL, &outsurface, &syncp);
    if (MFX_ERR_NONE == sts)
    {
        outsurface->FrameInterface->(*GetDeviceHandle)(outsurface, &device_handle, &device_type);
        // if application or component is familar with mfxHandleType and it's possible to share memory created by device_handle.
        if (isDeviceTypeCompatible(device_type) && isPossibleForMemorySharing(device_handle)) {
            // get native handle and type
            outsurface->FrameInterface->(*GetNativeHandle)(outsurface, &resource, &resource_type);
            if (isResourceTypeCompatible(resource_type)) {
                //use memory directly
                ProcessNativeMemory(resource);
                outsurface->FrameInterface->(*Release)(outsurface);
            }
        }
        // Application or component is not aware about such DeviceHandle or Resource type need to map to system memory.
        outsurface->FrameInterface->(*Map)(outsurface, MFX_MAP_READ);
        ProcessSystemMemory(outsurface);
        outsurface->FrameInterface->(*Unmap)(outsurface);
        outsurface->FrameInterface->(*Release)(outsurface);
    }


 