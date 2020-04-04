#version 130

in vec3 fragment_position;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform vec3 camera_position;

out vec4 out_fragment_color;

void main()
{
	float y = fragment_position.y;

	float stop1 = 0.4;
	float stop2 = 0.5;
	float stop3 = 0.8;

	vec3 c1=vec3(0.3,0.4,0.9);
	vec3 c2=vec3(0.9);
	vec3 c3=vec3(0.2,0.8,1)*0.8;

	out_fragment_color.w=1.0;

	out_fragment_color.xyz = c1;
	out_fragment_color.xyz = mix(out_fragment_color.xyz, c2, smoothstep(stop1, stop2, y));
	out_fragment_color.xyz = mix(out_fragment_color.xyz, c3, smoothstep(stop2, stop3, y));	

	// out_fragment_color = vec4(.1f, .1f, .5f, 1.0f);
} 
