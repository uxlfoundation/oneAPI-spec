The following sections address a few aspects of additional requirements that streaming or video conferencing applications may use in the
encoding or transcoding process. See also `Configuration Change`_ chapter.

Dynamic Bitrate Change
~~~~~~~~~~~~~~~~~~~~~~

The SDK encoder supports dynamic bitrate change differently depending on bitrate control mode and HRD conformance requirement. If HRD conformance is
required, i.e. if application sets **NalHrdConformance** option in :cpp:struct:`mfxExtCodingOption` structure to **ON**, the only allowed bitrate
control mode is VBR. In this mode, the application can change **TargetKbps** and **MaxKbps** values. The application can change these values by
calling the  :cpp:func:`MFXVideoENCODE_Reset` function. Such change in bitrate usually results in generation of a new key-frame and sequence header.
There are some exceptions though. For example, if HRD Information is absent in the stream then change of **TargetKbps** does not require change of
sequence header and as a result the SDK encoder does not insert a key frame.

If HRD conformance **is not** required, i.e. if application turns off **NalHrdConformance** option in :cpp:struct:`mfxExtCodingOption` structure,
all bitrate control modes are available. In CBR and AVBR modes the application can change **TargetKbps**, in VBR mode the application can change
**TargetKbps** and **MaxKbps** values. Such change in bitrate will not result in generation of a new key-frame or sequence header.

The SDK encoder may change some of the initialization parameters provided by the application during initialization. That in turn may lead to
incompatibility between the parameters provided by the application during reset and working set of parameters used by the SDK encoder. That is why
it is strongly recommended to retrieve the actual working parameters by :cpp:func:`MFXVideoENCODE_GetVideoParam` function before making any
changes to bitrate settings.

In all modes, the SDK encoders will respond to the bitrate changes as quickly as the underlying algorithm allows, without breaking other encoding
restrictions, such as HRD compliance if it is enabled. How soon the actual bitrate can catch up with the specified bitrate is implementation
dependent.

Alternatively, the application may use the CQP (constant quantization parameter) encoding mode to perform customized bitrate adjustment on a
per-frame base. The application may use any of the encoded or display order modes to use per-frame CQP.

Dynamic Resolution Change
~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK encoder supports dynamic resolution change in all bitrate control modes. The application may change resolution by calling
:cpp:func:`MFXVideoENCODE_Reset` function. The application may decrease or increase resolution up to the size specified during encoder initialization.

Resolution change always results in insertion of key IDR frame and new sequence parameter set header. The only exception is SDK VP9
encoder (see section for `Dynamic reference frame scaling`_). The SDK encoder does not guarantee HRD conformance across resolution change point.

The SDK encoder may change some of the initialization parameters provided by the application during initialization. That in turn may lead to
incompatibility of parameters provide by the application during reset and working set of parameters used by the SDK encoder. That is why it is
strongly recommended to retrieve the actual working parameters set by :cpp:func:`MFXVideoENCODE_GetVideoParam` function before making any
resolution change.

Dynamic reference frame scaling
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VP9 standard allows to change resolution without insertion of key-frame. It's possible because of native built-in capability of VP9 decoder to
upscale and downscale reference frames to match resolution of frame which is being encoded. By default SDK VP9 encoder inserts key-frame when
application does `Dynamic Resolution Change`_. In this case first frame with new resolution is encoded using Inter prediction from scaled
reference frame of previous resolution. Dynamic scaling has following limitation coming from VP9 specification: resolution of any active
reference frame cannot exceed 2x resolution of current frame, and can't be smaller than 1/16 of current frame resolution. In case of dynamic
scaling SDK VP9 encoder always uses single active reference frame for first frame after resolution change. So SDK VP9 encoder has following
limitation for dynamic resolution change: new resolution shouldn't exceed 16x and be below than 1/2 of current resolution.

Application may force insertion of key-frame at the place of resolution change by invoking encoder reset with
:cpp:member:`mfxExtEncoderResetOption::StartNewSequence` set to :cpp:enumerator:`MFX_CODINGOPTION_ON`. In case of inserted key-frame above limitations
for new resolution are not in force.

