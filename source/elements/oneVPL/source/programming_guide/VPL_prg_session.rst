.. _sdk-session:

==============
oneVPL Session
==============

Before calling any oneVPL functions, the application must initialize the
library and create a oneVPL session. A oneVPL session maintains context for the
use of any of :term:`DECODE`, :term:`ENCODE`, or :term:`VPP` functions.

------------------------------------
|msdk_full_name| Dispatcher (Legacy)
------------------------------------

The :cpp:func:`MFXInit` or :cpp:func:`MFXInitEx` function starts (initializes)
a session. The :cpp:func:`MFXClose` function closes (de-initializes) the
session. To avoid memory leaks, always call :cpp:func:`MFXClose` after
:cpp:func:`MFXInit`.

The application can initialize a session as a software-based session
(:cpp:enumerator:`MFX_IMPL_SOFTWARE`) or a hardware-based session
(:cpp:enumerator:`MFX_IMPL_HARDWARE`). In a software-based session, the SDK
functions execute on a CPU. In a hardware-base session, the SDK functions
use platform acceleration capabilities. For platforms that expose multiple
graphic devices, the application can initialize a session on any
alternative graphic device using the :cpp:enumerator:`MFX_IMPL_HARDWARE`,
:cpp:enumerator:`MFX_IMPL_HARDWARE2`, :cpp:enumerator:`MFX_IMPL_HARDWARE3`, or
:cpp:enumerator:`MFX_IMPL_HARDWARE4` values of :cpp:type:`mfxIMPL`.

The application can also initialize a session to be automatic (
:cpp:enumerator:`MFX_IMPL_AUTO` or :cpp:enumerator:`MFX_IMPL_AUTO_ANY`),
instructing the dispatcher library to detect the platform capabilities and
choose the best SDK library available. After initialization, the SDK returns the
actual implementation through the :cpp:func:`MFXQueryIMPL` function.

Internally, the dispatcher works as follows:

#. Dispatcher searches for the shared library with the specific name:

   ========= =============== ====================================
   **OS**    **Name**        **Description**
   ========= =============== ====================================
   Linux\*   libmfxsw64.so.1 64-bit software-based implementation
   Linux     libmfxsw32.so.1 32-bit software-based implementation
   Linux     libmfxhw64.so.1 64-bit hardware-based implementation
   Linux     libmfxhw64.so.1 32-bit hardware-based implementation
   Windows\* libmfxsw32.dll  64-bit software-based implementation
   Windows   libmfxsw32.dll  32-bit software-based implementation
   Windows   libmfxhw64.dll  64-bit hardware-based implementation
   Windows   libmfxhw64.dll  32-bit hardware-based implementation
   ========= =============== ====================================

#. Once the library is loaded, the dispatcher obtains addresses for each SDK
   function. See the
   :ref:`Exported Functions/API Version table <export-func-version-table-2x>` for
   the list of functions to expose.

.. _legacy_search_order:

How the shared library is identified using the implementation search strategy
will vary according to the OS.

* On Windows, the dispatcher searches the following locations, in the specified
  order, to find the correct implementation library:

  #. The :file:`Driver Store` directory for the current adapter.
     All types of graphics drivers can install libraries in this directory. `Learn more about Driver Store <https://docs.microsoft.com/en-us/windows-hardware/drivers/install/driver-store>`__.
  #. The directory specified for the current hardware under the registry key
     ``HKEY_CURRENT_USER\Software\Intel\MediaSDK\Dispatch``.
  #. The directory specified for the current hardware under the registry key
     ``HKEY_LOCAL_MACHINE\Software\Intel\MediaSDK\Dispatch``.
  #. The directory that is stored in these registry keys: :file:`C:\Program Files\Intel\Media SDK`.
     This directory is where legacy graphics drivers install libraries.
  #. The directory where the current module (the module that links the dispatcher)
     is located (only if the current module is a dll).

  After the dispatcher completes the main search, it additionally checks:

  #. The directory of the exe file of the current process, where it looks for
     software implementation only, regardless of which implementation the
     application requested.
  #. Default dll search. This provides loading from the directory of the
     application's exe file and from the :file:`System32` and :file:`SysWOW64`
     directories. `Learn more about default dll search order <https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order?redirectedfrom=MSDN#search-order-for-desktop-applications>`__.
  #. The :file:`System32` and :file:`SysWOW64` directories, which is where DCH
     graphics drivers install libraries.

* On Linux, the dispatcher searches the following locations, in the specified
  order, to find the correct implementation library:

  #. Directories provided by the environment variable ``LD_LIBRARY_PATH``.
  #. Content of the :file:`/etc/ld.so.cache` cache file.
  #. Default path :file:`/lib`, then :file`/usr/lib` or :file:`/lib64`, and then
     :file:`/usr/lib64` on some 64 bit OSs. On Debian: :file:`/usr/lib/x86_64-linux-gnu`.
  #. SDK installation folder.


-----------------
oneVPL Dispatcher
-----------------

The oneVPL dispatcher extends the legacy dispatcher by providing additional
ability to select the appropriate implementation based on the implementation
capabilities. Implementation capabilities include information about supported
decoders, encoders, and VPP filters. For each supported encoder, decoder, and
filter, capabilities include information about supported memory types, color
formats, and image (frame) size in pixels.

