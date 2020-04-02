#version 130

#define MAX_DIRECTIONAL_LIGHTS 1

in vec3 fragment_camera_position;
in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

// v --- I don't think we really need a Material struct, since we already have diffuse and specular maps.
uniform float shininess;

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse, ambient, specular;
};

uniform DirectionalLight directional_lights[MAX_DIRECTIONAL_LIGHTS];

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_direction)
{
	vec3 light_direction = normalize(-light.direction);
	
	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse_texture, fragment_uv));

	vec3 ambient = light.ambient * vec3(texture(diffuse_texture, fragment_uv));

	vec3 reflection_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
	vec3 specular = light.specular * spec * vec3(texture(specular_texture, fragment_uv));

	return (diffuse + ambient + specular);
}

void main()
{
	vec3 normal = normalize(fragment_normal);
	vec3 view_direction = normalize(fragment_camera_position - fragment_position);
	vec3 result;

	// Calculate the directional lights.
	for(int i = 0; i < MAX_DIRECTIONAL_LIGHTS; ++i)
	{
		result += CalculateDirectionalLight(directional_lights[i], normal, view_direction);
	}

	out_fragment_color = vec4(result, 1.0);
} 
