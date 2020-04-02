#version 130

#define MAX_DIRECTIONAL_LIGHTS 1

in vec3 fragment_camera_position;
in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

void main()
{
	vec3 diffuse_color = vec3(.5, .5, .5);
	vec3 ambient_color = vec3(.2, .2, .2);
	vec3 specular_color = vec3(1., 1., 1.);
	float shininess = 64.0;

	vec3 normal = normalize(fragment_normal);
	vec3 light_direction = normalize(vec3(0.3, 1, 0.5));
	float difference = max(dot(normal, light_direction), 0.0);

	vec3 diffuse = diffuse_color * difference * texture(diffuse_texture, fragment_uv).rgb;
	vec3 ambient = ambient_color * texture(diffuse_texture, fragment_uv).rgb;

	vec3 view_direction = normalize(fragment_camera_position - fragment_position);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
	vec3 specular = specular_color * spec * texture(specular_texture, fragment_uv).rgb;

	vec3 result = diffuse + ambient + specular;

	out_fragment_color = vec4(result, 1.0);
} 
