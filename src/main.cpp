#include "OpenGLWindow.hpp"
#include <sstream>
#include <vector>

#include "cl.hpp"

#include "OpenCLContext.hpp"

int    main ( void ) {
	cl_int err;

	std::cout << "=== Particle System ===" << std::endl;
	OpenCLContext CL;

	CL.addKernelFromFile("../src/kernels/test.cl");
	CL.buildProgram();
	
	// 6. Create Data Buffers
	cl::Buffer buffer_A(CL.context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &err);
	CL.checkError(err, "new buffer A");
	cl::Buffer buffer_B(CL.context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &err);
	CL.checkError(err, "new buffer B");
	
	int *A = (int *)malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; ++i) {
		A[i] = i;
	}
	
	// write arrays A and B to the device
	err = CL.queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
	CL.checkError(err, "enqueueWriteBuffer");
	
	cl::Kernel test(CL.program, "test", &err);
	CL.checkError(err, "Create Kernel Program");
	test.setArg(0, buffer_A);
	test.setArg(1, buffer_B);
	// test.setArg(2, buffer_C);
	err = CL.queue.enqueueNDRangeKernel(test, cl::NullRange, cl::NDRange(10), cl::NullRange);
	CL.checkError(err, "enqueueNDRangeKernel");
	
	err = CL.queue.finish();
	CL.checkError(err, "finish queue");
	
	int *B = (int *)malloc(sizeof(int) * 10);
	
	err = CL.queue.enqueueReadBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);
	CL.checkError(err, "enqueueReadBuffer");
	
	// std::cout << "size of B: " << length(A) << std::endl;
	
	// exit(0);
	
	std::cout << "result: \n";
	for(int i = 0; i < 10; i++){
		std::cout << B[i] << " ";
	}
	
	// OpenGLWindow::initOpenGL();
	
	// OpenGLWindow w(1280, 720, "Particle System");
	
	// w.loop();

	return (0);
}