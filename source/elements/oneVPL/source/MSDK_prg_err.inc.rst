The SDK accelerates decoding, encoding and video processing through a hardware device. The SDK
functions may return the following errors or warnings if the hardware device encounters errors:

============================================== ====================================================================================================================================================
Status                                         Description
============================================== ====================================================================================================================================================
:cpp:enumerator:`MFX_ERR_DEVICE_FAILED`        Hardware device returned unexpected errors. SDK was unable to restore operation.
:cpp:enumerator:`MFX_ERR_DEVICE_LOST`          Hardware device was lost due to system lock or shutdown.
:cpp:enumerator:`MFX_WRN_PARTIAL_ACCELERATION` The hardware does not fully support the specified configuration. The encoding, decoding, or video processing operation may be partially accelerated.
:cpp:enumerator:`MFX_WRN_DEVICE_BUSY`          Hardware device is currently busy.
============================================== ====================================================================================================================================================

SDK functions **Query**, **QueryIOSurf**, and **Init** return :cpp:enumerator:`MFX_WRN_PARTIAL_ACCELERATION` to indicate that the encoding,
decoding or video processing operation can be partially hardware accelerated or not hardware accelerated at all.
The application can ignore this warning and proceed with the operation. (Note that SDK functions may return
errors or other warnings overwriting :cpp:enumerator:`MFX_WRN_PARTIAL_ACCELERATION`, as it is a lower priority warning.)

SDK functions return :cpp:enumerator:`MFX_WRN_DEVICE_BUSY` to indicate that the hardware device is busy and unable to take commands at this time.
Resume the operation by waiting for a few milliseconds and resubmitting the request. Example below shows the decoding pseudo-code.
The same procedure applies to encoding and video processing.

SDK functions return :cpp:enumerator:`MFX_ERR_DEVICE_LOST` or :cpp:enumerator:`MFX_ERR_DEVICE_FAILED` to indicate that there is a complete failure in
hardware acceleration. The application must close and reinitialize the SDK function class. If the application
has provided a hardware acceleration device handle to the SDK, the application must reset the device.

Pseudo-Code to Handle :cpp:enumerator:`MFX_WRN_DEVICE_BUSY`:

.. code-block:: c++

   mfxStatus sts=MFX_ERR_NONE;
   for (;;) {
      // do something
      sts=MFXVideoDECODE_DecodeFrameAsync(session, bitstream,  surface_work, &surface_disp, &syncp);
      if (sts == MFX_WRN_DEVICE_BUSY) Sleep(5);
   }

