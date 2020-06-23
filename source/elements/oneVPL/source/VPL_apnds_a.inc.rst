The mfxFrameInfo structure is used by both the :cpp:struct:`mfxVideoParam` structure during SDK class initialization and the
:cpp:struct:`mfxFrameSurface1` structure during the actual SDK class function. The following constraints apply:

Constraints common for **DECODE**, **ENCODE** and **VPP**:

+--------------+---------------------------+---------------------------------------------------------------------------------------------+
| Parameters   | During SDK initialization | During SDK operation                                                                        |
+==============+===========================+=============================================================================================+
| FourCC       | Any valid value           | The value must be the same as the initialization value.                                     |
|              |                           |                                                                                             |
|              |                           | The only exception is **VPP** in composition mode, where in some cases it is allowed to     |
|              |                           |                                                                                             |
|              |                           | mix RGB and NV12 surfaces. See :cpp:struct:`mfxExtVPPComposite` for more details.           |
+--------------+---------------------------+---------------------------------------------------------------------------------------------+
| ChromaFormat | Any valid value           | The value must be the same as the initialization value.                                     |
+--------------+---------------------------+---------------------------------------------------------------------------------------------+

Constraints for **DECODE**:

+-------------------+-------------------------------------------------------------+------------------------------------------------------------+
| Parameters        | During SDK initialization                                   | During SDK operation                                       |
+===================+=============================================================+============================================================+
| Width             | Aligned frame size                                          | The values must be the equal to or larger than the         |
|                   |                                                             |                                                            |
| Height            |                                                             | initialization values.                                     |
+-------------------+-------------------------------------------------------------+------------------------------------------------------------+
| CropX, CropY      | Ignored                                                     | **DECODE** output. The cropping values are per-frame based.|
|                   |                                                             |                                                            |
| CropW, CropH      |                                                             |                                                            |
+-------------------+-------------------------------------------------------------+------------------------------------------------------------+
| AspectRatioW      | Any valid values or unspecified (zero); if unspecified,     | **DECODE** output.                                         |
|                   |                                                             |                                                            |
| AspectRatioH      | values from the input bitstream will be used;               |                                                            |
|                   |                                                             |                                                            |
|                   | see note below the table.                                   |                                                            |
+-------------------+-------------------------------------------------------------+------------------------------------------------------------+
| FrameRateExtN     | If unspecified, values from the input bitstream will be     | **DECODE** output.                                         |
|                   |                                                             |                                                            |
| FrameRateExtD     | used; see note below the table.                             |                                                            |
+-------------------+-------------------------------------------------------------+------------------------------------------------------------+
| PicStruct         | Ignored                                                     | **DECODE** output.                                         |
+-------------------+-------------------------------------------------------------+------------------------------------------------------------+

.. note:: Note about priority of initialization parameters.

.. note:: If application explicitly sets FrameRateExtN/FrameRateExtD or AspectRatioW/AspectRatioH during initialization then decoder uses these
          values during decoding regardless of values from bitstream and does not update them on new SPS. If application sets them to 0, then decoder
          uses values from stream and update them on each SPS.

Constraints for **VPP**:

+-------------------+----------------------------------------------+------------------------------------------------------------+
| Parameters        | During SDK initialization                    | During SDK operation                                       |
+===================+==============================================+============================================================+
| Width             | Any valid values                             | The values must be the equal to or larger than the         |
|                   |                                              |                                                            |
| Height            |                                              | initialization values.                                     |
+-------------------+----------------------------------------------+------------------------------------------------------------+
| CropX, CropY      | Ignored                                      | These parameters specify the region of interest            |
|                   |                                              |                                                            |
| CropW, CropH      |                                              | from input to output.                                      |
+-------------------+----------------------------------------------+------------------------------------------------------------+
| AspectRatioW      | Ignored                                      | Aspect ratio values will be passed through from            |
|                   |                                              |                                                            |
| AspectRatioH      |                                              | input to output.                                           |
+-------------------+----------------------------------------------+------------------------------------------------------------+
| FrameRateExtN     | Any valid values                             | Frame rate values will be updated with the                 |
|                   |                                              |                                                            |
| FrameRateExtD     |                                              | initialization value at output.                            |
+-------------------+----------------------------------------------+------------------------------------------------------------+
| PicStruct         | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`      | The base value must be the same as the                     |
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE`  | initialization value unless                                |
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF`    | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN` is specified during|
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`    | initialization.                                            |
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_SINGLE` | Other decorative picture structure flags are               |
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TOP`    | passed through or added as needed. See the                 |
|                   |                                              |                                                            |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BOTTOM` | `PicStruct`_ enumerator for details.                       |
+-------------------+----------------------------------------------+------------------------------------------------------------+

Constraints for **ENCODE**:

