#include "FPS.hpp"

FPS::FPS(unsigned int sampleSize) : fps(NAN), sampleSize(sampleSize) {
	this->reset();
}

FPS::~FPS() {}

void	FPS::reset(double startTime) {
	glfwSetTime(startTime);
}

void	FPS::update() {
	// std::cout << "udpate" << std::endl;
	// if timeList is larger that sampleSize, remove first element
	if (this->timeList.size() >= this->sampleSize) {
		this->timeList.pop_front();
	}
	this->timeList.push_back(glfwGetTime());
	// std::cout << "added: " << this->timeList.back() << std::endl;
	// calculate FPS
	double elapsedTime = this->timeList.back() - this->timeList.front();
	this->fps = this->timeList.size() / elapsedTime;
}

// Getters
int		FPS::getFPS() const {
	return this->fps;
}