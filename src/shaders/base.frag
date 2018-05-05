#version 410 core

out vec4 FragColor;

in vec3 ObjColor;

void main()
{
	FragColor = vec4(ObjColor, 1.0);
}