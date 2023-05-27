#include "Example08.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "stb/stb_image.h"

Example08::Example08()
{
    mTitle = "Example08_Transform";
}

Example08::~Example08()
{
}

void Example08::RunWithParam(ShaderType shaderType)
{
    mShaderType = shaderType;

    Example01::Run();
}

bool Example08::LoadShaderFromFile(std::string vertexPath, std::string fragmentPath)
{
    auto LoadTextFile = [](const std::string& filePath)
    {
        std::ifstream shaderFile(filePath);
        std::stringstream stream{};
        stream << shaderFile.rdbuf();
        std::string text = stream.str();
        shaderFile.close();
        return text;
    };

    std::string vertexCode{};
    std::string fragmentCode{};

    try
    {
        vertexCode = LoadTextFile(vertexPath);
        fragmentCode = LoadTextFile(fragmentPath);
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "[error] shader file read error : " << e.what() << std::endl;
        return false;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // compile shaders
    unsigned int vertex{};
    unsigned int fragment{};

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckShaderCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckShaderCompileErrors(fragment, "FRAGMENT");

    // shader Program
    mDefaultShaderID = glCreateProgram();
    glAttachShader(mDefaultShaderID, vertex);
    glAttachShader(mDefaultShaderID, fragment);

    glLinkProgram(mDefaultShaderID);
    CheckShaderCompileErrors(mDefaultShaderID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void Example08::CreateDefaultShader()
{
    LoadShaderFromFile("../resources/shaders/Color.vs", "../resources/shaders/Color.fs");
}

void Example08::CheckShaderCompileErrors(unsigned int shader, std::string type)
{
    GLint success{};
    GLchar errorLog[1024]{};
    if ("PROGRAM" == type)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, errorLog);
            std::cout << "[error] shader program linking error. type" << type << std::endl;
            std::cout << "log : " << errorLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, errorLog);
            std::cout << "[error] shader compilation error. type" << type << std::endl;
            std::cout << "log : " << errorLog << std::endl;
        }
    }
}

void Example08::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example08::Matrix4_Vec4(float matrix[][4], float vector4[4], float* result)
{
    for (int row = 0; row < 4; ++row)
    {
        float sum = 0;
        for (int col = 0; col < 4; ++col)
        {
            sum += matrix[row][col] * vector4[col];
        }
        result[row] = sum;
    }
}

void Example08::Vec4_Matrix4(float vector4[4], float matrix[][4], float* result)
{
    for (int row = 0; row < 4; ++row)
    {
        float sum = 0;
        for (int col = 0; col < 4; ++col)
        {
            sum += vector4[col] * matrix[col][row];
        }
        result[row] = sum;
    }
}

void Example08::Matrix4_Multiply3(float matrixA[][4], float matrixB[][4], float matrixC[][4], float(*result)[4])
{
    // ab = matrixA * matrixB
    float ab[4][4]{};
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            float sum = 0;
            for (int i = 0; i < 4; ++i)
            {
                sum += matrixA[row][i] * matrixB[i][col];
            }
            ab[row][col] = sum;
        }
    }

    // ab * matrixC
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            float sum = 0;
            for (int i = 0; i < 4; ++i)
            {
                sum += ab[row][i] * matrixC[i][col];
            }
            result[row][col] = sum;
        }
    }
}

void Example08::Transpose(float matrix[][4], float(*result)[4])
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result[row][col] = matrix[row][col];
        }
    }

    for (int row = 0; row < 4; ++row)
    {
        for (int col = row + 1; col < 4; ++col)
        {
            float temp = result[col][row];
            result[col][row] = result[row][col];
            result[row][col] = temp;
        }
    }
}

