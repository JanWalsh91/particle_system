#include "ParticleSystem.hpp"

/**
	Initializes OpenGL and OpenCL contexts
	Loads kernels and shaders
	Creates OpenGL VAO and VBO
*/
ParticleSystem::ParticleSystem() {
	std::cout << "Particle System constructor" << std::endl;

	cl_int err = 0;
	// init OpenGL
	OpenGLWindow::initOpenGL();
	// Create Window
	this->GL = new OpenGLWindow(100, 100, "test");

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/base.vert");
	shaderPaths.push_back("../src/Shaders/base.frag");
	this->GL->addShaders(shaderPaths);

	// Create OpenCL Context
	this->CL = new OpenCLContext(false, true);
	// Add Kernels, init Kernel programs
	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	this->CL->addKernelFromFile("../src/kernels/test.cl");
	this->CL->buildProgram("test");
	this->CL->addKernelFromFile("../src/kernels/init_particles.cl");
	this->CL->buildProgram("init_particles");
	
	// Create Vertex Arrays and Buffer Objects
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

/**
	Initializes particles and buffers based on number of particles and layout
*/
void ParticleSystem::init(int numParticles, std::string initLayout) {
	// std::cout << "Particle System init" << std::endl;
	cl_int err = 0; 

	this->numParticles = numParticles;

	// Initialize size of Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, nullptr, GL_STATIC_DRAW);
	
	glFinish();

	// Create openCL Buffer form openGL Buffer (VBO)
	cl::BufferGL clbuf = cl::BufferGL(this->CL->context, CL_MEM_READ_WRITE, this->VBO, &err);
	this->CL->checkError(err, "BufferGL");

	// Convert to list of cl::Memory to acquire GLObejcts and launch kernel
	std::vector<cl::Memory> cl_vbos;
	cl_vbos.push_back(clbuf);

	// initialize particles with kernel program on GPU
	err = this->CL->queue.enqueueAcquireGLObjects(&cl_vbos, NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	this->CL->getKernel("init_particles").setArg(0, clbuf);
	err = this->CL->queue.enqueueNDRangeKernel(this->CL->getKernel("init_particles"), cl::NullRange, cl::NDRange(1), cl::NullRange);
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	err = this->CL->queue.enqueueReleaseGLObjects(&cl_vbos, NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::loop() {
	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		glEnable(GL_DEPTH_TEST);
		
		glfwPollEvents();

		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(this->GL->getWindow());
	}
}