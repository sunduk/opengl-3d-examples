#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inVertexColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTextureUV;
layout(location = 4) in vec4 inPosition4;

uniform mat4 mvp;

out vec3 color;
out vec2 TextureUV;

void main()
{
	gl_Position = mvp * vec4(inPosition, 1.0f);
	//gl_Position = vec4(inPosition, 1.0f);
	//gl_Position = inPosition4;
	TextureUV = inTextureUV;

	color = inVertexColor;
}