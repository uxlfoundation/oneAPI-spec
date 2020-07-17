Device Communication Support
============================

Device memory communications between processes are provided by :ref:`Device Communicator`.

The example below demonstrates the main concepts of communication on device memory buffers.

Example
-------

Consider a simple oneCCL ``allreduce`` example for GPU:

1. Create oneCCL device communicator objects with user-supplied size, rank <-> SYCL device mapping, SYCL context and kvs:

.. code:: cpp

    auto env = environment::instance();
    auto comms = env.create_device_communicators(size, rank_sycl_dev_map, sycl_ctx, kvs);

2. Create oneCCL stream object from user-supplied ``sycl::queue`` object:

.. code:: cpp

    auto stream = env.create_stream(sycl_queue);

3. Initialize ``send_buf`` (in real scenario it is supplied by the user):

.. code:: cpp

    const size_t elem_count = <N>;

    /* using SYCL buffer and accessor */
    auto send_buf_host_acc = send_buf.get_access<mode::write>();
    for (idx = 0; idx < elem_count; idx++) {
        send_buf_host_acc[idx] = rank;
    }

.. code:: cpp

    /* or using SYCL USM */
    for (idx = 0; idx < elem_count; idx++) {
        send_buf[idx] = rank;
    }

4. For demonstration purposes, modify the ``send_buf`` on the GPU side:

.. code:: cpp

    /* using SYCL buffer and accessor */
    sycl_queue.submit([&](cl::sycl::handler& cgh) {
        auto send_buf_dev_acc = send_buf.get_access<mode::write>(cgh);
        cgh.parallel_for<class allreduce_send_buf_modify>(range<1>{elem_count}, [=](item<1> idx) {
            send_buf_dev_acc[idx] += 1;
        });
    });

.. code:: cpp

    /* or using SYCL USM */
    for (idx = 0; idx < elem_count; idx++) {
        send_buf[idx]+ = 1;
    }

5. ``allreduce`` invocation performs reduction of values from all processes and then distributes the result to all processes. In this case, the result is an array with ``elem_count`` elements, where all elements are equal to the sum of arithmetical progression:

    .. math::
        p \cdot (p + 1) / 2

.. code:: cpp

    std::vector<request_t> reqs;
    for (auto& comm : comms) {
        reqs.push_back(comm->allreduce(send_buf,
                                       recv_buf,
                                       elem_count,
                                       reduction::sum,
                                       streams[comm->rank()]));
    }

    for (auto& req : reqs) {
        req->wait();
    }

6. Check the correctness of ``allreduce`` operation on the GPU:

.. code:: cpp

    /* using SYCL buffer and accessor */

    auto comm_size = comm->size();
    auto expected = comm_size * (comm_size + 1) / 2;

    sycl_queue.submit([&](handler& cgh) {
        auto recv_buf_dev_acc = recv_buf.get_access<mode::write>(cgh);
        cgh.parallel_for<class allreduce_recv_buf_check>(range<1>{elem_count}, [=](item<1> idx) {
            if (recv_buf_dev_acc[idx] != expected) {
                recv_buf_dev_acc[idx] = -1;
            }
        });
    });

    ...

    auto recv_buf_host_acc = recv_buf.get_access<mode::read>();
    for (idx = 0; idx < elem_count; idx++) {
        if (recv_buf_host_acc[idx] == -1) {
            std::count << "unexpected value at index " << idx << std::endl;
            break;
        }
    }

.. code:: cpp

    /* or using SYCL USM */

    auto comm_size = comm->size();
    auto expected = comm_size * (comm_size + 1) / 2;

    for (idx = 0; idx < elem_count; idx++) {
        if (recv_buf[idx] != expected) {
            std::count << "unexpected value at index " << idx << std::endl;
            break;
        }
    }
