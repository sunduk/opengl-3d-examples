#pragma once

#include "Line.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

Line::Line()
{
}

Line::~Line()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
}

void Line::Initialize(const std::vector<Vertex>& vertices)
{
    mVertices = vertices;

    glGenVertexArrays(1, &mVertexArrayObjectId);
    glGenBuffers(1, &mVertexBufferObjectId);

    glBindVertexArray(mVertexArrayObjectId);
    {
        // copy to video memory.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObjectId);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // attributes.
        // position.
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // color.
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mColor));
    }
    glBindVertexArray(0);
}

void Line::Render()
{
    glBindVertexArray(mVertexArrayObjectId);
    {
        glDrawArrays(GL_LINES, 0, static_cast<unsigned int>(mVertices.size()));
    }
}