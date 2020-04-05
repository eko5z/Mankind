#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 MVP;

out vec3 fragment_position;

void main()
{
    gl_Position = vec4(position, 1.0);

    fragment_position = position;
}
