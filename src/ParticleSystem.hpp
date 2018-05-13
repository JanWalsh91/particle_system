#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include <string>
# include <cmath>

# include "OpenGLWindow.hpp"
# include "OpenCLContext.hpp"
# include "Camera.hpp"
# include "FPS.hpp"
# include "Forces.hpp"

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

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	private:
		void updateParticles();
		void processInput();
		void updateForcePosition(int x, int y);

		cl_uint				numParticles;
		OpenCLContext		*CL;
		OpenGLWindow		*GL;
		FPS					*fps;
		bool				paused;
		float				cursorDepth;
		Forces				forces;
};

#endif