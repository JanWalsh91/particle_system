#include "OpenGLWindow.hpp"
#include "ExceptionMsg.hpp"

OpenGLWindow::OpenGLWindow( int width, int height, std::string const & title ): nanogui::Screen(), width(width), height(height) {
	
	std::cout << "OpenGLWindow constructor" << std::endl;
	if (!(this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
		throw ExceptionMsg("Failed to create window");
	}
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ExceptionMsg("Failed to initialize GLAD");
	}
	
	// nanogui function
	this->initialize(this->window, true);

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSwapInterval(0);
	glfwSwapBuffers(window);

	bool enabled = true;
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

void OpenGLWindow::addShaders(std::vector<std::string> shaderPaths) {
	if (shaderPaths.size() != 2) {
		std::cout << "Need two shaders" << std::endl;
		exit(1);
	}
	this->shaderProgram = Shader(shaderPaths[0].c_str(), shaderPaths[1].c_str());
	this->shaderProgram.use();
}

void OpenGLWindow::initOpenGL() {
	if (!glfwInit()) {
		throw ExceptionMsg("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}