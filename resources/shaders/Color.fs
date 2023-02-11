#version 330 core

in vec3 color;
in vec2 TextureUV;

out vec4 FragColor;

uniform sampler2D sample0;

void main()
{
    //FragColor = vec4(1, 0, 0, 1);
    FragColor = texture(sample0, TextureUV);
    //FragColor = vec4(color, 1);
}