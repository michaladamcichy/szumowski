#version 330 core
out vec4 FragColor;

struct Light {
	vec3 position;
	float ambient;
	float diffuse;
	float specular;
	vec3 direction;
	vec3 color;
};

in vec2 uv;
in vec3 normal;
in vec4 fragmentPosition;
in float textureId;

uniform sampler2D textures[9];
uniform sampler2D texture1;
uniform sampler2D texture2;


uniform float near;
uniform float far;

uniform vec3 cameraDirection;
uniform vec3 cameraPosition;

uniform Light light;
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	float depth = 1 - LinearizeDepth(gl_FragCoord.z) / far;
	int index = int(round(textureId));

	vec4 textureColor = texture(textures[index], uv);

	if(textureColor.a == 0.0) {
		discard;
	}

	float ambient = light.ambient;
	float diffuse = max(dot(normal, -light.direction), 0.0);
	
	vec3 fragmentTowardsCamera = normalize(vec3(cameraPosition) - vec3(fragmentPosition));
	vec3 fragmentTowardsLight = normalize(-reflect(-light.direction, normal));
	
	float specular = pow(max(dot(fragmentTowardsCamera, fragmentTowardsLight), 0.0), 32); //ALERT hardcoded specular

	vec4 final = vec4(textureColor.xyz * (diffuse + specular) * depth, textureColor.a);
	
	//vec4 final = vec4(vec3(abs(normal.x), abs(normal.y), abs(normal.z)) * depth, textureColor.a);
	FragColor = final;
}
