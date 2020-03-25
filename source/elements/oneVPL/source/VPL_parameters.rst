:class:`vpl::VplParams` defines the parameter settings for decode, video processing, encode
and DL inference. It addresses two aspects of video processing:

- Easy to use device independent parameter settings for VPL application developers
- Easy to translate into device dependent settings for VPL hardware plugin writers

This class provides common settings for video processing in :class:`vpl::VplParams`, such as 
input/output formats, resolutions, frame rates, crop factors, aspect ratios, and operation
specific settings in :class:`vpl::VplParamsDecode` and :class:`vpl::VplParamsEncode`,
such as CODEC type, input/output buffer sizes, encoding bit rate control, and GOP
structure parameters.

In the near future, oneVPL will support target devices running autonomously on different nodes,
where parameter settings need to be passed across host boundaries similar to 
gRPC. We will extend :class:`vpl::VplParams` to include serialization and deserialization
of the parameters as messages. We are also evaluating general message packages such as protobuf
as we finalize the API.

Note that vendor specific extensions can be supported by subclassing
:class:`vpl::VplParams` to expose them to oneVPL application developers.
