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
			std::string layout = "sphere",
			bool paused = false,
			bool optimized = false,
			std::vector<std::string> skyboxFaces = {""}
		);
		void loop();

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPosCallback(GLFWwindow* window, double x, double y);
		static void scrollCallback(GLFWwindow* window, double x, double y);
		
		// Getters
		OpenGLWindow	*getGL();

	private:
		void initSkybox(std::vector<std::string> skyboxFaces);
		void initParticles();
		void initForces();
		void initCube();
		void initSphere();
		void updateParticles();
		void processInput();
		void reset();

		std::string			preset;
		bool				isReset;
		bool				optimized;
		unsigned int		skyboxTextureRef;
		cl_uint				numParticles;
		cl_uint				cubeSize;
		OpenCLContext		*CL;
		OpenGLWindow		*GL;
		FPS					*fps;
		bool				paused;
		float				cursorDepth;
		Forces				forces;
};

#endif