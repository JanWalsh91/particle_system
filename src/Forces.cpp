#include "Force.hpp"

Force::Force() {
	num = 0;
}

Force::Force( Force const & force ) {
	*this = force;
}

Force::~Force() {}

Force &Force::operator=(Force const & rhs) {
	return *this;
}



// void Force::addForce(glm::vec3 position, glm::vec3 color = glm::vec3(1, 1, 1), float mass = 1) {
// 	std::vector<float> newForce;

// 	newForce[0] = position.x;
// 	newForce[1] = position.y;
// 	newForce[2] = position.z;
// 	newForce[3] = color.x;
// 	newForce[4] = color.y;
// 	newForce[5] = color.z;
// 	newForce[6] = mass;
// 	this->data.insert( this->data.end(), newForce.begin(), newForce.end() );
// 	++this->num;
// }
