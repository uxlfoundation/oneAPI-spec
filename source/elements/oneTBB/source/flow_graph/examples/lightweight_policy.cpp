#include "tbb/flow_graph.h"

int main() {
    using namespace tbb::flow;

    graph g;

    function_node< int, int > add( g, unlimited, [](const int &v) {
        return v+1;
    } );
    function_node< int, int, lightweight > multiply( g, unlimited, [](const int &v) {
        return v*2;
    } );
    function_node< int, int, lightweight > cube( g, unlimited, [](const int &v) {
        return v*v*v;
    } );

    make_edge(add, multiply);
    make_edge(multiply, cube);

    for(int i = 1; i <= 10; ++i)
        add.try_put(i);
    g.wait_for_all();

    return 0;
}
