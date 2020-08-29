Operation Progress Tracking
===========================

oneCCL communication operation shall return a request object to be used for tracking the operation's progress.

The ``request`` class shall provide the ability to wait for completion of an operation in a blocking manner, the ability to check the completion status in a non-blocking manner, and the ability to retrieve the underlying ``event`` object that is signaled when the device communication operation completes on the device.

Request
*******

Waiting for the completion of an operation in a blocking manner:

.. code:: cpp

    void request::wait();


Checking for the completion of an operation in a non-blocking manner:

.. code:: cpp

    bool request::test();

return ``bool``
    ``true`` if the operation has been completed
    ``false`` if the operation has not been completed


Retrieving an event object that is signaled when the device communication operation completes on the device:

.. code:: cpp

    event request::get_event() const;

return ``event``
    an event object that is signaled when the communication operation completes on the device
