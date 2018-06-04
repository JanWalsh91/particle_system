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
	if (i < (int)this->forces.size()) {
		return this->forces[i];
	}
	else
		throw "No force at this index";
}

int		Forces::size() {
	return this->forces.size();
}

void Forces::addForce() {
	if ((int)this->forces.size() >= 3)
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
	glm::vec3 colorVector = glm::vec3(0, 0, 0);
	if (colors[0] == "red")
		colorVector = glm::vec3(1, 0, 0);
	if (colors[0] == "blue")
		colorVector = glm::vec3(0, 0, 1);
	if (colors[0] == "green")
		colorVector = glm::vec3(0, 1, 0);
	this->forces.push_back(Forces::Force(glm::vec3(0, 0, 0), colorVector, 0.1));
	this->currentForce = this->forces.size() - 1;
	this->updateData();
	printf("New Force. Total: %lu, Current: %d\n", this->forces.size(), this->currentForce);
}

void Forces::nextForce() {
	++this->currentForce;
	if (this->currentForce >= (int)this->forces.size())
		this->currentForce = 0;
	printf("Current Force: %d\n", this->currentForce);
}

// del force

void Forces::delForce(bool forceDel) {
	if (((int)this->forces.size() > 1 && this->currentForce < (int)this->forces.size()) || forceDel == true) {
		this->forces.erase(this->forces.begin() + this->currentForce);
		this->updateData();
		this->currentForce = this->forces.size() - 1;
		printf("Del Force. Total: %lu, Current: %d\n", this->forces.size(), this->currentForce);
	}
}

void Forces::toggleLock() {
	this->forces[this->currentForce].locked = !this->forces[this->currentForce].locked;
	this->updateData();
}

// update force position
void Forces::updateData() {
	GLuint buffSize = sizeof(float) * 7 * this->forces.size();
	glBindVertexArray(this->VAO);
	glBufferData(GL_ARRAY_BUFFER, buffSize, this->data(), GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void Forces::updateForcePosition(Camera &camera, float depth, int x, int y) {
	// get viewport info
	GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
	GLint height = viewport[3];
	GLint width = viewport[2];
 
	// calculate ray plane intersection
	float aspectRatio = (float)width/height;

	glm::vec4 vec;
	float scale = tan(glm::radians(45 * 0.5));
	vec.x = (2 * (x + 0.5) / (float)width - 1) * aspectRatio * scale; 
	vec.y = (1 - 2 * (y + 0.5) / (float)height) * scale;
	vec.z = -1;
	vec.w = 0;

	vec = glm::normalize(vec);
	vec = vec * camera.getViewMatrix();

	glm::vec4 planePos = glm::vec4(camera.getPosition() + camera.getFront() * depth, 0);
	glm::vec4 planeDir = glm::vec4(camera.getFront(), 0);
	
	vec = glm::normalize(vec);
	float d1 = glm::dot(planeDir, vec);
	glm::vec4 v1 = planePos - glm::vec4(camera.getPosition(), 0);
	float r1 = glm::dot(v1, planeDir) / d1;
	vec = r1 * glm::normalize(vec);

	vec = vec + glm::vec4(camera.getPosition(), 0);
	
	Forces::Force &f = this->forces[currentForce];
	f.position.x = vec.x;
	f.position.y = vec.y;
	f.position.z = vec.z;
	
	// update forces data in buffer
	this->updateData();
}

void Forces::setVAO(GLuint VAO) {
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