The :class:`vpl::Encode` class implements elementary stream encode from raw frame to encoded bitstream. 

.. graphviz::

  digraph {
    rankdir=LR;
    Bitstream [shape=record label="Bitstream" ];
    Encode [shape=record  label="Encode"];
    Raw [shape=rect];
    Raw->Encode->Bitstream;
  }

**Supported bitstream formats**

- h264 
- h265 


**EncodeFrame C++ interface**:

The encode function :func:`vpl::Encode::EncodeFrame` interface is

.. code-block:: c++

  size_t Encode::EncodeFrame(vplm_mem* image, void *pbs_out);


**States**:

During execution, state communicates what the application should do next.

.. graphviz::

  digraph {
    rankdir=LR
    
    start
    READ_INPUT
    ERROR 
    OUTPUT_BUFFER_FULL 
    OUTPUT_EXCEEDS_BUFFER_SIZE 
    END_OF_OPERATION
    end

    start->READ_INPUT 
    
    READ_INPUT->READ_INPUT[label="almost everything happens here"]
    READ_INPUT->ERROR[label="internal error"]
    ERROR->READ_INPUT
    
    READ_INPUT->OUTPUT_BUFFER_FULL[label="output size>remaining buffer size"]
    OUTPUT_BUFFER_FULL->READ_INPUT

    READ_INPUT->OUTPUT_EXCEEDS_BUFFER_SIZE[label="output size>total buffer size"]
    OUTPUT_EXCEEDS_BUFFER_SIZE->READ_INPUT
    
    READ_INPUT->END_OF_OPERATION[label="no more to process"]
    END_OF_OPERATION->end
  }

======================================     ====================================== 
State                                      Meaning
======================================     ======================================     
READ_INPUT                                 workstream can read raw frame input
ERROR                                      an error occurred during processing, try again
OUTPUT_BUFFER_FULL                         output size > remaining space in the output bitstream buffer 
OUTPUT_EXCEEDS_BUFFER_SIZE                 output size> total buffer size 
======================================     ======================================

**Settings**:

Encode configuration parameters are specified in :class:`vpl::VplParamsEncode`,
which controls per session and per frame settings of the encode operations.

**Data model**:

VPL allocates pools of VPL Memory used by decode and consumers of decoded frames.  The application is expected to manage reference counts.  Only surfaces with no external references can be used to decode new frames.

.. graphviz::

   digraph  {
    rankdir=LR
    node [shape=record];
    struct1 [label="<f0> surface pool|<f1> DecodeFrame"];
    struct3 [label="<f1> rest of pipeline"];
    
    struct1:f1 -> struct3:f1 [label="VPL Memory"]; 
   }



**Sample code**:

.. code-block:: c 

    #include "vpl/vpl.hpp"
    #define BUFFER_SIZE 1024 * 1024

    int main(int argc, char* argv[]) {

      // Find all the devices in the system and select a preferred device
      DeviceInfo *dinfo = new DeviceInfo();
      DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_ENCODE);

      // Get encode preset
      VplParamsEncode *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_ENCODE, dev->m_id);

      // Create an Encode workstream and a device context on the device
      Encode *ws = new Encode(dconfig, *dev);

      uint8_t *pbsout=new uint8_t[BUFFER_SIZE];
      VplFile* fInput = vplOpenFile(argv[1],"rb");
      FILE* fOutput = fopen("out.h264","wb");

      vplm_mem* decimage;
      vplm_image_info info={};
      info.width=300;
      info.height=300;
      info.format=VPLM_PIXEL_FORMAT_NV12;
      vplm_create_cpu_image(&info, &decimage);

      for (;;) {
        vplStatus sts=vplReadData(fInput,decimage);
        if (sts<0) break;
        vplm_ref(decimage);

        size_t nbytesout=ws->EncodeFrame(decimage,pbsout);
        fwrite(pbsout, 1, nbytesout, fOutput);

        printf(".");
        fflush(stdout);

      }
      puts("");

      vplCloseFile(fInput);
      fclose(fOutput);

      delete[] pbsout;

      return 0;
    }
