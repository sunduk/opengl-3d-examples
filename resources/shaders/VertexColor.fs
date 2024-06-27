#version 330 core

in vec3 VertexColor;

uniform vec3 customColor;

out vec4 Color;

void main()
{
    Color = vec4(VertexColor,1);
}