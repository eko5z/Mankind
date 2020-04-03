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
	vec3 normal = normalize(fragment_normal);
	vec3 light_direction = vec3(0.3, 1.0, 0.3);

	vec3 ambient_color = vec3(0.5, 0.5, 0.5);
	vec3 diffuse_color = vec3(1, 1, 1);

	vec3 ambient = ambient_color * vec3(texture(diffuse_texture, fragment_uv));

	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diff * diffuse_color * vec3(texture(diffuse_texture, fragment_uv));

	vec3 result = ambient + diffuse;

	out_fragment_color = vec4(result, 0.0);
} 
