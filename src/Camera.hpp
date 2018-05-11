#ifndef CAMERA_HPP
# define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

	public:
		Camera(
			glm::vec3 position = glm::vec3(.0f, .0f, -5.0f),
			glm::vec3 target = glm::vec3(.0f, .0f, 1.0f)
		);
		~Camera();

		void		updateViewMatrix();

		// Getters
		glm::mat4 getViewMatrix() { return this->viewMatrix; }

	private:
		glm::vec3	position;
		glm::vec3	up;
		glm::vec3	target;
		glm::mat4	viewMatrix;

		// rotation around Y
		float		horizontal_rotation;
		// rotation around X
		float		vertical_rotation;
};

#endif