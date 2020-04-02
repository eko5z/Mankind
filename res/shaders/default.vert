#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 MVP;

out vec2 fragment_uv;
out vec3 fragment_normal;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    fragment_uv = uv;
	fragment_normal = normal;
}
