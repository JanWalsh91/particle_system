#include "Camera.hpp"

Camera::Camera( glm::vec3 position, glm::vec3 target ) :
	position(position),
	target(target)	
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
		this->target,
		this->up
	);
}