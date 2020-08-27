=================
Programming Guide
=================

This chapter describes the concepts used in programming with oneVPL.

The application must use the include file :file:`mfxvideo.h` for C/C++ programming
and link the oneVPL dispatcher library :file:`libmfx.so`.

Include these files:

.. code-block:: c++

   #include "mfxvideo.h"    /* oneVPL include file */

Link this library:

.. code-block:: c++

   libmfx.so                /* oneVPL dynamic dispatcher library (Linux\*) */

.. toctree::
   :hidden:

   VPL_prg_stc
   VPL_prg_session
   VPL_prg_frame
   VPL_prg_decoding
   VPL_prg_encoding
   VPL_prg_vpp
   VPL_prg_transcoding
   VPL_prg_hw
   VPL_prg_mem
   VPL_prg_err
