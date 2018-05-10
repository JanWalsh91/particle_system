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

		void	addKernelFromString(std::string kernelCode);
		void	addKernelFromFile(std::string kernelPath);
		void	buildProgram(std::string name);

		static void checkError(cl_int error, std::string loc="");
		
		cl::Context				context;
		cl::CommandQueue		queue;
		cl::Platform			platform;
		
		// getters
		cl::Kernel &getKernel(std::string name) { return this->kernels[name]; }
	
	private:
		std::map<std::string, cl::Kernel>	kernels;
		cl::Device				device;
		cl::Program::Sources	sources;
};

#endif
