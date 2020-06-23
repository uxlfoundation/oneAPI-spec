The SDK takes care of all memory and synchronization related operations in VA API. However, in some cases the application may need to extend the
SDK functionality by working directly with VA API for Linux*. For example, to implement customized external allocator. This chapter describes some
basic memory management and synchronization techniques.

To create VA surface pool the application should call vaCreateSurfaces:

.. code-block:: c++

   VASurfaceAttrib attrib;
   attrib.type = VASurfaceAttribPixelFormat;
   attrib.value.type = VAGenericValueTypeInteger;
   attrib.value.value.i = VA_FOURCC_NV12;
   attrib.flags = VA_SURFACE_ATTRIB_SETTABLE;

   #define NUM_SURFACES 5;
   VASurfaceID surfaces[NUMSURFACES];

   vaCreateSurfaces(va_display, VA_RT_FORMAT_YUV420, width, height, surfaces, NUM_SURFACES, &attrib, 1);

To destroy surface pool the application should call vaDestroySurfaces:

.. code-block:: c++

   vaDestroySurfaces(va_display, surfaces, NUM_SURFACES);

If the application works with hardware acceleration through the SDK then it can access surface data immediately after successful completion of
:cpp:func:`MFXVideoCORE_SyncOperation` call. If the application works with hardware acceleration directly then it has to check surface status
before accessing data in video memory. This check can be done asynchronously by calling vaQuerySurfaceStatus function or synchronously by
vaSyncSurface function.

After successful synchronization the application can access surface data. It is performed in two steps. At the first step VAImage is created
from surface and at the second step image buffer is mapped to system memory. After mapping VAImage.offsets[3] array holds offsets to each color
plain in mapped buffer and VAImage.pitches[3] array holds color plain pitches, in bytes. For packed data formats, only first entries in these
arrays are valid. How to access data in NV12 surface:

.. code-block:: c++
   
   VAImage image;
   unsigned char *buffer, Y, U, V;

   vaDeriveImage(va_display, surface_id, &image);
   vaMapBuffer(va_display, image.buf, &buffer);

   /* NV12 */
   Y = buffer + image.offsets[0];
   U = buffer + image.offsets[1];
   V = U + 1;


After processing data in VA surface the application should release resources allocated for mapped buffer and VAImage object:

.. code-block:: c++

   vaUnmapBuffer(va_display, image.buf);
   vaDestroyImage(va_display, image.image_id);

In some cases, for example, to retrieve encoded bitstream from video memory, the application has to use VABuffer to store data. Example below shows
how to create, use and then destroy VA buffer. Note, that vaMapBuffer function returns pointers to different objects depending on mapped buffer type.
It is plain data buffer for VAImage and VACodedBufferSegment structure for encoded bitstream. The application cannot use VABuffer for
synchronization and in case of encoding it is recommended to synchronize by input VA surface as described above.

.. code-block:: c++

   /* create buffer */
   VABufferID buf_id;
   vaCreateBuffer(va_display, va_context, VAEncCodedBufferType, buf_size, 1, NULL, & buf_id);

   /* encode frame */
   // ...

   /* map buffer */
   VACodedBufferSegment *coded_buffer_segment;

   vaMapBuffer(va_display, buf_id, (void **)(& coded_buffer_segment));

   size   = coded_buffer_segment->size;
   offset = coded_buffer_segment->bit_offset;
   buf    = coded_buffer_segment->buf;

   /* retrieve encoded data*/
   // ...

   /* unmap and destroy buffer */
   vaUnmapBuffer(va_display, buf_id);
   vaDestroyBuffer(va_display, buf_id);

