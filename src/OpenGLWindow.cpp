#include "OpenGLWindow.hpp"
#include "ExceptionMsg.hpp"

OpenGLWindow::OpenGLWindow( int width, int height, std::string const & title ): nanogui::Screen(), width(width), height(height) {
	
	std::cout << "creating window with height: " << height << " width: " << width << " title: " << title << std::endl;
	if (!(this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
		throw ExceptionMsg("Failed to create window");
	}
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ExceptionMsg("Failed to initialize GLAD");
	}
	this->shaderProgram = Shader("../src/Shaders/base.vert", "../src/Shaders/base.frag");
	this->shaderProgram.use();
	
	this->initialize(this->window, true);

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSwapInterval(0);
	glfwSwapBuffers(window);

	bool enabled = true;

	// this->gui = new GUI(this);
	// this->gui->createSettings();

	// this->setVisible(true);
	// this->performLayout();

	// glfwSetWindowUserPointer(this->window, this);

	// glfwSetCursorPosCallback(window, [](GLFWwindow *win, double x, double y) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		 screen->cursorPosCallbackEvent(x, y);
	// 	 }
	// );

	// glfwSetMouseButtonCallback(window, [](GLFWwindow *win, int button, int action, int modifiers) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		screen->mouseButtonCallbackEvent(button, action, modifiers);
	// 	}
	// );

	// glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
   	// 		screen->keyCallbackEvent(key, scancode, action, mods);
	//    }
	// );

	// glfwSetCharCallback(window, [](GLFWwindow *win, unsigned int codepoint) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		screen->charCallbackEvent(codepoint);
	// 	}
	// );

	// glfwSetDropCallback(window, [](GLFWwindow *win, int count, const char **filenames) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		screen->dropCallbackEvent(count, filenames);
	// 	}
	// );

	// glfwSetScrollCallback(window, [](GLFWwindow *win, double x, double y) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		screen->scrollCallbackEvent(x, y);
	// 	}
	// );

	// glfwSetFramebufferSizeCallback(window, [](GLFWwindow *win, int width, int height) {
	// 	OpenGLWindow* screen = (OpenGLWindow*)glfwGetWindowUserPointer(win);
	// 		screen->resizeCallbackEvent(width, height);
	//    }
	// );
}

OpenGLWindow::OpenGLWindow( OpenGLWindow const & Window ) {
	*this = Window;
}

OpenGLWindow::~OpenGLWindow() {
	glfwTerminate();
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

//void OpenGLWindow::drawContents() {
//
//}


void OpenGLWindow::loop() {

	// Matrix i;
	// Vector o;

	while (!glfwWindowShouldClose(this->window) && glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		glEnable(GL_DEPTH_TEST);
		
		glfwPollEvents();

		glClearColor(.0f, .0f, .0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// this->drawContents();

//		this->shaderProgram.setVector("color", Vector(1, 0.5, 0));

		// this->shaderProgram.setMatrix("viewMatrix",  this->viewMatrix);
		// this->shaderProgram.setMatrix("projectionMatrix",  this->PMatrix);
//
		// this->shaderProgram.use();


		// glBindVertexArray(human->getVAO());
		// glBindBuffer(GL_ARRAY_BUFFER, human->getVBO());

		

		// torso.recursivelyRender(this->shaderProgram);
		// exit(0);

//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);

		// this->drawWidgets();
		glfwSwapBuffers(this->window);
	}
}

OpenGLWindow & OpenGLWindow::operator=( OpenGLWindow const & rhs ) {
	this->window = rhs.window;
	this->width = rhs.width;
	this->height = rhs.height;
	return *this;
}