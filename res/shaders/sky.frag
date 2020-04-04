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
	vec4 bottom_color = vec4(1.0, 0.0, 0.0, 1.0); // < 0.5
	vec4 top_color = vec4(0.0, 0.4, 0.7, 1.0); // > 0.5

	float factor = (cos(camera_pitch + (radians(45.0) / 2) * fragment_position.y) + 1) / 2;

	out_fragment_color = mix(bottom_color, top_color, factor);
} 
