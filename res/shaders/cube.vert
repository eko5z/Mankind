#version 120

attribute vec4 coord;
uniform mat4 mvp;
varying vec4 texcoord;

void main(void) {
	texcoord = coord;
	gl_Position = mvp * vec4(coord.xyz, 1);
}

