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
	this->GL = new OpenGLWindow(2000, 1000, "Particle System");	
	
	// nanoGUI
	// this->GL->initGUI(); 

	// Set callback
	glfwSetWindowUserPointer(this->GL->getWindow(), this);
	glfwSetMouseButtonCallback(this->GL->getWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(this->GL->getWindow(), cursorPosCallback);
	glfwSetScrollCallback(this->GL->getWindow(), scrollCallback);

	// Add Shaders
	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/particle.vert");
	shaderPaths.push_back("../src/Shaders/particle.frag");
	this->GL->addShaderProgram("particleShader", shaderPaths);

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
	this->GL->getShaderProgram("particleShader").setMatrix("viewMatrix", this->camera.getViewMatrix());
	this->GL->getShaderProgram("particleShader").setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
	);
}

// TODO: Free stuff
ParticleSystem::~ParticleSystem() {}

/**
	Initializes particles and buffers based on number of particles and layout
*/
void ParticleSystem::init(int numParticles, std::string layout, bool paused) {
	std::cout << "Particle System init" << std::endl;
	this->paused = paused;
	// this->currentForce = 0;
	this->cursorDepth = glm::length(this->camera.getPosition());
	if (layout != "cube" && layout != "sphere") {
		layout = "cube";
	}
	this->preset = layout;
	// add initial force
	this->forces.addForce(Forces::Force(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 0.1));

	cl_int err = 0;

	this->cubeSize = std::ceil(std::cbrt(numParticles));
	this->numParticles = cubeSize * cubeSize * cubeSize;
	std::cout << "cubeSize: " << this->cubeSize << std::endl;
	std::cout << "this->numParticles: " << this->numParticles << std::endl;

	// Initialize particles VBO
	this->GL->addVAO("particles");
	this->GL->addVBO("particles");
	glBindVertexArray(this->GL->getVAO("particles"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("particles"));
	GLuint buffSize = sizeof(float) * 8 * this->numParticles;
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
	buffSize = sizeof(float) * 7 * this->forces.size();
	std::cout << "forces.size: " << this->forces.size() << std::endl;
	glBufferData(GL_ARRAY_BUFFER, buffSize, this->forces.data(), GL_DYNAMIC_DRAW);
	// define attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// pass VAO info to forces manager
	this->forces.setVAO(this->GL->getVAO("forces"));

	// Create openCL Buffer from openGL Buffer (VBO)
	this->CL->addBuffer("particles", this->GL->getVBO("particles"));
	this->CL->addBuffer("forces", this->GL->getVBO("forces"));
	glFinish();
	
	// initialize particles with kernel program on GPU
	cl::CommandQueue queue = this->CL->getQueue();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	
	// init cube
	if (this->preset == "cube")
		this->initCube();
	
	// init sphere
	if (this->preset == "sphere")
		this->initSphere();

	// create FPS object
	this->fps = new FPS(10);

	// cl_half test;
	// std::cout << "finish init" << std::endl;
	// exit(0);
}

void ParticleSystem::initCube() {
	std::cout << "init cube: " << this->cubeSize << std::endl;
	std::cout << "numParticles: " << this->numParticles << std::endl;
	glFinish();
	this->isReset = true;
	cl_int err = 0;
	cl::CommandQueue queue = this->CL->getQueue();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");
	// init cube
	this->CL->getKernel("init_particle_cube").setArg(0, this->CL->getBuffer("particles"));
	this->CL->getKernel("init_particle_cube").setArg(1, sizeof(cl_uint), &this->numParticles);
	this->CL->getKernel("init_particle_cube").setArg(2, sizeof(cl_uint), &this->cubeSize);
	err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	queue.finish();
	std::cout << "done init cube" << std::endl;
}

void ParticleSystem::initSphere() {
	std::cout << "init sphere" << std::endl;
	glFinish();
	this->isReset = true;
	cl_int err = 0;
	cl::CommandQueue queue = this->CL->getQueue();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->getKernel("init_particle_sphere").setArg(0, this->CL->getBuffer("particles"));
	this->CL->getKernel("init_particle_sphere").setArg(1, sizeof(cl_uint), &this->numParticles);
	err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_sphere"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
	std::cout << "done init sphere" << std::endl;
}

void ParticleSystem::updateParticles() {
	// std::cout << "updateParticles" << std::endl;
	this->isReset = false;
	static bool setArgs = false;
	cl_int err = 0; 
	
	glFinish();

	cl::CommandQueue queue = this->CL->getQueue();
	glBindVertexArray(this->GL->getVAO("particles"));
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueAcquireGLObjects");
	if (!setArgs) {
		this->CL->getKernel("update_particle").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("update_particle").setArg(1, this->CL->getBuffer("forces"));
	}
	int numForces = this->forces.size();
	float deltaTime = this->fps->getDeltaTime();
	this->CL->getKernel("update_particle").setArg(2, sizeof(int), &numForces);
	this->CL->getKernel("update_particle").setArg(3, sizeof(float), &deltaTime);
	err = queue.enqueueNDRangeKernel(this->CL->getKernel("update_particle"), cl::NullRange, cl::NDRange(this->numParticles/2), cl::NullRange);
	this->CL->checkError(err, "updateParticles: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueReleaseGLObjects");
	glBindVertexArray(0);
	setArgs = true;
}

void ParticleSystem::loop() {
	std::cout << "loopstart" << std::endl;
	// reset fps counter
	this->fps->reset();

	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		// sleep if necessary
		if (this->fps->getDeltaTime() < 0.016) {
			float sleepTime = (0.016 - this->fps->getDeltaTime()) * 1000;
			usleep(sleepTime);
		}

		// update FPS and window title
		this->fps->update();
		this->GL->setWindowName("Particle System\t(FPS: " + std::to_string(this->fps->getFPS()) + ")");

		// clear
		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// handle user input
		this->processInput();

		// update uniforms (not necessary to do all the time!) TODO: move to appropriate location
		// this->GL->getShaderProgram("particleShader").use();
		this->GL->getShaderProgram("particleShader").setVector("camPos", this->camera.getPosition());
		this->GL->getShaderProgram("particleShader").setVector("camDir", this->camera.getFront());
		this->GL->getShaderProgram("particleShader").setFloat("cursorDepth", this->cursorDepth);
		this->GL->getShaderProgram("particleShader").setMatrix("viewMatrix", this->camera.getViewMatrix());
		this->GL->getShaderProgram("particleShader").setMatrix("projectionMatrix",
			glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
		);
		float forces[7 * MAX_FORCES];
		for (int i = 0; i < 7 * this->forces.size(); ++i) {
			forces[i] = this->forces.data()[i];
		}
		this->GL->getShaderProgram("particleShader").setArray("forces", forces, this->forces.size()*7);
		this->GL->getShaderProgram("particleShader").setInt("forcesNum", this->forces.size());

		if (!this->paused) {
			// update position with OpenCL
			this->updateParticles();
		}
		
		// draw particles with OpenGL
		this->GL->getShaderProgram("particleShader").use();
		glBindVertexArray(this->GL->getVAO("particles"));
		glDrawArrays(GL_POINTS, 0, this->numParticles);
		glBindVertexArray(0);

		// nanogui stuff:
		// this->GL->drawContents(); // ?? what does this do?
		// this->GL->drawWidgets();

		// swap buffers
		glfwSwapBuffers(this->GL->getWindow());
		glfwPollEvents();
	}
}

