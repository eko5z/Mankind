#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 MVP;

out vec2 out_uv;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    out_uv = uv;
}
