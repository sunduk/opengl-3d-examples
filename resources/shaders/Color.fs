#version 330 core

uniform vec3 customColor;

out vec4 Color;

void main()
{
    Color = vec4(customColor,1);
}