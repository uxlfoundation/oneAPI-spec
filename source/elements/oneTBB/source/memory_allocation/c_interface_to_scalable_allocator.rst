=================================
C Interface to Scalable Allocator
=================================


Summary
-------

Low level interface for scalable memory allocation.

Syntax
------

.. code:: cpp

   extern "C" {
       // Scalable analogs of C memory allocator
       void* scalable_malloc( size_t size );
       void  scalable_free( void* ptr );
       void* scalable_calloc( size_t nobj, size_t size );
       void* scalable_realloc( void* ptr, size_t size );
   
       // Analog of _msize/malloc_size/malloc_usable_size.
       size_t scalable_msize( void* ptr );
   
       // Scalable analog of posix_memalign
       int scalable_posix_memalign( void** memptr, size_t alignment, size_t size );
   
       // Aligned allocation
       void* scalable_aligned_malloc( size_t size, size_t alignment);
       void scalable_aligned_free( void* ptr ); 
       void* scalable_aligned_realloc( void* ptr, size_t size, size_t alignment );
   
       // Return values for scalable_allocation_* functions
       typedef enum {
           TBBMALLOC_OK,
           TBBMALLOC_INVALID_PARAM,
           TBBMALLOC_UNSUPPORTED,
           TBBMALLOC_NO_MEMORY,
           TBBMALLOC_NO_EFFECT
       } ScalableAllocationResult;
   
       typedef enum {
           // To turn on/off the use of huge memory pages
           TBBMALLOC_USE_HUGE_PAGES,
           // To set a threshold for the allocator memory usage.
           // Exceeding it will forcefully clean internal memory buffers
           TBBMALLOC_SET_SOFT_HEAP_LIMIT,
           // Lower bound for the size (Bytes), that is interpreted as huge
           // and not released during regular cleanup operations
           TBBMALLOC_SET_HUGE_SIZE_THRESHOLD
       } AllocationModeParam;
   
       // Set allocator-specific allocation modes.
       int scalable_allocation_mode(int param, intptr_t value);
   
       typedef enum {
           // Clean internal allocator buffers for all threads.
           TBBMALLOC_CLEAN_ALL_BUFFERS,
           // Clean internal allocator buffer for current thread only.
           TBBMALLOC_CLEAN_THREAD_BUFFERS
       } ScalableAllocationCmd;
   
       // Call allocator-specific commands.
       int scalable_allocation_command(int cmd, void *param);
   }


Header
------

.. code:: cpp

   #include "tbb/scalable_allocator.h"


Description
-----------

These functions provide a C level interface to the
scalable allocator. With the exception of scalable_allocation_mode and
scalable_allocation_command, each routine scalable_``x``
behaves analogously to library function 
``x``. The routines form the two families shown in
the table below, "C Interface to Scalable Allocator" . Storage allocated by a
scalable_``x`` function in one family must be freed or
resized by a scalable_``x`` function in the same family,
not by a C standard library function. Likewise storage allocated by a C
standard library function should not be freed or resized by a
scalable_``x`` function.

.. table:: C Interface to Scalable Allocator

   +--------------------------+-----------------------+-------------------------------+
   | Allocation Routine       | Deallocation Routine  | Analogous Library             |
   +==========================+=======================+===============================+
   | scalable_malloc          | scalable_free         | C standard library            |
   +--------------------------+                       +                               +
   | scalable_calloc          |                       |                               |
   +--------------------------+                       +                               +
   | scalable_realloc         |                       |                               |
   +--------------------------+                       +-------------------------------+
   | scalable_posix_memalign  |                       | POSIX*                        |
   +--------------------------+-----------------------+-------------------------------+
   | scalable_aligned_malloc  | scalable_aligned_free | Microsoft* C run-time library |
   +--------------------------+                       +                               +
   | scalable_aligned_realloc |                       |                               |
   +--------------------------+-----------------------+-------------------------------+
   
The following functions do not allocate or free memory but allow
to obtain useful information or to influence behavior of the memory allocator.

size_t scalable_msize( void* ptr )
----------------------------------

**Returns:** The usable size of the memory block
pointed to by *ptr* if it was allocated by the scalable allocator.
Returns zero if *ptr* does not point to such a block.

int scalable_allocation_mode(int mode, intptr_t value)
------------------------------------------------------


This function may be used to adjust behavior of the scalable memory allocator.

