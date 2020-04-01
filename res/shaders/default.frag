#version 130

in vec2 fragment_uv;

uniform sampler2D texture_1;

out vec4 out_fragment_color;

void main()
{
	out_fragment_color = texture(texture_1, fragment_uv);
} 
