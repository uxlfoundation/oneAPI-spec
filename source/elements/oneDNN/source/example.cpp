#include <vector>
#include <unordered_map>

namespace sycl {
struct device {};
struct context {};
struct queue {};
struct event {};
template <int N>
struct range {
    range(int);
};
template <typename T, int N>
struct buffer {
    buffer(sycl::range<N>);
};
} // namespace sycl

namespace dnnl {
struct engine {
    enum class kind { gpu };
    engine(kind, sycl::device, sycl::context);
};
struct stream {
    stream(engine, sycl::queue);
};
struct memory {
    enum class data_type { f32 };
    enum class format_tag { nhwc };
    struct desc {
        desc(std::vector<int> dims, data_type, format_tag);
    };
    memory(dnnl::memory::desc, dnnl::engine);
    memory(dnnl::memory::desc, dnnl::engine, sycl::buffer<float, 1>);
    memory::desc get_desc();
};

enum class prop_kind { forward_inference };
enum class algorithm { eltwise_relu };

struct eltwise_forward {
    struct desc {
        desc(prop_kind, algorithm, memory::desc, float, float);
    };
    struct primitive_desc {
        primitive_desc(desc, engine);
    };
    eltwise_forward(primitive_desc);

    sycl::event execute_sycl(dnnl::stream, std::unordered_map<int, dnnl::memory> args,
            std::vector<sycl::event> dependencies);
    void execute(dnnl::stream, std::unordered_map<int, dnnl::memory> args);
};
} // namespace dnnl

#define DNNL_ARG_SRC 0
#define DNNL_ARG_DST 1


// Tensor dimensions
int N, C, H, W;

// User-owned DPC++ objects
sycl::device dev; // Device
sycl::context ctx; // Context
sycl::queue queue; // Queue
std::vector<sycl::event> dependencies; // Input dependencies
sycl::buffer<float, 1> buf_src {sycl::range<1> {N * C * H * W}}; // Buffer with source data
sycl::buffer<float, 1> buf_dst {sycl::range<1> {N * C * H * W}}; // Buffer for result data

// Create a GPU engine encapsulating users' DPC++ GPU device and context
dnnl::engine engine {dnnl::engine::kind::gpu, dev, ctx};
// Create a GPU stream encapsulating users' DPC++ GPU queue
dnnl::stream stream {engine, queue};
// Create oneDNN memory objects that use buf_src and buf_dst as the underlying storage
dnnl::memory mem_src {{{N, C, H, W}, dnnl::memory::data_type::f32, dnnl::memory::format_tag::nhwc},
        engine, buf_src};
dnnl::memory mem_dst {{{N, C, H, W}, dnnl::memory::data_type::f32, dnnl::memory::format_tag::nhwc},
        engine, buf_dst};
// Create a ReLU elementwise primitive
dnnl::eltwise_forward relu {{{dnnl::prop_kind::forward_inference, dnnl::algorithm::eltwise_relu,
                                     mem_src.get_desc(), 0.f, 0.f},
        engine}};
// Execute the ReLU primitive in the stream passing input events and retrieving the output event
sycl::event event = relu.execute_sycl(
        stream, {{DNNL_ARG_SRC, mem_src}, {DNNL_ARG_DST, mem_dst}}, dependencies);
