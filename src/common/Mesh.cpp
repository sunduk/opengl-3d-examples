#pragma once

#include "Mesh.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}

void Mesh::Initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    mVertices = vertices;
    mIndices = indices;

    glGenVertexArrays(1, &mVertexArrayObjectId);
    glGenBuffers(1, &mVertexBufferObjectId);
    glGenBuffers(1, &mElementBufferObjectId);

    glBindVertexArray(mVertexArrayObjectId);
    {
        // copy to video memory.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObjectId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // attributes.
        // position.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // color.
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mColor));

        // normal.
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));

        // uv.
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mUV));
    }
    glBindVertexArray(0);
}

void Mesh::Render()
{
    glBindVertexArray(mVertexArrayObjectId);
    {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
}