#ifndef OPENCL_CONTEXT_HPP
# define OPENCL_CONTEXT_HPP

# include "cl.hpp"

# include <string>
# include <iostream>
# include <fstream>
# include <sstream>

class OpenCLContext {
	public:
		OpenCLContext( bool verbose = false);
		~OpenCLContext();

		void	addKernelFromString(std::string kernelCode);
		void	addKernelFromFile(std::string kernelPath);
		void	buildProgram();

		static void checkError(cl_int error, std::string loc="");

		cl::Context				context;
		cl::CommandQueue		queue;
		cl::Program				program;

	private:
		cl::Platform			platform;
		cl::Device				device;
		cl::Program::Sources	sources;
};

#endif

// include_directories(cl_gl.h)
