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

 	vec3 scale = vec3(length(vm[0].xyz), length(vm[1].xyz), length(vm[2].xyz));

  	vm[0][1] = 0;
	vm[0][2] = 0;
  	vm[2][0] = 0;
  	vm[2][1] = 0; 

	vm[0][0] = scale.x;
	vm[1][1] = scale.y;
	vm[2][2] = scale.z;

    	gl_Position = (projection * vm) * vec4(position, 1.0);

    	fragment_position = position;
    	fragment_normal = normal;      
    	fragment_uv = uv;
}
