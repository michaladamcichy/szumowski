#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUv;
layout(location = 2) in vec3 inNormal;

uniform mat4 mvp;

out vec2 uv;
out vec3 normal;
out vec4 fragmentPosition;

uniform mat3 normalTransformation;
uniform mat4 modelTransformation;

uniform mat4 lookTowardsCamera;

void main() {
	gl_Position = mvp * lookTowardsCamera * vec4(inPosition, 1.0);

	uv = inUv;
	normal =  normalize(normalTransformation * inNormal);
	fragmentPosition = modelTransformation * vec4(inPosition, 1.0);
};