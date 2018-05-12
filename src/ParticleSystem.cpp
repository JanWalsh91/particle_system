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
	this->GL = new OpenGLWindow(1500, 1000, "Particle System");	

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/base.vert");
	shaderPaths.push_back("../src/Shaders/base.frag");
	this->GL->addShaders(shaderPaths);

	// Create OpenCL Context
	this->CL = new OpenCLContext(false, true);

	// Add Kernels, init Kernel programs
	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	// this->CL->addKernelFromFile("../src/kernels/init_particle.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_cube.cl");
	// this->CL->addKernelFromFile("../src/kernels/init_particle_cube2.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle.cl");
	this->CL->buildProgram();
	// this->CL->setKernel("init_particle");
	this->CL->setKernel("init_particle_cube");
	// this->CL->setKernel("init_particle_cube2");
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
	// this->GL->getShaderProgram().setMatrix("modelMatrix", glm::mat4());
	this->GL->getShaderProgram().setMatrix("viewMatrix", this->camera.getViewMatrix());
	this->GL->getShaderProgram().setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
	);
}

// TODO: Free stuff
ParticleSystem::~ParticleSystem() {}

/**
	Initializes particles and buffers based on number of particles and layout
*/
void ParticleSystem::init(int numParticles, std::string initLayout) {
	std::cout << "Particle System init" << std::endl;
	cl_int err = 0;

	cl_uint cubeSize = std::ceil(std::cbrt(numParticles));
	this->numParticles = cubeSize * cubeSize * cubeSize;
	std::cout << "cubeSize: " << cubeSize << std::endl;
	// is it necessary ?
	// glFinish();

	// Initialize size of Buffer
	// GLuint buffSize = sizeof(Particle) * this->numParticles;
	GLuint buffSize = sizeof(float) * 8 * this->numParticles;
	std::cout << "this->numParticles: " << this->numParticles << std::endl;
	// std::cout << "buffSize: " << buffSize << std::endl;
	glBindVertexArray(this->GL->getVAO("particles"));
	glBufferData(GL_ARRAY_BUFFER, buffSize, nullptr, GL_DYNAMIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, buffSize, init, GL_DYNAMIC_DRAW);

	// define attribute pointers
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid *)0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid *)(sizeof(float) * 3));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Create openCL Buffer from openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->GL->getVBO("particles"));

	glFinish();
	if (1) {
		// initialize particles with kernel program on GPU
		cl::CommandQueue queue = this->CL->getQueue();
		err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
		this->CL->checkError(err, "init: enqueueAcquireGLObjects");
		this->CL->getKernel("init_particle_cube").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_cube").setArg(1, sizeof(cl_uint), &this->numParticles);
		this->CL->getKernel("init_particle_cube").setArg(2, sizeof(cl_uint), &cubeSize);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
		// std::cout << "==============" << std::endl;
		// this->CL->getKernel("init_particle_cube2").setArg(0, this->CL->getBuffer("particles"));
		// err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube2"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
		this->CL->checkError(err, "init: enqueueNDRangeKernel");
		queue.finish();
		err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
		this->CL->checkError(err, "init: enqueueReleaseGLObjects");
		glBindVertexArray(0);
	}

	// create FPS object
	std::cout << "num particles: " << this->numParticles << std::endl;
	this->fps = new FPS(100);
}

void ParticleSystem::updateParticles() {
	// std::cout << "updateParticles" << std::endl;
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
	std::cout << "loopstart" << std::endl;
	// reset fps counter
	this->fps->reset();

	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		// clear
		glClearColor(.0f, .0f, .0f, 1.0f);
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

		// update FPS and window title
		this->fps->update();
		this->GL->setWindowName("Particle System\t(FPS: " + std::to_string(this->fps->getFPS()) + ")");
	}
}