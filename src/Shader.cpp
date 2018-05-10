#include "Shader.hpp"

Shader::Shader() {}

Shader::Shader( const char* vertexPath, const char* fragmentPath ) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	fShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch ( std::ifstream::failure e )
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader( Shader const & Shader ) {
	*this = Shader;
}

Shader::~Shader( void ) {
}

Shader & Shader::operator=( Shader const & rhs ) {
	this->ID = rhs.ID;
	return *this;
}

void Shader::checkCompileErrors( unsigned int shader, std::string type )
{
	int success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
		if (!success)
		{
			glGetShaderInfoLog( shader, 1024, NULL, infoLog );
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << " [" << infoLog << "]" << std::endl;
		}
	}
	else
	{
		glGetProgramiv( shader, GL_LINK_STATUS, &success );
		if (!success)
		{
			glGetProgramInfoLog( shader, 1024, NULL, infoLog );
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << " [" << infoLog << "]" << std::endl;
		}
	}
}

void Shader::use( void ) 
{ 
	glUseProgram(ID); 
}

void Shader::setBool( const std::string &name, bool value ) const
{         
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt( const std::string &name, int value ) const
{ 
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat( const std::string &name, float value) const
{ 
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setVector( const std::string &name, glm::vec4 v) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z);
}

void Shader::setMatrix( const std::string &name, glm::mat4 m) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

	