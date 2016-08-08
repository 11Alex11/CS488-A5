#version 330
in vec3 position;


uniform mat4 MVP;
out vec3 texCoord;

void main()
{
    texCoord = position;

    gl_Position = (MVP * vec4(position, 1.0f)).xyww;
}
