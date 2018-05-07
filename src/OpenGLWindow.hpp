#ifndef OPENGL_WINDOW_HPP
# define OPENGL_WINDOW_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
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

private:
	GLFWwindow	*window;
	GUI*		gui;
	Shader		shaderProgram;
	int			width;
	int			height;
	double		lastTimeFrame;

	// double poubelle;
};

# include "GUI.hpp"

#endif