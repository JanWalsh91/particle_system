#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 speed;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 camPos;
uniform vec3 camDir;
uniform float cursorDepth;

out vec3 ObjColor;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position.xyz, 1.0);
	
	vec3 center = vec3(0, 0, 0);
	vec3 color = vec3(1, 0.2, 0.4);
	vec3 distance = abs( position.xyz );
	//ObjColor = (0.9 - length(distance)) * color;
	ObjColor = color;


	vec3 grey = vec3(0.5, 0.5, 0.5);
	vec3 CP = position.xyz - camPos;
	float distFromCam = dot(CP, camDir)/length(camDir);
	if (distFromCam > cursorDepth) {
		ObjColor = mix(ObjColor, grey, 0.5);
	}
}
