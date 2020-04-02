#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 MVP;

out mat4 fragment_MVP;
out vec3 fragment_position;
out vec3 fragment_normal;
out vec2 fragment_uv;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);

    fragment_MVP = MVP;
    fragment_position = position;
    fragment_normal = normal;      
    fragment_uv = uv;
}