void ParticleSystem::processInput() {
	glFinish();

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
		this->camera.processInput(TURN_DOWN, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		this->camera.processInput(TURN_UP, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		this->camera.processInput(TURN_LEFT, this->fps->getDeltaTime());
    if (glfwGetKey(this->GL->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		this->camera.processInput(TURN_RIGHT, this->fps->getDeltaTime());

	// Current Force
	static int oldState_TAB = GLFW_RELEASE;
	int newState_TAB = glfwGetKey(this->GL->getWindow(), GLFW_KEY_TAB);
	if (newState_TAB == GLFW_RELEASE && oldState_TAB == GLFW_PRESS)
		this->forces.nextForce();
	oldState_TAB = newState_TAB;

	// Toggle Lock
	static int oldState_L = GLFW_RELEASE;
	int newState_L = glfwGetKey(this->GL->getWindow(), GLFW_KEY_L);
	if (newState_L == GLFW_RELEASE && oldState_L == GLFW_PRESS)
		this->forces.toggleLock();
	oldState_L = newState_L;

	// New Force
	static int oldState_N = GLFW_RELEASE;
	int newState_N = glfwGetKey(this->GL->getWindow(), GLFW_KEY_N);
	if (newState_N == GLFW_RELEASE && oldState_N == GLFW_PRESS)
		this->forces.addForce();
	oldState_N = newState_N;

	// Delete Force
	static int oldState_BACKSPACE = GLFW_RELEASE;
	int newState_BACKSPACE = glfwGetKey(this->GL->getWindow(), GLFW_KEY_BACKSPACE);
	if (newState_BACKSPACE == GLFW_RELEASE && oldState_BACKSPACE == GLFW_PRESS)
		this->forces.delForce();
	oldState_BACKSPACE = newState_BACKSPACE;

	// Reset / Change Preset
	static int oldState_SPACE = GLFW_RELEASE;
	int newState_SPACE = glfwGetKey(this->GL->getWindow(), GLFW_KEY_SPACE);
	if (newState_SPACE == GLFW_RELEASE && oldState_SPACE == GLFW_PRESS)
		this->reset();
	oldState_SPACE = newState_SPACE;
}

void ParticleSystem::reset() {
	std::cout << "reset" << std::endl;
	this->paused = true;
	// change preset if is reset
	if (this->isReset) {
		if (this->preset == "sphere")
			this->preset = "cube";
		else if (this->preset == "cube")
			this->preset = "sphere";
	}
	// delete all forces, add red one in middle
	while (this->forces.size() > 1)
		this->forces.delForce();
	this->forces.getForce(0).position = glm::vec3(0, 0, 0);
	this->forces.getForce(0).color = glm::vec3(1, 0, 0);
	this->forces.getForce(0).locked = true;
	// init cube
	if (this->preset == "cube")
		this->initCube();
	// init sphere
	if (this->preset == "sphere")
		this->initSphere();
	// reset cirspr depth
	this->camera = Camera();
	
	printf("force[0].pos: {%.2f, %.2f, %.2f}\n", this->forces.getForce(0).position[0], this->forces.getForce(0).position[1], this->forces.getForce(0).position[2]);

}

void ParticleSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	std::cout << "mouseButtonCallback" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
		ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		PS->forces.updateForcePosition(PS->camera, PS->cursorDepth, xpos, ypos);
		PS->getGL()->mouseButtonCallbackEvent(button, action, mods);
	}
}

void ParticleSystem::cursorPosCallback(GLFWwindow* window, double x, double y) {
	// std::cout << "cursorPosCallback" << std::endl;
	ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
	if (!PS->forces.getForce(PS->forces.getCurrentForce()).locked) {
		PS->forces.updateForcePosition(PS->camera, PS->cursorDepth, x, y);
		PS->getGL()->cursorPosCallbackEvent(x, y);
	}
}

void ParticleSystem::scrollCallback(GLFWwindow* window, double x, double y) {
	// std::cout << "scrollPosCallback. x: " << x << ", y: " << y << std::endl;
	ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
	PS->cursorDepth += y * 0.01f;
	if (!PS->forces.getForce(PS->forces.getCurrentForce()).locked) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		PS->forces.updateForcePosition(PS->camera, PS->cursorDepth, xpos, ypos);
		PS->getGL()->scrollCallbackEvent(x, y);
	}
}

// Getters
OpenGLWindow	*ParticleSystem::getGL() {
	return this->GL;
}