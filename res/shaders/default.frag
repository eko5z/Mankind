#version 130

#define N_DIRECTIONAL_LIGHTS 1

in vec3 fragment_camera_position;
in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse_color, ambient_color;
};

uniform DirectionalLight directional_light;

void main()
{
	vec3 normal = normalize(fragment_normal);

	vec3 ambient = directional_light.ambient_color * vec3(texture(diffuse_texture, fragment_uv));

	float diff = max(dot(normal, directional_light.direction), 0.0);
	vec3 diffuse = diff * directional_light.diffuse_color * vec3(texture(diffuse_texture, fragment_uv));

	vec3 result = ambient + diffuse;

	out_fragment_color = vec4(result, 0.0);
} 
