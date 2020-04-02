#version 330 core
out vec4 FragColor;


struct Material {
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  

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
uniform vec3 lightSourcePosition;

uniform Material material;



uniform float ambientLighting;
uniform float diffuseLighting;
uniform float specularLighting;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float additionalRed;

uniform mat3 normalTransformation;
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	float depth = 1 - LinearizeDepth(gl_FragCoord.z) / far;
	vec4 textureColor = texture(textureDiffuse, uv);
	
	vec3 ambient = vec3(ambientLighting)*vec3(0.8);

	
	//diffuse
	vec3 norm = normal;
	vec3 lightDir = normalize(-lightDirection); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * diffuseLighting) * lightColor;

	//specular
	vec3 viewDir = normalize(cameraPosition - fragmentPosition.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * specularLighting) * lightColor;
	//vec3 specular = (spec * specularLighting) * lightColor * vec3(texture(textureSpecular, uv));

	vec4 output = vec4(textureColor.xyz * depth * ( diffuse+ambient+specular) , textureColor.a);
	output.r += additionalRed;
	FragColor = output;
}