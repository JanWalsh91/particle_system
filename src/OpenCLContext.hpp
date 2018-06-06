#ifndef OPENCL_CONTEXT_HPP
# define OPENCL_CONTEXT_HPP

# include <OpenGL/CGLCurrent.h>
# include <cl.hpp>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>

#include "ExceptionMsg.hpp"

class OpenCLContext {
	public:
		OpenCLContext( bool verbose = false, bool openGLShare = false );
		~OpenCLContext();

		void		addKernelFromString(std::string kernelCode);
		void		addKernelFromFile(std::string kernelPath);
		void		buildProgram();
		void		setKernel(std::string kernelName);

		void		addBuffer(std::string name, GLuint VBO);

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
