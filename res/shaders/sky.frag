#version 130

in vec3 fragment_position;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

void main()
{
	out_fragment_color = vec4(.5f, .5f, .5f, 1.0f);
} 
