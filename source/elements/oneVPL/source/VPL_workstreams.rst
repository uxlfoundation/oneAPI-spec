The :class:`vpl::Workstream` class is the core of the VPL interface.  It represents a 
media building block running decode, frame processing, DL inference and 
encode operations on a single device context. Workstreams can be offloaded to 
different devices. Complex pipelines can be formed from multiple workstreams. 

There are four subclasses of :class:`vpl::Workstream` that perform the following basic operations

- :class:`vpl::Decode`: decode a bitstream to raw frames 
- :class:`vpl::VideoProcess`: implement a video processing filter operation with raw frame input and output
- :code:`vpl::Infer`: invoke a Deep Learning model to infer on raw frame. Details of this subclass will be provided in a future release.
- :class:`vpl::Encode`: encode raw frames to a bitstream 

In the :class:`vpl::VideoProcess` subclass, a sequence of filters with single input and single output running on the same device context can be fused to the same workstream. 
Operations executing on different device contexts are seperated to different worksteams such that each workstream can be dispatched to a single device context. 

Workstream Internals
--------------------

Each :class:`vpl::Workstream` contains the following information

- :class:`vpl::VplParams`: the parameter settings of the workstream, i.e., resolution of the output per session or per frame.
- :class:`vpl::DeviceContext`: contains the execution device context of the workstream, i.e., VAAPI, DX, OCL, GL contexts for media, compute and rendering operations

The :class:`vpl::VplParams` provides the interface for setting the workstream configuration during initialization
and dynamically changing workstream settings during processing for frame level control.

Initialization Sequence
-----------------------

The standard sequence to create a workstream consists of the following steps:

#. Select a device to execute the workstream

   #. Create a device context or use an existing device context to execute the workstream
   
#. Get the configuration presets for the selected device
#. Create the workstream with the configuration setting :class:`vpl::config::VPLParams` and :class:`vpl::DeviceContext`.

The following transcoding example uses three workstreams: :class:`vpl::Decode`, :class:`vpl::Process` and :class:`vpl::Encode`, and shares a single context to execute them together:

.. code-block:: c++

   #include "vpl/vpl.hpp"
   #define BUFFER_SIZE 1024 * 1024 * 80

   using namespace vpl;

   int main(int argc, char* argv[]) {

   // Find all the devices in the system and select a preferred device
   DeviceInfo *dinfo = new DeviceInfo();
   DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_DECODE | VPL_WORKSTREAM_VIDEOPROC, VPL_WORKSTREAM_ENCODE);

   // Get decode preset
   config::VPLParams *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_DECODE, dev->m_id);
   // Create a Decode workstream and a device context on the device
   Decode *decode = new Decode(dconfig, *dev);

   // Create a VPP workstream, use the same device context as Decode
   config::VPLParams *pconfig = dinfo->GetVideoProcessPreset(dev->m_dtype, VPL_WORKSTREAM_VIDEOPROC, dev->m_id);
   VideoProcess *proc = new Process(pconfig, decode->GetContext());

   // Create an Encode workstream, use the same device context as Decode
   config::VPLParams *econfig = dinfo->GetEncodePreset(dev->m_dtype, VPL_WORKSTEAM_ENCODE, dev->m_id);
   Encode *encode = new Encode(econfig, decode->GetContext());

   uint8_t* pbs = new uint8_t[BUFFER_SIZE];
   uint8_t* pbsout = new uint8_t[BUFFER_SIZE];

   FILE* fInput = fopen(argv[1], "rb");
   FILE* fOutput = fopen("out.h264", "wb");

   int frameCount = 0;
   // Run the pipeline explicitly
   for (vplWorkstreamState decode_state = VPL_STATE_READ_INPUT;
         decode_state != VPL_STATE_END_OF_OPERATION && decode_state != VPL_STATE_ERROR;
         decode_state = decode->GetState()) {
      vplm_mem* dec_image =
         decode->DecodeFrame(pbs, fread(pbs, 1, BUFFER_SIZE, fInput));
      if (!dec_image) continue;
      frameCount++;

      vplm_mem* vpp_image = proc->ProcessFrame(dec_image);
      if (vpp_image) {
         size_t nbytesout = encode->EncodeFrame(vpp_image, pbsout);
         fwrite(pbsout, 1, nbytesout, fOutput);
         printf("%d\r", frameCount);
         fflush(stdout);
      }
   }

   printf("\ndone !\n");

   fclose(fInput);
   fclose(fOutput);

   delete[] pbs;
   delete[] pbsout;
   return 0;
   }

Dynamic Setting Control
-----------------------

The :class:`vpl::VplParams` defines the workstream settings for the device. 
User program can use its access functions to read and set the settings for the workstream.
After changing the configuration setting, user program then call the :cpp:func:`vpl::Workstream::UpdateDeviceConfig` function to propapge the setting to
device context. Configuration setting change takes effect for the subsequent calls to the worksteam.
The following example changes the output resolution in the middle of a decoding sequence.

.. code-block:: c++

   // Decoding loop
   while (decode->GetState() != VPL_STATE_END_OF_OPERATION) {
      vplm_mem *image = decode->DecodeFrame(*bs_ptr, bs_size);
      
      // Change output resolution
      if (need_resize) {
         VplVideoSurfaceResolution resol = {480, 780};
         dconfig->SetOutputResolution(resol);
         
         // propagate the new settings to the driver
         decode->UpdateDeviceConfig();
      }
   }

In the future releases, serialization operations of :class:`vpl::VplParams`
will be added to support the configuration synchronization to accelerator drivers
that are running autonomously on remote nodes.  
