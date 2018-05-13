#ifndef FORCE_HPP
# define FORCE_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class Force {

	public:
		Force();
		Force(glm::vec3 position, float mass = 1, glm::vec3 color = glm::vec3(1, 1, 1));
		Force(Force const &);
		~Force();

	Force &operator=(Force const & rhs);
	
	private:
		glm::vec4	position;
		glm::vec4	color;
		float		mass;
};

#endif