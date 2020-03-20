The :class:`vpl::VideoProcess` class implements a variety of filter operations.  
Current API is limited to single input and single output.  

.. graphviz::

  digraph {
    rankdir=LR;
    Raw0 [shape=rect label="raw" ];
    Decode [shape=record  label="Decode"];
    Raw [shape=rect label="raw"];
    Raw0->Decode->Raw;
  }

**Supported Filter Operations**
The list of filters will expand based on implementation schedule. 
Current release supports the following filters: 

- Resize 
- Colorspace conversion (in=i420,nv12,bgra out=i420,nv12,bgra)


**C++ interface**: 

The video process function :func:`vpl::VideoProcess::ProcessFrame` interface is

.. code-block:: c++

  vplm_mem* VideoProcess::ProcessFrame(vplm_mem* image);


**States**:

During execution, state communicates what the application should do next.

======================================     ====================================== 
State                                      Meaning
======================================     ======================================     
READ_INPUT                                 workstream can read raw input
ERROR                                      an error occurred during processing, try again
======================================     ======================================

**Settings**:

Video processing configuration parameters are specified in :class:`vpl::VplParams`,
which controls per session and per frame settings of the encode operations.
:func:`vpl::VideoProcess::ProcessFrame` converts the input image to the output image
according to the output image specification in the settings. 

**Data model**:

VPL allocates pools of VPL Memory used by frame process and consumers of processed frames.  The application is expected to manage reference counts.  Only surfaces with no external references can be used to for new frame output.

.. graphviz::

   digraph  {
    rankdir=LR
    node [shape=record];
    struct1 [label="<f0> surface pool|<f1> ProcessFrame"];
    struct3 [label="<f1> rest of pipeline"];
    
    struct1:f1 -> struct3:f1 [label="VPL Memory"]; 
   }


**Sample code**:

.. code-block:: c

    #include "vpl/vpl.hpp"

    int main(int argc, char* argv[]) {

      // Find all the devices in the system and select a preferred device
      DeviceInfo *dinfo = new DeviceInfo();
      DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_VIDEOPROC);

      // Get vidoe process preset
      VplParams *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_VIDEOPROC, dev->m_id);

      // Create an Encode workstream and a device context on the device
      VideoProcess *ws = new VideoProcess(dconfig, *dev);

      // Set output image formats
      VplVideoSurfaceResolution output_size = {300,300};
      dconfig->SetOutputResolution(output_size);
      dconfig->SetOutputFromat(VPL_FOURCC_I420);

      // Propagate the settings to the device driver
      ws->UpdateDeviceConfig();

      VplFile* fInput = vplOpenFile(argv[1],"rb");
      VplFile* fOutput = vplOpenFile("out.i420", "wb");

      vplm_mem* dec_image;
      vplm_image_info info={};
      info.width=1280;
      info.height=720;
      info.format=VPLM_PIXEL_FORMAT_RGBA;
      vplm_create_cpu_image(&info, &dec_image);

      int frameCount = 0;
      for (;;) {
        vplStatus sts=vplReadData(fInput,dec_image);
        if (sts<0) break;
        vplm_ref(dec_image);
        frameCount++;

        vplm_mem* vpp_image = ws->ProcessFrame(dec_image);

        vplWriteData(fOutput,vpp_image);
        printf("%d\r", frameCount);
        fflush(stdout);
        vplm_unref(vpp_image);
      }
      printf("\ndone !\n");

      vplCloseFile(fInput);
      vplCloseFile(fOutput);


      return 0;
    }

