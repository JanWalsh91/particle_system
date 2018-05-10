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

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/base.vert");
	shaderPaths.push_back("../src/Shaders/base.frag");
	this->GL->addShaders(shaderPaths);

	// Create OpenCL Context
	this->CL = new OpenCLContext(false, true);

	// Add Kernels, init Kernel programs
	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle.cl");
	this->CL->buildProgram();
	this->CL->setKernel("init_particle");
	this->CL->setKernel("update_particle");
	
	// Create Vertex Arrays and Buffer Objects
	this->GL->addVAO("particles");
	this->GL->addVBO("particles");
	glBindVertexArray(this->GL->getVAO("particles"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("particles"));
	glBindVertexArray(0);

	// set polygon mode to points
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// TODO: move elsewhere
	this->GL->getShaderProgram().setMatrix("modelMatrix", glm::mat4());
	this->GL->getShaderProgram().setMatrix("viewMatrix", this->camera.getViewMatrix());
	this->GL->getShaderProgram().setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
	);
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

	// Initialize size of Buffer
	size_t buffSize = sizeof(float) * 6 * numParticles;
	glBindVertexArray(this->GL->getVAO("particles"));
	glBufferData(GL_ARRAY_BUFFER, buffSize, nullptr, GL_STATIC_DRAW);

	// define attribute pointers 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, buffSize, (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, buffSize, (void *)0);
	glEnableVertexAttribArray(1);

	// Create openCL Buffer form openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->GL->getVBO("particles"));

	// initialize particles with kernel program on GPU
	cl::CommandQueue queue = this->CL->getQueue();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	this->CL->getKernel("init_particle").setArg(0, this->CL->getBuffer("particles"));
	err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
	glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem() {}

void ParticleSystem::updateParticles() {
	cl_int err = 0; 
	
	glFinish();

	cl::CommandQueue queue = this->CL->getQueue();
	glBindVertexArray(this->GL->getVAO("particles"));
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueAcquireGLObjects");
	this->CL->getKernel("update_particle").setArg(0, this->CL->getBuffer("particles"));
	err = queue.enqueueNDRangeKernel(this->CL->getKernel("update_particle"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	this->CL->checkError(err, "updateParticles: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueReleaseGLObjects");
	glBindVertexArray(0);
}

void ParticleSystem::loop() {
	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		// std::cout << "loop" << std::endl;
		// clear
		glClearColor(.0f, .0f, .0f, .0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// update position with OpenCL
		this->updateParticles();

		// draw arrays with OpenGL
		glBindVertexArray(this->GL->getVAO("particles"));
		glDrawArrays(GL_POINTS, 0, this->numParticles);
		glBindVertexArray(0);

		// swap buffers
		glfwSwapBuffers(this->GL->getWindow());
		glfwPollEvents();
	}
}