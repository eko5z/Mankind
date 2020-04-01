#version 130

out gl_PerVertex { vec4 gl_Position; };

void main()
{
	gl_Position = gl_Vertex;
}

