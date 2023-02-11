#include "Example09.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb/stb_image.h"

#include "BoxShape.h"

Example09::Example09()
{
    mTitle = "Example09_MVP";
}

Example09::~Example09()
{
}

void Example09::RunWithParam(ProjectionType projectionType)
{
    mProjectionType = projectionType;

    Example01::Run();
}

bool Example09::LoadShaderFromFile(std::string vertexPath, std::string fragmentPath)
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

void Example09::CreateDefaultShader()
{
    LoadShaderFromFile("../resources/shaders/MVP.vs", "../resources/shaders/Color.fs");
}

void Example09::CheckShaderCompileErrors(unsigned int shader, std::string type)
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

void Example09::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example09::Initialize()
{
    CreateDefaultShader();

    BoxShape box{};

    mTransform.SetPosition(glm::vec3(10.0f, 0.0f, -5.0f));
    mTransform.SetEulerAngles(glm::vec3(45.0f, 45.0f, 0.0f));

    // test.
    //mTransform.SetEulerAngles(glm::vec3(45.0f, 0.0f, 0.0f));

    mMesh.Initialize(box.GetVertices(), box.GetIndices());

    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mTextureId1 = LoadTexture("../resources/circle_mask.png");
}

void Example09::Render()
{
    glEnable(GL_DEPTH_TEST);

    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId0);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample0"), 0);

    {
        glm::mat4 modelMatrix = mTransform.GetModelMatrix();

        glm::vec3 cameraPosition = glm::vec3(10, 0, 0);
        glm::vec3 forward = glm::normalize(glm::vec3(0, 0, -1));

        // test.
        /*glm::vec3 cameraPosition = glm::vec3(10, 2.7f, 0);
        glm::vec3 forward = glm::normalize(glm::vec3(0.0f, -0.5f, -1.0f));*/

        glm::vec3 worldUp = glm::vec3(0, 1, 0);
        glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + forward, worldUp);

        glm::mat4 projectionMatrix{};
        switch (mProjectionType)
        {
        case ProjectionType::Perspective:
        {
            // 원근 투영.
            float fov = 45.0f;
            float windowWidth = static_cast<float>(mWindowParam.width);
            float windowHeight = static_cast<float>(mWindowParam.height);
            float near = 0.1f;
            float far = 1000.0f;
            projectionMatrix = glm::perspective(glm::radians(fov), windowWidth / windowHeight, near, far);
        }
        break;

        case ProjectionType::Ortho1:
        {
            // 직교 투영 1)
            // 윈도우의 세로 사이즈에 영향 받음.
            float size = 2.0f;
            float windowWidth = static_cast<float>(mWindowParam.width);
            float windowHeight = static_cast<float>(mWindowParam.height);
            float ratio = size / windowHeight;
            float horizontalSize = ratio * windowWidth;
            float near = 0.1f;
            float far = 1000.0f;
            projectionMatrix = glm::ortho(-horizontalSize, horizontalSize, -size, size, near, far);
        }
        break;

        case ProjectionType::Ortho2:
        {
            // 직교 투영 2)
            // 윈도우의 가로 사이즈에 영향 받음.
            float size = 2.0f;
            float windowWidth = static_cast<float>(mWindowParam.width);
            float windowHeight = static_cast<float>(mWindowParam.height);
            float near = 0.1f;
            float far = 1000.0f;
            float ratio = size / windowWidth;
            float verticalSize = ratio * windowHeight;
            projectionMatrix = glm::ortho(-size, size, -verticalSize, verticalSize, near, far);
        }
        break;
        }

        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(mDefaultShaderID, "mvp"), 1, GL_FALSE, &mvpMatrix[0][0]);
        mMesh.Render();
    }
}

void Example09::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();
}

unsigned int Example09::LoadTexture(const std::string& path)
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

        case 4:     // with alpha challen.
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