#include "Forces.hpp"

Forces::Forces() {}

Forces::~Forces() {}

void Forces::addForce(Forces::Force force) {
	this->forces.push_back(force);
}

float	*Forces::data() {
	std::vector<float> *data = new std::vector<float>;

	for (Forces::Force & force : this->forces) {
		data->push_back(force.position.x);
		data->push_back(force.position.y);
		data->push_back(force.position.z);
		data->push_back(force.color.x);
		data->push_back(force.color.y);
		data->push_back(force.color.z);
		data->push_back(force.mass);
	}
	return data->data();
}

std::vector<Forces::Force> &Forces::getForces() {
	return this->forces;
}

Forces::Force & Forces::getForce(int i) {
	if (i < this->forces.size()) {
		return this->forces[i];
	}
	else
		throw "No force at this index";
}

void	Forces::delForce(int i) {
	if (i < this->forces.size()) {
		this->forces.erase(this->forces.begin() + i);
	}
	else
		throw "No force at this index";
}

int		Forces::size() {
	return this->forces.size();
}

// ======== Force ========= //
Forces::Force::Force(glm::vec3 position, glm::vec3 color, float mass) :
	position(position),
	color(color),
	mass(mass),
	locked(true) {}