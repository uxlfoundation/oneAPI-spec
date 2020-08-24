================
Frame and Fields
================

In oneVPL terminology, a frame (also referred to as frame surface) contains either
a progressive frame or a complementary field pair. If the frame is a
complementary field pair, the odd lines of the surface buffer store the top
fields and the even lines of the surface buffer store the bottom fields.

.. _frame-surface-lock:

---------------------
Frame Surface Locking
---------------------

During encoding, decoding, or video processing, cases arise that require reserving
input or output frames for future use. For example, when decoding, a frame that
is ready for output must remain as a reference frame until the current sequence
pattern ends. The usual approach to manage this is to cache the frames internally.
This method requires a copy operation, which can significantly reduce performance.

oneVPL functions define a frame-locking mechanism to avoid the need for copy
operations. The frame-locking mechanism works as follows:

#. The application allocates a pool of frame surfaces large enough to include oneVPL
   function I/O frame surfaces and internal cache needs. Each frame surface
   maintains a ``Locked`` counter, which is part of the :cpp:struct:`mfxFrameData`
   structure. The ``Locked`` counter is initially set to zero.
#. The application calls a oneVPL function with frame surfaces from the pool, whose
   ``Locked`` counter is set as appropriate for the desired operation. For decoding
   or video processing operations, where oneVPL uses the surfaces to write, the
   ``Locked`` counter should be equal to zero. If the oneVPL function needs to reserve
   any frame surface, the oneVPL function increases the ``Locked`` counter of the frame
   surface. A non-zero ``Locked`` counter indicates that the calling application must
   treat the frame surface as “in use.” When the frame surface is in use, the
   application can read, but cannot alter, move, delete, or free the frame surface.
#. In subsequent oneVPL executions, if the frame surface is no longer in use,
   oneVPL decreases the ``Locked`` counter. When the ``Locked`` counter reaches zero, the
   application is free to do as it wishes with the frame surface.

In general, the application should not increase or decrease the ``Locked`` counter,
since oneVPL manages this field. If, for some reason, the application needs to
modify the ``Locked`` counter, the operation must be atomic to avoid a race condition.

oneVPL API version 2.0 introduces the :cpp:struct:`mfxFrameSurfaceInterface` structure
which provides a set of callback functions for the :cpp:struct:`mfxFrameSurface1`
structure to work with frame surfaces. This interface defines :cpp:struct:`mfxFrameSurface1` as a
reference counted object which can be allocated by oneVPL or the application. The
application must follow the general rules of operation with reference counted
objects. For example, when surfaces are allocated by oneVPL during
:cpp:func:`MFXVideoDECODE_DecodeFrameAsync` or with the help of
:cpp:func:`MFXMemory_GetSurfaceForVPP` or :cpp:func:`MFXMemory_GetSurfaceForEncode`,
the application must call the corresponding
:cpp:struct:`mfxFrameSurfaceInterface->(\*Release) <mfxFrameSurfaceInterface>`
function for the surfaces that are no longer in use.

Applications can use :cpp:struct:`mfxFrameSurfaceInterface` to manage a pool of frame 
surfaces.

.. attention:: Note that the ``Locked`` counter defines read/write access policies
               and the reference counter is responsible for managing a frame's
               lifetime.

.. note:: All :cpp:struct:`mfxFrameSurface1` structures starting from
          mfxFrameSurface1::mfxStructVersion = {1,1} support the
          :cpp:struct:`mfxFrameSurfaceInterface`.
