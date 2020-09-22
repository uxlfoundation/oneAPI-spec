.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Generic Workflow
================

Below is a generic workflow with oneCCL API

1. Create a main built-in key-value store. Its address should be distributed
using an out-of-band communication mechanism and be used to create key-value stores on other processes:

.. code:: cpp

    /* for example use MPI as an out-of-band communication mechanism */

    int mpi_rank, mpi_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    kvs_interface kvs;
    kvs::address_type kvs_addr;

    if (mpi_rank == 0) {
        kvs = ccl::create_main_kvs();
        kvs_addr = kvs->get_address();
        MPI_Bcast((void*)kvs_addr.data(), kvs::address_max_size, MPI_BYTE, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Bcast((void*)kvs_addr.data(), kvs::address_max_size, MPI_BYTE, 0, MPI_COMM_WORLD);
        kvs = ccl::create_kvs(kvs_addr);
    }

2. Create communicator(s):

.. code:: cpp

    /* for host communications */
    auto comm = ccl::create_communicator(mpi_size, mpi_rank, kvs);

.. code:: cpp

    /* for SYCL devices communications, for example with multiple devices per process */

    /* sycl_context -> cl::sycl::context */
    /* sycl_devices -> vector<cl::sycl::device> */
    /* sycl_queues  -> vector<cl::sycl::queue> */

    /* create ccl::context object from cl::sycl::context object */
    auto ccl_context = ccl::create_context(sycl_context);

    /* create ccl::device objects from cl::sycl::device objects */
    std::vector<device> ccl_devices;
    for (size_t idx = 0; idx < sycl_devices.size(); idx++) {
        ccl_devices.push_back(ccl::create_device(sycl_devices[idx]));
    }

    std::vector<std::pair<size_t, device>> r2d_map;
    for (auto& dev : ccl_devices) {
        r2d_map.push_back(<rank>, dev);
    }

    /* create ccl::stream objects from cl::sycl::queue objects */
    std::vector<stream> ccl_streams;
    for (size_t idx = 0; idx < sycl_queues.size(); idx++) {
        ccl_streams.push_back(ccl::create_stream(sycl_queues[idx]));
    }

    auto comms = ccl::create_communicators(mpi_size * r2d_map.size(),
                                           r2d_map,
                                           ccl_context,
                                           kvs);

3. Execute a communication operation of choice on the communicator(s):

.. code:: cpp

    /* for host communications */
    allreduce(..., comm).wait();

.. code:: cpp

    /* for SYCL devices communications */
    std::vector<event> events;
    for (auto& comm : comms) {
        events.push_back(allreduce(..., comm, ccl_streams[comm.rank()]));
    }

    for (auto& e : events) {
        e.wait();
    }
