#version 130

#define N_DIRECTIONAL_LIGHTS 1

in vec3 fragment_camera_position;
in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

void main()
{
	out_fragment_color = texture(diffuse_texture, fragment_uv);
} 
