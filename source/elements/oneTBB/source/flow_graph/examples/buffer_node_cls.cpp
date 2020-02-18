#include "tbb/flow_graph.h"
#include <chrono>
#include <thread>

int main() {
    tbb::flow::graph g;

    tbb::flow::function_node< int, int > prepare(g, tbb::flow::unlimited, [] (const int& data) {
        printf("Prepare data: %d\n", data);
        return data;
    });

    tbb::flow::buffer_node< int > load_balancer(g); 

    tbb::flow::function_node< int, tbb::flow::continue_msg, tbb::flow::rejecting > 
            first_worker(g, tbb::flow::serial, [] (const int& data) {
                 printf("Process data with first worker: %d\n", data);
                 // Long computation
                 std::this_thread::sleep_for(std::chrono::milliseconds(5));
    });

    tbb::flow::function_node< int, tbb::flow::continue_msg, tbb::flow::rejecting > 
            second_worker(g, tbb::flow::serial, [] (const int& data) {
                 printf("Process data with second worker: %d\n", data);
                 // Long computation
                 std::this_thread::sleep_for(std::chrono::milliseconds(5));
    });

    tbb::flow::make_edge(prepare, load_balancer);
    tbb::flow::make_edge(load_balancer, first_worker);
    tbb::flow::make_edge(load_balancer, second_worker);

    for (int i = 0; i < 10; ++i) {
        prepare.try_put(i);
    }

    g.wait_for_all();

    return 0;
}
