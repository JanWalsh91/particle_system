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
	
	// Set callback
	glfwSetWindowUserPointer(this->GL->getWindow(), this);
	glfwSetMouseButtonCallback(this->GL->getWindow(), mouseButtonCallback);

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/base.vert");
	shaderPaths.push_back("../src/Shaders/base.frag");
	this->GL->addShaders(shaderPaths);

	// Create OpenCL Context
	this->CL = new OpenCLContext(false, true);

	// Add Kernels, init Kernel programs
	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_cube.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_sphere.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle.cl");
	this->CL->buildProgram();
	this->CL->setKernel("init_particle_cube");
	this->CL->setKernel("init_particle_sphere");
	this->CL->setKernel("update_particle");

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
void ParticleSystem::init(int numParticles, std::string initLayout, bool paused) {
	std::cout << "Particle System init" << std::endl;
	this->paused = paused;
	this->cursorDepth = glm::length(this->camera.getPosition());
	// printf("depth: %f\n", this->cursorDepth);

	this->forces.addForce(Forces::Force(glm::vec3(1, 2, 3), glm::vec3(5, 6, 7), 4));
	// Force force = Force();
	// force.position = glm::vec4(1, 2, 3, 4);

	cl_int err = 0;

	cl_uint cubeSize = std::ceil(std::cbrt(numParticles));
	this->numParticles = cubeSize * cubeSize * cubeSize;
	std::cout << "cubeSize: " << cubeSize << std::endl;
	std::cout << "this->numParticles: " << this->numParticles << std::endl;
	
	// is it necessary ?
	// glFinish();

	// Initialize particles VBO
	this->GL->addVAO("particles");
	this->GL->addVBO("particles");
	glBindVertexArray(this->GL->getVAO("particles"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("particles"));
	// glBindVertexArray(0);
	GLuint buffSize = sizeof(float) * 8 * this->numParticles;
	// glBindVertexArray(this->GL->getVAO("particles"));
	glBufferData(GL_ARRAY_BUFFER, buffSize, nullptr, GL_DYNAMIC_DRAW);
	// define attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Initialize forces VBO
	this->GL->addVAO("forces");
	this->GL->addVBO("forces");
	glBindVertexArray(this->GL->getVAO("forces"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("forces"));
	buffSize = sizeof(float) * 9 * this->forces.size();
	glBindVertexArray(this->GL->getVAO("forces"));
	std::cout << "forces.size: " << this->forces.size() << std::endl;
	glBufferData(GL_ARRAY_BUFFER, buffSize, this->forces.data(), GL_DYNAMIC_DRAW);
	// define attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid *)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid *)(sizeof(float) * 4));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Create openCL Buffer from openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->GL->getVBO("particles"));
	this->CL->addBuffer("forces", this->GL->getVBO("forces"));
	glFinish();
	// exit(0);
	if (1) {
		// initialize particles with kernel program on GPU
		cl::CommandQueue queue = this->CL->getQueue();
		err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
		this->CL->checkError(err, "init: enqueueAcquireGLObjects");
		this->CL->getKernel("init_particle_cube").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_cube").setArg(1, sizeof(cl_uint), &this->numParticles);
		this->CL->getKernel("init_particle_cube").setArg(2, sizeof(cl_uint), &cubeSize);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
		queue.finish();
		// std::cout << "==============" << std::endl;
		this->CL->getKernel("init_particle_sphere").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_sphere").setArg(1, sizeof(cl_uint), &this->numParticles);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_sphere"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
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
		if (this->fps->getDeltaTime() < 0.016) {
			this->fps->updateLast();
			continue ;
		}
		// clear
		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->processInput();

		this->GL->getShaderProgram().setVector("camPos", this->camera.getPosition());
		this->GL->getShaderProgram().setVector("camDir", this->camera.getFront());
		this->GL->getShaderProgram().setFloat("cursorDepth", this->cursorDepth);

		if (!this->paused) {
			// update position with OpenCL
			this->updateParticles();
		}

		this->GL->getShaderProgram().setMatrix("viewMatrix", this->camera.getViewMatrix());
		this->GL->getShaderProgram().setMatrix("projectionMatrix",
			glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
		);
		
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
		// std::cout << "Delta Time: " << this->fps->getDeltaTime() << std::endl;
		// glm::mat4 m = this->camera.getViewMatrix();
		// printf("===========\n");
		// for (int i = 0; i < 4; i++) {
		// 	for (int y = 0; y < 4; y++) {
		// 		printf("%.2lf, ", m[i][y]);
		// 	}
		// 	printf("\n");
		// }
	}
}

void ParticleSystem::processInput() {
	// Pause
	static int oldState_P = GLFW_RELEASE;
	int newState_P = glfwGetKey(this->GL->getWindow(), GLFW_KEY_P);
	if (newState_P == GLFW_RELEASE && oldState_P == GLFW_PRESS) {
		this->paused = !this->paused;
	}
	oldState_P = newState_P;
	
	// Camera movement
	if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		this->camera.processInput(FORWARD, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		this->camera.processInput(BACKWARD, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		this->camera.processInput(LEFT, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->camera.processInput(RIGHT, this->fps->getDeltaTime());
	
	// Camera rotation
	if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		this->camera.processInput(TURN_UP, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		this->camera.processInput(TURN_DOWN, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		this->camera.processInput(TURN_LEFT, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		this->camera.processInput(TURN_RIGHT, this->fps->getDeltaTime());

	// Cursor Depth
	if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_KP_ADD) == GLFW_PRESS)
		this->cursorDepth += 0.01;
	if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		this->cursorDepth -= 0.01;
	
}

void ParticleSystem::updateForcePosition(int x, int y) {
	std::cout << "updateForcePos" << std::endl;
}

void ParticleSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	std::cout << "mouseButtonCallback" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
		ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		PS->updateForcePosition(xpos, ypos);
	}
}
