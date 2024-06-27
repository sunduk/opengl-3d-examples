#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 normal;

out vec3 Normal;

uniform mat4 mvp;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	Normal = normalMatrix * normal;
}