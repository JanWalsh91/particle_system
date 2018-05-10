#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include <string>

# include "OpenGLWindow.hpp"
# include "OpenCLContext.hpp"
# include "Camera.hpp"

class ParticleSystem {

	public:
		ParticleSystem();
		~ParticleSystem();

		Camera	camera;

		void init(int numParticles = 1, std::string initLayout = "");
		void loop();
		void updateParticles();

	private:
		int				numParticles;
		OpenCLContext	*CL;
		OpenGLWindow	*GL;
		GLuint			VAO;
		GLuint			VBO;
		// cl::BufferGL	*clbuf;

};

#endif