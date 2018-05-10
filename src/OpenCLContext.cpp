#include "OpenCLContext.hpp"
#include "OpenGLWindow.hpp"

OpenCLContext::OpenCLContext( bool verbose, bool openGlShare ) {
	cl_int err;

	// 1. Get platform
	std::vector<cl::Platform> all_platforms;
	err = cl::Platform::get(&all_platforms);
	this->checkError(err, "Get Platforms");
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!" <<std::endl;
		exit(1);
	}
	this->platform = all_platforms[0];
	if (verbose)
		std::cout << "Using platform: " << this->platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
	
	// 2. Find a GPU device
	std::vector<cl::Device> all_devices;
	err = this->platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	this->checkError(err, "Get Devices");
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!" << std::endl;
		exit(1);
	}
	this->device = all_devices[1]; // [0] is CPU. [1] is GPU.
	if (verbose)
		std::cout << "Using device: " << this->device.getInfo<CL_DEVICE_NAME>() << std::endl;

	// 3. Create Context
	if (openGlShare) {
		CGLContextObj glContext = (CGLContextObj)CGLGetCurrentContext();
		CGLShareGroupObj shareGroup = CGLGetShareGroup(glContext);
		cl_context_properties properties[] = {
			CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
			(cl_context_properties)shareGroup,
			0
		};
		this->context = cl::Context(this->device, properties, nullptr, nullptr, &err);
	}
	else {
		this->context = cl::Context(this->device, nullptr, nullptr, nullptr, &err);
	}
	this->checkError(err, "Create Context");

	
	// 4. Command Queue on that device
	this->queue = cl::CommandQueue(this->context, this->device, 0, &err);
	this->checkError(err, "Create Queue");
}

OpenCLContext::~OpenCLContext( void ) {}

void	OpenCLContext::addKernelFromString(std::string kernelCode) {
	if (kernelCode == "") {
		std::cout << "Empty Kernel" << std::endl;
		exit(1);
	}
	this->sources.push_back({strdup(kernelCode.c_str()), kernelCode.length()});
}

void	OpenCLContext::addKernelFromFile(std::string kernelPath) {
	// std::cout << "addKernelFromFile" << std::endl;
	std::ifstream		kernelFile;
	std::string			kernelCode;
	std::stringstream	kernelStream;

	try {
		kernelFile.open(kernelPath);
		if (!kernelFile.is_open()) {
			std::cout << "Failed to open kernel file" << std::endl;
			exit(1);
		}
		kernelStream << kernelFile.rdbuf();
		kernelFile.close();
		kernelCode = kernelStream.str();
	}
	catch ( std::ifstream::failure e ) {
		std::cout << "Failed to read kernel from file" << std::endl;
	}
	this->addKernelFromString(kernelCode);
	// std::cout << "done" << std::endl;
}

void	OpenCLContext::buildProgram(std::string kernelName) {
	cl_int err;

	cl::Program program = cl::Program(this->context, this->sources, &err);
	checkError(err, "Create program");

	err = program.build({this->device});
	checkError(err, "Build program");

	this->sources.clear();

	this->kernels[kernelName] = cl::Kernel(program, "init_particles", &err);
}

void	OpenCLContext::addBuffer(std::string bufferName, GLuint VBO) {
	cl_int err;

	this->buffers.push_back(cl::BufferGL(this->context, CL_MEM_READ_WRITE, VBO, &err));
	this->checkError(err, "BufferGL");
	this->bufferIdx[bufferName] = this->buffers.size() - 1;
}


