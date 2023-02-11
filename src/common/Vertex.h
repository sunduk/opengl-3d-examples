#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 mPosition{ 0,0,0 };
    glm::vec3 mColor{ 0,0,0 };
    glm::vec3 mNormal{ 0,0,0 };
    glm::vec2 mUV{ 0,0 };
    glm::vec4 mPosition4{ 0,0,0,0 };

    Vertex()
    {
    }

    Vertex(const glm::vec3& position, const glm::vec3& color)
    {
        mPosition = position;
        mColor = color;
    }

    Vertex(const glm::vec3& position, const glm::vec3& color, const glm::vec3& normal)
    {
        mPosition = position;
        mColor = color;
        mNormal = normal;
    }

    Vertex(const glm::vec3& position, const glm::vec3& color, const glm::vec3& normal, const glm::vec2& uv)
    {
        mPosition = position;
        mColor = color;
        mNormal = normal;
        mUV = uv;
    }
};

struct VertexUV
{
    glm::vec3 mPosition{ 0,0,0 };
    glm::vec3 mColor{ 0,0,0 };
    glm::vec2 mUV{ 0,0 };

    VertexUV()
    {
    }

    VertexUV(const glm::vec3& position, const glm::vec3& color, const glm::vec2& uv)
    {
        mPosition = position;
        mColor = color;
        mUV = uv;
    }
};