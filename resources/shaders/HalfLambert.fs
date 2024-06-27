#version 330 core

in vec3 Normal;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 customColor;

out vec4 Color;

void main()
{
    vec3 normal = normalize(Normal);
    float brightness = max(dot(lightDirection, -normal) * 0.5f + 0.5f, 0);
    brightness = pow(brightness, 2);
    vec3 diffuse = brightness * lightColor * customColor;

    Color = vec4(diffuse, 1);
}