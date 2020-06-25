Multiple-segment encoding is useful in video editing applications when during production; the encoder encodes multiple video clips according to
their time line. In general, one can define multiple-segment encoding as dividing an input sequence of frames into segments and encoding them in
different encoding sessions with the same or different parameter sets:

======================= =================== =====================
Segment already Encoded Segment in encoding Segment to be encoded
======================= =================== =====================
0s                      200s                500s
======================= =================== =====================

.. note:: Note that different encoders can also be used.

The application must be able to:

- Extract encoding parameters from the bitstream of previously encoded segment;
- Import these encoding parameters to configure the encoder.

Encoding can then continue on the current segment using either the same or the similar encoding parameters.

Extracting the header containing the encoding parameter set from the encoded bitstream is usually the task of a format splitter (de-multiplexer).
Nevertheless, the SDK :cpp:func:`MFXVideoDECODE_DecodeHeader` function can export the raw header if the application attaches the
:cpp:struct:`mfxExtCodingOptionSPSPPS` structure as part of the parameters.

The encoder can use the :cpp:struct:`mfxExtCodingOptionSPSPPS` structure to import the encoding parameters during :cpp:func:`MFXVideoENCODE_Init`.
The encoding parameters are in the encoded bitstream format. Upon a successful import of the header parameters, the encoder will generate
bitstreams with a compatible (not necessarily bit-exact) header. Table below shows all functions that can import a header and their error codes if
there are unsupported parameters in the header or the encoder is unable to achieve compatibility with the imported header.

====================================== ==================================================
Function Name                          Error Code if Import Fails
====================================== ==================================================
:cpp:func:`MFXVideoENCODE_Init`        :cpp:enumerator:`MFX_ERR_INCOMPATIBLE_VIDEO_PARAM`
:cpp:func:`MFXVideoENCODE_QueryIOSurf` :cpp:enumerator:`MFX_ERR_INCOMPATIBLE_VIDEO_PARAM`
:cpp:func:`MFXVideoENCODE_Reset`       :cpp:enumerator:`MFX_ERR_INCOMPATIBLE_VIDEO_PARAM`
:cpp:func:`MFXVideoENCODE_Query`       :cpp:enumerator:`MFX_ERR_UNSUPPORTED`
====================================== ==================================================

The encoder must encode frames to a GOP sequence starting with an IDR frame for H.264 (or I frame for MPEG-2) to ensure that the current segment
encoding does not refer to any frames in the previous segment. This ensures that the encoded segment is self-contained, allowing the application to
insert it anywhere in the final bitstream. After encoding, each encoded segment is HRD compliant. However, the concatenated segments may not be
HRD compliant.

Example below shows an example of the encoder initialization procedure that imports H.264 sequence and picture parameter sets:

.. code-block:: c++

   mfxStatus init_encoder() {
      mfxExtCodingOptionSPSPPS option, *option_array;

      /* configure mfxExtCodingOptionSPSPPS */
      memset(&option,0,sizeof(option));
      option.Header.BufferId=MFX_EXTBUFF_CODING_OPTION_SPSPPS;
      option.Header.BufferSz=sizeof(option);
      option.SPSBuffer=sps_buffer;
      option.SPSBufSize=sps_buffer_length;
      option.PPSBuffer=pps_buffer;
      option.PPSBufSize=pps_buffer_length;

      /* configure mfxVideoParam */
      mfxVideoParam param;
      //...
      param.NumExtParam=1;
      option_array=&option;
      param.ExtParam=&option_array;

      /* encoder initialization */
      mfxStatus status;
      status=MFXVideoENCODE_Init(session, &param);
      if (status==MFX_ERR_INCOMPATIBLE_VIDEO_PARAM) {
         printf(“Initialization failed\n”);
      } else {
         printf(“Initialized\n”);
      }
      return status;
   }

