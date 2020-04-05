#version 130

#define M_PI 3.14159

in vec3 fragment_position;

uniform vec3 sun_direction;
uniform float camera_pitch;
uniform float camera_yaw;
uniform float vertical_fov;
uniform float horizontal_fov;

out vec4 out_fragment_color;

float GetAngle(vec3 u, vec3 v)
{
	float dotproduct = dot(u, v);
	float angle = acos(dotproduct);
	if (dotproduct < 0) {
		angle += M_PI;
	}
	return angle;
}

void main()
{
	// Render the sky gradient.
	vec4 zenith_color = vec4(0.04, 0.22, 0.35, 1.0);
	vec4 nadir_color = vec4(0.98, 0.96, 0.77, 1.0);

	float frag_X_angle = asin(fragment_position.x * sin(horizontal_fov / 2)) - camera_yaw;
	float frag_Y_angle = asin(fragment_position.y * sin(vertical_fov / 2)) + camera_pitch;

	float factor = (sin(frag_Y_angle) + 1) / 2;

	vec4 sky = mix(nadir_color, zenith_color, factor);


	// Render the sun.
	vec3 fragment_vector = normalize(vec3(
		-sin(frag_Y_angle) * cos(frag_X_angle),
		cos(frag_Y_angle),
		sin(frag_Y_angle) * sin(frag_X_angle)
	));

	if (GetAngle(fragment_vector, normalize(sun_direction * 1.f)) < .1 ) {
		out_fragment_color = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		out_fragment_color = sky;
	}
} 

