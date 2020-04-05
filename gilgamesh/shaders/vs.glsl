#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in float inTexture;

out vec2 uv;
out vec3 normal;
out vec4 fragmentPosition;
out float textureId;

uniform mat4 cameraTransformation;
uniform mat3 cameraRotations;

void main() {
	gl_Position = cameraTransformation * vec4(inPosition, 1.0);
	
	uv = inUv;
	normal =  normalize(cameraRotations * inNormal); //ALERT! nie testowane
	fragmentPosition = vec4(inPosition, 1.0);
	textureId = inTexture;
};