#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;

out vec3 VertexColor;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	VertexColor = vertex_color;
}