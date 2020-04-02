#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec4 fragmentPosition;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;
uniform sampler2D textureNormals;


uniform vec3 cameraDirection;
uniform vec3 cameraPosition;
uniform vec3 lightSourcePosition;

uniform float ambientLighting;
uniform float diffuseLighting;
uniform float specularLighting;
uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform mat3 normalTransformation;
  
void main()
{
	vec4 textureColor = texture(textureDiffuse, uv);

	vec3 norm = texture(textureNormals, uv).xyz * 2 - vec3(1.0);
	norm.y = -norm.y;
	norm = normalize(normalTransformation * (-norm.xyz));
	vec3 lightDir = normalize(-lightDirection);
	float diff = max(dot(norm.xyz, lightDir), 0.0);
	//vec3 diffuse = diff * lightColor;

	vec4 output = vec4(diff * textureColor.xyz, textureColor.a);
	//FragColor = vec4(normalTransformation[0][1], normalTransformation[1][2], normalTransformation[2][1], 1.0);
	FragColor = vec4(diff * textureColor.xyz, textureColor.a);
	//FragColor = vec4(norm, textureColor.a);
}