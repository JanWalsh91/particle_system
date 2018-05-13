#include "Force.hpp"

Force::Force() : Force::Force(glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1)) {}

Force::Force(glm::vec3 position, float mass, glm::vec3 color) :
	position(glm::vec4(position, 0)),
	color(glm::vec4(color, 0)),
	mass(mass) {}

Force::Force( Force const & force ) {
	*this = force;
}

Force::~Force() {}

Force &Force::operator=(Force const & rhs) {
	return *this;
}