It should be noted that resolution change with dynamic reference scaling is compatible with multiref (:cpp:member:`mfxVideoParam::NumRefFrame` > 1).
For multiref configuration SDK VP9 encoder uses multiple references within stream pieces of same resolution, and uses single reference at
the place of resolution change.

Forced Key Frame Generation
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK supports forced key frame generation during encoding. The application can set the FrameType parameter of the :cpp:struct:`mfxEncodeCtrl`
structure to control how the current frame is encoded, as follows:

- If the SDK encoder works in the display order, the application can enforce any current frame to be a key frame. The application cannot change the
  frame type of already buffered frames inside the SDK encoder.
- If the SDK encoder works in the encoded order, the application must exactly specify frame type for every frame thus the application can enforce the
  current frame to have any frame type that particular coding standard allows.

Reference List Selection
~~~~~~~~~~~~~~~~~~~~~~~~

During streaming or video conferencing, if the application can obtain feedbacks about how good the client receives certain frames, the application
may need to adjust the encoding process to use or not use certain frames as reference. The following paragraphs describe how to fine-tune the
encoding process based on such feedbacks.

The application can specify the reference window size by specifying the parameter :cpp:member:`mfxInfoMFX::NumRefFrame` during encoding
initialization. Certain platform may have limitation on how big the size of the reference window is. Use the function
:cpp:func:`MFXVideoENCODE_GetVideoParam` to retrieve the current working set of parameters.

During encoding, the application can specify the actual reference list lengths by attaching the :cpp:struct:`mfxExtAVCRefListCtrl` structure to the
:cpp:func:`MFXVideoENCODE_EncodeFrameAsync` function. The :cpp:member:`mfxExtAVCRefListCtrl::NumRefIdxL0Active` member specifies the length of the
reference list L0 and the :cpp:member:`mfxExtAVCRefListCtrl::NumRefIdxL1Active` member specifies the length of the reference list L1.
These two numbers must be less or equal to the parameter :cpp:member:`mfxInfoMFX::NumRefFrame` during encoding initialization.

The application can instruct the SDK encoder to use or not use certain reference frames. To do this, there is a prerequisite that the application
must uniquely identify each input frame, by setting the :cpp:member:`mfxFrameData::FrameOrder` parameter. The application then specifies the
preferred reference frame list :cpp:member:`mfxExtAVCRefListCtrl::PreferredRefList` and/or the rejected frame list
:cpp:member:`mfxExtAVCRefListCtrl::RejectedRefList`, and attach the :cpp:struct:`mfxExtAVCRefListCtrl` structure to the
:cpp:func:`MFXVideoENCODE_EncodeFrameAsync` function. The two lists fine-tune how the SDK encoder chooses the reference frames of the current frame.
The SDK encoder does not keep **PreferredRefList** and application has to send it for each frame if necessary. There are a few limitations:

- The frames in the lists are ignored if they are out of the reference window.
- If by going through the lists, the SDK encoder cannot find a reference frame for the current frame, the SDK encoder will encode the current
  frame without using any reference frames.
- If the GOP pattern contains B-frames, the SDK encoder may not be able to follow the :cpp:struct:`mfxExtAVCRefListCtrl` instructions.

Low Latency Encoding and Decoding
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The application can set :cpp:member:`mfxVideoParam::AsyncDepth` = 1 to disable any decoder buffering of output frames, which is aimed to improve the
transcoding throughput. With :cpp:member:`mfxVideoParam::AsyncDepth` = 1, the application must synchronize after the decoding or transcoding
operation of each frame.

The application can adjust :cpp:member:`mfxExtCodingOption::MaxDecFrameBuffering`, during encoding initialization, to improve decoding latency.
It is recommended to set this value equal to number of reference frames.

Reference Picture Marking Repetition SEI message
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The application can request writing the reference picture marking repetition SEI message during encoding initialization, by setting the
:cpp:member:`mfxExtCodingOption::RefPicMarkRep` of the :cpp:struct:`mfxExtCodingOption` structure. The reference picture marking repetition SEI message
repeats certain reference frame information in the output bitstream for robust streaming.

