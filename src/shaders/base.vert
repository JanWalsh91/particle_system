#version 410 core

#define MAX_FORCES 3

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 speed;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 camPos;
uniform vec3 camDir;
uniform float cursorDepth;
uniform float forces[MAX_FORCES * 7];
uniform int forcesNum;

out vec3 ObjColor;

float asymptote(float x) {
	return 1 / x;
}

vec3 asymptotevec3(vec3 v) {
	v.x = asymptote(v.x);
	v.y = asymptote(v.y);
	v.z = asymptote(v.z);
	return v;
}

void main()
{
	gl_Position = projectionMatrix * viewMatrix * vec4(position.xyz, 1.0);
	ObjColor = vec3(.0f, .0f, .0f);
	vec3 center = vec3(.0f, .0f, .0f);
	vec3 color = vec3(.0f, .0f, .0f);

	for (int i = 0; i < forcesNum; ++i) {
		center = vec3(forces[i*7 + 0], forces[i*7 + 1], forces[i*7 + 2]);
		color = vec3(forces[i*7 + 3], forces[i*7 + 4], forces[i*7 + 5]);
		ObjColor += color * asymptote(length(position.xyz - center)) * forces[i*7 + 6] * 1000;
	}

	vec3 grey = vec3(0.01, 0.01, 0.015);
	vec3 CP = position.xyz - camPos;
	float distFromCam = dot(CP, camDir)/length(camDir);
	ObjColor = mix(ObjColor, grey, distFromCam / (distFromCam + 1));
}

