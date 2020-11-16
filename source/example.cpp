#include <CL/sycl.hpp>
using namespace sycl;

int main() {
  // declare host arrays
  double *Ahost = new double[M*N];
  double *Bhost = new double[N*P];
  double *Chost = new double[M*P];

  {
    // Initializing the devices queue with a gpu_selector
    queue q{gpu_selector()};

    // Creating 2D buffers for matrices which are bound to host arrays
    buffer<double, 2> a{Ahost, range<2>{M,N}};
    buffer<double, 2> b{Bhost, range<2>{N,P}};
    buffer<double, 2> c{Chost, range<2>{M,P}};

    // Submitting command group to queue to compute matrix c=a*b
    q.submit([&](handler &h){
	       // Read from a and b, write to c
	       auto A = a.get_access<access::mode::read>(h);
	       auto B = b.get_access<access::mode::read>(h);
	       auto C = c.get_access<access::mode::write>(h);

	       int WidthA = a.get_range()[1];

	       // Executing kernel
	       h.parallel_for(range<2>{M, P},
			      [=](id<2> index){
				int row = index[0];
				int col = index[1];

				// Compute the result of one element in c
				double sum = 0.0;
				for (int i = 0; i < WidthA; i++) {
				  sum += A[row][i] * B[i][col];
				}
				C[index] = sum;
			      });
	     });
  }
  // when we exit the block, the buffer destructor will write result back to C.
}
