#include "OpenGLWindow.hpp"
#include "ExceptionMsg.hpp"

OpenGLWindow::OpenGLWindow( int width, int height, std::string const & title ): nanogui::Screen(), width(width), height(height) {
	
	std::cout << "OpenGLWindow constructor" << std::endl;
	if (!(this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
		throw ExceptionMsg("Failed to create window");
	}

	// position on top right of the monitor
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	std::cout << "widthMM: " << mode->width << ", heightMM: " << mode->height << std::endl;
	glfwSetWindowPos(this->window, mode->width - width - 50, 50);

	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ExceptionMsg("Failed to initialize GLAD");
	}
	
	// nanogui function
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
	glfwSwapInterval(1);
}

void OpenGLWindow::initGUI() {
	std::cout << "initGUI" << std::endl;
	// initialize nanogui::screen with this window
	// this->initialize(this->window, true);


	// nanogui::FormHelper *gui = new nanogui::FormHelper(this);
    // nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
    // gui->addGroup("Basic types");
	// bool bvar = true;
	// gui->addVariable("bool", bvar)->setTooltip("Test tooltip.");
    // gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; })->setTooltip("Testing a much longer tooltip, that will wrap around to new lines multiple times.");;

	nanogui::Window* guiWindow = new nanogui::Window(this, "HumanGL Settings");
	guiWindow->setPosition(nanogui::Vector2i(20, 15));
	guiWindow->setLayout(new nanogui::GroupLayout());

	new nanogui::Label(guiWindow, "Rotation", "sans-bold");

	nanogui::Widget *panel = new nanogui::Widget(guiWindow);
	panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(panel, "X", "sans-bold");

	nanogui::Slider *slider = new nanogui::Slider(panel);
	slider->setValue(1.0f);
	slider->setFixedWidth(100);

	nanogui::TextBox *textBox = new nanogui::TextBox(panel);
	textBox->setFixedSize(nanogui::Vector2i(60, 25));
	textBox->setValue("100");
	textBox->setUnits("%");


	slider->setCallback([this, textBox](float value) {
		textBox->setValue(std::to_string((int) (value * 100)));
		std::cout << value << std::endl;

	});
	slider->setFinalCallback([&](float value) {
		std::cout << "Final slider value: " << (int) (value * 100) << std::endl;
	});

	textBox->setFixedSize(nanogui::Vector2i(60,25));
	textBox->setFontSize(20);
	textBox->setAlignment(nanogui::TextBox::Alignment::Right);

    this->setVisible(true);
    this->performLayout();
	guiWindow->center();
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