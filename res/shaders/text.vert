#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform vec2 element_offset;
uniform mat4 transform;

out vec3 fragment_position;
out vec2 fragment_uv;

void main()
{
    gl_Position = /*transform */ vec4(position + vec3(element_offset, 0.), 1.0);

    fragment_position = position;
    fragment_uv = uv;
}