The SDK decoder will respond to the reference picture marking repetition SEI message if such message exists in the bitstream, and check with the
reference list information specified in the sequence/picture headers. The decoder will report any mismatch of the SEI message with the reference
list information in the :cpp:member:`mfxFrameData::Corrupted` field.

Long-term Reference frame
~~~~~~~~~~~~~~~~~~~~~~~~~

The application may use long-term reference frames to improve coding efficiency or robustness for video conferencing applications. The application
controls the long-term frame marking process by attaching the :cpp:struct:`mfxExtAVCRefListCtrl` extended buffer during encoding. The SDK encoder
itself never marks frame as long-term.

There are two control lists in the :cpp:struct:`mfxExtAVCRefListCtrl` extended buffer. The :cpp:member:`mfxExtAVCRefListCtrl::LongTermRefList` list
contains the frame orders (the :cpp:member:`mfxFrameData::FrameOrder` value in the :cpp:struct:`mfxFrameData` structure) of the frames that should be
marked as long-term frames. The :cpp:member:`mfxExtAVCRefListCtrl::RejectedRefList` list contains the frame order of the frames that should be
unmarked as long-term frames. The application can only mark/unmark those frames that are buffered inside encoder. Because of this, it is recommended
that the application marks a frame when it is submitted for encoding. Application can either explicitly unmark long-term reference frame or wait for
IDR frame, there all long-term reference frames will be unmarked.

The SDK encoder puts all long-term reference frames at the end of a reference frame list. If the number of active reference frames (the
:cpp:member:`mfxExtAVCRefListCtrl::NumRefIdxL0Active` and :cpp:member:`mfxExtAVCRefListCtrl::NumRefIdxL1Active` values in the
:cpp:struct:`mfxExtAVCRefListCtrl` extended buffer) is smaller than the total reference frame number (the :cpp:member:`mfxInfoMFX::NumRefFrame` value
in the :cpp:struct:`mfxInfoMFX` structure during the encoding initialization), the SDK encoder may ignore some or all long term reference frames.
The application may avoid this by providing list of preferred reference frames in the :cpp:member:`mfxExtAVCRefListCtrl::PreferredRefList` list
in the :cpp:struct:`mfxExtAVCRefListCtrl` extended buffer. In this case, the SDK encoder reorders the reference list based on the specified list.

Temporal scalability
~~~~~~~~~~~~~~~~~~~~

The application may specify the temporal hierarchy of frames by using the :cpp:struct:`mfxExtAvcTemporalLayers` extended buffer during the encoder
initialization, in the display-order encoding mode. The SDK inserts the prefix NAL unit before each slice with a unique temporal and priority ID.
The temporal ID starts from zero and the priority ID starts from the :cpp:member:`mfxExtAvcTemporalLayers::BaseLayerPID` value. The SDK increases
the temporal ID and priority ID value by one for each consecutive layer.

If the application needs to specify a unique sequence or picture parameter set ID, the application must use the :cpp:struct:`mfxExtCodingOptionSPSPPS`
extended buffer, with all pointers and sizes set to zero and valid :cpp:member:`mfxExtCodingOptionSPSPPS::SPSId`/:cpp:member:`mfxExtCodingOptionSPSPPS::PPSId`
fields. The same SPS and PPS ID will be used for all temporal layers.

Each temporal layer is a set of frames with the same temporal ID. Each layer is defined by the :cpp:member:`mfxExtAvcTemporalLayers::Scale` value.
Scale for layer N is equal to ratio between the frame rate of subsequence consisted of temporal layers with temporal ID lower or equal to N and
frame rate of base temporal layer. The application may skip some of the temporal layers by specifying the :cpp:member:`mfxExtAvcTemporalLayers::Scale`
value as zero. The application should use an integer ratio of the frame rates for two consecutive temporal layers.

For example, 30 frame per second video sequence typically is separated by three temporal layers, that can be decoded as 7.5 fps (base layer),
15 fps (base and first temporal layer) and 30 fps (all three layers). :cpp:member:`mfxExtAvcTemporalLayers::Scale` for this case should have next
values {1,2,4,0,0,0,0,0}.