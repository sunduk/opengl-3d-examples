#include "Example05.h"

#include <iostream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"

Example05::Example05()
{
    mTitle = "Example05_Texture";
}

Example05::~Example05()
{
}

void Example05::RunWithParam(ShaderType shaderType)
{
    mShaderType = shaderType;

    Example01::Run();
}

unsigned int Example05::CreateShader(const char* FRAGMENT_SHADER_CODE)
{
    // 버텍스 셰이더 코드.
    std::string vertexCode = "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec3 vertex_color;\n"
        "layout(location = 2) in vec2 texture_uv;\n"
        "out vec3 VertexColor;\n"
        "out vec2 TextureUV;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 1.0f);\n"
        "   VertexColor = vertex_color;\n"
        "   TextureUV = texture_uv;\n"
        "}\n";

    const char* VERTEX_SHADER_CODE = vertexCode.c_str();

    unsigned int vertex{};
    unsigned int fragment{};

    // 버텍스 셰이더 컴파일을 수행한다.
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &VERTEX_SHADER_CODE, NULL);
    glCompileShader(vertex);
    // 컴파일 에러가 발생했는지 체크 한다.
    CheckShaderCompileErrors(vertex, "VERTEX");

    // 프래그먼트 셰이더 컴파일을 수행한다.
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &FRAGMENT_SHADER_CODE, NULL);
    glCompileShader(fragment);
    // 컴파일 에러가 발생했는지 체크 한다.
    CheckShaderCompileErrors(fragment, "FRAGMENT");

    // OpenGL에 셰이더 프로그램을 등록한다.
    unsigned int shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);

    glLinkProgram(shaderID);
    // 컴파일 에러가 발생했는지 체크 한다.
    CheckShaderCompileErrors(shaderID, "PROGRAM");

    // 컴파일과 프로그램 등록이 모두 완료되었으면 더이상 갖고 있을 필요가 없으므로 자원을 해제 한다.
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderID;
}

unsigned int Example05::CreateTextureColorShader()
{
    // 텍스쳐 컬러.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    Color = texture(sample0, TextureUV);\n"
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

unsigned int Example05::CreateInvertShader()
{
    // 색상 반전.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    Color = texture(sample0, TextureUV);\n"
        "    Color = vec4(1 - Color.rgb, 1);\n"
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

unsigned int Example05::CreateGrayscaleShader()
{
    // 그레이스케일.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    Color = texture(sample0, TextureUV);\n"
        "    // 그레이 스케일\n"
        "    //float gray = (Color.r + Color.g + Color.b) / 3.0f;\n"
        "    //Color = vec4(gray, gray, gray, 1);\n" //+
        //0.299R + 0.587G + 0.114B
        "    float gray = (Color.r * 0.299f + Color.g * 0.587f + Color.b * 0.114f);\n"
        "    Color = vec4(gray, gray, gray, 1);\n" //+
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

unsigned int Example05::CreateAddShader()
{
    // Add 합성.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    vec4 Color1 = texture(sample0, TextureUV);\n" //+
        "    vec4 Color2 = texture(sample1, TextureUV);\n" //+
        "    Color = Color1 + Color2;\n" //+
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

unsigned int Example05::CreateMultipleyShader()
{
    // Multiply 합성.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    vec4 Color1 = texture(sample0, TextureUV);\n" //+
        "    vec4 Color2 = texture(sample1, TextureUV);\n" //+
        "    Color = Color1 * Color2;\n" //+
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

unsigned int Example05::CreateLerpShader()
{
    // 선형 보간.
    std::string fragmentCode = "#version 330 core\n"
        "in vec3 VertexColor;\n"
        "in vec2 TextureUV;\n"  //+
        "out vec4 Color;\n"  //+
        "uniform sampler2D sample0;\n"
        "uniform sampler2D sample1;\n"
        "void main()\n"
        "{\n"
        "    vec4 Color1 = texture(sample0, TextureUV);\n" //+
        "    vec4 Color2 = texture(sample1, TextureUV);\n" //+
        "    Color = mix(Color1, Color2, 0.5f);\n" //+
        "}\n";

    return CreateShader(fragmentCode.c_str());
}

void Example05::CheckShaderCompileErrors(unsigned int shader, std::string type)
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

void Example05::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example05::CreateRectangle()
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

    float scale = 0.8f;
    mVertices.push_back(VertexUV(scale * glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1, 0, 0), uvLeftTop));     // left top
    mVertices.push_back(VertexUV(scale * glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0, 1, 0), uvLeftBottom));    // left bottom
    mVertices.push_back(VertexUV(scale * glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightBottom));     // right bottom
    mVertices.push_back(VertexUV(scale * glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0, 0, 1), uvRightTop));      // right top

    mIndices.push_back(0);  // first vertex.
    mIndices.push_back(1);  // second vertex.
    mIndices.push_back(2);  // third vertex.

    mIndices.push_back(0);  // first vertex.
    mIndices.push_back(2);  // second vertex.
    mIndices.push_back(3);  // third vertex.
}

void Example05::CreateVertexBuffer()
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

void Example05::Initialize()
{
    switch (mShaderType)
    {
    case ShaderType::TextureColor:
        mDefaultShaderID = CreateTextureColorShader();
        break;

    case ShaderType::Invert:
        mDefaultShaderID = CreateInvertShader();
        break;

    case ShaderType::Grayscale:
        mDefaultShaderID = CreateGrayscaleShader();
        break;

    case ShaderType::Add:
        mDefaultShaderID = CreateAddShader();
        break;

    case ShaderType::Multiply:
        mDefaultShaderID = CreateMultipleyShader();
        break;

    case ShaderType::Lerp:
        mDefaultShaderID = CreateLerpShader();
        break;

    default:
        mDefaultShaderID = CreateTextureColorShader();
    }

    CreateRectangle();
    CreateVertexBuffer();
    mTextureId0 = LoadTexture("../resources/opengl_texture.png");
    mTextureId1 = LoadTexture("../resources/circle_mask.png");
}

void Example05::Render()
{
    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    //+
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId1);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample0"), 0);
    glUniform1i(glGetUniformLocation(mDefaultShaderID, "sample1"), 1);

    // Bind VAO.
    glBindVertexArray(mVertexArrayObjectId);
    {
        // 인덱스 버퍼(element buffer)를 이용한 삼각형 렌더링.
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void Example05::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();

    // 생성했던 버퍼들을 해제한다.
    DeleteVertexBuffer();
}

void Example05::DeleteVertexBuffer()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}

unsigned int Example05::LoadTexture(const std::string& path)
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