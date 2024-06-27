#version 330 core

uniform vec3 outlineColor;

out vec4 Color;

void main()
{
    Color = vec4(outlineColor,1);
}