**Returns**: TBBMALLOC_OK if the operation succeeded, TBBMALLOC_INVALID_PARAM if
``mode`` is not one of the described below, or if ``value``
is not valid for the given mode. Other return values are possible, as described below.

= ========================================================================================
\ Parameter, Description
==========================================================================================
\ ``TBBMALLOC_USE_HUGE_PAGES``
  \
  ``scalable_allocation_mode(TBBMALLOC_USE_HUGE_PAGES, 1)``
  tells the allocator to use huge pages if enabled by the operating system.
  ``scalable_allocation_mode(TBBMALLOC_USE_HUGE_PAGES, 0)``
  disables it. Setting ``TBB_MALLOC_USE_HUGE_PAGES``
  environment variable to 1 has the same effect as
  ``scalable_allocation_mode(TBBMALLOC_USE_HUGE_PAGES, 1)``.
  The mode set with ``scalable_allocation_mode()`` takes
  priority over the environment variable.
  
  **May return**: TBBMALLOC_NO_EFFECT if huge pages are not supported
  on the platform.
  
  For now, this allocation mode is only supported for Linux* OS.
  It works with both explicitly configured and transparent huge pages.
  For information about enabling and configuring huge pages, refer to OS
  documentation or ask your system administrator.
  
  .. caution::

     In this mode, it is not recommended to round up memory request size
     or alignment to a multiple of the huge page size, as it may result in
     inefficient use of huge pages and loss of performance.
  
------------------------------------------------------------------------------------------
\ ``TBBMALLOC_SET_SOFT_HEAP_LIMIT``
  \
  ``scalable_allocation_mode(TBBMALLOC_SET_SOFT_HEAP_LIMIT, size)``
  sets a threshold of ``size`` bytes on the amount
  of memory the allocator takes from OS. Exceeding the threshold
  will urge the allocator to release memory from its internal buffers;
  however it does not prevent from requesting more memory if needed.
------------------------------------------------------------------------------------------
\ ``TBBMALLOC_SET_HUGE_SIZE_THRESHOLD``
  \
  ``scalable_allocation_mode(TBBMALLOC_SET_HUGE_SIZE_THRESHOLD, size)``
  sets a lower bound threshold (with no upper limit) of ``size`` bytes.
  Any object that is bigger than this threshold becomes huge and doesn't participate
  in internal periodic cleanup logic. However, it doesn't affect the logic of
  ``TBBMALLOC_SET_SOFT_HEAP_LIMIT`` mode as well as ``TBBMALLOC_CLEAN_ALL_BUFFERS`` operation.
  
  Setting ``TBB_MALLOC_SET_HUGE_SIZE_THRESHOLD`` environment variable
  to the size value has the same effect, but is limited to the ``LONG_MAX`` value.
  The mode set with ``scalable_allocation_mode`` takes priority over the environment variable.
------------------------------------------------------------------------------------------
= ========================================================================================


int scalable_allocation_command(int cmd, void* reserved)
--------------------------------------------------------

This function may be used to command the scalable memory allocator to perform an
action specified by the first parameter. The second parameter is reserved and
must be set to 0.

**Returns**: TBBMALLOC_OK if the operation succeeded, TBBMALLOC_INVALID_PARAM if
``cmd`` is not one of the described below, or if ``reserved``
is not equal to 0.

= ========================================================================================
\ Parameter, Description
==========================================================================================
\ ``TBBMALLOC_CLEAN_ALL_BUFFERS``
  \
  ``scalable_allocation_command(TBBMALLOC_CLEAN_ALL_BUFFERS, 0)``
  cleans internal memory buffers of the allocator, and possibly reduces memory
  footprint. It may result in increased time for subsequent memory allocation
  requests. The command is not designed for frequent use, and careful
  evaluation of the performance impact is recommended.
  
  **May return**: TBBMALLOC_NO_EFFECT if no buffers were released.
  
  .. note::

     It is not guaranteed that the call will release all unused memory.
  
------------------------------------------------------------------------------------------
\ ``TBBMALLOC_CLEAN_THREAD_BUFFERS``
  \
  ``scalable_allocation_command(TBBMALLOC_CLEAN_THREAD_BUFFERS, 0)``
  cleans internal memory buffers but only for the calling thread. It may result
  in increased time for subsequent memory allocation requests; careful evaluation
  of the performance impact is recommended.
  
  **May return**: TBBMALLOC_NO_EFFECT if no buffers were released.
------------------------------------------------------------------------------------------
= ========================================================================================
