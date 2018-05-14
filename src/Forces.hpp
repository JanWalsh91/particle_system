#ifndef FORCES_HPP
# define FORCES_HPP

# include <vector>
# include <exception>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>


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
		void	delForce(int i);
		float	*data();

		// Getters
		std::vector<Forces::Force>	&getForces();
		Forces::Force & getForce(int i);
		int	size();
		
	private:
		std::vector<Forces::Force> forces;
};

#endif