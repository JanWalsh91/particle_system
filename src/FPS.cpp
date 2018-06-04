#include "FPS.hpp"

FPS::FPS(unsigned int sampleSize) : fps(NAN), sampleSize(sampleSize) {
	this->reset();
}

FPS::~FPS() {}

void	FPS::reset(float startTime) {
	glfwSetTime(startTime);
}

void	FPS::update() {
	if (this->timeList.size() >= this->sampleSize) {
		this->timeList.pop_front();
	}
	this->timeList.push_back(glfwGetTime());
	float elapsedTime = this->timeList.back() - this->timeList.front();
	this->fps = this->timeList.size() / elapsedTime;
}

void	FPS::updateLast() {
	this->timeList.pop_back();
	this->timeList.push_back(glfwGetTime());
}

float	FPS::getDeltaTime() {
	if (this->timeList.size() > 1) {
		return this->timeList.back() - *std::prev(this->timeList.end(), 2);
	}
	else if (this->timeList.size() == 1) {
		return this->timeList.back();
	}
	else {
		return NAN;
	}
}

// Getters
int		FPS::getFPS() const {
	return this->fps;
}