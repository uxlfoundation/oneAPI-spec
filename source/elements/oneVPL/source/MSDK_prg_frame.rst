In SDK terminology, a frame (or frame surface, interchangeably) contains either a progressive frame or a complementary field pair.
If the frame is a complementary field pair, the odd lines of the surface buffer store the top fields and the even lines of the
surface buffer store the bottom fields.

Frame Surface Locking
~~~~~~~~~~~~~~~~~~~~~

During encoding, decoding or video processing, cases arise that require reserving input or output frames for future use.
In the case of decoding, for example, a frame that is ready for output must remain as a reference frame until the current
sequence pattern ends. The usual approach is to cache the frames internally. This method requires a copy operation, which
can significantly reduce performance.

SDK functions define a frame-locking mechanism to avoid the need for copy operations. This mechanism is as follows:

- The application allocates a pool of frame surfaces large enough to include SDK function I/O frame surfaces and internal
  cache needs. Each frame surface maintains a Locked counter, part of the mfxFrameData structure. Initially, the Locked
  counter is set to zero.
- The application calls an SDK function with frame surfaces from the pool, whose Locked counter is set as appropriate: for decoding or video processing 
  operations where the SDK   uses the surfaces to write it should be equal to zero.  If the SDK  function needs to reserve any frame surface, 
  the SDK function increases the Locked counter of the frame surface.
  A non-zero Locked counter indicates that the calling application must treat the frame surface as “in use.” That is,
  the application can read, but cannot alter, move, delete or free the frame surface.
- In subsequent SDK executions, if the frame surface is no longer in use, the SDK decreases the Locked counter.
  When the Locked counter reaches zero, the application is free to do as it wishes with the frame surface.

In general, the application must not increase or decrease the Locked counter, since the SDK manages this field. If,
for some reason, the application needs to modify the Locked counter, the operation must be atomic to avoid race condition.

.. attention:: Modifying the Locked counter is not recommended.

Starting from API version 2.0 mfxFrameSurfaceInterface structure as a set of callback functions was introduced for mfxFrameSurface1 to work with frames.
This interface defines mfxFrameSurface1 as a reference counted object which can be allocated by the SDK or application. Application has to follow the general rules of operations 
with reference countend objects. As example, when surfaces are allocated by the SDK during MFXVideoDECODE_DecodeFrameAsync or with help of 
MFXMemory_GetSurfaceForVPP, MFXMemory_GetSurfaceForEncode, application has to call correspondent mfxFrameSurfaceInterface->(\*Release) for the surfaces whose are no longer in use.

.. attention:: Need to distinguish Locked counter which defines read/write access polices and reference counter responsible for managing frames' lifetime.

.. note:: all mfxFrameSurface1 structures starting from mfxFrameSurface1::mfxStructVersion = {1,1} supports mfxFrameSurfaceInterface.
