#version 130

in vec3 coordinates;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(coordinates, 1.0);
}
