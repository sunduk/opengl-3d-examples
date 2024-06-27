#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 normal;

out vec3 Normal;
out vec4 VertexWorldPosition;

uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	Normal = normalMatrix * normal;

	VertexWorldPosition = modelMatrix * vec4(position, 1.0f);
}