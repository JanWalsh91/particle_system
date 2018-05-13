#ifndef FORCES_HPP
# define FORCES_HPP

# include <vector>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class Forces {

	public:
		Forces();
		Forces(Forces const &);
		~Forces();

		Forces &operator=(Forces const & rhs);
	
		class Force {
			public:
				Force();
				Force(glm::vec3 position, glm::vec3 color = glm::vec3(1, 1, 1), float mass = 1);
				~Force();

				glm::vec3	position;
				glm::vec3	color;
				float		mass;
		}

		void	addForce();
		void	data();

		// Getters
		std::vector<Forces::Force>	&getForces() { return this->forces; }
		
	private:
		std::vector<Forces::Force> forces;
};

#endif