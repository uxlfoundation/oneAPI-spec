:class:`vpl::DeviceInfo` defines device and property query interface.
At runtime, VPL discovers available devices in :type:`VplDeviceType`,
the number of devices of each type (:func:`vpl::DeviceInfo::GetDeviceCount`),  
and :type:`vpl::VplDeviceProperty` of each device (:func:`vpl::DeviceInfo::GetDeviceProperty`).

This class also provides two additional important classes of functions:

1. :func:`vpl::DeviceInfo::GetPreferredDevice`: get a preferred device instance :type:`vpl::DeviceInstance` for a work
2. :func:`vpl::DeviceInfo::GetPreset`: get the device preset configuration for workstream :enum:`VplWorkstreamType` and device instance

We recommend the following code sequence to select a device and get the device's preset 
configuration parameters before creating a workstream on a device:

.. code-block:: c++

   // Find all the devices in the system and select a preferred device
   DeviceInfo *dinfo = new DeviceInfo();
   DeviceInstance *dev = dinfo->GetPreferredDevice(VPL_WORKSTREAM_DECODE);

   // Get decode preset
   config::VPLParams *dconfig = dinfo->GetPreset(dev->m_dtype, VPL_WORKSTREAM_DECODE, dev->m_id);