This chapter describes the concepts used in programming the SDK.

The application must use the include file, **mfxvideo.h** for C/C++ programming) and link the SDK dispatcher library, **libmfx.so**.

Include these files:

.. code-block:: c++

   #include "mfxvideo.h"    /* The SDK include file */

Link this library:

.. code-block:: c++

   libmfx.so                /* The SDK dynamic dispatcher library (Linux)*/

Status Codes
------------
.. include:: MSDK_prg_stc.rst

SDK Session
-----------
.. include:: MSDK_prg_session.rst

Frame and Fields
----------------
.. include:: MSDK_prg_frame.rst

Decoding Procedures
-------------------
.. include:: MSDK_prg_decoding.rst

Encoding Procedures
-------------------
.. include:: MSDK_prg_encoding.rst

Video Processing Procedures
---------------------------
.. include:: MSDK_prg_vpp.rst

Transcoding Procedures
---------------------------
.. include:: MSDK_prg_transcoding.rst

Working with hardware acceleration
----------------------------------
.. include:: MSDK_prg_hw.rst

Memory Allocation and External Allocators
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. include:: MSDK_prg_mem.rst

Hardware Device Error Handling
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. include:: MSDK_prg_err.rst

