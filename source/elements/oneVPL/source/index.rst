..
  Copyright 2020 Intel Corporation

.. _oneVPL-section:

************************
|vpl_full_name| (oneVPL)
************************

The |vpl_full_name| is a programming interface for all video/image
related usages, with focus on portable media pipeline on CPU, GPU, AI
accelerators and FPGA, media, compute and render interoperability, to
provide the best cross domain pipeline experience.  oneVPL libary provides
the following features:

1. Cross architecture building blocks for Decode, Video Processing, 
   Deep Learning (DL) based video analytics and Encode.
2. A VPL-Memory Library provides image object passing among media, compute and graphics render.
   phases of a video analytics pipeline, and, enables zero-copy buffer sharing
   among CPU, GPU and various hardware accelerators.
3. Device discovery and device selection query interface for video operations. 

Intel's implementation of VPL will be hosted at 
https://software.intel.com/en-us/oneapi/vpl# after release to public.

See `VPL API Reference`_ for a detailed API description.

Device Discovery
================
.. include:: VPL_device.rst

Device Context
==============
.. include:: VPL_device_context.rst

Workstream Settings
===================
.. include:: VPL_parameters.rst

Workstreams
===========
.. include:: VPL_workstreams.rst

The VPL API is defined around workstreams, which are referenced by
:cpp:type:`vplWorkstream`, an opaque pointer. See
:ref:`workstream-api` for all workstream APIs.

A Workstream defines a set of settable and gettable properties to configure:

* *Input and output*: image formats, frame rates, resolutions,
  cropping, aspect ratios
* *Internal settings*: maximum number of decoded image buffers,
  internal input raw data buffer size
* *Encoding preset and heuristics*: encoding bitrates, scenarios and
  target usage

:cpp:type:`VplWorkstreamProp` names all the properties. Get and set
the properites with :cpp:type:`vplGetConfigProperty` and
:cpp:func:`vplSetConfigProperty`.

Decode
------
.. include:: VPL_decode.rst

Encode
------
.. include:: VPL_encode.rst

Video Processing
----------------
.. include:: VPL_processframe.rst

VPL Memory
==========
.. include:: VPL_memory.rst


VPL API Reference
=================

.. _device-api:

Device
------

vpl::DeviceInfo
~~~~~~~~~~~~~~~
.. doxygenenum:: VplDeviceType
   :project: oneVPL

.. doxygenstruct:: vpl::VplDeviceProperty
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

.. doxygenclass:: vpl::DeviceInstance
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

.. doxygenclass:: vpl::DeviceInfo
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

.. _device-context-api:

Device Context
--------------

vpl::DeviceContext
~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::DeviceContext
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

.. _config-setting-api:

Workstream Settings
-------------------

vpl::VplParams
~~~~~~~~~~~~~~
.. doxygenclass:: vpl::VplParams
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

Decode Settings
---------------

vpl::VplParamsDecode
~~~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::VplParamsDecode
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

Encode Settings
---------------

vpl::VplParamsEncode
~~~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::VplParamsEncode
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

.. _workstream-api:

Workstreams
-----------

VplWorkstreamType
~~~~~~~~~~~~~~~~~
.. doxygenenum:: VplWorkstreamType
   :project: oneVPL


Workstream
----------

vpl::Workstream
~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::Workstream
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

Workstream::Decode
~~~~~~~~~~~~~~~~~~
.. doxygenenum:: vplWorkstreamState
   :project: oneVPL

.. doxygenclass:: vpl::Decode
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

Workstream::Encode
~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::Encode
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

Workstream::VideoProcess
~~~~~~~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vpl::VideoProcess
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

Memory
------

vplm::cpu_image
~~~~~~~~~~~~~~~
.. doxygenclass:: vplm::cpu_image
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::memory
~~~~~~~~~~~~
.. doxygenclass:: vplm::memory
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::cpu::memory
~~~~~~~~~~~~~~~~~
.. doxygenclass:: vplm::cpu::memory
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::cpu::image
~~~~~~~~~~~~~~~~
.. doxygenclass:: vplm::cpu::image
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::cpu::make_memory
~~~~~~~~~~~~~~~~~~~~~~
.. doxygennamespace:: vplm::cpu
   :outline:
   :project: oneVPL
   :undoc-members:   

vplm::opencl::memory
~~~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vplm::opencl::memory
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::opencl::image
~~~~~~~~~~~~~~~~~~~
.. doxygenclass:: vplm::opencl::image
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::opencl::make_memory
~~~~~~~~~~~~~~~~~~~~~~~~~
.. doxygennamespace:: vplm::opencl
   :outline:
   :project: oneVPL

vplm::sycl::memory
~~~~~~~~~~~~~~~~~~

.. doxygenclass:: vplm::sycl::memory
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::sycl::make_memory
~~~~~~~~~~~~~~~~~~~~~~~

.. doxygennamespace:: vplm::sycl
   :outline:
   :project: oneVPL

vplm::vaapi::memory
~~~~~~~~~~~~~~~~~~~

.. doxygenclass:: vplm::vaapi::memory
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::vaapi::image
~~~~~~~~~~~~~~~~~~

.. doxygenclass:: vplm::vaapi::image
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

vplm::vaapi::make_memory
~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygennamespace:: vplm::vaapi
   :outline:
   :project: oneVPL
		     

Miscellaneous
-------------

vplStatus
~~~~~~~~~~~~~~~~~
.. doxygenenum:: vplStatus
   :project: oneVPL

VplCodecType
~~~~~~~~~~~~
.. doxygenenum:: VplCodecType
   :project: oneVPL

VplFourCC
~~~~~~~~~
.. doxygenenum:: VplFourCC
   :project: oneVPL

VplCrop
~~~~~~~
.. doxygenstruct:: VplCrop
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

VplAspectRatio
~~~~~~~~~~~~~~
.. doxygenstruct:: VplAspectRatio
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

VplEncodePreset
~~~~~~~~~~~~~~~
.. doxygenenum:: VplEncodePreset
   :project: oneVPL

VplEncodeScenario
~~~~~~~~~~~~~~~~~
.. doxygenenum:: VplEncodeScenario
   :project: oneVPL

VplBRC
~~~~~~
.. doxygenenum:: VplBRC
   :project: oneVPL

VplFrameRate
~~~~~~~~~~~~
.. doxygenstruct:: VplFrameRate
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:   

VplVersion
~~~~~~~~~~
.. doxygenstruct:: VplVersion
   :project: oneVPL
   :members:
   :protected-members:
   :undoc-members:

vplLogLevel
~~~~~~~~~~~
.. doxygenenum:: vplLogLevel
   :project: oneVPL
