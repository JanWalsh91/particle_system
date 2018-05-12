#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

	public:
		Camera(
			glm::vec3 position = glm::vec3(.0f, .0f, -2.0f),
			glm::vec3 front = glm::vec3(.0f, .0f, 1.0f)
		);
		~Camera();

		void		updateViewMatrix();

		// Getters
		glm::mat4 getViewMatrix() { return this->viewMatrix; }
		void processInput(GLFWwindow *win);

	private:
		glm::vec3	position;
		glm::vec3	up;
		glm::vec3	front;
		glm::mat4	viewMatrix;

		float		speed;

		// rotation around Y
		float		horizontal_rotation;
		// rotation around X
		float		vertical_rotation;
};

#endif