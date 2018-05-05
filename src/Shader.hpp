#ifndef SHADER_H
# define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader {

	public:
		Shader( const char* vertexPath, const char* fragmentPath );
		Shader( void );
		Shader( Shader const & );
		~Shader( void );
		Shader & operator=( Shader const & rhs );
		void use( void );

		unsigned int	ID;

		void setBool( const std::string &name, bool value ) const;
		void setInt( const std::string &name, int value ) const;
		void setFloat( const std::string &name, float value) const;
		// void setVector( const std::string &name, Vector v) const;
		// void setMatrix( const std::string &name, Matrix m) const;

	private:
		void checkCompileErrors( unsigned int shader, std::string type );



	};

#endif