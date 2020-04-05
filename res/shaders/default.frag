#version 130

#define N_DIRECTIONAL_LIGHTS 1

in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

out vec4 out_fragment_color;

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse_color, ambient_color, specular_color;
};

uniform DirectionalLight directional_lights[N_DIRECTIONAL_LIGHTS];
uniform vec3 camera_position;

void main()
{
	vec3 normal = normalize(fragment_normal);
	vec4 result;

	vec3 someshit = directional_lights[0].specular_color + vec3(1.0, 1.0, 1.0);

	for (int i = 0; i < N_DIRECTIONAL_LIGHTS; ++i)
	{
		vec4 ambient = vec4(directional_lights[i].ambient_color, 1.0) * texture(diffuse_texture, fragment_uv);

		float diff = max(dot(normal, directional_lights[i].direction), 0.0);
		vec4 diffuse = diff * vec4(directional_lights[i].diffuse_color, 1.0) * texture(diffuse_texture, fragment_uv);

		// Maybe the fix for Adrien?
		if(i == 0)
		{
			result = ambient + diffuse;
		}
		else
		{
			result += ambient + diffuse;
		}
	}

	out_fragment_color = result;
} 
