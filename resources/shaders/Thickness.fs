#version 330 core

in vec3 VertexColor;
in vec2 TextureUV;
in vec3 Normal;
in vec3 LightDir;

uniform sampler2D sample0;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float ambientIntensity;

out vec4 Color;

void main()
{
    vec3 ambientColor = ambientIntensity * lightColor;

    vec3 normal = normalize(Normal);
    float brightness = max(dot(lightDirection, -normal), 0);
    vec3 diffuse = brightness * lightColor;

    vec4 texture_color = texture(sample0, TextureUV);
    Color = vec4((ambientColor + diffuse) * texture_color.rgb, texture_color.a);
}