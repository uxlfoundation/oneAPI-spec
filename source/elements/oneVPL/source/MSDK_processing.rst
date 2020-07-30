================
Video Processing
================

Video processing functions (:term:`VPP`) take raw frames as input and provide
raw frames as output.

The actual conversion process is a chain operation with many single-function
filters, as shown in Figure 3.

.. graphviz::
   :caption: Figure 3: Video processing operation pipeline

   digraph {
     rankdir=LR;
     F1 [shape=record label="Function 1" ];
     F2 [shape=record  label="Function 2"];
     F3 [shape=record  label="Additional Filters"];
     F4 [shape=record label="Function N-1" ];
     F5 [shape=record  label="Function N"];
     F1->F2->F3->F4->F5;
   }

The application specifies the input and output format and the SDK configures the
pipeline accordingly. The application can also attach one or more hint structures
to configure individual filters or turn them on and off. Unless specifically
instructed, the SDK builds the pipeline in a way that best utilizes hardware
acceleration or generates the best video processing quality.

The :ref:`Video Processing Features table <vid-processing-feat-table>` shows SDK
video processing features. The application can configure supported video
processing features through the video processing I/O parameters. The application
can also configure optional features through hints.
See :ref:`Video Processing Procedures <vid_process_procedure>` for more details
on how to configure optional filters.

.. _vid-processing-feat-table:

.. table:: Video Processing Features

   =================================================================================   =====================================
   Video Processing Features                                                           Configuration
   =================================================================================   =====================================
   Convert color format from input to output                                           I/O parameters
   De-interlace to produce progressive frames at the output                            I/O parameters
   Crop and resize the input frames                                                    I/O parameters
   Convert input frame rate to match the output                                        I/O parameters
   Perform inverse telecine operations                                                 I/O parameters
   Fields weaving                                                                      I/O parameters
   Fields splitting                                                                    I/O parameters
   Remove noise                                                                        hint (optional feature)
   Enhance picture details/edges                                                       hint (optional feature)
   Adjust the brightness, contrast, saturation, and hue settings                       hint (optional feature)
   Perform image stabilization                                                         hint (optional feature)
   Convert input frame rate to match the output, based on frame interpolation          hint (optional feature)
   Perform detection of picture structure                                              hint (optional feature)
   =================================================================================   =====================================

------------------------
Color Conversion Support
------------------------

The :ref:`Color Conversion Support table <color-conversion-table>` shows
color conversion supported by VPP. 'X' indicates a supported function.

.. _color-conversion-table:

.. table:: Color Conversion Support

   =============   ===========    ===========   ====    ====    ====    =======
   Output Color>
   Input Color     NV12           RGB32         P010    P210    NV16    A2RGB10
   =============   ===========    ===========   ====    ====    ====    =======
   RGB4 (RGB32)    X (limited)    X (limited)
   NV12            X              X             X               X
   YV12            X              X
   UYVY            X
   YUY2            X              X
   P010            X                            X       X               X
   P210            X                            X       X       X       X
   NV16            X                                    X       X
   =============   ===========    ===========   ====    ====    ====    =======

.. note:: The SDK video processing pipeline supports limited functionality for
          RGB4 input. Only filters that are required to convert input format to
          output one are included in the pipeline. All optional filters are
          skipped. See description of the :cpp:enumerator:`MFX_WRN_FILTER_SKIPPED`
          warning in the :cpp:enum:`mfxStatus` enum for more details on how to
          retrieve list of active filters.

--------------------------------------
Deinterlacing/Inverse Telecine Support
--------------------------------------

The :ref:`Deinterlacing/Inverse Telecine Support table <telecine-support-table>`
shows deinterlacing/inverse telecine support in :term:`VPP`. 'X' indicates a supported
function.

.. _telecine-support-table:

.. table:: Deinterlacing/Inverse Telecine Support

   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | Input Field Rate | Output Frame Rate                                                 |
   | (fps)            | (fps)                                                             |
   | Interlaced	      | Progressive                                                       |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | -                | 23.976            | 25    | 29.97 | 30    | 50    | 59.94 | 60    |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | 29.97            | Inverse Telecine  |       | X     |       |       |       |       |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | 50               |                   | X     |       |       | X     |       |       |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | 59.94            |                   |       | X     |       |       | X     |       |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+
   | 60               |                   |       |       | X     |       |       | X     |
   +------------------+-------------------+-------+-------+-------+-------+-------+-------+

The table describes a pure deinterlacing algorithm. The application can combine
the algorithm with frame rate conversion to achieve any desirable input or output
frame rate ratio. Note that in this table input rate is field rate, which is the
number of video fields in one second of video. Because the SDK uses frame rate
in all configuration parameters, this input field rate should be divided by two
during the SDK configuration. For example, a 60i to 60p conversion is shown in the
right bottom cell of the table. It should be described in the
:cpp:struct:`mfxVideoParam` structure as input frame rate equal to 30 and output
60.

The SDK supports two hardware accelerated deinterlacing algorithms: BOB DI (in
Linux\* libVA terms, VAProcDeinterlacingBob) and Advanced DI
(VAProcDeinterlacingMotionAdaptive). Default is ADI (Advanced DI) which uses
reference frames and has better quality. BOB DI is faster than ADI mode. The user
can select between speed and quality as needed.

Configure DI modes with the :cpp:struct:`mfxExtVPPDeinterlacing` structure.

There is one special mode of deinterlacing available in combination with frame
rate conversion. If VPP input frame is interlaced (TFF or BFF), output is
progressive, and the ratio between source frame rate and destination frame rate
is ½ (for example 30 to 60, 29.97 to 59.94, 25 to 50), a special mode of VPP is
turned on: For 30 interlaced input frames, the application will get 60 different
progressive output frames.

--------------------
Color Format Support
--------------------

The :ref:`VPP Filter Color Format Support table <color-format-table>` shows
color formats supported by :term:`VPP` filters. 'X' indicates a supported function.

.. _color-format-table:

.. table:: VPP Filter Color Format Support

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


.. note:: The SDK video processing pipeline supports limited hardware acceleration
          for the P010 format. A zero value for the :cpp:member:`mfxFrameInfo::Shift` field leads to partial acceleration.

          The SDK video processing pipeline does not support hardware
          acceleration for the P210 format.
