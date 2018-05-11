#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include <string>
# include <cmath>

# include "OpenGLWindow.hpp"
# include "OpenCLContext.hpp"
# include "Camera.hpp"
# include "FPS.hpp"

typedef struct	Particle {
	float positionx;
	float positiony;
	float positionz;
	float positionw;
	float speedx;
	float speedy;
	float speedz;
	float speedw;
}				Particle;

class ParticleSystem {

	public:
		ParticleSystem();
		~ParticleSystem();

		Camera	camera;

		void init(int numParticles = 1, std::string initLayout = "cube");
		void loop();
		void updateParticles();

	private:
		cl_uint			numParticles;
		OpenCLContext	*CL;
		OpenGLWindow	*GL;
		FPS				*fps;

};

#endif