#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# define MAX_FORCES 3

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
		static void cursorPosCallback(GLFWwindow* window, double x, double y);
		
		// Getters
		OpenGLWindow	*getGL();

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
		int					currentForce;
};

#endif