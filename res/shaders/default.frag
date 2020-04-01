#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform sampler2D texture_1;

out vec4 out_fragment_color;

void main()
{
	out_fragment_color = texture(texture_1, uv);
} 
