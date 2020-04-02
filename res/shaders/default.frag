#version 130

in vec2 fragment_uv;
in vec3 fragment_normal;

uniform sampler2D texture_1;

out vec4 out_fragment_color;

void main()
{
	vec3 diffuse_color = vec3(.5, .5, .5);
	vec3 ambient_color = vec3(.2, .2, .2);

	vec3 normal = normalize(fragment_normal);
	vec3 light_direction = normalize(vec3(0.3, 1, 0.5));
	float difference = max(dot(normal, light_direction), 0.0);

	vec3 diffuse = diffuse_color * difference * texture(texture_1, fragment_uv).rgb;
	vec3 ambient = ambient_color * texture(texture_1, fragment_uv).rgb;
	vec3 result = diffuse + ambient;

	out_fragment_color = vec4(result, 1.0);
} 
