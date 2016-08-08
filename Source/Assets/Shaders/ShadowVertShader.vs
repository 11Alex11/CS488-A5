#version 330

in vec3 position;
uniform mat4 depthMVP;
void main() {
	gl_Position = depthMVP*vec4(position,1);
}
