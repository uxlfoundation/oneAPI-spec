The :class:`vpl::Decode` implements elementary stream decode from encoded bitstreams and outputs raw frames. 

.. graphviz::

  digraph {
    rankdir=LR;
    Bitstream [shape=record label="Bitstream" ];
    Decode [shape=record  label="Decode"];
    Raw [shape=rect];
    Bitstream->Decode->Raw;
  }

**Supported bitstream formats**

- h264 
- h265 

**DecodeFrame C++ interface**: 

The decode function :func:`vpl::Decode::DecodeFrame` interface is

.. code-block:: c++

  vplm_mem* Decode::DecodeFrame(const void* pbs, size_t size);  


**States**:

During execution, state communicates what the application should do next.

.. graphviz::

  digraph {
    rankdir=LR
    
    start
    READ_INPUT
    ERROR 
    INPUT_BUFFER_FULL 
    INPUT_EXCEEDS_BUFFER_SIZE 
    END_OF_OPERATION
    end

    start->READ_INPUT 
    
    READ_INPUT->READ_INPUT[label="almost everything happens here"]
    READ_INPUT->ERROR[label="internal error"]
    ERROR->READ_INPUT
    
    READ_INPUT->INPUT_BUFFER_FULL[label="input size>remaining buffer size"]
    INPUT_BUFFER_FULL->READ_INPUT

    READ_INPUT->INPUT_EXCEEDS_BUFFER_SIZE[label="input size>total buffer size"]
    INPUT_EXCEEDS_BUFFER_SIZE->READ_INPUT
    
    READ_INPUT->END_OF_OPERATION[label="no more to process"]
    END_OF_OPERATION->end
  }

======================================     ====================================== 
State                                      Meaning
======================================     ======================================     
READ_INPUT                                 workstream can read bitstream input
ERROR                                      an error occurred during processing, try again
INPUT_BUFFER_FULL                          input size > remaining space in the input bitstream buffer, input ignored and decode operation should be allowed to drain before attempting to add more bitstream again 
INPUT_EXCEEDS_BUFFER_SIZE                  input size> total buffer size 
======================================     ======================================

**Settings**:

Encode configuration parameters are specified in :class:`vpl::VplParamsDecode`,
which controls per session and per frame settings of the decode operations.

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

    int main(int argc, char *argv[]) {

      // Find all the devices in the system and select a preferred device
      DeviceInfo *dinfo = new DeviceInfo();
      DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_DECODE);

      // Get decode preset
      VplParamsDecode *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_DECODE, dev->m_id);

      // Create a Decode workstream and a device context on the device
      Decode *ws = new Decode(dconfig, *dev);

      uint8_t *pbs = new uint8_t[BUFFER_SIZE];

      FILE *fInput = fopen(argv[1], "rb");
      VplFile *fOutput = vplOpenFile("out.nv12", "wb");

      vplm_mem *dec_image = nullptr;
      bool bdrain_mode = false;
      int frameCount = 0;
      vplWorkstreamState decode_state = VPL_STATE_READ_INPUT;

      while (1) {
        decode_state = ws->GetState();
        if (decode_state == VPL_STATE_END_OF_OPERATION ||
            decode_state == VPL_STATE_ERROR) {
          break;
        }

        // read more input if state indicates buffer space
        // is available
        uint32_t bs_size = 0;
        if ((decode_state == VPL_STATE_READ_INPUT) && (!bdrain_mode)) {
          bs_size = (uint32_t)fread(pbs, 1, BUFFER_SIZE, fInput);
        }

        if (bs_size == 0 || decode_state == VPL_STATE_INPUT_BUFFER_FULL) {
          bdrain_mode = true;
        }

        if (bdrain_mode)
          dec_image = ws->DecodeFrame(nullptr, 0);
        else
          dec_image = ws->DecodeFrame(pbs, bs_size);

        if (!dec_image)
          continue;

        frameCount++;

        vplWriteData(fOutput, dec_image);
        printf("%d\r", frameCount);
        fflush(stdout);

        vplm_unref(dec_image);
      }

      printf("\ndone !\n");
      fclose(fInput);
      vplCloseFile(fOutput);

      delete[] pbs;
      return 0;
    }
