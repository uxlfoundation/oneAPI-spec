:class:`vpl::VplParams` defines the parameter settings for decode, video process, encode
and DL inference. It addesses two separate aspects of video processing:

- Easy to use device independent parameter settings for VPL application developers
- Easy to translate into device dependent settings for hardware accelerators

This class provides common settings for video processing :class:`vpl::VplParams` such as 
input/output formats, resolutions, frame rates, crop factors, aspect ratios, and operation
specific settings :class:`vpl::VplParamsDecode` and :class:`vpl::VplParamsEncode`
such as codec type, input/output buffer sizes, encoding bit rate control, and GOP
structure parameters.

For VPL device plugin providers that support accelerators running autonomously on different nodes, 
the parameter settings will need to be passsed across host boundaries similar to 
gRPC. :class:`vpl::VplParams` will provide interface for serialization and deserialization
of the parameters as messages for this purpose. We are also evaluating general message
packages such as protobuf for future releases.

Note that vendor specific extensions can be supported by subclassing
:class:`vpl::VplParams` to expose them to VPL application developers.

