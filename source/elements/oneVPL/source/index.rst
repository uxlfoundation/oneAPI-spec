..
  Copyright 2020 Intel Corporation

.. _oneVPL-section:

**Thank you for using oneAPI Video Processing Library.  Based on developer
  feedback, we are revising oneVPL to make it even better.  Stay tuned for a new
  oneVPL.  Thanks again!**

********************
oneVPL |vpl_version|
********************

The |vpl_full_name| is a programming interface for video processing and video analytics,
focusing on building portable media pipeline on CPU, GPU, Deep Learning (DL) 
accelerators and FPGA. It aims for function and performance portability such that
applications built with oneVPL can be efficiently executed on the current and future 
generation hardware without modification. oneVPL library provides the following features:

1. Cross architecture building blocks for Decode, Video Processing, Encode and 
   DL based video analytics.
2. A VPL-Memory Library for image object passing among media, compute and 3D rendering
   phases of a video analytics pipeline, with zero-copying buffer sharing
   among CPU, GPU, DL accelerators and FPGA. 
3. Device discovery and device selection query interface for video and DL operations. 

Intel's implementation of VPL will be hosted at 
https://software.intel.com/en-us/oneapi/vpl# with each public release.

See `VPL API Reference`_ for the detailed API description.

Device Discovery
================
.. include:: VPL_device.rst

Device Context
==============
.. include:: VPL_device_context.rst

Workstream Settings
===================
.. include:: VPL_parameters.rst

Workstream
==========
.. _workstream:
.. include:: VPL_workstreams.rst

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
