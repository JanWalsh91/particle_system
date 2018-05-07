#include <sstream>
#include <vector>
#include <cl.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cl_gl.h> // is this necessary?

#include "OpenGLWindow.hpp"
#include "OpenCLContext.hpp"

int    main ( void ) {
	cl_int err = 0;

	std::cout << "=== Particle System ===" << std::endl;
	OpenCLContext CL;

	CL.addKernelFromFile("../src/kernels/particle.h.cl");
	CL.addKernelFromFile("../src/kernels/test.cl");
	// CL.addKernelFromFile("../src/kernels/update_particle.cl");
	CL.buildProgram();
	
	
	OpenGLWindow::initOpenGL();
	OpenGLWindow GL(100, 100, "test");
	
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float *particle = nullptr;

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, particle, GL_STATIC_DRAW);
	
	// cl::BufferGL clbuf = cl::BufferGL(CL.context, CL_MEM_READ_WRITE, VAO, &err);
	CL.checkError(err, "BufferGL");

	GL.loop();



	// == OPENCL tests == 
	// // 6. Create Data Buffers
	// cl::Buffer buffer_A(CL.context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &err);
	// CL.checkError(err, "new buffer A");
	// cl::Buffer buffer_B(CL.context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &err);
	// CL.checkError(err, "new buffer B");
	
	// int *A = (int *)malloc(sizeof(int) * 10);
	// for (int i = 0; i < 10; ++i) {
	// 	A[i] = i;
	// }
	
	// // write arrays A and B to the device
	// err = CL.queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
	// CL.checkError(err, "enqueueWriteBuffer");
	
	// cl::Kernel test(CL.program, "test", &err);
	// CL.checkError(err, "Create Kernel Program");
	// test.setArg(0, buffer_A);
	// test.setArg(1, buffer_B);
	// // test.setArg(2, buffer_C);
	// err = CL.queue.enqueueNDRangeKernel(test, cl::NullRange, cl::NDRange(10), cl::NullRange);
	// CL.checkError(err, "enqueueNDRangeKernel");
	
	// err = CL.queue.finish();
	// CL.checkError(err, "finish queue");
	
	// int *B = (int *)malloc(sizeof(int) * 10);
	
	// err = CL.queue.enqueueReadBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);
	// CL.checkError(err, "enqueueReadBuffer");
	
	// // std::cout << "size of B: " << length(A) << std::endl;
	
	// // exit(0);
	
	// std::cout << "result: \n";
	// for(int i = 0; i < 10; i++){
	// 	std::cout << B[i] << " ";
	// }
	// == END test == 


	// OpenGLWindow::initOpenGL();
	
	// OpenGLWindow w(1280, 720, "Particle System");
	
	// w.loop();

	return (0);
}