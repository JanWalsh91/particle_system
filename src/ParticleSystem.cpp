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

	// define attribute pointers 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// set polygon mode to points
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);
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
	
	// is it necessary ?
	glFinish();

	// Create openCL Buffer form openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->VBO);

	// initialize particles with kernel program on GPU
	err = this->CL->queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	this->CL->getKernel("init_particles").setArg(0, this->CL->getBuffer("particles"));
	err = this->CL->queue.enqueueNDRangeKernel(this->CL->getKernel("init_particles"), cl::NullRange, cl::NDRange(1), cl::NullRange);
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	err = this->CL->queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::loop() {
	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		// clear
		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// update position with OpenCL
		

		// draw arrays with OpenGL
		glDrawArrays(GL_POINTS, 0, this->numParticles);


		// swap buffers
		glfwSwapBuffers(this->GL->getWindow());
		glfwPollEvents();
	}
}