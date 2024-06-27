#version 330 core

in vec2 TextureUV;

out vec4 FragColor;

uniform sampler2D sample0;

void main()
{
    FragColor = texture(sample0, TextureUV);
}