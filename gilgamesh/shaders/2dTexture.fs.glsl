#version 330 core
out vec4 FragColor;
in vec2 uv;

uniform sampler2D texture;

void main()
{
	FragColor = texture(texture, uv);
	if (FragColor.r < 0.2 && FragColor.g < 0.2 && FragColor.b < 0.2) discard;
};