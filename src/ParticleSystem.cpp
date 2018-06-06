#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem() {
	OpenGLWindow::initOpenGL();
	
	this->GL = new OpenGLWindow(2000, 1000, "Particle System");	

	glfwSetWindowUserPointer(this->GL->getWindow(), this);
	glfwSetMouseButtonCallback(this->GL->getWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(this->GL->getWindow(), cursorPosCallback);
	glfwSetScrollCallback(this->GL->getWindow(), scrollCallback);

	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/Shaders/particle.vert");
	shaderPaths.push_back("../src/Shaders/particle.frag");
	this->GL->addShaderProgram("particleShader", shaderPaths);

	this->CL = new OpenCLContext(false, true);

	this->CL->addKernelFromFile("../src/kernels/particle.h.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_cube.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_cube_optimized.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_sphere.cl");
	this->CL->addKernelFromFile("../src/kernels/init_particle_sphere_optimized.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle.cl");
	this->CL->addKernelFromFile("../src/kernels/update_particle_optimized.cl");
	this->CL->buildProgram();
	this->CL->setKernel("init_particle_cube");
	this->CL->setKernel("init_particle_cube_optimized");
	this->CL->setKernel("init_particle_sphere");
	this->CL->setKernel("init_particle_sphere_optimized");
	this->CL->setKernel("update_particle");
	this->CL->setKernel("update_particle_optimized");

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glEnable(GL_DEPTH_TEST);

	this->GL->getShaderProgram("particleShader").setMatrix("viewMatrix", this->camera.getViewMatrix());
	this->GL->getShaderProgram("particleShader").setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
	);
}

ParticleSystem::~ParticleSystem() {}

//Initializes particles and buffers based on number of particles and layout
void ParticleSystem::init(int numParticles, std::string layout, bool paused, bool optimized, std::vector<std::string> skyboxFaces) {
	this->paused = paused;
	this->optimized = optimized;
	this->cursorDepth = glm::length(this->camera.getPosition());
	if (layout != "cube" && layout != "sphere")
		layout = "cube";
	this->preset = layout;	
	this->cubeSize = std::ceil(std::cbrt(numParticles));
	this->numParticles = cubeSize * cubeSize * cubeSize;

	this->initParticles();

	this->initSkybox(skyboxFaces);

	this->initForces();
	
	if (this->preset == "cube")
		this->initCube();
	else if (this->preset == "sphere")
		this->initSphere();

	this->fps = new FPS(10);
}