The recommended approach to configure the dispatcher's capabilities
search filters and to create a session based on a suitable implementation is as
follows:

#. Create loader with :cpp:func:`MFXLoad`.
#. Create loader's configuration with :cpp:func:`MFXCreateConfig`.
#. Add configuration properties with :cpp:func:`MFXSetConfigFilterProperty`.
#. Explore available implementations with :cpp:func:`MFXEnumImplementations`.
#. Create a suitable session with :cpp:func:`MFXCreateSession`.

The procedure to terminate an application is as follows:

#. Destroy session with :cpp:func:`MFXClose`.
#. Destroy loader with :cpp:func:`MFXUnload`.

.. note:: Multiple loader instances can be created.

.. note:: Each loader may have multiple configuration objects associated with it.
          When a configuration object is modified through :cpp:func:`MFXSetConfigFilterProperty`
          it implicitly impacts the state and configuration of the associated loader.

.. important:: One configuration object can handle only one filter property.

.. note:: Multiple sessions can be created by using one loader object.

When the dispatcher searches for the implementation, it uses the following
priority rules:

#. Hardware implementation has priority over software implementation.
#. General hardware implementation has priority over VSI hardware implementation.
#. Highest API version has higher priority over lower API version.

.. note:: Implementation has priority over the API version. In other words, the
          dispatcher must return the implementation with the highest API
          priority (greater than or equal to the implementation requested).

The dispatcher searches for the implementation in the following folders at
runtime, in priority order:

#. User-defined search folders.
#. oneVPL package.
#. Path from :envvar:`PATH` or :envvar:`LD_LIBRARY_PATH` environmental variables,
   depending on OS.
#. Default system folders.
#. Standalone |msdk_full_name| package (or driver).

For more details, see the `legacy dispatcher search order <legacy_search_order>`_.

A user can develop their own implementation and direct the oneVPL dispatcher to
load their implementation by providing a list of search folders. The specific
steps depend on which OS is used.

* Linux: User can provide a colon separated list of folders in the
  :envvar:`ONEVPL_SEARCH_PATH` environmental variable.
* Windows: User can provide a semicolon separated list of folders in the
  :envvar:`ONEVPL_SEARCH_PATH` environmental variable. Alternatively, the user
  can use the Windows registry.


.. list-table:: Dispatcher Environmental Variables
   :header-rows: 1
   :widths: 40 60

   * - **Variable**
     - **Purpose**
   * - :envvar:`ONEVPL_SEARCH_PATH`
     - List of user-defined search folders used by the dispatcher during implementation search.


The dispatcher supports different software implementations. The user can use
the :cpp:member:`mfxImplDescription::VendorID` field, the
:cpp:member:`mfxImplDescription::VendorImplID` field, or the
:cpp:member:`mfxImplDescription::ImplName` field to search for the specific
implementation.

Internally, the dispatcher works as follows:

#. Dispatcher loads any shared library within the given search folders.
#. For each loaded library, the dispatcher tries to resolve address of the
   :cpp:func:`MFXQueryImplsCapabilities` function to collect the implementation's
   capabilities.
#. Once the user has requested to create the session based on this implementation,
   the dispatcher obtains addresses of each oneVPL function. See the
   :ref:`Exported Functions/API Version table <export-func-version-table-2x>` for
   the list of functions to export.

.. note:: For backward compartibility with |msdk_full_name|, dispatcher will try to
          load |msdk_full_name| first, if 1.x was requesuested to be loaded. If loading
          was failed, dispatcher will search for the implementation with highest
          2.x API verstion.

-----------------
Multiple Sessions
-----------------

Each oneVPL session can run exactly one instance of the DECODE, ENCODE, and
VPP functions. This is adequate for a simple transcoding operation. If the
application needs more than one instance of DECODE, ENCODE, or VPP
in a complex transcoding setting or needs more simultaneous transcoding
operations to balance CPU/GPU workloads, the application can initialize multiple
oneVPL sessions. Each independent oneVPL session can be a software-based session or
hardware-based session.

The application can use multiple oneVPL sessions independently or run a “joined”
session. Independently operated oneVPL sessions cannot share data unless the
application explicitly synchronizes session operations. This is to ensure that
data is valid and complete before passing from the source to the destination
session.

To join two sessions together, the application can use the function
:cpp:func:`MFXJoinSession`. Alternatively, the application can use the
:cpp:func:`MFXCloneSession` function to duplicate an existing session. Joined
oneVPL sessions work together as a single session, sharing all session resources,
threading control, and prioritization operations except hardware acceleration
devices and external allocators. When joined, the first session (first join)
serves as the parent session and will schedule execution resources with all
other child sessions. Child sessions rely on the parent session for resource
management.

With joined sessions, the application can set the priority of session operations
through the :cpp:func:`MFXSetPriority` function. A lower priority session
receives fewer CPU cycles. Session priority does not affect hardware accelerated
processing.

After the completion of all session operations, the application can use the
:cpp:func:`MFXDisjoinSession` function to remove the joined state of a session.
Do not close the parent session until all child sessions are disjoined or closed.

