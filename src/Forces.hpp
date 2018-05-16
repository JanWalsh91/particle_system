#ifndef FORCES_HPP
# define FORCES_HPP

# include <vector>
# include <string>
# include <exception>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/fwd.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "Camera.hpp"

class Forces {

	public:
		Forces();
		~Forces();
	
		class Force {
			public:
				Force(
					glm::vec3 position = glm::vec3(1, 1, 1),
					glm::vec3 color = glm::vec3(1, 1, 1),
					float mass = 1
				);
				~Force() {};

				glm::vec3	position;
				glm::vec3	color;
				float		mass;
				bool		locked;
		};

		void	addForce(Forces::Force force);
		void	addForce();
		void	nextForce();
		void	delForce();
		void	toggleLock();
		void	updateData();
		void	updateForcePosition(Camera &camera, float depth, int x, int y);
		float	*data();
		void	setVAO(int VAO);

		// Getters
		std::vector<Forces::Force>	&getForces();
		Forces::Force & getForce(int i);
		int	getCurrentForce();
		int	size();
		
	private:
		std::vector<Forces::Force> forces;
		int	VAO;
		int currentForce;
};

#endif