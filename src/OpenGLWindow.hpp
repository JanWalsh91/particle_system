#ifndef OPENGL_WINDOW_HPP
# define OPENGL_WINDOW_HPP

# include <string>
# include <vector>
# include <map>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/fwd.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <nanogui/nanogui.h>

# include "Shader.hpp"

class GUI;

class OpenGLWindow: public nanogui::Screen {

public:
	OpenGLWindow() {}
	OpenGLWindow( int width, int height, std::string const & title );
	OpenGLWindow( OpenGLWindow const & );
	~OpenGLWindow( void );
	OpenGLWindow & operator=( OpenGLWindow const & rhs );

	// void createWidget();
	void addShaders(std::vector<std::string> paths);
	
	void addVBO(std::string);
	void addVAO(std::string);

	static void initOpenGL();
	static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

	// Getters
	GLFWwindow  *getWindow();
	Shader  	&getShaderProgram(); 
	int			getWidth();
	int			getHeight();
	GLuint		getVAO(std::string);
	GLuint		getVBO(std::string);

private:
	GLFWwindow						*window;
	GUI*							gui;
	Shader							shaderProgram;
	int								width;
	int								height;
	std::map<std::string, GLuint>	VBOs;
	std::map<std::string, GLuint>	VAOs;
	// double		lastTimeFrame;
};

# include "GUI.hpp"

#endif