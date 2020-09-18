#include <vector>
#include <unordered_map>

namespace sycl {
struct device_selector {
    virtual ~device_selector();
};
struct gpu_selector : public device_selector {};
struct device {
    device(device_selector);
};
struct context {
    context(device);
};
struct queue {
    queue(device);
};
struct event {};
void *malloc_device(size_t, device, context);
} // namespace sycl

namespace dnnl {
struct engine {};
struct stream {};
struct memory {
    enum class data_type { f32 };
    enum class format_tag { nhwc };
    struct desc {
        desc(std::vector<int> dims, data_type, format_tag);
    };
    memory::desc get_desc();

    memory(memory::desc, engine, void *);
};

enum class memory_kind { usm };
enum class prop_kind { forward_inference };
enum class algorithm { eltwise_relu };

struct primitive {
    virtual ~primitive();
};

struct eltwise_forward : public primitive {
    struct desc {
        desc(prop_kind, algorithm, memory::desc, float, float);
    };
    struct primitive_desc {
        primitive_desc(desc, engine);
    };
    eltwise_forward(primitive_desc);
};

namespace sycl_interop {
engine make_engine(sycl::device, sycl::context);

stream make_stream(engine, sycl::queue);

memory make_memory(memory::desc, engine, memory_kind, void *);

sycl::event execute(primitive, stream, std::unordered_map<int, dnnl::memory>,
        std::vector<sycl::event>);
} // namespace sycl_interop
} // namespace dnnl

#define DNNL_ARG_SRC 0
#define DNNL_ARG_DST 1

// Tensor dimensions
int N, C, H, W;

// User-owned DPC++ objects
sycl::device dev {sycl::gpu_selector {}}; // Device
sycl::context ctx {dev}; // Context
sycl::queue queue {dev}; // Queue
std::vector<sycl::event> dependencies; // Input events dependencies
// Source
float *buf_src = static_cast<float *>(
        sycl::malloc_device((N * C * H * W) * sizeof(float), dev, ctx));
// Results
float *buf_dst = static_cast<float *>(
        sycl::malloc_device((N * C * H * W) * sizeof(float), dev, ctx));

// Create an engine encapsulating users' DPC++ GPU device and context
dnnl::engine engine = dnnl::sycl_interop::make_engine(dev, ctx);
// Create a stream encapsulating users' DPC++ GPU queue
dnnl::stream stream = dnnl::sycl_interop::make_stream(engine, queue);
// Create memory objects that use buf_src and buf_dst as the underlying storage
dnnl::memory mem_src({{N, C, H, W}, dnnl::memory::data_type::f32,
                             dnnl::memory::format_tag::nhwc},
        engine, buf_src);
dnnl::memory mem_dst({{N, C, H, W}, dnnl::memory::data_type::f32,
                             dnnl::memory::format_tag::nhwc},
        engine, buf_dst);
// Create a ReLU elementwise primitive
dnnl::eltwise_forward relu {
        {{dnnl::prop_kind::forward_inference, dnnl::algorithm::eltwise_relu,
                 mem_src.get_desc(), 0.f, 0.f},
                engine}};
// Execute the ReLU primitive in the stream passing input dependencies and
// retrieving the output dependency
sycl::event event = dnnl::sycl_interop::execute(relu, stream,
        {{DNNL_ARG_SRC, mem_src}, {DNNL_ARG_DST, mem_dst}}, dependencies);
