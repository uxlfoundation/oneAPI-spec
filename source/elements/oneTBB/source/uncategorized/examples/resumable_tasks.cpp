#include <thread>
#include <iostream>

#define TBB_PREVIEW_RESUMABLE_TASKS 1
#include "tbb/task.h"
#include "tbb/parallel_for.h"
#include "tbb/concurrent_queue.h"

typedef int data_t;

class AsyncActivity {
    typedef std::pair<data_t*, tbb::task::suspend_point> work_t;

public:
    AsyncActivity() : m_asyncThread(&AsyncActivity::asyncLoop, this) {}

    ~AsyncActivity() {
        m_tagQueue.push({NULL, NULL});
        m_asyncThread.join();
    }

    void submit(data_t& data, tbb::task::suspend_point tag) {
        m_tagQueue.push({&data, tag});
    }

private:
    void asyncLoop() {
        work_t work;
        m_tagQueue.pop(work);
        while (work.second) {
            // Process an async work
            asyncWork(*work.first);
            // Signal to resume execution of the task referenced by the tbb::task::suspend_point
            tbb::task::resume(work.second);
            // Process a next item
            m_tagQueue.pop(work);
        }
    }

    void asyncWork(data_t& data) {
        data++;
    }

    // Work items storage
    tbb::concurrent_bounded_queue<work_t> m_tagQueue;
    // Dedicated thread to process async work
    std::thread m_asyncThread;
};

data_t preStep(int data) {
    std::cout << "Pre step: " << data << std::endl;
    return data_t(data);
}

void postStep(data_t& data) {
    std::cout << "Post step: " << data << std::endl;
}

int main() {
    // Dedicated user-managed activity that processes async requests
    AsyncActivity async_activity;

    // Parallel computation
    tbb::parallel_for(0, 10, [&async_activity](int i) {
        data_t data = preStep(i);
        // Suspend the current task execution and capture the context
        tbb::task::suspend([&async_activity, &data] (tbb::task::suspend_point tag) {
            async_activity.submit(data, tag); // could be OpenCL/IO/Database/Network etc.
        }); // execution will be resumed after this function
        postStep(data);
    });

    return 0;
}
