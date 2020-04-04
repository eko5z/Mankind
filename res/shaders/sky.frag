#version 130

in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform float camera_pitch;

out vec4 out_fragment_color;

void main()
{
	vec4 zenith_color = vec4(0.1, 0.1, 1.0, 1.0);
	vec4 nadir_color = vec4(0.5, 0.5, 1.0, 1.0);

	float factor = (sin(camera_pitch + (radians(45.0) / 2) * fragment_position.y) + 1) / 2;

	out_fragment_color = mix(zenith_color, nadir_color, factor);
} 
