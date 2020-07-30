.. _sdk-session:

===========
SDK Session
===========

Before calling any SDK functions, the application must initialize the SDK
library and create an SDK session. An SDK session maintains context for the use
of any of :term:`DECODE`, :term:`ENCODE`, or :term:`VPP` functions.

------------------------------------
|msdk_full_name| Dispatcher (Legacy)
------------------------------------

The function :cpp:func:`MFXInit` starts (initializes) an SDK session.
:cpp:func:`MFXClose` closes (de-initializes) the SDK session. To avoid memory
leaks, always call :cpp:func:`MFXClose` after :cpp:func:`MFXInit`.

The application can initialize a session as a software-based session
(:cpp:enumerator:`MFX_IMPL_SOFTWARE`) or a hardware-based session
(:cpp:enumerator:`MFX_IMPL_HARDWARE`). In a software-based session, the SDK
functions execute on a CPU. In a hardware-base session, the SDK functions
use platform acceleration capabilities. For platforms that expose multiple
graphic devices, the application can initialize the SDK session on any
alternative graphic device using the :cpp:enumerator:`MFX_IMPL_HARDWARE`,
:cpp:enumerator:`MFX_IMPL_HARDWARE2`, :cpp:enumerator:`MFX_IMPL_HARDWARE3`, or
:cpp:enumerator:`MFX_IMPL_HARDWARE4` values of :cpp:type:`mfxIMPL`

The application can also initialize a session to be automatic (
:cpp:enumerator:`MFX_IMPL_AUTO` or :cpp:enumerator:`MFX_IMPL_AUTO_ANY`),
instructing the dispatcher library to detect the platform capabilities and
choose the best SDK library available. After initialization, the SDK returns the
actual implementation through the :cpp:func:`MFXQueryIMPL` function.

Internally, the dispatcher works as follows:

#. It searches for the shared library with the specific name:

   ========= =============== ====================================
   OS        Name            Description
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
   :ref:`Exported Functions/API Version table <export-func-version-table>` for
   the list of functions to export.

Shared library with the implementation search strategy:

- **Windows** Dispatcher goes through the following list in specified order
  until it finds implementstion library:

  1. **Driver Store** directory for the current adapter
     `(more about Driver Store) <https://docs.microsoft.com/en-us/windows-hardware/drivers/install/driver-store>`__.
     **This is directory which library can be installed in by all types of graphics driver.**
  2. The directory which is specified for the current hardware under the
     registry key ``HKEY_CURRENT_USER\Software\Intel\MediaSDK\Dispatch``.
  3. The directory which is specified for the current hardware under the
     registry key ``HKEY_LOCAL_MACHINE\Software\Intel\MediaSDK\Dispatch``.
  4. The actual directory which is stored in these registry keys is ``C:\Program Files\Intel\Media SDK``. 
     **This is directory which library is installed in by Legacy graphics driver.**
  5. The directory where the current module (module that links dispatcher) is located (only if the current module is a dll).

  After the main search part, dispatcher additionally checks:

  1. The directory of the exe file of the current process, where it looks for software implementation only,
     no matter which implementation is requested by application.
  2. Default dll search, this way provides loading from directory of application's exe file and from
     **System32**/**SysWOW64** directories `(more about default dll search order) <https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order?redirectedfrom=MSDN#search-order-for-desktop-applications>`__.
  3. **System32** and **SysWOW64** are directories which library is installed in by DCH graphics driver.
- **Linux** Dispatcher goes through the following list in specified order
  until it finds implementation library:

  1. Directories provided by the environment variable **LD_LIBRARY_PATH**.
  2. Content of the cache file /etc/ld.so.cache.
  3. Default path ``/lib``, and then ``/usr/lib`` or ``/lib64``, and then ``/usr/lib64`` on some 64 bit OSes. On Debian:
     ``/usr/lib/x86_64-linux-gnu``.
  4. SDK installation folder.


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
search filters and to create a session based on suitable implementation is as
follows:

#. Create loader (dispatcher function :cpp:func:`MFXLoad`).
#. Create loader's configuration (dispatcher function :cpp:func:`MFXCreateConfig`).
#. Add configuration properties (dispatcher function :cpp:func:`MFXSetConfigFilterProperty`).
#. Explore available implementations (dispatcher function
   :cpp:func:`MFXEnumImplementations`).
#. Create suitable session (dispatcher function :cpp:func:`MFXCreateSession`).

The procedure to terminate an application is as follows:

#. Destroy session (function :cpp:func:`MFXClose`).
#. Destroy loader (dispatcher function :cpp:func:`MFXUnload`).

.. note:: Multiple loader instances can be created.

.. note:: Each loader may have multiple configuration objects associated with it.

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
runtime (in priority order):

#. User-defined search folders.
#. oneVPL package, including default system folders.
#. Standalone |msdk_full_name| package (or driver).

For more details, see legacy dispatcher search order.

A user has the ability to develop their own implementation and guide the oneVPL
dispatcher to load their implementation by providing a list of search folders.
The specific steps depend on which OS is used.

* Linux: User can provide a colon separated list of folders in
  ONEVPL_SEARCH_PATH environmental variable.
* Windows: User can provide semicolon separated list of folders in
  ONEVPL_SEARCH_PATH environmental variable. Alternatively, the user can use the
  Windows registry.

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
   the dispatcher obtains addresses of each SDK function. See the
   :ref:`Exported Functions/API Version table <export-func-version-table>` for
   the list of functions to export.

This table summarizes the list of environmental variables used to control the
dispatcher behavior:

================== =============================================================
Variable           Purpose
================== =============================================================
ONEVPL_SEARCH_PATH List of user-defined search folders.
================== =============================================================


.. note:: Each implementation must support both dispatchers for backward
          compatibility with existing applications.

-----------------
Multiple Sessions
-----------------

Each SDK session can run exactly one instance of the DECODE, ENCODE, and
VPP functions. This is good for a simple transcoding operation. If the
application needs more than one instance of DECODE, ENCODE, or VPP
in a complex transcoding setting or needs more simultaneous transcoding
operations to balance CPU/GPU workloads, the application can initialize multiple
SDK sessions. Each independent SDK session can be a software-based session or
hardware-based session.

The application can use multiple SDK sessions independently or run a “joined”
session. Independently operated SDK sessions cannot share data unless the
application explicitly synchronizes session operations. This is to ensure that
data is valid and complete before passing from the source to the destination
session.

To join two sessions together, the application can use the function
:cpp:func:`MFXJoinSession`. Alternatively, the application can use the
:cpp:func:`MFXCloneSession` function to duplicate an existing session. Joined
SDK sessions work together as a single session, sharing all session resources,
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

