Before calling any SDK functions, the application must initialize the SDK library and create an SDK session.
An SDK session maintains context for the use of any of **DECODE**, **ENCODE**, or **VPP** functions.

Media SDK dispatcher (legacy)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The function :cpp:func:`MFXInit` starts (initializes) an SDK session. :cpp:func:`MFXClose` closes (de-initializes) the SDK session.
To avoid memory leaks, always call :cpp:func:`MFXClose` after :cpp:func:`MFXInit`.

The application can initialize a session as a software-based session (:cpp:enumerator:`MFX_IMPL_SOFTWARE`) or a hardware-based session
(:cpp:enumerator:`MFX_IMPL_HARDWARE`). In the former case, the SDK functions execute on a CPU, and in the latter case, the SDK functions
use platform acceleration capabilities. For platforms that expose multiple graphic devices, the application can initialize
the SDK session on any alternative graphic device (:cpp:enumerator:`MFX_IMPL_HARDWARE1`,..., :cpp:enumerator:`MFX_IMPL_HARDWARE4`).

The application can also initialize a session to be automatic (:cpp:enumerator:`MFX_IMPL_AUTO` or :cpp:enumerator:`MFX_IMPL_AUTO_ANY`), instructing
the dispatcher library to detect the platform capabilities and choose the best SDK library available. After initialization,
the SDK returns the actual implementation through the :cpp:func:`MFXQueryIMPL` function.

Internally, dispatcher works in that way:

1. It seaches for the shared library with the specific name:

   ======= =============== ====================================
   OS      Name            Description
   ======= =============== ====================================
   Linux   libmfxsw64.so.1 64-bit software-based implementation
   Linux   libmfxsw32.so.1 32-bit software-based implementation
   Linux   libmfxhw64.so.1 64-bit hardware-based implementation
   Linux   libmfxhw64.so.1 32-bit hardware-based implementation
   Windows libmfxsw32.dll  64-bit software-based implementation
   Windows libmfxsw32.dll  32-bit software-based implementation
   Windows libmfxhw64.dll  64-bit hardware-based implementation
   Windows libmfxhw64.dll  32-bit hardware-based implementation
   ======= =============== ====================================

2. Once library is loaded, dispatcher obtains addresses of an each SDK function. See table with the list of functions to export.



oneVPL diapatcher
~~~~~~~~~~~~~~~~~

oneVPL dispatcher extends the legacy dispatcher by providing additional ability to select appropriate implementation based on the implementation
capabilities. Implementation capabilities include information about supported decoders, encoders and VPP filters. For each supported encoder, decoder and filter,
capabilities include information about supported memory types, color formats, image (frame) size in pixels and so on.

This is recomended way for the user to configure the dispatcher's capabilities search filters and create session based on suitable implementation:

- Create loader (:cpp:func:`MFXLoad` dispatcher's function).
- Create loader's config (:cpp:func:`MFXCreateConfig` dispatcher's function).
- Add config properties (:cpp:func:`MFXSetConfigFilterProperty` dispatcher's function).
- Explore avialable implementations according (:cpp:func:`MFXEnumImplementations` dispatcher's function).
- Create suitable session (:cpp:func:`MFXCreateSession` dispatcher's function).

This is application termination procedure:

- Destroys session (:cpp:func:`MFXClose` function).
- Destroys loader (:cpp:func:`MFXUnload` dispatcher's function).

.. note:: Multiple loader instances can be created.
.. note:: Each loader may have multiple config objects assotiated with it.
.. important:: One config object can handle only one filter property.
.. note:: Multiple sessions can be created by using one loader object.

When dispatcfher searches for the implementation it uses following priority rules:

1. HW implementation has priority over SW implementation.
2. Gen HW implementation hase priority over VSI HW implementation.
3. Highest API version has higher priority over lower API version.

.. note:: Implementation has priority over the API version. In other words, dispatcher must return implementation with highest API priority (greater
          or equal to the requested).

Dispatcher searches implemetation in the following folders at runtime (in priority order):

1. User-defined search folders.
2. oneVPL package.
3. Standalone MSDK package (or driver).

User has ability to develop it's own implementation and guide oneVPL dispatcher to load his implementation by providing list of search folders.
The way how it can be done depends on OS.

- linux: User can provide colon separated list of folders in ONEVPL_SEARCH_PATH environmental variable.
- Windows: User can provide semicolon separated list of folders in ONEVPL_SEARCH_PATH environmental variable. Alternatively, user can use Windows registry.

Different SW implementations is supported by the dispatcher. User can use field :cpp:member:`mfxImplDescription::VendorID` or 
:cpp:member:`mfxImplDescription::VendorImplID` or :cpp:member:`mfxImplDescription::ImplName` to search for the particular implementation.

Internally, dispatcher works in that way:

1. Dispatcher loads any shared library with in given search floders.
2. For each loaded library, dispatcher tries to resolve adress of the :cpp:func:`MFXQueryImplCapabilities` function to collect the implamentation;s
   capabilities.
3. Once user requested to create the session based on this implementation, dispatcher obtains addresses of an each SDK function. See table with the
   list of functions to export.

This table summarizes list of evviromental variables to control the dispatcher behaviour:

================== ====================================================================
Varible            Purpose
================== ====================================================================
ONEVPL_SEARCH_PATH List of user-defined search folders.
================== ====================================================================


.. note:: Each implementation must support both dispatchers for backward compatibility with existing applications.

Multiple Sessions
~~~~~~~~~~~~~~~~~

Each SDK session can run exactly one instance of **DECODE**, **ENCODE** and **VPP** functions. This is good for a simple transcoding operation.
If the application needs more than one instance of **DECODE**, **ENCODE** and **VPP** in a complex transcoding setting, or needs more
simultaneous transcoding operations to balance CPU/GPU workloads, the application can initialize multiple SDK sessions.
Each SDK session can independently be a software-based session or hardware-based session.

The application can use multiple SDK sessions independently or run a “joined” session. Independently operated SDK sessions
cannot share data unless the application explicitly synchronizes session operations (to ensure that data is valid and
complete before passing from the source to the destination session.)

To join two sessions together, the application can use the function :cpp:func:`MFXJoinSession`. Alternatively, the application can use
the function :cpp:func:`MFXCloneSession` to duplicate an existing session. Joined SDK sessions work together as a single session, sharing
all session resources, threading control and prioritization operations (except hardware acceleration devices and external
allocators). When joined, one of the sessions (the first join) serves as a parent session, scheduling execution resources,
with all others child sessions relying on the parent session for resource management.

With joined sessions, the application can set the priority of session operations through the :cpp:func:`MFXSetPriority` function.
A lower priority session receives less CPU cycles. Session priority does not affect hardware accelerated processing.

After the completion of all session operations, the application can use the function :cpp:func:`MFXDisjoinSession` to remove
the joined state of a session. Do not close the parent session until all child sessions are disjoined or closed.

