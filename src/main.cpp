#include "OpenGLWindow.hpp"
#include <sstream>
#include <vector>

#include "cl.hpp"

int    main ( void ) {
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	// get default device (CPUs, GPUs) of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0){
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}

	// use device[1] because that's a GPU; device[0] is the CPU
	const cl::Device default_device = all_devices[1];
	cl::Platform platform;
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
	std::cout << "Platform info: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
	std::cout << "numbder of devices: " << all_devices.size() << std::endl;

	cl::Context context(default_device);
	
	cl::Program::Sources sources;

	std::ifstream kernelFile;
	std::string path = "../src/kernels/test.cl";
	// std::string path = "main.cpp";
	std::string kernelCode;
	try
	{
		kernelFile.open(path);
		if (!kernelFile.is_open()) {
			std::cout << "Failed to open file" << std::endl;
		}
		std::stringstream kernelStream;
		kernelStream << kernelFile.rdbuf();
		kernelFile.close();
		kernelCode = kernelStream.str();
	}
	catch ( std::ifstream::failure e )
	{
		std::cout << "ERROR::KERNEL::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	std::cout << "kernelCode: " << kernelCode << std::endl;
	
	sources.push_back({kernelCode.c_str(), kernelCode.length()});

	cl::Program program(context, sources);
	
	if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
	}
	
	// create buffers on the device
	cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);

	int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context,default_device);
	
	//write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
    // queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);
	
	
	cl::Kernel times_two(program, "times_two");
	times_two.setArg(0, buffer_A);
	times_two.setArg(1, buffer_B);
	// times_two.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(times_two, cl::NullRange, cl::NDRange(10), cl::NullRange);

	// queue.finish();

	// times_two(buffer_A, buffer_B);

	std::vector<int> B(0, 10);

	queue.enqueueReadBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B.data());
	
	std::cout << "size of B: " << B.size() << std::endl;

	exit(0);

	std::cout<<" result: \n";
    for(int i=0;i<10;i++){
		std::cout<<B[i]<<" ";
    }
	
	// OpenGLWindow::initOpenGL();

	// OpenGLWindow w(1280, 720, "Particle System");

	// w.loop();

	return (0);
}