#version 330 core

in vec2 TextureUV;

out vec4 Color;

uniform vec3 customColor;
uniform sampler2D sample0;



void main()
{
    vec4 TextureColor = texture(sample0, TextureUV);
    Color = vec4(customColor * TextureColor.rgb, 1);
}