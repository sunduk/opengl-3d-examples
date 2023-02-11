#version 330 core

in vec3 color;
in vec3 Normal;
in vec3 LightDir;

out vec4 FragColor;

uniform vec3 COLOR;

void main()
{
    vec3 norm = normalize(Normal);
    float brightness = dot(LightDir, -norm);
	FragColor = vec4(COLOR * brightness, 1);
}