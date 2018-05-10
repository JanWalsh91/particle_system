#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 speed;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ObjColor;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
	ObjColor = vec3(1, 1, 1);
}
