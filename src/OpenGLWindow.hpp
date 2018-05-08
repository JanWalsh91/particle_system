#ifndef OPENGL_WINDOW_HPP
# define OPENGL_WINDOW_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/fwd.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <string>
# include <nanogui/nanogui.h>

# include "Shader.hpp"

class GUI;

class OpenGLWindow: public nanogui::Screen {

public:
	OpenGLWindow( int width, int height, std::string const & title );
	OpenGLWindow( OpenGLWindow const & );
	~OpenGLWindow( void );

	OpenGLWindow & operator=( OpenGLWindow const & rhs );
	void loop();
	void createWidget();

	static void initOpenGL();
	GLFWwindow  *getWindow() { return this->window; }

private:
	GLFWwindow	*window;
	GUI*		gui;
	Shader		shaderProgram;
	int			width;
	int			height;
	double		lastTimeFrame;
};

# include "GUI.hpp"

#endif