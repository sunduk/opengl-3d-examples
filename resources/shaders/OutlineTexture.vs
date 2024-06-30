#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texture_uv;

uniform mat4 mvp;
out vec2 TextureUV;

void main()
{
	vec3 expand = normal * 0.01f;
	vec3 position2 = position + expand;
	gl_Position = mvp * vec4(position2, 1.0f);
	TextureUV = texture_uv;
}