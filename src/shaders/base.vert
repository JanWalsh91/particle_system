#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 speed;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ObjColor;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position.xyz, 1.0);
	//gl_Position = viewMatrix * vec4(position, 1.0);
	ObjColor = vec3(1, 1, 1);
}
