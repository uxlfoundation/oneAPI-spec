Generic Workflow
================

Below is a generic workflow with oneCCL API

1. Initialize the library:

.. code:: cpp

    auto env = environment::instance();

2. Create a main built-in key-value store. Its address should be distributed
using an out-of-band communication mechanism and be used to create key-value stores on other processes:

.. code:: cpp

    /* for example use MPI as an out-of-band communication mechanism */
    int mpi_rank, mpi_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    kvs_interface kvs;
    kvs::addr kvs_addr;

    if (mpi_rank == 0) {
        kvs = env.create_main_kvs();
        kvs_addr = kvs->get_addr();
        MPI_Bcast((void*)kvs_addr.data(), kvs::addr_max_size, MPI_BYTE, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Bcast((void*)kvs_addr.data(), kvs::addr_max_size, MPI_BYTE, 0, MPI_COMM_WORLD);
        kvs = env.create_kvs(kvs_addr);
    }

3. Create a host communicator or device communicator(s):

.. code:: cpp

    /* for host communications */
    auto comm = env.create_communicator(mpi_size, kvs);

.. code:: cpp

    /* for device communications, for example with multiple devices per process */

    /* rank_to_sycl_dev_map -> map<size_t, sycl::device> */
    /* sycl_queues -> vector<sycl::queue> */
    /* sycl_ctx -> sycl::context */

    auto comms = env.create_device_communicators(mpi_size * rank_to_sycl_dev_map.size(),
                                                 rank_to_sycl_dev_map,
                                                 sycl_ctx,
                                                 kvs);

    /* create stream objects from sycl::queue objects */
    std::vector<request> streams;
    for (auto& comm : comms) {
        streams.push_back(env.create_stream(sycl_queues[comm->rank()]));
    }

4. Execute a communication operation of choice on the communicator(s):

.. code:: cpp

    /* for host communications */
    auto request = comm->allreduce(...);
    request->wait();

.. code:: cpp

    /* for device communications */
    std::vector<request> reqs;
    for (auto& comm : comms) {
        reqs.push_back(comm->allreduce(..., streams[comm->rank()]));
    }

    for (auto& req : reqs) {
        req->wait();
    }
