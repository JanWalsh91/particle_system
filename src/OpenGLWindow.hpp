#ifndef OPENGL_WINDOW_HPP
# define OPENGL_WINDOW_HPP

# include <string>
# include <vector>
# include <map>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <nanogui/nanogui.h>
# include <glm/fwd.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
// # define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

# include "Shader.hpp"

class ParticleSystem;

class OpenGLWindow: public nanogui::Screen {

public:
	OpenGLWindow() {}
	OpenGLWindow( int width, int height, std::string const & title );
	OpenGLWindow( OpenGLWindow const & );
	~OpenGLWindow( void );
	OpenGLWindow & operator=( OpenGLWindow const & rhs );

	// void createWidget();
	void addShaderProgram(std::string name, std::vector<std::string> paths);
	
	unsigned int loadSkybox(std::vector<std::string> faces);

	void addVBO(std::string);
	void addVAO(std::string);

	void	setWindowName(std::string);

	static void initOpenGL();
	static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

	// Getters
	GLFWwindow  *getWindow();
	Shader  	&getShaderProgram(std::string); 
	int			getWidth();
	int			getHeight();
	GLuint		getVAO(std::string);
	GLuint		getVBO(std::string);

private:
	GLFWwindow						*window;
	int								width;
	int								height;
	std::map<std::string, GLuint>	VBOs;
	std::map<std::string, GLuint>	VAOs;
	std::map<std::string, Shader>	shaderPrograms;
};

# include "ParticleSystem.hpp"

#endif