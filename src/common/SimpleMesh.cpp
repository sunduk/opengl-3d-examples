#pragma once

#include "SimpleMesh.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

SimpleMesh::SimpleMesh()
{
}

SimpleMesh::~SimpleMesh()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}

void SimpleMesh::Initialize(const std::vector<VertexUV>& vertices, const std::vector<unsigned int>& indices)
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
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexUV), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // attributes.
        // position.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUV), (void*)0);

        // color.
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUV), (void*)offsetof(VertexUV, mColor));

        // uv.
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUV), (void*)offsetof(VertexUV, mUV));
    }
    glBindVertexArray(0);
}

void SimpleMesh::Initialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    mVerticesEx = vertices;
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

void SimpleMesh::RefreshVertexBuffer()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    mVertexArrayObjectId = 0;
    glDeleteBuffers(1, &mVertexBufferObjectId);
    mVertexBufferObjectId = 0;
    glDeleteBuffers(1, &mElementBufferObjectId);
    mElementBufferObjectId = 0;

    glGenVertexArrays(1, &mVertexArrayObjectId);
    glGenBuffers(1, &mVertexBufferObjectId);
    glGenBuffers(1, &mElementBufferObjectId);

    glBindVertexArray(mVertexArrayObjectId);
    {
        // copy to video memory.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObjectId);
        glBufferData(GL_ARRAY_BUFFER, mVerticesEx.size() * sizeof(Vertex), &mVerticesEx[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

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

void SimpleMesh::Render()
{
    //RefreshVertexBuffer();
    glBindVertexArray(mVertexArrayObjectId);
    {
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
}