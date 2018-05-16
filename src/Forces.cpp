#include "Forces.hpp"

Forces::Forces() : 
	currentForce(0) {}

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

void Forces::addForce() {
	if (this->forces.size() >= 3)
		return ;
	std::vector<std::string> colors = {"red", "blue", "green"};
	for (Forces::Force & force: this->forces) {
		if (force.color.x == 1.0f)
			colors.erase(std::remove(colors.begin(), colors.end(), "red"), colors.end());
		if (force.color.y == 1.0f)
			colors.erase(std::remove(colors.begin(), colors.end(), "green"), colors.end());
		if (force.color.z == 1.0f)
			colors.erase(std::remove(colors.begin(), colors.end(), "blue"), colors.end());
	}
	glm::vec3 colorVector;
	if (colors[0] == "red")
		colorVector = glm::vec3(1, 0, 0);
	if (colors[0] == "blue")
		colorVector = glm::vec3(0, 0, 1);
	if (colors[0] == "green")
		colorVector = glm::vec3(0, 1, 0);
	this->forces.push_back(Forces::Force(glm::vec3(0, 0, 0), colorVector, 1));
	this->updateData();
}

// del force

// update forces data

// update force position
void Forces::updateData() {
	GLuint buffSize = sizeof(float) * 7 * this->size();
	glBindVertexArray(this->VAO);
	glBufferData(GL_ARRAY_BUFFER, buffSize, this->data(), GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void	Forces::setVAO(int VAO) {
	this->VAO = VAO;
}

int	Forces::getCurrentForce() {
	return this->currentForce;
}
// ======== Force ========= //
Forces::Force::Force(glm::vec3 position, glm::vec3 color, float mass) :
	position(position),
	color(color),
	mass(mass),
	locked(true) {}