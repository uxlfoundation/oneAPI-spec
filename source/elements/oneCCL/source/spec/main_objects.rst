.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

oneCCL Concepts
===============

oneCCL specification defines the following list of concepts:

- `Environment`_
- `Key-Value Store`_
- `Communicator`_
- `Device Communicator`_
- `Request`_
- `Event`_
- `Stream`_
- `Operation Attributes`_

Environment
***********

oneCCL specification defines ``environment`` class that shall provide a singleton object and helper methods to manage other oneCCL objects, such as communicators, attributes, and so on.

Retrieves the environment singleton object and initializes the library.

.. code:: cpp

    static environment& environment::instance();

return ``environment``
    an environment object


Key-Value Store
***************

``kvs_interface`` defines the key-value store (KVS) interface to be used to connect the ranks during the creation of oneCCL communicator. The interface shall include blocking ``get`` and ``set`` methods.

Getting a record from the key-value store:

.. code:: cpp

    virtual vector_class<char> kvs_interface::get(
        const string_class& prefix,
        const string_class& key) const = 0;

prefix
    the prefix that allows operations with KVS in a separate namespace
    to avoid key names conflicts with the existing KVS records
key
    the key at which the value should be stored
return ``vector_class<char>``
    the value associated with the given key

Saving a record in the key-value store:

.. code:: cpp

    void kvs_interface::set(
        const string_class& prefix,
        const string_class& key,
        const vector_class<char>& data) const = 0;

prefix
    the prefix that allows operations with KVS in a separate namespace
    to avoid key names conflicts with the existing KVS records
key
    the key at which the value should be stored
data
    the value that should be associated with the given key


oneCCL specification defines ``kvs`` class as a built-in KVS provided by oneCCL.

.. code:: cpp

    class kvs : public kvs_interface {
    
    public:

    static constexpr size_t address_max_size = 256;
    using address_type = array_class<char, address_max_size>;

    const address_type& get_address() const;

    ~kvs() override;

    vector_class<char> get(
        const string_class& prefix,
        const string_class& key) const override;

    void set(
        const string_class& prefix,
        const string_class& key,
        const vector_class<char>& data) const override;

    }

Retrieving an address of built-in key-value store:

.. code:: cpp

    const address_type& kvs::get_address() const;

return ``kvs::address_type``
    | the address of the key-value store
    | should be retrieved from the main built-in KVS and distributed to other processes for the built-in KVS creation


The ``environment`` class shall provide the ability to create an instance of ``kvs`` class.

Creating a main built-in key-value store. Its address should be distributed using an out-of-band communication mechanism
and be used to create key-value stores on other ranks:

.. code:: cpp

    kvs environment::create_main_kvs() const;

return ``kvs``
    the main key-value store object

Creating a new key-value store from main kvs address:

.. code:: cpp

    kvs environment::create_kvs(const kvs::addr_type& addr) const;

addr
    the address of the main kvs
return ``kvs``
    key-value store object


.. _Communicator:

Communicator
************

oneCCL specification defines ``communicator`` class that describes a group of communicating ranks, where rank is a single process. ``communicator`` defines communication operations on host memory buffers.

The ``environment`` class shall provide the ability to create an instance of ``communicator`` class.

Creating a new host communicator with user-supplied size, rank, and kvs:

.. code:: cpp

    communicator environment::create_communicator(
        const size_t size,
        const size_t rank,
        shared_ptr_class<kvs_interface> kvs) const;

size
    user-supplied total number of ranks
rank
    user-supplied rank
kvs
    key-value store for ranks wire-up
return ``communicator``
    communicator object

``communicator`` shall provide methods to retrieve the rank that corresponds to the communicator object and the number of ranks in the communicator. It shall also provide communication operations on host memory buffers.

Retrieving the rank in a communicator:

.. code:: cpp

    size_t communicator::rank() const;

return ``size_t``
    rank of the current process

Retrieving the number of ranks in a communicator:

.. code:: cpp

    size_t communicator::size() const;

return ``size_t``
    number of the ranks

.. note::
    See also: :doc:`collective_operations`


.. _Device Communicator:

Device Communicator
*******************

oneCCL specification defines ``device_communicator`` class that describes a group of communicating ranks, where rank is a single device. ``device_communicator`` defines communication operations on device memory buffers.

.. note::
    Here and below, a device, a device memory, a device context, a queue, and an event are defined in the scope of SYCL device runtime.

The ``environment`` class shall provide the ability to create an instance of ``device_communicator`` class.

Creating a new device communicator with user-supplied size, rank, and kvs:

.. code:: cpp

    using native_device_type = sycl::device;
    using native_context_type = sycl::context;

    vector_class<device_communicator> environment::create_device_communicators(
        const size_t size,
        vector_class<pair_class<size_t, native_device_type>>& rank_device_map,
        native_context_type& context,
        shared_ptr_class<kvs_interface> kvs) const;

size
    user-supplied total number of ranks
rank_device_map
    user-supplied mapping of local ranks on devices
context
    device context
kvs
    key-value store for ranks wire-up
return ``vector_class<device_communicator>``
    a vector of device communicators

``device_communicator`` shall provide methods to retrieve the rank, the device, and the device context that correspond to the communicator object as well as the number of ranks in the communicator. It shall also provide communication operations on device memory buffers.

Retrieving the rank in a communicator:

.. code:: cpp

    size_t device_communicator::rank() const;

return ``size_t``
    the rank that corresponds to the communicator object

Retrieving the number of ranks in a communicator:

.. code:: cpp

    size_t device_communicator::size() const;

return ``size_t``
    the number of the ranks

Retrieving an underlying device, which was used as communicator construction argument:

.. code:: cpp

    native_device_type get_device() const;

return ``native_device_type``
    the device that corresponds to the communicator object

Retrieving an underlying device context, which was used as communicator construction argument:

.. code:: cpp

    native_context_type get_context() const;

return ``native_context_type``
    the device context that corresponds to the communicator object

.. note::
    See also: :doc:`collective_operations`


.. _Request:

Request
*******

Each communication operation of oneCCL shall return a request object for tracking the operation's progress.

.. note::
    See also: :doc:`operation_progress`


.. _Event:

Event
*****

oneCCL specification defines the ``event`` class that wraps the ``sycl::event`` object and encapsulates synchronization context for ``device_communicator`` communication operations.

A vector of events may be passed to the ``device_communicator`` communication operation to designate input dependencies for the operation. An event may be retrieved from ``request`` object to be passed further as an input dependency in other device communication operations or in computation operations.

The ``environment`` class shall provide the ability to create an instance of the ``event`` class from the ``sycl::event`` object.

Creating a new event from ``sycl::event`` object:

.. code:: cpp

    using native_event_type = sycl::event;
    event environment::create_event(native_event_type& native_event) const;

native_event
    the existing native handle for an event
return ``event``
    an event object


.. _Stream:

Stream
******

oneCCL specification defines ``stream`` class that wraps ``sycl::queue`` object and encapsulates execution context for ``device_communicator`` communication operations.

Stream shall be passed to ``device_communicator`` communication operation.

The ``environment`` class shall provide the ability to create an instance of the ``stream`` class from the ``sycl::queue`` object.

Creating a new stream from ``sycl::queue`` object:

.. code:: cpp

    using native_stream_type = sycl::queue;
    stream environment::create_stream(native_stream_type& native_stream) const;

native_stream
    the existing native handle for a stream
return ``stream``
    a stream object


Operation Attributes
********************

Communication operation behavior may be controlled through operation attributes.

:doc:`operation_attributes`
