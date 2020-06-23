Video processing (**VPP**) takes raw frames as input and provides raw frames as output.

.. graphviz::

  digraph {
    rankdir=LR;
    F1 [shape=record label="Function 1" ];
    F2 [shape=record  label="Function 2"];
    F3 [shape=record  label="Additional Filters"];
    F4 [shape=record label="Function N-1" ];
    F5 [shape=record  label="Function N"];
    F1->F2->F3->F4->F5;
  }


The actual conversion process is a chain operation with many single-function filters, as Figure 3 illustrates.
The application specifies the input and output format, and the SDK configures the pipeline accordingly.
The application can also attach one or more hint structures to configure individual filters or turn them on and off.
Unless specifically instructed, the SDK builds the pipeline in a way that best utilizes hardware acceleration or generates
the best video processing quality.

Table 1 shows the SDK video processing features. The application can configure supported video processing features through
the video processing I/O parameters. The application can also configure optional features through hints. See
“Video Processing procedure / Configuration” for more details on how to configure optional filters.

.. todo:: create link to “Video Processing procedure / Configuration”

=================================================================================   ====================================== 
Video Processing Features                                                           Configuration
=================================================================================   ====================================== 
Convert color format from input to output                                       	I/O parameters
De-interlace to produce progressive frames at the output                         	I/O parameters
Crop and resize the input frames                                                 	I/O parameters
Convert input frame rate to match the output	                                    I/O parameters
Perform inverse telecine operations	                                                I/O parameters
Fields weaving	                                                                    I/O parameters
Fields splitting	                                                                I/O parameters
Remove noise	                                                                    hint (optional feature)
Enhance picture details/edges	                                                    hint (optional feature)
Adjust the brightness, contrast, saturation, and hue settings	                    hint (optional feature)
Perform image stabilization	                                                        hint (optional feature)
Convert input frame rate to match the output, based on frame interpolation	        hint (optional feature)
Perform detection of picture structure	                                            hint (optional feature)
=================================================================================   ====================================== 

Color Conversion Support:

=============   ===========    ===========   ====    ====    ====    =======
Output Color>
Input Color   	NV12	       RGB32         P010    P210    NV16    A2RGB10
=============   ===========    ===========   ====    ====    ====    =======
RGB4 (RGB32)	X (limited)    X (limited)
NV12            X              X             X               X
YV12            X              X
UYVY            X
YUY2            X              X
P010            X                            X       X               X
P210            X                            X       X       X       X
NV16            X                                    X       X
=============   ===========    ===========   ====    ====    ====    =======

.. note:: 'X' indicates a supported function.

.. note:: The SDK video processing pipeline supports limited functionality for RGB4 input. Only filters that are
          required to convert input format to output one are included in pipeline. All optional filters are skipped.
          See description of :cpp:enumerator:`MFX_WRN_FILTER_SKIPPED` warning in :cpp:enum:`mfxStatus` enum for more details on how to retrieve list of active filters.

Deinterlacing/Inverse Telecine Support in **VPP**:

+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| Input Field Rate | Output Frame Rate | Output Frame Rate | Output Frame Rate | Output Frame Rate | Output Frame Rate | Output Frame Rate | Output Frame Rate |
| (fps)            | (fps)             | (fps)             | (fps)             | (fps)             | (fps)             | (fps)             | (fps)             |
| Interlaced	   | Progressive       | Progressive       | Progressive       | Progressive       | Progressive       | Progressive       | Progressive       |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| -                | 23.976            |  25               |  29.97            |  30               |  50               |   59.94           |  60               |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| 29.97	           |  Inverse Telecine |                   |  X                |                   |                   |                   |                   |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| 50	           |                   | X                 |                   |                   | X                 |                   |                   |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| 59.94	           |                   |                   |  X                |                   |                   | X                 |                   |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+
| 60	           |                   |                   |                   | X                 |                   |                   | X                 |
+------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+-------------------+

.. note:: 'X' indicates a supported function.

This table describes pure deinterlacing algorithm. The application can combine it with frame rate conversion to achieve
any desirable input/output frame rate ratio. Note, that in this table input rate is field rate, i.e. number of video fields
in one second of video. The SDK uses frame rate in all configuration parameters, so this input field rate should be divided
by two during the SDK configuration. For example, 60i to 60p conversion in this table is represented by right bottom cell.
It should be described in mfxVideoParam as input frame rate equal to 30 and output 60.

SDK support two HW-accelerated deinterlacing algorithms: BOB DI (in Linux’s libVA terms VAProcDeinterlacingBob) and
Advanced DI (VAProcDeinterlacingMotionAdaptive). Default is ADI (Advanced DI) which uses reference frames and has better quality.
BOB DI is faster than ADI mode. So user can select as usual between speed and quality.

User can exactly configure DI modes via :cpp:struct:`mfxExtVPPDeinterlacing`.

There is one special mode of deinterlacing available in combination with frame rate conversion. If VPP input frame is interlaced
(TFF or BFF) and output is progressive and ratio between source frame rate and destination frame rate is ½ (for example 30 to 60,
29.97 to 59.94, 25 to 50), special mode of VPP turned on: for 30 interlaced input frames application will get 60 different
progressive output frames

Color formats supported by **VPP** filters:

===================== ============    ====    ====    ====    ====    ====    ===
Color>
Filter                RGB4 (RGB32)    NV12    YV12    YUY2    P010    P210    NV1
===================== ============    ====    ====    ====    ====    ====    ===
Denoise                               X
MCTF                                  X
Deinterlace                           X
Image stabilization                   X
Frame rate conversion                 X
Resize                                X                       X       X       X
Detail                                X
Color conversion      X               X       X       X       X       X       X
Composition           X               X
Field copy                            X
Fields weaving                        X
Fields splitting                      X
===================== ============    ====    ====    ====    ====    ====    ===

.. note:: 'X' indicates a supported function.

.. note:: The SDK video processing pipeline supports limited HW acceleration for P010 format - zeroed mfxFrameInfo::Shift
          leads to partial acceleration.

.. todo:: create link to mfxFrameInfo::Shift

.. note:: The SDK video processing pipeline does not support HW acceleration for P210 format.

.. todo:: Keep or remove HW?