void	OpenCLContext::checkError(cl_int error, std::string loc) {
	if (error) {
		if (loc != "")
			std::cout << loc << ": ";
		std::cout << "error code: " << error << ": ";
		switch(error) {
			// run-time and JIT compiler errors
			case 0: std::cout << "CL_SUCCESS" << std::endl; break;
			case -1: std::cout << "CL_DEVICE_NOT_FOUND" << std::endl; break;
			case -2: std::cout << "CL_DEVICE_NOT_AVAILABLE" << std::endl; break;
			case -3: std::cout << "CL_COMPILER_NOT_AVAILABLE" << std::endl; break;
			case -4: std::cout << "CL_MEM_OBJECT_ALLOCATION_FAILURE" << std::endl; break;
			case -5: std::cout << "CL_OUT_OF_RESOURCES" << std::endl; break;
			case -6: std::cout << "CL_OUT_OF_HOST_MEMORY" << std::endl; break;
			case -7: std::cout << "CL_PROFILING_INFO_NOT_AVAILABLE" << std::endl; break;
			case -8: std::cout << "CL_MEM_COPY_OVERLAP" << std::endl; break;
			case -9: std::cout << "CL_IMAGE_FORMAT_MISMATCH" << std::endl; break;
			case -10: std::cout << "CL_IMAGE_FORMAT_NOT_SUPPORTED" << std::endl; break;
			case -11: std::cout << "CL_BUILD_PROGRAM_FAILURE" << std::endl; break;
			case -12: std::cout << "CL_MAP_FAILURE" << std::endl; break;
			case -13: std::cout << "CL_MISALIGNED_SUB_BUFFER_OFFSET" << std::endl; break;
			case -14: std::cout << "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST" << std::endl; break;
			case -15: std::cout << "CL_COMPILE_PROGRAM_FAILURE" << std::endl; break;
			case -16: std::cout << "CL_LINKER_NOT_AVAILABLE" << std::endl; break;
			case -17: std::cout << "CL_LINK_PROGRAM_FAILURE" << std::endl; break;
			case -18: std::cout << "CL_DEVICE_PARTITION_FAILED" << std::endl; break;
			case -19: std::cout << "CL_KERNEL_ARG_INFO_NOT_AVAILABLE" << std::endl; break;
		
			// compile-time errors
			case -30: std::cout << "CL_INVALID_VALUE" << std::endl; break;
			case -31: std::cout << "CL_INVALID_DEVICE_TYPE" << std::endl; break;
			case -32: std::cout << "CL_INVALID_PLATFORM" << std::endl; break;
			case -33: std::cout << "CL_INVALID_DEVICE" << std::endl; break;
			case -34: std::cout << "CL_INVALID_CONTEXT" << std::endl; break;
			case -35: std::cout << "CL_INVALID_QUEUE_PROPERTIES" << std::endl; break;
			case -36: std::cout << "CL_INVALID_COMMAND_QUEUE" << std::endl; break;
			case -37: std::cout << "CL_INVALID_HOST_PTR" << std::endl; break;
			case -38: std::cout << "CL_INVALID_MEM_OBJECT" << std::endl; break;
			case -39: std::cout << "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR" << std::endl; break;
			case -40: std::cout << "CL_INVALID_IMAGE_SIZE" << std::endl; break;
			case -41: std::cout << "CL_INVALID_SAMPLER" << std::endl; break;
			case -42: std::cout << "CL_INVALID_BINARY" << std::endl; break;
			case -43: std::cout << "CL_INVALID_BUILD_OPTIONS" << std::endl; break;
			case -44: std::cout << "CL_INVALID_PROGRAM" << std::endl; break;
			case -45: std::cout << "CL_INVALID_PROGRAM_EXECUTABLE" << std::endl; break;
			case -46: std::cout << "CL_INVALID_KERNEL_NAME" << std::endl; break;
			case -47: std::cout << "CL_INVALID_KERNEL_DEFINITION" << std::endl; break;
			case -48: std::cout << "CL_INVALID_KERNEL" << std::endl; break;
			case -49: std::cout << "CL_INVALID_ARG_INDEX" << std::endl; break;
			case -50: std::cout << "CL_INVALID_ARG_VALUE" << std::endl; break;
			case -51: std::cout << "CL_INVALID_ARG_SIZE" << std::endl; break;
			case -52: std::cout << "CL_INVALID_KERNEL_ARGS" << std::endl; break;
			case -53: std::cout << "CL_INVALID_WORK_DIMENSION" << std::endl; break;
			case -54: std::cout << "CL_INVALID_WORK_GROUP_SIZE" << std::endl; break;
			case -55: std::cout << "CL_INVALID_WORK_ITEM_SIZE" << std::endl; break;
			case -56: std::cout << "CL_INVALID_GLOBAL_OFFSET" << std::endl; break;
			case -57: std::cout << "CL_INVALID_EVENT_WAIT_LIST" << std::endl; break;
			case -58: std::cout << "CL_INVALID_EVENT" << std::endl; break;
			case -59: std::cout << "CL_INVALID_OPERATION" << std::endl; break;
			case -60: std::cout << "CL_INVALID_GL_OBJECT" << std::endl; break;
			case -61: std::cout << "CL_INVALID_BUFFER_SIZE" << std::endl; break;
			case -62: std::cout << "CL_INVALID_MIP_LEVEL" << std::endl; break;
			case -63: std::cout << "CL_INVALID_GLOBAL_WORK_SIZE" << std::endl; break;
			case -64: std::cout << "CL_INVALID_PROPERTY" << std::endl; break;
			case -65: std::cout << "CL_INVALID_IMAGE_DESCRIPTOR" << std::endl; break;
			case -66: std::cout << "CL_INVALID_COMPILER_OPTIONS" << std::endl; break;
			case -67: std::cout << "CL_INVALID_LINKER_OPTIONS" << std::endl; break;
			case -68: std::cout << "CL_INVALID_DEVICE_PARTITION_COUNT" << std::endl; break;
		
			// extension errors
			case -1000: std::cout << "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR" << std::endl; break;
			case -1001: std::cout << "CL_PLATFORM_NOT_FOUND_KHR" << std::endl; break;
			case -1002: std::cout << "CL_INVALID_D3D10_DEVICE_KHR" << std::endl; break;
			case -1003: std::cout << "CL_INVALID_D3D10_RESOURCE_KHR" << std::endl; break;
			case -1004: std::cout << "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR" << std::endl; break;
			case -1005: std::cout << "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR" << std::endl; break;
			default: std::cout << "Unknown OpenCL error" << std::endl; break;
		}
		exit(0);
	}
}

// Getters
cl::Kernel	&OpenCLContext::getKernel(std::string name) {
	return this->kernels[name];
}

cl::Memory	&OpenCLContext::getBuffer(std::string name) {
	return this->buffers[this->bufferIdx[name]];
}

std::vector<cl::Memory>	&OpenCLContext::getBuffers() {
	return this->buffers;
}