+-------------------+----------------------------------------------+---------------------------------------------------------------------------+
| Parameters        | During SDK initialization                    | During SDK operation                                                      |
+===================+==============================================+===========================================================================+
| Width             | Encoded frame size                           | The values must be the equal to or larger than the                        |
|                   |                                              |                                                                           |
| Height            |                                              | initialization values.                                                    |
+-------------------+----------------------------------------------+---------------------------------------------------------------------------+
| CropX, CropY      | H.264: Cropped frame size                    | Ignored                                                                   |
|                   |                                              |                                                                           |
|                   | MPEG-2: CropW and CropH                      |                                                                           |
|                   |                                              |                                                                           |
| CropW, CropH      | specify the real width and height            |                                                                           |
|                   |                                              |                                                                           |
|                   | (maybe unaligned) of the coded               |                                                                           |
|                   |                                              |                                                                           |
|                   | frames. CropX and CropY                      |                                                                           |
|                   |                                              |                                                                           |
|                   | must be zero.                                |                                                                           |
+-------------------+----------------------------------------------+---------------------------------------------------------------------------+
| AspectRatioW      | Any valid values                             | Ignored                                                                   |
|                   |                                              |                                                                           |
| AspectRatioH      |                                              |                                                                           |
+-------------------+----------------------------------------------+---------------------------------------------------------------------------+
| FrameRateExtN     | Any valid values                             | Ignored                                                                   |
|                   |                                              |                                                                           |
| FrameRateExtD     |                                              |                                                                           |
+-------------------+----------------------------------------------+---------------------------------------------------------------------------+
| PicStruct         | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`      | The base value must be the same as the                                    |
|                   |                                              |                                                                           |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE`  | initialization value unless                                               |
|                   |                                              |                                                                           |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF`    | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN` is specified during               |
|                   |                                              |                                                                           |
|                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`    | initialization.                                                           |
|                   |                                              |                                                                           |
|                   |                                              | Add other decorative picture structure flags to indicate                  |
|                   |                                              |                                                                           |
|                   |                                              | additional display attributes. Use :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`|
|                   |                                              |                                                                           |
|                   |                                              | during initialization for field attributes and                            |
|                   |                                              |                                                                           |
|                   |                                              | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE` for frame attributes. See the |
|                   |                                              |                                                                           |
|                   |                                              | `PicStruct`_ enumerator for details.                                      |
+-------------------+----------------------------------------------+---------------------------------------------------------------------------+

The following table summarizes how to specify the configuration parameters during initialization and during encoding, decoding and video processing:

=========================== =============== =================== =============== =================== ============ ==================
Structure (param)           **ENCODE** Init **ENCODE** Encoding **DECODE** Init **DECODE** Decoding **VPP** Init **VPP** Processing
=========================== =============== =================== =============== =================== ============ ==================
:cpp:struct:`mfxVideoParam`	   					
   Protected                R               -                   R               -                   R            -
   IOPattern                M               -                   M               -                   M            -
   ExtParam                 O               -                   O               -                   O            -
   NumExtParam              O               -                   O               -                   O            -
:cpp:struct:`mfxInfoMFX`						
   CodecId                  M               -                   M               -                   -            -
   CodecProfile             O               -                   O/M*            -                   -            -
   CodecLevel               O               -                   O               -                   -            -
   NumThread                O               -                   O               -                   -            -
   TargetUsage              O               -                   -               -                   -            -
   GopPicSize               O               -                   -               -                   -            -
   GopRefDist               O               -                   -               -                   -            -
   GopOptFlag               O               -                   -               -                   -            -
   IdrInterval              O               -                   -               -                   -            -
   RateControlMethod        O               -                   -               -                   -            -
   InitialDelayInKB         O               -                   -               -                   -            -
   BufferSizeInKB           O               -                   -               -                   -            -
   TargetKbps               M               -                   -               -                   -            -
   MaxKbps                  O               -                   -               -                   -            -
   NumSlice                 O               -                   -               -                   -            -
   NumRefFrame              O               -                   -               -                   -            -
   EncodedOrder             M               -                   -               -                   -            -
:cpp:struct:`mfxFrameInfo`						
   FourCC                   M               M                   M               M                   M            M
   Width                    M               M                   M               M                   M            M
   Height                   M               M                   M               M                   M            M
   CropX                    M               Ign                 Ign             U                   Ign          M
   CropY                    M               Ign                 Ign             U                   Ign          M
   CropW                    M               Ign                 Ign             U                   Ign          M
   CropH                    M               Ign                 Ign             U                   Ign          M
   FrameRateExtN            M               Ign                 O               U                   M            U
   FrameRateExtD            M               Ign                 O               U                   M            U
   AspectRatioW             O               Ign                 O               U                   Ign          PT
   AspectRatioH             O               Ign                 O               U                   Ign          PT
   PicStruct                O               M                   Ign             U                   M            M/U
   ChromaFormat             M               M                   M               M                   Ign          Ign
=========================== =============== =================== =============== =================== ============ ==================

Table Legend:

======= =================
Remarks
======= =================
Ign     Ignored
PT      Pass Through
-       Does Not Apply
M       Mandated
R       Reserved
O       Optional
U       Updated at output
======= =================

.. note:: `CodecProfile`_ is mandated for HEVC REXT and SCC profiles and optional for other cases. If application doesn't explicitly set
          `CodecProfile`_ during initialization, HEVC decoder will use profile up to Main10.