:class:`vpl::DeviceInfo` defines a device and property query interface.
At runtime, VPL discovers available devices declared in :type:`VplDeviceType`,
the number of devices of each type (:func:`vpl::DeviceInfo::GetDeviceCount`),  
and :type:`vpl::VplDeviceProperty` of each device (:func:`vpl::DeviceInfo::GetDeviceProperty`).

This class also provides two important member functions:

1. :func:`vpl::DeviceInfo::GetPreferredDevice`: get a preferred device instance :type:`vpl::DeviceInstance` for a :class:`vpl::Workstream` (workstream_)
2. :func:`vpl::DeviceInfo::GetPreset`: get the device preset configuration for a :enum:`VplWorkstreamType` and a device instance

We recommend the following code sequence to select a device and get the device's preset 
configuration parameters before creating a :class:`Workstream` on a device:

.. code-block:: c++

   // Find all the devices in the system and select a preferred device
   DeviceInfo *dinfo = new DeviceInfo();
   DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_DECODE);

   // Get decode preset
   config::VPLParams *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_DECODE, dev->m_id);