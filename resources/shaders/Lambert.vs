#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVertexColor;
layout (location = 2) in vec3 inNormal;

out vec3 Normal;
out vec3 LightDir;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec3 lightPosition;

void main()
{
	gl_Position = model * vec4(inPosition, 1.0f);
	LightDir = normalize(vec3(gl_Position) - lightPosition);
	gl_Position = viewProjection * gl_Position;

	Normal = vec3(model * vec4(inNormal, 1.0f));
}