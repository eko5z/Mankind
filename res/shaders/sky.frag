#version 130

in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform vec3 sun_direction;
uniform float camera_pitch;
uniform float camera_yaw;
uniform float vertical_fov;
uniform float horizontal_fov;

out vec4 out_fragment_color;

void main()
{
	// Render the sky gradient.
	vec4 zenith_color = vec4(0.04, 0.22, 0.35, 1.0);
	vec4 nadir_color = vec4(0.98, 0.96, 0.77, 1.0);

	float factor = (sin(camera_pitch + (radians(45.0) / 2) * fragment_position.y) + 1) / 2;

	vec4 sky = mix(nadir_color, zenith_color, factor);

	out_fragment_color = sky;

	// Render the sun.

	// The y middle fragment of the screen is camera_pitch + radians(FOV) / 2.
	// The x middle fragment of the screen is camera_yaw + radians(HFOV) / 2.
	float middle_y = camera_pitch + radians(vertical_fov) / 2;
	float middle_x = camera_yaw + radians(horizontal_fov) / 2;

	float vertical_angle = dot(middle_y, sun_direction.y);
	float horizontal_angle = dot(middle_x, sun_direction.x);

	vec3 fragment_vector = vec3(sin(horizontal_angle) * cos(horizontal_angle), sin(vertical_angle), cos(horizontal_angle) * cos(vertical_angle));

	float angle = acos(dot(fragment_vector, sun_direction * vec3(-1.0, -1.0, -1.0)) / (length(fragment_vector) * length(sun_direction)));

	if(angle < 0.5)
	{
		out_fragment_color = vec4(1.0, 1.0, 1.0, 1.0);
	}
} 
