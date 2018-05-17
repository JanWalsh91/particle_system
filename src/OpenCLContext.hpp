#ifndef OPENCL_CONTEXT_HPP
# define OPENCL_CONTEXT_HPP

// # define __CL_ENABLE_EXCEPTIONS
# include <OpenCL/opencl.h>
# include <OpenGL/CGLCurrent.h>
# include <cl.hpp>

// #define CL_HPP_TARGET_OPENCL_VERSION 200
// #define CL_HPP_MINIMUM_OPENCL_VERSION 120
// #include <cl2.hpp>
#include <cl_gl.h>
// # pragma OPENCL EXTENSION cl_khr_fp16 : enable
#pragma OPENCL EXTENSION CL_APPLE_gl_sharing : enable
#pragma OPENCL EXTENSION CL_KHR_gl_sharing : enable


# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>

class OpenCLContext {
	public:
		OpenCLContext( bool verbose = false, bool openGLShare = false );
		~OpenCLContext();

		// Kernel management
		void		addKernelFromString(std::string kernelCode);
		void		addKernelFromFile(std::string kernelPath);
		void		buildProgram();
		void		setKernel(std::string kernelName);

		// Buffer management
		void		addBuffer(std::string name, GLuint VBO);

		// OpenCL error checking
		static void checkError(cl_int error, std::string loc="");
		
		// getters
		cl::CommandQueue		&getQueue();
		cl::Kernel				&getKernel(std::string name);
		cl::Memory				&getBuffer(std::string name);
		std::vector<cl::Memory>	&getBuffers();

	private:
		cl::Platform						platform;
		cl::Device							device;
		cl::Context							context;
		cl::CommandQueue					queue;
		cl::Program::Sources				sources;
		cl::Program							program;
		std::map<std::string, cl::Kernel>	kernels;
		std::map<std::string, int>			bufferIdx;
		std::vector<cl::Memory>				buffers;
};

#endif
