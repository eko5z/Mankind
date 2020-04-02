#version 130

in vec2 fragment_uv;
in vec3 fragment_normal;

uniform sampler2D texture_1;

out vec4 out_fragment_color;

void main()
{
	vec3 light_color = vec3(1., 1., 1.);
	vec3 norm = normalize(fragment_normal);
	vec3 light_dir = normalize(vec3(-1, -1, -1));
	float diff = max(dot(norm, light_dir), 0.0);
	out_fragment_color = texture(texture_1, fragment_uv);
} 
