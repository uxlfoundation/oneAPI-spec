===================================
Configuration Parameter Constraints
===================================

The mfxFrameInfo structure is used by both the :cpp:struct:`mfxVideoParam`
structure during SDK class initialization and the :cpp:struct:`mfxFrameSurface1`
structure during the actual SDK class function. The parameter constraints
described in the following tables apply.

-----------------------------------
DECODE, ENCODE, and VPP Constraints
-----------------------------------

The :ref:`DECODE, ENCODE, and VPP Constraints table <common-constraint-table>`
lists parameter constraints common to :term:`DECODE`, :term:`ENCODE`, and
:term:`VPP`.

.. _common-constraint-table:

.. table:: DECODE, ENCODE, and VPP Constraints

    +--------------+---------------------------+-----------------------------------------------------------+
    | Parameters   | During SDK Initialization | During SDK Operation                                      |
    +==============+===========================+===========================================================+
    | FourCC       | Any valid value           | The value must be the same as the initialization value.   |
    |              |                           | The only exception is :term:`VPP` in composition mode,    |
    |              |                           | where in some cases it is allowed to mix RGB and NV12     |
    |              |                           | surfaces. See :cpp:struct:`mfxExtVPPComposite` for more   |
    |              |                           | details.                                                  |
    +--------------+---------------------------+-----------------------------------------------------------+
    | ChromaFormat | Any valid value           | The value must be the same as the initialization value.   |
    +--------------+---------------------------+-----------------------------------------------------------+

------------------
DECODE Constraints
------------------

The :ref:`DECODE Constraints table <decode-constraint-table>` lists :term:`DECODE`
parameter constraints.

.. _decode-constraint-table:

.. table:: DECODE Constraints

    +---------------+-----------------------------------------+----------------------------------------+
    | Parameters    | During SDK initialization               | During SDK operation                   |
    +===============+=========================================+========================================+
    | Width         | Aligned frame size                      | The values must be the equal to or     |
    |               |                                         | larger than the initialization values. |
    | Height        |                                         |                                        |
    +---------------+-----------------------------------------+----------------------------------------+
    | CropX, CropY  | Ignored                                 | :term:`DECODE` output. The cropping    |
    |               |                                         | values are per-frame based.            |
    | CropW, CropH  |                                         |                                        |
    +---------------+-----------------------------------------+----------------------------------------+
    | AspectRatioW  | Any valid values or unspecified (zero); | DECODE output.                         |
    |               | if unspecified, values from the input   |                                        |
    | AspectRatioH  | bitstream will be used.                 |                                        |
    |               | See note below the table.               |                                        |
    +---------------+-----------------------------------------+----------------------------------------+
    | FrameRateExtN | If unspecified, values from the input   | DECODE output.                         |
    |               | bitstream will be used.                 |                                        |
    | FrameRateExtD | See note below the table.               |                                        |
    +---------------+-----------------------------------------+----------------------------------------+
    | PicStruct     | Ignored                                 | DECODE output.                         |
    +---------------+-----------------------------------------+----------------------------------------+

.. note:: If the application explicitly sets FrameRateExtN/FrameRateExtD or
          AspectRatioW/AspectRatioH during initialization, then the decoder will
          use these values during decoding regardless of the values from bitstream
          and does not update them on new SPS. If the application sets them to 0,
          then the decoder uses values from the stream and updates them on each SPS.

------------------
ENCODE Constraints
------------------

The :ref:`ENCODE Constraints table <encode-constraint-table>` lists :term:`ENCODE`
parameter constraints.

.. _encode-constraint-table:

