#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include <string>
# include <cmath>

# include "OpenGLWindow.hpp"
# include "OpenCLContext.hpp"
# include "Camera.hpp"
# include "FPS.hpp"

class ParticleSystem {

	public:
		ParticleSystem();
		~ParticleSystem();

		Camera	camera;

		void init(
			int numParticles = 1,
			std::string initLayout = "cube",
			bool paused = false
		);
		void loop();

	private:
		void updateParticles();
		void processInput();

		cl_uint			numParticles;
		OpenCLContext	*CL;
		OpenGLWindow	*GL;
		FPS				*fps;
		bool			paused;

};

#endif