#include "Camera.hpp"

Camera::Camera( glm::vec3 position, glm::vec3 front ) :
	position(position),
	front(front),
	speed(0.01)
{
	this->up = glm::vec3(.0f, 1.0f, .0f);
	this->horizontal_rotation = 0;
	this->vertical_rotation = 0;
	this->updateViewMatrix();
}

Camera::~Camera() {}

void	Camera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(
		this->position,
		this->position + this->front,
		this->up
	);
}

void	Camera::processInput(GLFWwindow *win) {
	if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
        this->position += this->speed * this->front;
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        this->position -= this->speed * this->front;
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        this->position -= glm::normalize(glm::cross(this->front, this->up)) * this->speed;
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        this->position += glm::normalize(glm::cross(this->front, this->up)) * this->speed;
	this->updateViewMatrix();
}