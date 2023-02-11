#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inVertexColor;
layout(location = 2) in vec2 inTextureUV;

uniform mat4 TRSMatrix;

out vec2 TextureUV;

void main()
{
	gl_Position = TRSMatrix * vec4(inPosition, 1.0f);
	TextureUV = inTextureUV;
}