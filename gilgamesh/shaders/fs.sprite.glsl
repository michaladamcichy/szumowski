#version 330 core
out vec4 FragColor;

uniform float near;
uniform float far;

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

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	vec4 textureColor = texture(textureDiffuse, uv);
	if(textureColor.a == 0) {
		discard;
	}

	vec3 norm = texture(textureNormals, uv).xyz * 2 - vec3(1.0);
	//norm.y = -norm.y;
	//norm = normalize(normalTransformation * (-norm.xyz));
	vec3 lightDir = normalize(-lightDirection);
	float diff = max(dot(norm.xyz, lightDir), 0.0);

	float darkening = min(dot(lightDirection, cameraDirection), 0.0);

	vec4 output = vec4(diff * textureColor.xyz, textureColor.a);

	float depth = 1 - LinearizeDepth(gl_FragCoord.z) / far;


	FragColor = vec4(depth * diff * textureColor.xyz + darkening, textureColor.a);
	//FragColor = vec4(lightDirection.xyz, textureColor.a);
};
