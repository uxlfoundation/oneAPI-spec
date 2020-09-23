.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

========================================
Working Directly with VA API for Linux\*
========================================

|msdk_full_name| takes care of all memory and synchronization related operations in the VA API.
The application may need to extend |msdk_full_name| functionality by working directly
with the VA API for Linux\*, for example to implement a customized external allocator.
This section describes basic memory management and synchronization techniques.

To create the VA surface pool, the application should call the vaCreateSurfaces
function:

.. code-block:: c++
   :lineno-start: 1

   VASurfaceAttrib attrib;
   attrib.type = VASurfaceAttribPixelFormat;
   attrib.value.type = VAGenericValueTypeInteger;
   attrib.value.value.i = VA_FOURCC_NV12;
   attrib.flags = VA_SURFACE_ATTRIB_SETTABLE;

   #define NUM_SURFACES 5;
   VASurfaceID surfaces[NUMSURFACES];

   vaCreateSurfaces(va_display, VA_RT_FORMAT_YUV420, width, height, surfaces, NUM_SURFACES, &attrib, 1);

To destroy the surface pool, the application should call the vaDestroySurfaces
function:

.. code-block:: c++
   :lineno-start: 1

   vaDestroySurfaces(va_display, surfaces, NUM_SURFACES);

If the application works with hardware acceleration through |msdk_full_name|, then it can
access surface data immediately after successful completion of
the :cpp:func:`MFXVideoCORE_SyncOperation` call. If the application works with
hardware acceleration directly, then it must check surface status before
accessing data in video memory. This check can be done asynchronously by calling
the vaQuerySurfaceStatus function or synchronously by calling the vaSyncSurface
function.

After successful synchronization, the application can access surface data.
Accessing surface data is performed in two steps:

#. Create VAImage from surface.
#. Map image buffer to system memory.

After mapping, the VAImage.offsets[3] array holds offsets to each color
plain in a mapped buffer and the VAImage.pitches[3] array holds color plain
pitches in bytes. For packed data formats, only first entries in these
arrays are valid. The following example shows how to access data in a NV12 surface:

.. code-block:: c++
   :lineno-start: 1

   VAImage image;
   unsigned char *buffer, Y, U, V;

   vaDeriveImage(va_display, surface_id, &image);
   vaMapBuffer(va_display, image.buf, &buffer);

   /* NV12 */
   Y = buffer + image.offsets[0];
   U = buffer + image.offsets[1];
   V = U + 1;


After processing data in a VA surface, the application should release resources
allocated for the mapped buffer and VAImage object:

.. code-block:: c++
   :lineno-start: 1

   vaUnmapBuffer(va_display, image.buf);
   vaDestroyImage(va_display, image.image_id);

In some cases, in order to retrieve encoded bitstream data from video memory,
the application must use the VABuffer to store data. The following example shows
how to create, use, and destroy the VABuffer:

.. code-block:: c++
   :lineno-start: 1

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

Note that the vaMapBuffer function returns pointers to different objects
depending on the mapped buffer type. The VAImage is a plain data buffer and the
encoded bitstream is a VACodedBufferSegment structure. The application cannot use
VABuffer for synchronization. If encoding, it is recommended to synchronize
using the VA surface as described above.
