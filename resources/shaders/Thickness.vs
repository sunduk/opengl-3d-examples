#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texture_uv;

out vec3 VertexColor;
out vec2 TextureUV;
out vec3 Normal;

uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform float thickness;

void main()
{
    vec3 expand = position + normal * thickness;
    gl_Position = mvp * vec4(expand, 1.0f);

    Normal = normalMatrix * normal;
    VertexColor = vertex_color;
    TextureUV = texture_uv;
}