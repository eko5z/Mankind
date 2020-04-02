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
	vec3 ambient, diffuse, specular;
};

uniform DirectionalLight directional_lights[N_DIRECTIONAL_LIGHTS];
uniform float shininess;

vec3 DirectionalLightCalculate(DirectionalLight light, vec3 normal, vec3 view_direction)
{
	vec3 ambient = light.ambient * vec3(texture(diffuse_texture, fragment_uv));

	float diff = max(dot(normal, light.direction), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse_texture, fragment_uv));

	vec3 reflection_direction = reflect(-light.direction, normal);
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
	vec3 specular = light.specular * spec * vec3(texture(specular_texture, fragment_uv));

	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(fragment_normal);
	vec3 view_direction = normalize(fragment_camera_position - fragment_position);
	vec3 result;

	for (int i = 0; i < N_DIRECTIONAL_LIGHTS; ++i)
	{
		result += DirectionalLightCalculate(directional_lights[i], normal, view_direction);
	}

	out_fragment_color = vec4(result, 1.0);
} 
