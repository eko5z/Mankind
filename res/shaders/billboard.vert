#version 130

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 model, view, projection;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec2 fragment_uv;

void main()
{
	// Undoing the rotations in the MV matrix.
	mat4 vm = view * model;

	for(int i = 0; i < 3; i += 2)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j)
			{
				vm[i][j] = 1.0;
			}
			else
			{
				vm[i][j] = 0.0;
			}
		}
	}

    gl_Position = (projection * vm) * vec4(position, 1.0);

    fragment_position = position;
    fragment_normal = normal;      
    fragment_uv = uv;
}
