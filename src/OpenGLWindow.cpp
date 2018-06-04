#include "OpenGLWindow.hpp"

OpenGLWindow::OpenGLWindow( int width, int height, std::string const & title ): nanogui::Screen(), width(width), height(height) {
	if (!(this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
		throw ExceptionMsg("Failed to create window");
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(this->window, mode->width - width - 50, 50);

	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ExceptionMsg("Failed to initialize GLAD");
	}
	
	this->initialize(this->window, true);

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSwapInterval(1);
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, 1);
	glfwSwapBuffers(this->window);
	glfwSetFramebufferSizeCallback(this->window, this->framebufferSizeCallback);
}

OpenGLWindow::OpenGLWindow( OpenGLWindow const & Window ) {
	*this = Window;
}

OpenGLWindow::~OpenGLWindow() {
	glfwTerminate();
}


OpenGLWindow & OpenGLWindow::operator=( OpenGLWindow const & rhs ) {
	this->window = rhs.window;
	this->width = rhs.width;
	this->height = rhs.height;
	return *this;
}

void OpenGLWindow::addShaderProgram(std::string name, std::vector<std::string> shaderPaths) {
	if (shaderPaths.size() != 2) {
		std::cout << "Need two shaders" << std::endl;
		exit(1);
	}
	this->shaderPrograms[name] = Shader(shaderPaths[0].c_str(), shaderPaths[1].c_str());
	this->shaderPrograms[name].use();
}

void OpenGLWindow::addVBO(std::string name) {
	GLuint VBO;

	glGenBuffers(1, &VBO);
	this->VBOs[name] = VBO;
}

void OpenGLWindow::addVAO(std::string name) {
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	this->VAOs[name] = VAO;
}

void OpenGLWindow::setWindowName(std::string name) {
	glfwSetWindowTitle(this->window, name.c_str());
}

void OpenGLWindow::initOpenGL() {
	if (!glfwInit()) {
		throw ExceptionMsg("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwSwapInterval(0);
}

unsigned int OpenGLWindow::loadSkybox(std::vector<std::string> faces) {
	unsigned int textureID;
	glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
			return 0;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void	OpenGLWindow::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
	ParticleSystem *PS = reinterpret_cast<ParticleSystem *>(glfwGetWindowUserPointer(window));
	(void)window;
	PS->getGL()->height = height;
	PS->getGL()->width = width;
	glViewport(0, 0, width, height);

	PS->getGL()->getShaderProgram("particleShader").setMatrix("projectionMatrix",
		glm::perspective(glm::radians(45.0f), (float)PS->getGL()->getWidth() / (float)PS->getGL()->getHeight(), 0.1f, 100.0f)
	);
}

// Getters
GLFWwindow  *OpenGLWindow::getWindow() {
	return this->window;
}

Shader  	&OpenGLWindow::getShaderProgram(std::string name) {
	return this->shaderPrograms[name];
}

int			OpenGLWindow::getWidth() {
	return this->width;
}

int			OpenGLWindow::getHeight() {
	return this->height;
}

GLuint		OpenGLWindow::getVAO(std::string name) {
	return this->VAOs[name];
}

GLuint		OpenGLWindow::getVBO(std::string name) {
	return this->VBOs[name];
}