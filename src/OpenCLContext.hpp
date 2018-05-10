#ifndef OPENCL_CONTEXT_HPP
# define OPENCL_CONTEXT_HPP

#include <cl.hpp>
# include <OpenCL/opencl.h>
# include <OpenGL/CGLCurrent.h>
// #include <cl.h>
#include <cl_gl.h>
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

		// make private if possible
		cl::Context				context;
		cl::CommandQueue		queue;
		cl::Platform			platform;

		// Kernel management
		void	addKernelFromString(std::string kernelCode);
		void	addKernelFromFile(std::string kernelPath);
		void	buildProgram(std::string kernelName);

		// Buffer management
		void	addBuffer(std::string name, GLuint VBO);

		static void checkError(cl_int error, std::string loc="");
		
		// getters
		cl::Kernel	&getKernel(std::string name);
		cl::Memory	&getBuffer(std::string name);
		std::vector<cl::Memory>			&getBuffers();

	private:
		std::map<std::string, cl::Kernel>	kernels;
		std::map<std::string, int>			bufferIdx;
		std::vector<cl::Memory>				buffers;
		cl::Device				device;
		cl::Program::Sources	sources;
};

#endif
