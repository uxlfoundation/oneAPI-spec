The application can use the SDK encoding, decoding and video processing functions together for
transcoding operations. This section describes the key aspects of connecting two or more SDK functions together.

Asynchronous Pipeline
~~~~~~~~~~~~~~~~~~~~~

The application passes the output of an upstream SDK function to the input of the downstream SDK function
to construct an asynchronous pipeline. Such pipeline construction is done at runtime and can be dynamically changed,
as illustrated below:

.. code-block:: c++

   mfxSyncPoint sp_d, sp_e;
   MFXVideoDECODE_DecodeFrameAsync(session,bs,work,&vin, &sp_d);
   if (going_through_vpp) {
      MFXVideoVPP_RunFrameVPPAsync(session,vin,vout, &sp_d);
      MFXVideoENCODE_EncodeFrameAsync(session,NULL,vout,bits2,&sp_e);
   } else {
      MFXVideoENCODE_EncodeFrameAsync(session,NULL,vin,bits2,&sp_e);
   }
   MFXVideoCORE_SyncOperation(session,sp_e,INFINITE);

The SDK simplifies the requirement for asynchronous pipeline synchronization. The application only needs to synchronize
after the last SDK function. Explicit synchronization of intermediate results is not required and in fact can slow performance.

The SDK tracks the dynamic pipeline construction and verifies dependency on input and output parameters to ensure
the execution order of the pipeline function. In Example 6, the SDK will ensure MFXVideoENCODE_EncodeFrameAsync does not
begin its operation until MFXVideoDECODE_DecodeFrameAsync or MFXVideoVPP_RunFrameVPPAsync has finished.

During the execution of an asynchronous pipeline, the application must consider the input data in use and must not change
it until the execution has completed. The application must also consider output data unavailable until the execution has finished.
In addition, for encoders, the application must consider extended and payload buffers in use while the input surface is locked.

The SDK checks dependencies by comparing the input and output parameters of each SDK function in the pipeline.
Do not modify the contents of input and output parameters before the previous asynchronous operation finishes.
Doing so will break the dependency check and can result in undefined behavior. An exception occurs when the input and
output parameters are structures, in which case overwriting fields in the structures is allowed.

.. note:: Note that the dependency check works on the pointers to the structures only.

There are two exceptions with respect to intermediate synchronization:

- The application must synchronize any input before calling the SDK function MFXVideoDECODE_DecodeFrameAsync,
  if the input is from any asynchronous operation.
- When the application calls an asynchronous function to generate an output surface in video memory and passes that
  surface to a non-SDK component, it must explicitly synchronize the operation before passing the surface to the non-SDK component.

Pseudo Code of Asynchronous **ENC**->**ENCODE** Pipeline Construction:

.. code-block:: c++

   mfxENCInput enc_in = ...;
   mfxENCOutput enc_out = ...;
   mfxSyncPoint sp_e, sp_n;
   mfxFrameSurface1* surface = get_frame_to_encode();
   mfxExtBuffer dependency;
   dependency.BufferId = MFX_EXTBUFF_TASK_DEPENDENCY;
   dependency.BufferSz = sizeof(mfxExtBuffer);

   enc_in.InSurface = surface;
   enc_out.ExtParam[enc_out.NumExtParam++] = &dependency;
   MFXVideoENC_ProcessFrameAsync(session, &enc_in, &enc_out, &sp_e);

   surface->Data.ExtParam[surface->Data.NumExtParam++] = &dependency;
   MFXVideoENCODE_EncodeFrameAsync(session, NULL, surface, &bs, &sp_n);

   MFXVideoCORE_SyncOperation(session, sp_n, INFINITE);
   surface->Data.NumExtParam--;

Surface Pool Allocation
~~~~~~~~~~~~~~~~~~~~~~~

When connecting SDK function **A** to SDK function **B**, the application must take into account the needs of both functions
to calculate the number of frame surfaces in the surface pool. Typically, the application can use the formula **Na+Nb**,
where **Na** is the frame surface needs from SDK function **A** output, and **Nb** is the frame surface needs from
SDK function **B** input.

For performance considerations, the application must submit multiple operations and delays synchronization as much as possible,
which gives the SDK flexibility to organize internal pipelining. For example, the operation sequence:

.. graphviz::

   digraph {
      rankdir=LR;
      f1 [shape=record label="ENCODE(F1)" ];
      f2 [shape=record label="ENCODE(F2)" ];
      f3 [shape=record label="SYNC(F1)" ];
      f4 [shape=record label="SYNC(F2)" ];
      f1->f2->f3->f4;
   }

is recommended, compared with:

.. graphviz::

   digraph {
      rankdir=LR;
      f1 [shape=record label="ENCODE(F1)" ];
      f2 [shape=record label="ENCODE(F2)" ];
      f3 [shape=record label="SYNC(F1)" ];
      f4 [shape=record label="SYNC(F2)" ];
      f1->f3->f2->f4;
   }

In this case, the surface pool needs additional surfaces to take into account multiple asynchronous operations
before synchronization. The application can use the **AsyncDepth** parameter of the mfxVideoParam structure to inform
an SDK function that how many asynchronous operations the application plans to perform before synchronization.
The corresponding SDK **QueryIOSurf** function will reflect such consideration in the NumFrameSuggested value.
Example below shows a way of calculating the surface needs based on NumFrameSuggested values:

.. code-block:: c++

   async_depth=4;
   init_param_v.AsyncDepth=async_depth;
   MFXVideoVPP_QueryIOSurf(session, &init_param_v, response_v);
   init_param_e.AsyncDepth=async_depth;
   MFXVideoENCODE_QueryIOSurf(session, &init_param_e, &response_e);
   num_surfaces=    response_v[1].NumFrameSuggested
            +response_e.NumFrameSuggested
            -async_depth; /* double counted in ENCODE & VPP */

Pipeline Error Reporting
~~~~~~~~~~~~~~~~~~~~~~~~

During asynchronous pipeline construction, each stage SDK function will return a synchronization point (sync point).
These synchronization points are useful in tracking errors during the asynchronous pipeline operation.

Assume the pipeline is:

.. graphviz::

   digraph {
      rankdir=LR;
      A->B->C;
   }

The application synchronizes on sync point **C**. If the error occurs in SDK function **C**, then the synchronization
returns the exact error code. If the error occurs before SDK function **C**, then the synchronization returns MFX_ERR_ABORTED.
The application can then try to synchronize on sync point **B**. Similarly, if the error occurs in SDK function **B**,
the synchronization returns the exact error code, or else MFX_ERR_ABORTED. Same logic applies
if the error occurs in SDK function **A**.
