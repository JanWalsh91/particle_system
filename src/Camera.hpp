#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm/fwd.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <GLFW/glfw3.h>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
	TURN_UP,
	TURN_DOWN,
	TURN_LEFT,
	TURN_RIGHT
};

class Camera {

	public:
		Camera(
			glm::vec3 position = glm::vec3(.0f, .0f, 2.5f)
		);
		~Camera();

		void		updateViewMatrix();
		void		processInput(CameraMovement movement, float deltaTime);

		// Getters
		glm::mat4	&getViewMatrix() { return this->viewMatrix; }
		glm::vec3	&getPosition() { return this->position; }
		glm::vec3	&getFront() { return this->front; }
		glm::vec3	&getUp() { return this->up; }

	private:
		glm::vec3	position;
		glm::vec3	up;
		glm::vec3	right;
		glm::vec3	front;
		glm::vec3	worldUp;
		glm::mat4	viewMatrix;

		float yaw;
		float pitch;

		void		updateVectors();

		float			speed;
		static float	minSpeed;
		static float	maxSpeed;
		float			lastUpdate;
};

#endif