.. table:: ENCODE Constraints

    +-------------------+----------------------------------------------+---------------------------------------------+
    | Parameters        | During SDK initialization                    | During SDK operation                        |
    +===================+==============================================+=============================================+
    | Width             | Encoded frame size                           | The values must be the equal to or larger   |
    |                   |                                              | than the initialization values.             |
    | Height            |                                              |                                             |
    +-------------------+----------------------------------------------+---------------------------------------------+
    | CropX, CropY      | H.264: Cropped frame size                    | Ignored                                     |
    |                   | MPEG-2: CropW and CropH                      |                                             |
    |                   |                                              |                                             |
    | CropW, CropH      | Specify the real width and height            |                                             |
    |                   | (maybe unaligned) of the coded frames.       |                                             |
    |                   | CropX and CropY must be zero.                |                                             |
    +-------------------+----------------------------------------------+---------------------------------------------+
    | AspectRatioW      | Any valid values                             | Ignored                                     |
    |                   |                                              |                                             |
    | AspectRatioH      |                                              |                                             |
    +-------------------+----------------------------------------------+---------------------------------------------+
    | FrameRateExtN     | Any valid values                             | Ignored                                     |
    |                   |                                              |                                             |
    | FrameRateExtD     |                                              |                                             |
    +-------------------+----------------------------------------------+---------------------------------------------+
    | PicStruct         | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`      | The base value must be the same as the      |
    |                   |                                              | initialization value unless                 |
    |                   | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE`  | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`     |
    |                   |                                              | is specified during initialization.         |
    |                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF`    | Add other decorative picture structure      |
    |                   |                                              | flags to indicate additional display        |
    |                   | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`    | attributes. Use                             |
    |                   |                                              | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`     |
    |                   |                                              | during initialization for field             |
    |                   |                                              | attributes and                              |
    |                   |                                              | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE` |
    |                   |                                              | for frame attributes. See the               |
    |                   |                                              | :ref:`PicStruct` enumerator for details.    |
    +-------------------+----------------------------------------------+---------------------------------------------+

---------------
VPP Constraints
---------------

The :ref:`VPP Constraints table <vpp-constraint-table>` lists :term:`VPP`
parameter constraints.

.. _vpp-constraint-table:

.. list-table:: VPP Constraints
   :header-rows: 1
   :widths: 20 25 55

   * - Parameters
     - During SDK initialization
     - During SDK operation
   * - Width, Height
     - Any valid values
     - The values must be the equal to or larger than the initialization values.
   * - | CropX, CropY,
       | CropW, CropH
     - Ignored
     - These parameters specify the region of interest from input to output.
   * - | AspectRatioW
       | AspectRatioH
     - Ignored
     - Aspect ratio values will be passed through from input to output.
   * - | FrameRateExtN
       | FrameRateExtD
     - Any valid values
     - Frame rate values will be updated with the initialization value at output.
   * - PicStruct
     - | :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN`
       | :cpp:enumerator:`MFX_PICSTRUCT_PROGRESSIVE`
       | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TFF`
       | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BFF`
       | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_SINGLE`
       | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_TOP`
       | :cpp:enumerator:`MFX_PICSTRUCT_FIELD_BOTTOM`
     - The base value must be the same as the initialization value unless
       :cpp:enumerator:`MFX_PICSTRUCT_UNKNOWN` is specified during initialization.
       Other decorative picture structure flags are passed through or added as
       needed. See the :ref:`PicStruct` enumerator for details.

-----------------------------------
Specifying Configuration Parameters
-----------------------------------

The :ref:`Configuration Parameters table <config-param-table>` summarizes how to specify the configuration
parameters during initialization, encoding, decoding, and video processing.

.. _config-param-table:

.. table:: Configuration Parameters

   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   | **Structure (param)** | **ENCODE** | **ENCODE**   | **DECODE** | **DECODE**   | **VPP**  | **VPP**        |
   |                       | **Init**   | **Encoding** | **Init**   | **Decoding** | **Init** | **Processing** |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   | :cpp:struct:`mfxVideoParam`                                                                               |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  Protected            | R          | -            | R          | -            | R        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  IOPattern            | M          | -            | M          | -            | M        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  ExtParam             | O          | -            | O          | -            | O        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  NumExtParam          | O          | -            | O          | -            | O        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   | :cpp:struct:`mfxInfoMFX`                                                                                  |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CodecId              | M          | -            | M          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CodecProfile         | O          | -            | O/M\*      | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CodecLevel           | O          | -            | O          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  NumThread            | O          | -            | O          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  TargetUsage          | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  GopPicSize           | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  GopRefDist           | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  GopOptFlag           | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  IdrInterval          | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  RateControlMethod    | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  InitialDelayInKB     | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  BufferSizeInKB       | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  TargetKbps           | M          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  MaxKbps              | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  NumSlice             | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  NumRefFrame          | O          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  EncodedOrder         | M          | -            | -          | -            | -        | -              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   | :cpp:struct:`mfxFrameInfo`                                                                                |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  FourCC               | M          | M            | M          | M            | M        | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  Width                | M          | M            | M          | M            | M        | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  Height               | M          | M            | M          | M            | M        | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CropX                | M          | Ign          | Ign        | U            | Ign      | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CropY                | M          | Ign          | Ign        | U            | Ign      | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CropW                | M          | Ign          | Ign        | U            | Ign      | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  CropH                | M          | Ign          | Ign        | U            | Ign      | M              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  FrameRateExtN        | M          | Ign          | O          | U            | M        | U              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  FrameRateExtD        | M          | Ign          | O          | U            | M        | U              |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  AspectRatioW         | O          | Ign          | O          | U            | Ign      | PT             |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  AspectRatioH         | O          | Ign          | O          | U            | Ign      | PT             |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  PicStruct            | O          | M            | Ign        | U            | M        | M/U            |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+
   |  ChromaFormat         | M          | M            | M          | M            | Ign      | Ign            |
   +-----------------------+------------+--------------+------------+--------------+----------+----------------+

Legend for the :ref:`Configuration Parameters table <config-param-table>`:

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

.. note:: :ref:`CodecProfile` is mandated for HEVC REXT and SCC profiles and optional
          for other cases. If the application doesn't explicitly set CodecProfile
          during initialization, the HEVC decoder will use a profile up to Main10.