Application can configure AVC encoder to work in CQP rate control mode with HRD model parameters. SDK will place HRD information to SPS/VUI and
choose appropriate profile/level. It’s responsibility of application to provide per-frame QP, track HRD conformance and insert required SEI
messages to the bitstream.

Example below shows how to enable CQP HRD mode. Application should set `RateControlMethod`_ to CQP, :cpp:member:`mfxExtCodingOption::VuiNalHrdParameters`
to **ON**, :cpp:member:`mfxExtCodingOption::NalHrdConformance` to **OFF** and set rate control parameters similar to CBR or VBR modes (instead
of QPI, QPP and QPB). SDK will choose CBR or VBR HRD mode based on **MaxKbps** parameter. If **MaxKbps** is set to zero, SDK will use CBR HRD model
(write cbr_flag = 1 to VUI), otherwise VBR model will be used (and cbr_flag = 0 is written to VUI).

.. code-block:: c++

   mfxExtCodingOption option, *option_array;

   /* configure mfxExtCodingOption */
   memset(&option,0,sizeof(option));
   option.Header.BufferId         = MFX_EXTBUFF_CODING_OPTION;
   option.Header.BufferSz         = sizeof(option);
   option.VuiNalHrdParameters     = MFX_CODINGOPTION_ON;
   option.NalHrdConformance       = MFX_CODINGOPTION_OFF;

   /* configure mfxVideoParam */
   mfxVideoParam param;

   // ...

   param.mfx.RateControlMethod         = MFX_RATECONTROL_CQP;
   param.mfx.FrameInfo.FrameRateExtN   = <valid_non_zero_value>;
   param.mfx.FrameInfo.FrameRateExtD   = <valid_non_zero_value>;
   param.mfx.BufferSizeInKB            = <valid_non_zero_value>;
   param.mfx.InitialDelayInKB          = <valid_non_zero_value>;
   param.mfx.TargetKbps                = <valid_non_zero_value>;

   if (<write cbr_flag = 1>)
      param.mfx.MaxKbps = 0;
   else /* <write cbr_flag = 0> */
      param.mfx.MaxKbps = <valid_non_zero_value>;

   param.NumExtParam = 1;
   option_array     = &option;
   param.ExtParam     = &option_array;

   /* encoder initialization */
   mfxStatus sts;
   sts = MFXVideoENCODE_Init(session, &param);
   
   // ...

   /* encoding */
   mfxEncodeCtrl ctrl;
   memset(&ctrl,0,sizeof(ctrl));
   ctrl.QP = <frame_qp>

   sts=MFXVideoENCODE_EncodeFrameAsync(session,&ctrl,surface2,bits,&syncp);

