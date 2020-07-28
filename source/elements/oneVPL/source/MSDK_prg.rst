=================
Programming Guide
=================

This chapter describes the concepts used in programming with the oneVPL SDK.

The application must use the include file, **mfxvideo.h** for C/C++ programming
and link the SDK dispatcher library, **libmfx.so**.

Include these files:

.. code-block:: c++

   #include "mfxvideo.h"    /* The SDK include file */

Link this library:

.. code-block:: c++

   libmfx.so                /* The SDK dynamic dispatcher library (Linux\*) */

.. toctree::
   :hidden:

   MSDK_prg_stc
   MSDK_prg_session
   MSDK_prg_frame
   MSDK_prg_decoding
   MSDK_prg_encoding
   MSDK_prg_vpp
   MSDK_prg_transcoding
   MSDK_prg_hw
   MSDK_prg_mem
   MSDK_prg_err
