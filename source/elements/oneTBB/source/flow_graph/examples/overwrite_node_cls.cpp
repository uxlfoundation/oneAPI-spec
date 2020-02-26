#include "tbb/flow_graph.h"
#include <chrono>
#include <thread>

int main() {
    const int data_limit = 20;
    int count = 0;

    tbb::flow::graph g;
 
    tbb::flow::function_node< int, int > data_set_preparation(g, tbb::flow::unlimited, []( int data ) {
        printf("Prepare large data set and keep it inside node storage\n");
        return data;
    });
 
    tbb::flow::overwrite_node< int > overwrite_storage(g);
 
    tbb::flow::source_node<int> data_generator(g, [&]( int& v ) -> bool {
        if ( count < data_limit ) {
            ++count;
            v = count;
            return true;
        } else {
            return false;
        }
    }, false);
 
    tbb::flow::function_node< int > process(g, tbb::flow::unlimited, [&]( const int& data) {
        int data_from_storage = 0;
        overwrite_storage.try_get(data_from_storage);
        printf("Data from a storage: %d\n", data_from_storage);
        printf("Data to process: %d\n", data);
    });
 
    tbb::flow::make_edge(data_set_preparation, overwrite_storage);
    tbb::flow::make_edge(data_generator, process);
 
    data_set_preparation.try_put(1);
    data_generator.activate();
 
    g.wait_for_all();

    return 0;
}
