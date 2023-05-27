#include "Example07.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "stb/stb_image.h"

Example07::Example07()
{
    mTitle = "Example07_Shader";
}

Example07::~Example07()
{
}

void Example07::RunWithParam(ShaderType shaderType)
{
    mShaderType = shaderType;

    Example01::Run();
}

bool Example07::LoadShaderFromFile(std::string vertexPath, std::string fragmentPath)
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

void Example07::CreateDefaultShader()
{
    LoadShaderFromFile("../resources/shaders/Color.vs", "../resources/shaders/Color.fs");
}

void Example07::CheckShaderCompileErrors(unsigned int shader, std::string type)
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

void Example07::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example07::Matrix4_Vec4(float matrix[][4], float vector4[4], float* result)
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

void Example07::Vec4_Matrix4(float vector4[4], float matrix[][4], float* result)
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

void Example07::Matrix4_Multiply3(float matrixA[][4], float matrixB[][4], float matrixC[][4], float(*result)[4])
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

void Example07::Transpose(float matrix[][4], float(*result)[4])
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

void Example07::CreateTriangle()
{
    glm::vec2 uvCenterTop{ 0 };
    glm::vec2 uvLeftBottom{ 0 };
    glm::vec2 uvRightBottom{ 0 };

    mVertices.push_back(VertexUV(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1, 0, 0), uvCenterTop));
    mVertices.push_back(VertexUV(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0, 1, 0), uvLeftBottom));
    mVertices.push_back(VertexUV(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightBottom));

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    float dx = 0.0f;
    float dy = 0.0f;
    float dz = 0.0f;
    glm::vec3 position(dx, dy, dz);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);

    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float scaleZ = 1.0f;
    glm::vec3 scale(scaleX, scaleY, scaleZ);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    float rotationX = glm::radians(0.0f);
    float rotationY = glm::radians(0.0f);
    float rotationZ = glm::radians(0.0f);
    glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationMatrixY * rotationMatrixX * rotationMatrixZ;

    mTRSMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Example07::CreateRectangle()
{
    glm::vec2 uvLeftTop{ 0 };
    glm::vec2 uvLeftBottom{ 0 };
    glm::vec2 uvRightBottom{ 0 };
    glm::vec2 uvRightTop{ 0 };
    int textureUVType = 0;
    switch (textureUVType)
    {
    case 0:     // fit.
        uvLeftTop = glm::vec2(0.0f, 1.0f);
        uvLeftBottom = glm::vec2(0.0f, 0.0f);
        uvRightBottom = glm::vec2(1.0f, 0.0f);
        uvRightTop = glm::vec2(1.0f, 1.0f);
        break;

    case 1:     // scale down.
        uvLeftTop = glm::vec2(0.0f, 1.0f);
        uvLeftBottom = glm::vec2(0.0f, -2.0f);
        uvRightBottom = glm::vec2(3.0f, -2.0f);
        uvRightTop = glm::vec2(3.0f, 1.0f);
        break;

    case 2:     // scale up.
        uvLeftTop = glm::vec2(0.0f, 1.0f);
        uvLeftBottom = glm::vec2(0.0f, 0.5f);
        uvRightBottom = glm::vec2(0.5f, 0.5f);
        uvRightTop = glm::vec2(0.5f, 1.0f);
        break;
    }

    mVertices.push_back(VertexUV(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1, 0, 0), uvLeftTop));     // left top
    mVertices.push_back(VertexUV(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0, 1, 0), uvLeftBottom));    // left bottom
    mVertices.push_back(VertexUV(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightBottom));     // right bottom
    mVertices.push_back(VertexUV(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightTop));      // right top

    mIndices.push_back(0);  // first vertex.
    mIndices.push_back(1);  // second vertex.
    mIndices.push_back(2);  // third vertex.

    mIndices.push_back(0);  // first vertex.
    mIndices.push_back(2);  // second vertex.
    mIndices.push_back(3);  // third vertex.


    //---------------------------------------------
    // 이동 행렬
    //---------------------------------------------
    // 이동할 거리.
    float dx = 1.0f;
    float dy = 0.0f;
    float dz = 0.0f;

    // 이동 행렬.
    /*float translationMatrix[4][4] =
    {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1},
    };*/

    glm::vec3 position(dx, dy, dz);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);



    //---------------------------------------------
    // 스케일 행렬
    //---------------------------------------------
    // 스케일 값.
    float scaleX = 0.5f;
    float scaleY = 0.5f;
    float scaleZ = 1.0f;

    // 스케일 행렬.
    //float scaleMatrix[4][4] =
    //{
    //    {scaleX, 0,      0,      0},
    //    {0,      scaleY, 0,      0},
    //    {0,      0,      scaleZ, 0},
    //    {0,      0,      0,      1},
    //};

    glm::vec3 scale(scaleX, scaleY, scaleZ);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);



    //---------------------------------------------
    // 회전 행렬
    //---------------------------------------------
    // 회전 값.
    float rotationX = glm::radians(0.0f);
    float rotationY = glm::radians(0.0f);
    float rotationZ = glm::radians(45.0f);

    //// 각 축 별로 cos, sin값을 구한다.
    //float cosX = glm::cos(rotationX);
    //float sinX = glm::sin(rotationX);

    //float cosY = glm::cos(rotationY);
    //float sinY = glm::sin(rotationY);

    //float cosZ = glm::cos(rotationZ);
    //float sinZ = glm::sin(rotationZ);

    //// 회전 행렬.
    //float rotationMatrixX[4][4] =
    //{
    //    {1,   0,      0,    0},
    //    {0,  cosX,  -sinX,  0},
    //    {0,  sinX,  cosX,   0},
    //    {0,   0,      0,    1},
    //};
    //float rotationMatrixY[4][4] =
    //{
    //    {cosY,   0,  sinY,  0},
    //    {  0,    1,   0,    0},
    //    {-sinY,  0,  cosY,  0},
    //    {  0,    0,   0,    1},
    //};
    //float rotationMatrixZ[4][4] =
    //{
    //    {cosZ,  -sinZ,  0,  0},
    //    {sinZ,  cosZ,   0,  0},
    //    { 0,     0,     1,  0},
    //    { 0,     0,     0,  1},
    //};

    //float rotationMatrix[4][4]{};
    //Matrix4_Multiply3(rotationMatrixY, rotationMatrixX, rotationMatrixZ, rotationMatrix);

    glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationMatrixY * rotationMatrixX * rotationMatrixZ;




    //---------------------------------------------
    // 이동, 회전, 스케일을 하나의 행렬로 만든다.
    //---------------------------------------------
    /*float trsMatrix[4][4]{};
    Matrix4_Multiply3(translationMatrix, rotationMatrix, scaleMatrix, trsMatrix);*/
    mTRSMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    // 잘못된 srt방식.
    /*float srtMatrix[4][4]{};
    Matrix4_Multiply3(scaleMatrix, rotationMatrix, translationMatrix, srtMatrix);*/

    // 올바른 srt방식.
    /*float scaleMatrixT[4][4]{};
    float rotationMatrixT[4][4]{};
    float translationMatrixT[4][4]{};
    Transpose(scaleMatrix, scaleMatrixT);
    Transpose(rotationMatrix, rotationMatrixT);
    Transpose(translationMatrix, translationMatrixT);
    float srtMatrix[4][4]{};
    Matrix4_Multiply3(scaleMatrixT, rotationMatrixT, translationMatrixT, srtMatrix);*/

    // 버텍스 좌표에 행렬 적용.
    //for (auto& v : mVertices)
    //{
    //    float position[4] = { v.mPosition.x, v.mPosition.y, v.mPosition.z, 1.0f };
    //    float result[4]{};
    //    Matrix4_Vec4(trsMatrix, position, result);
    //    //Vec4_Matrix4(position, srtMatrix, result);

    //    v.mPosition = glm::vec3(result[0], result[1], result[2]);
    //}
}

