#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include "Camera.hpp"

class ParticleSystem {

	public:
		// init with preset:
		// 	number of particles, 
		//  paticle setup (position)
		ParticleSystem(int numParticles = 1, std::string initLayout = "");
		~ParticleSystem();

		Camera	camera;

	private:
		// array of particle positions need to be on GPU
};

#endif