#version 330 core

in vec3 Normal;
in vec2 TextureUV;
in vec3 WorldPos;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 customColor;
uniform sampler2D sample0;

out vec4 Color;

void main()
{
    vec3 dFdxPos = dFdx(WorldPos);
    vec3 dFdyPos = dFdy(WorldPos);
    vec3 flatNormal = normalize(cross(dFdxPos, dFdyPos));
    
    float brightness = max(dot(lightDirection, -flatNormal) * 0.5f + 0.5f, 0);
    brightness = pow(brightness, 2);
    vec3 diffuse = brightness * lightColor * customColor;

    vec4 TextureColor = texture(sample0, TextureUV);
    Color = vec4(diffuse * TextureColor.rgb, 1);
}