void Example07::CreateVertexBuffer()
{
    // 버텍스 버퍼와 인덱스 버퍼를 보관할 "vertex array" 오브젝트를 생성한다.
    glGenVertexArrays(1, &mVertexArrayObjectId);
    // Create vertex buffer.
    glGenBuffers(1, &mVertexBufferObjectId);
    // Create element buffer.(index buffer)
    glGenBuffers(1, &mElementBufferObjectId);

    // Bind VAO.
    glBindVertexArray(mVertexArrayObjectId);
    {
        // 버텍스 데이터를 버텍스 버퍼에 올린다.
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObjectId);
        {
            glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(VertexUV), &mVertices[0], GL_STATIC_DRAW);
        }

        // 인덱스 데이터를 인덱스 버퍼(element array buffer)에 올린다.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
        }

        // 버텍스 속성(attribute)을 설정한다.
        glEnableVertexAttribArray(0);
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUV), nullptr);
        }

        glEnableVertexAttribArray(1);
        {
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUV), (void*)offsetof(VertexUV, mColor));
        }

        glEnableVertexAttribArray(2);
        {
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUV), (void*)offsetof(VertexUV, mUV));
        }
    }

    // Unbind.
    glBindVertexArray(0);
}

void Example07::Initialize()
{
    CreateDefaultShader();
    //CreateTriangle();
    CreateRectangle();
    CreateVertexBuffer();
    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mTextureId1 = LoadTexture("../resources/circle_mask.png");
}

void Example07::Render()
{
    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId1);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample0"), 0);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample1"), 1);

    glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "TRSMatrix"), 1, GL_FALSE, &mTRSMatrix[0][0]);

    // Bind VAO.
    glBindVertexArray(mVertexArrayObjectId);
    {
        // 인덱스 버퍼(element buffer)를 이용한 삼각형 렌더링.
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void Example07::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();

    // 생성했던 버퍼들을 해제한다.
    DeleteVertexBuffer();
}

void Example07::DeleteVertexBuffer()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}

unsigned int Example07::LoadTexture(const std::string& path)
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