void ParticleSystem::initParticles() {
	int floatsPerParticle = this->optimized ? 4 : 8;
	this->GL->addVAO("particles");
	this->GL->addVBO("particles");
	glBindVertexArray(this->GL->getVAO("particles"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("particles"));
	GLuint buffSize = sizeof(float) * floatsPerParticle * this->numParticles;
	glBufferData(GL_ARRAY_BUFFER, buffSize, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * floatsPerParticle, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	if (!this->optimized) {
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * floatsPerParticle, (GLvoid *)(sizeof(float) * 4));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);

	this->CL->addBuffer("particles", this->GL->getVBO("particles"));
}

void ParticleSystem::initForces() {
	this->forces.addForce(Forces::Force(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 0.1));

	this->GL->addVAO("forces");
	this->GL->addVBO("forces");
	glBindVertexArray(this->GL->getVAO("forces"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("forces"));
	GLuint buffSize = sizeof(float) * 7 * this->forces.size();
	glBufferData(GL_ARRAY_BUFFER, buffSize, this->forces.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid *)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	this->forces.setVAO(this->GL->getVAO("forces"));

	this->CL->addBuffer("forces", this->GL->getVBO("forces"));
}

void ParticleSystem::initSkybox(std::vector<std::string> skyboxFaces) {
	this->skyboxTextureRef = this->GL->loadSkybox(skyboxFaces);
	if (!this->skyboxTextureRef) {
		std::cout << "Failed to load skybox resources" << std::endl;
		exit(0);
	}
	float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	this->GL->addVAO("skybox");
	this->GL->addVBO("skybox");
	glBindVertexArray(this->GL->getVAO("skybox"));
	glBindBuffer(GL_ARRAY_BUFFER, this->GL->getVBO("skybox"));
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	std::vector<std::string> shaderPaths;
	shaderPaths.push_back("../src/shaders/skybox.vert");
	shaderPaths.push_back("../src/shaders/skybox.frag");
	this->GL->addShaderProgram("skyboxShader", shaderPaths);
	this->GL->getShaderProgram("skyboxShader").setInt("skybox", 0);
}

void ParticleSystem::initCube() {
	this->isReset = true;
	cl_int err = 0;
	cl::CommandQueue queue = this->CL->getQueue();
	glFinish();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");

	if (this->optimized) {
		this->CL->getKernel("init_particle_cube_optimized").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_cube_optimized").setArg(1, sizeof(cl_uint), &this->cubeSize);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube_optimized"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	}
	else {
		this->CL->getKernel("init_particle_cube").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_cube").setArg(1, sizeof(cl_uint), &this->cubeSize);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_cube"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	}
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
}

void ParticleSystem::initSphere() {
	this->isReset = true;
	cl_int err = 0;
	cl::CommandQueue queue = this->CL->getQueue();
	glFinish();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueAcquireGLObjects");

	if (this->optimized) {
		this->CL->getKernel("init_particle_sphere_optimized").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_sphere_optimized").setArg(1, sizeof(cl_uint), &this->numParticles);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_sphere_optimized"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	}
	else {
		this->CL->getKernel("init_particle_sphere").setArg(0, this->CL->getBuffer("particles"));
		this->CL->getKernel("init_particle_sphere").setArg(1, sizeof(cl_uint), &this->numParticles);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("init_particle_sphere"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	}
	this->CL->checkError(err, "init: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "init: enqueueReleaseGLObjects");
}

void ParticleSystem::updateParticles() {
	this->isReset = false;
	cl_int err = 0; 
	cl::CommandQueue queue = this->CL->getQueue();
	err = queue.enqueueAcquireGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueAcquireGLObjects");

	static bool setArgs = false;
	if (!setArgs) {
		if (this->optimized) {
			this->CL->getKernel("update_particle_optimized").setArg(0, this->CL->getBuffer("particles"));
			this->CL->getKernel("update_particle_optimized").setArg(1, this->CL->getBuffer("forces"));
		}
		else {
			this->CL->getKernel("update_particle").setArg(0, this->CL->getBuffer("particles"));
			this->CL->getKernel("update_particle").setArg(1, this->CL->getBuffer("forces"));
		}
		setArgs = true;
	}

	int numForces = this->forces.size();
	float deltaTime = this->fps->getDeltaTime();
	if (this->optimized) {
		this->CL->getKernel("update_particle_optimized").setArg(2, sizeof(int), &numForces);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("update_particle_optimized"), cl::NullRange, cl::NDRange(this->numParticles), cl::NullRange);
	}
	else {
		this->CL->getKernel("update_particle").setArg(2, sizeof(int), &numForces);
		this->CL->getKernel("update_particle").setArg(3, sizeof(float), &deltaTime);
		err = queue.enqueueNDRangeKernel(this->CL->getKernel("update_particle"), cl::NullRange, cl::NDRange(this->numParticles/2), cl::NullRange);
	}
	this->CL->checkError(err, "updateParticles: enqueueNDRangeKernel");
	queue.finish();
	err = queue.enqueueReleaseGLObjects(&this->CL->getBuffers(), NULL, NULL);
	this->CL->checkError(err, "updateParticles: enqueueReleaseGLObjects");
	
}

void ParticleSystem::loop() {
	this->fps->reset();

	while (!glfwWindowShouldClose(this->GL->getWindow()) && glfwGetKey(this->GL->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {

		this->fps->update();
		this->GL->setWindowName("Particle System\t(FPS: " + std::to_string(this->fps->getFPS()) + ")");

		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->processInput();

		this->GL->getShaderProgram("particleShader").use();
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

		if (!this->paused)
			this->updateParticles();

		glDepthMask(GL_FALSE);
		this->GL->getShaderProgram("skyboxShader").use();
		glm::mat4 view = glm::mat4(glm::mat3(this->camera.getViewMatrix())); 
		this->GL->getShaderProgram("skyboxShader").setMatrix("view", view);
		this->GL->getShaderProgram("skyboxShader").setMatrix("projection",
			glm::perspective(glm::radians(45.0f), (float)this->GL->getWidth() / (float)this->GL->getHeight(), 0.1f, 100.0f)
		);
		glBindVertexArray(this->GL->getVAO("skybox"));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTextureRef);
        glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);

		this->GL->getShaderProgram("particleShader").use();
		glBindVertexArray(this->GL->getVAO("particles"));
		glDrawArrays(GL_POINTS, 0, this->numParticles);
		glBindVertexArray(0);

		glfwSwapBuffers(this->GL->getWindow());
		glfwPollEvents();
	}

	this->GL->deleteBuffers();

	delete CL;
	delete GL;
	delete fps;
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
	this->paused = true;
	if (this->isReset) {
		if (this->preset == "sphere")
			this->preset = "cube";
		else if (this->preset == "cube")
			this->preset = "sphere";
	}

	while (this->forces.size() > 1)
		this->forces.delForce();
	this->forces.getForce(0).position = glm::vec3(0, 0, 0);
	this->forces.getForce(0).color = glm::vec3(1, 0, 0);
	this->forces.getForce(0).locked = true;
	
	if (this->preset == "cube")
		this->initCube();
	
	if (this->preset == "sphere")
		this->initSphere();
	
	this->camera = Camera();
}

void ParticleSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
		ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		PS->forces.updateForcePosition(PS->camera, PS->cursorDepth, xpos, ypos);
		PS->getGL()->mouseButtonCallbackEvent(button, action, mods);
	}
}

void ParticleSystem::cursorPosCallback(GLFWwindow* window, double x, double y) {
	ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
	if (!PS->forces.getForce(PS->forces.getCurrentForce()).locked) {
		PS->forces.updateForcePosition(PS->camera, PS->cursorDepth, x, y);
		PS->getGL()->cursorPosCallbackEvent(x, y);
	}
}

void ParticleSystem::scrollCallback(GLFWwindow* window, double x, double y) {
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