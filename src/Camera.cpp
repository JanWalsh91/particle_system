#include "Camera.hpp"

Camera::Camera( glm::vec3 position ) :
	position(position)
{
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->up = glm::vec3(.0f, 1.0f, .0f);
	this->worldUp = this->up;
	this->speed = this->minSpeed;
	this->updateVectors();
	this->updateViewMatrix();
	this->lastUpdate = glfwGetTime();
}

Camera::~Camera() {}

void	Camera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(
		this->position,
		this->position + this->front,
		this->up
	);
}

void	Camera::processInput(CameraMovement movement, float deltaTime) {
	float currentTime = glfwGetTime();
	if (currentTime - lastUpdate < 0.1)
		this->speed < this->maxSpeed ? this->speed += 0.1f : 0;
	else
		this->speed = this->minSpeed;
	this->lastUpdate = currentTime;
	float speed = this->speed * deltaTime;

	if (movement == FORWARD)
        this->position += (speed * this->front);
	else if (movement == BACKWARD)
        this->position -= (speed * this->front);
	else if (movement == LEFT)
        this->position -= this->right * speed;
	else if (movement == RIGHT)
        this->position += this->right * speed;
	else if (movement == TURN_UP)
		this->pitch += speed * 20;
	else if (movement == TURN_DOWN)
		this->pitch -= speed * 20;
	else if (movement == TURN_LEFT)
		this->yaw -= speed * 20;
	else if (movement == TURN_RIGHT)
		this->yaw += speed * 20;

	this->updateVectors();
	this->updateViewMatrix();
}

void	Camera::updateVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up    = glm::normalize(glm::cross(this->right, this->front));
}

float Camera::maxSpeed = 3.0f;
float Camera::minSpeed = 0.1f;