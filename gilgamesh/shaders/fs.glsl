#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec4 fragmentPosition;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;
uniform sampler2D textureNormals;

uniform float near;
uniform float far;

uniform vec3 cameraDirection;
uniform vec3 cameraPosition;
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	float depth = 1 - LinearizeDepth(gl_FragCoord.z) / far;
	//vec4 textureColor = texture(textureDiffuse, uv);
	
	vec4 output = vec4(1.0,1.0,1.0,1.0);
	//vec4 output = vec4(textureColor.xyz * depth, textureColor.a);
	FragColor = output;
}