#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texture_uv;

uniform mat4 mvp;

out vec2 TextureUV;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	TextureUV = texture_uv;
}