void Example08::CreateRectangle()
{
    glm::vec2 uvLeftTop{ 0 };
    glm::vec2 uvLeftBottom{ 0 };
    glm::vec2 uvRightBottom{ 0 };
    glm::vec2 uvRightTop{ 0 };
    uvLeftTop = glm::vec2(0.0f, 1.0f);
    uvLeftBottom = glm::vec2(0.0f, 0.0f);
    uvRightBottom = glm::vec2(1.0f, 0.0f);
    uvRightTop = glm::vec2(1.0f, 1.0f);

    std::vector<VertexUV> vertices{};
    std::vector<unsigned int> indices{};

    vertices.push_back(VertexUV(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1, 0, 0), uvLeftTop));     // left top
    vertices.push_back(VertexUV(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0, 1, 0), uvLeftBottom));    // left bottom
    vertices.push_back(VertexUV(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightBottom));     // right bottom
    vertices.push_back(VertexUV(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightTop));      // right top

    indices.push_back(0);  // first vertex.
    indices.push_back(1);  // second vertex.
    indices.push_back(2);  // third vertex.

    indices.push_back(0);  // first vertex.
    indices.push_back(2);  // second vertex.
    indices.push_back(3);  // third vertex.

    mMesh.Initialize(vertices, indices);

    mTransform.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    mTransform.SetEulerAngles(glm::vec3(0.0f, 0.0f, 45.0f));
    mTransform.SetScale(glm::vec3(0.5f, 0.5f, 1.0f));

    mTransform2.SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    mTransform2.SetEulerAngles(glm::vec3(0.0f, 0.0f, -45.0f));
    mTransform2.SetScale(glm::vec3(0.5f, 0.5f, 1.0f));

    mTransform3.SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    mTransform3.SetEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
    mTransform3.SetScale(glm::vec3(0.3f, 0.3f, 1.0f));

    mTransform4.SetPosition(glm::vec3(0.0f, -0.7f, 0.0f));
    mTransform4.SetEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
    mTransform4.SetScale(glm::vec3(0.5f, 0.2f, 1.0f));
}

void Example08::Initialize()
{
    CreateDefaultShader();
    CreateRectangle();
    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mTextureId1 = LoadTexture("../resources/circle_mask.png");
}

void Example08::Render()
{
    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId0);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample0"), 0);

    {
        glm::mat4 TRSMatrix = mTransform.GetModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "TRSMatrix"), 1, GL_FALSE, &TRSMatrix[0][0]);
        mMesh.Render();
    }

    {
        glm::mat4 TRSMatrix = mTransform2.GetModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "TRSMatrix"), 1, GL_FALSE, &TRSMatrix[0][0]);
        mMesh.Render();
    }

    {
        glm::mat4 TRSMatrix = mTransform3.GetModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "TRSMatrix"), 1, GL_FALSE, &TRSMatrix[0][0]);
        mMesh.Render();
    }

    {
        glm::mat4 TRSMatrix = mTransform4.GetModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "TRSMatrix"), 1, GL_FALSE, &TRSMatrix[0][0]);
        mMesh.Render();
    }
}

void Example08::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();
}

unsigned int Example08::LoadTexture(const std::string& path)
{
    unsigned int textureId{};
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // texture wrap.
    GLint wrapParam = GL_REPEAT;
    int wrapType = 0;
    switch (wrapType)
    {
    case 0:
        wrapParam = GL_REPEAT;
        break;

    case 1:
        wrapParam = GL_CLAMP_TO_EDGE;
        break;

    case 2:
        wrapParam = GL_MIRRORED_REPEAT;
        break;

    case 3:
        wrapParam = GL_CLAMP_TO_BORDER;
        float borderColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);

    // texture sampling.
    GLint samplingParam = GL_NEAREST;
    int samplingType = 0;
    switch (samplingType)
    {
    case 0:
        samplingParam = GL_NEAREST;
        break;

    case 1:
        samplingParam = GL_LINEAR;
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplingParam);

    // Load Texture.
    int width{};
    int height{};
    int channels{};
    stbi_set_flip_vertically_on_load(1);
    unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (imageData)
    {
        switch (channels)
        {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            break;

        case 4:     // with alpha channel.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            break;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(imageData);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    return textureId;
}