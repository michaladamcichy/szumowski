#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNormal;

out vec2 uv;
out vec3 normal;
out vec4 fragmentPosition;

void main() {
	gl_Position = vec4(inPosition, 1.0);
	
	uv = inUv;
	normal =  normalize(inNormal);
	fragmentPosition = vec4(inPosition, 1.0);
};