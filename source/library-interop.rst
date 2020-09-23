.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Library Interoperability
========================

Libraries support API programming. oneAPI libraries meet the
following requirements to ensure interoperability and provide full
platform performance.

Queueing
--------

APIs that launch a computation on a device allow the programmer to control where
the computation is performed by passing a queue. A queue can be passed
with every invocation or it can be passed once and retained in a library's
internal state.

API Arguments
-------------

When an API accepts a buffer as an argument there is an
equivalent API that accepts a unified-shared memory (USM)
pointer. Some API's accept a USM pointer but do not have variants that
accept buffers.

APIs document when an argument is accessed from a device and when an
argument is accessed by the host. Behavior is undefined if you pass a
device argument that is not accessible by the device (non-USM pointer,
for example), or a host argument that is not accessible by the host
(:code:`malloc_device`, for example).

Asynchronous APIs
------------------

To achieve the best performance on a oneAPI platform, the host and
devices should execute concurrently. Concurrent execution is supported
via asynchronous APIs that queue one or more kernels and immediately
return control to the host.  Synchronous APIs stall the host thread
until the API is complete.

Scheduling of an asynchronous oneAPI library call is controlled by two
mechanisms:

* APIs that accept buffers rely on the buffer/accessor mechanism in
  the oneAPI runtime to schedule computation on the host and devices.
  
* APIs that accept USM pointers accept a vector of prerequisite events
  and the scheduler waits on the events before submitting the call for
  execution on the device.  The API returns an event that another
  kernel or library API can wait on to ensure the output data is
  ready.

Exceptions
----------

This specification recommends that oneAPI library APIs signal errors by
throwing C++ exceptions.  Some APIs use alternative methods for error
reporting, due to legacy requirements.
