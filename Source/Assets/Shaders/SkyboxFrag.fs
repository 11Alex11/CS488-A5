#version 330
out vec4 color;
in vec3 texCoord;

uniform samplerCube  cubeMap;

void main()
{
    color = texture(cubeMap,texCoord);

}
