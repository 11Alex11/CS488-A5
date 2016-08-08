#version 330

uniform mat4 ModelView;
uniform mat4 Perspective;
in vec3 position;
in vec3 normal;
void main() {
	vec4 vert = Perspective * ModelView * vec4(position+0.01*normal, 1.0);
	gl_Position = vert;
}
