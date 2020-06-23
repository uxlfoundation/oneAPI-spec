The **DECODE** class of functions takes a compressed bitstream as input and converts it to raw frames as output.

**DECODE** processes only pure or elementary video streams. The library cannot process bitstreams
that reside in a container format, such as MP4 or MPEG. The application must first de-multiplex the bitstreams.
De-multiplexing extracts pure video streams out of the container format. The application can provide the input
bitstream as one complete frame of data, less than one frame (a partial frame), or multiple frames.
If only a partial frame is provided, **DECODE** internally constructs one frame of data before decoding it.

The time stamp of a bitstream buffer must be accurate to the first byte of the frame data. That is, the first byte of a video coding
layer NAL unit for H.264, or picture header for MPEG-2 and VC-1. **DECODE** passes the time stamp to the output surface for audio and
video multiplexing or synchronization.

Decoding the first frame is a special case, since **DECODE** does not provide enough configuration parameters to correctly process
the bitstream. **DECODE** searches for the sequence header (a sequence parameter set in H.264, or a sequence header in MPEG-2 and VC-1)
that contains the video configuration parameters used to encode subsequent video frames. The decoder skips any bitstream prior
to that sequence header. In the case of multiple sequence headers in the bitstream, **DECODE** adopts the new configuration parameters,
ensuring proper decoding of subsequent frames.

**DECODE** supports repositioning of the bitstream at any time during decoding. Because there is no way to obtain the correct
sequence header associated with the specified bitstream position after a position change, the application must supply **DECODE**
with a sequence header before the decoder can process the next frame at the new position. If the sequence header required to
correctly decode the bitstream at the new position is not provided by the application, **DECODE** treats the new location as a new
“first frame” and follows the procedure for decoding first frames.