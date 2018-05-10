#include "ParticleSystem.hpp"
#include <exception>
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
	this->GL = new OpenGLWindow(1000, 600, "Particle System");

	std::cout << "check1" << std::endl;
	

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/base.vert");
	shaderPaths.push_back("../src/Shaders/base.frag");
	this->GL->addShaders(shaderPaths);

	std::cout << "check2" << std::endl;
	// Create OpenCL Context
	this->CL = new OpenCLContext(false, true);

	std::cout << "check3" << std::endl;
	// Add Kernels, init Kernel programs
	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particles.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle.cl");
	this->CL->buildProgram();
	// this->CL->setKernel("init_particles");
	// this->CL->setKernel("update_particle");
	
	std::cout << "check4" << std::endl;
	// Create Vertex Arrays and Buffer Objects
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	// Initialize size of Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_STATIC_DRAW);

	std::cout << "check5" << std::endl;
	// define attribute pointers 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	std::cout << "check6" << std::endl;
	// set polygon mode to points
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	std::cout << "check7" << std::endl;
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	std::cout << "check8" << std::endl;
	// tmp:
	this->GL->getShaderProgram().setMatrix("modelMatrix", glm::mat4());
	this->GL->getShaderProgram().setMatrix("viewMatrix", this->camera.getViewMatrix());
	this->GL->getShaderProgram().setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
	);
	std::cout << "check9" << std::endl;
}

/**
	Initializes particles and buffers based on number of particles and layout
*/
void ParticleSystem::init(int numParticles, std::string initLayout) {
	std::cout << "Particle System init" << std::endl;
	cl_int err = 0; 

	this->numParticles = numParticles;
	
	// is it necessary ?
	// glFinish();

	std::cout << "check1" << std::endl;
	// Create openCL Buffer form openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->VBO);

	std::cout << "check2" << std::endl;
	// initialize particles with kernel program on GPU
	// err = this->CL->queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	// this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	// this->CL->getKernel("init_particles").setArg(0, this->CL->getBuffer("particles"));
	// err = this->CL->queue.enqueueNDRangeKernel(this->CL->getKernel("init_particles"), cl::NullRange, cl::NDRange(1), cl::NullRange);
	// this->CL->checkError(err, "init: enqueueNDRangeKernel");
	// this->CL->queue.finish();
	// err = this->CL->queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	// this->CL->checkError(err, "init: enqueueReleaseGLObjects");


	cl::Kernel kernel = cl::Kernel(this->CL->program, "init_particles");
	err = this->CL->queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	kernel.setArg(0, this->CL->getBuffer("particles"));
	err = this->CL->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NullRange);
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	std::cout << "check4" << std::endl;
	err = this->CL->queue.finish();
	this->CL->checkError(err, "init: flush");
	std::cout << "check5" << std::endl;
	err = this->CL->queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	std::cout << "check6" << std::endl;
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
	std::cout << "check7" << std::endl;
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::updateParticles() {
	cl_int err = 0; 
	
	glFinish();

	cl::Kernel kernel = cl::Kernel(this->CL->program, "update_particle");
	err = this->CL->queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	std::cout << "check1" << std::endl;
	this->CL->checkError(err, "updateParticles: enqueueAcquireGLObjects");
	kernel.setArg(0, this->CL->getBuffer("particles"));
	std::cout << "check2" << std::endl;
	err = this->CL->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NullRange);
	this->CL->checkError(err, "updateParticles: enqueueNDRangeKernel");
	std::cout << "check3" << std::endl;
	this->CL->queue.finish();
	std::cout << "check4" << std::endl;
	err = this->CL->queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueReleaseGLObjects");
	std::cout << "check5" << std::endl;
}

void ParticleSystem::loop() {
	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		std::cout << "loop" << std::endl;
		// clear
		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// update position with OpenCL
		this->updateParticles();

		// draw arrays with OpenGL
		std::cout << "draw arrays" << std::endl;
		glDrawArrays(GL_POINTS, 0, this->numParticles);

		// swap buffers
		glfwSwapBuffers(this->GL->getWindow());
		glfwPollEvents();
	}
}