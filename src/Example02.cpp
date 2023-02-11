#include "Example02.h"

#include <iostream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Example02::Example02()
{
    mTitle = "Example02_Triangle";
}

Example02::~Example02()
{
}

void Example02::CreateDefaultShader()
{
    // 버텍스 셰이더 코드.
    std::string vertexCode = "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 1.0f);\n"
        "}\n";

    // 프래그먼트 셰이더 코드.
    std::string fragmentCode = "#version 330 core\n"
        "out vec4 Color;\n"
        "void main()\n"
        "{\n"
        "   Color = vec4(1, 0, 0, 1); \n"
        "}\n";

    const char* VERTEX_SHADER_CODE = vertexCode.c_str();
    const char* FRAGMENT_SHADER_CODE = fragmentCode.c_str();

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
    mDefaultShaderID = glCreateProgram();
    glAttachShader(mDefaultShaderID, vertex);
    glAttachShader(mDefaultShaderID, fragment);

    glLinkProgram(mDefaultShaderID);
    // 컴파일 에러가 발생했는지 체크 한다.
    CheckShaderCompileErrors(mDefaultShaderID, "PROGRAM");

    // 컴파일과 프로그램 등록이 모두 완료되었으면 더이상 갖고 있을 필요가 없으므로 자원을 해제 한다.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Example02::CheckShaderCompileErrors(unsigned int shader, std::string type)
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

void Example02::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example02::CreateTriangle()
{
    /*
    *          (0, 1, 0)
    *          (index:0)
    *              *
    *             * *
    *            *   *
    *           *     *
    *          *   +   *
    *         * (center)*
    *        *  (0,0,0)  *
    *       *             *
    *      *****************
    * (-1,-1,0)         (1,-1,0)
    * (index:1)         (index:2)
    */

    // NDC(Normalized Device Coordinate) 기준으로 삼각형의 버텍스 좌표를 설정한다.
    mVertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));       // center top.
    mVertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));     // left bottom.
    mVertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));      // right bottom.

    mIndices.push_back(0);  // first vertex.
    mIndices.push_back(1);  // second vertex.
    mIndices.push_back(2);  // third vertex.

    // 사각형.
    // 위의 삼각형 버텍스 설정 코드를 주석 처리 하고 이 코드의 주석을 풀어서 빌드 하면 사각형이 렌더링 되는 것을 확인할 수 있습니다.
    //float scale = 0.5f;
    //mVertices.push_back(scale * glm::vec3(-1.0f, 1.0f, 0.0f));
    //mVertices.push_back(scale * glm::vec3(-1.0f, -1.0f, 0.0f));
    //mVertices.push_back(scale * glm::vec3(1.0f, -1.0f, 0.0f));
    //mVertices.push_back(scale * glm::vec3(1.0f, 1.0f, 0.0f));

    //// 인덱스를 설정한다.
    //mIndices.push_back(0);  // first vertex.
    //mIndices.push_back(1);  // second vertex.
    //mIndices.push_back(2);  // third vertex.

    //mIndices.push_back(0);  // first vertex.
    //mIndices.push_back(2);  // second vertex.
    //mIndices.push_back(3);  // third vertex.
}

void Example02::CreateVertexBuffer()
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
            glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(glm::vec3), &mVertices[0], GL_STATIC_DRAW);
        }

        // 인덱스 데이터를 인덱스 버퍼(element array buffer)에 올린다.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectId);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
        }

        // 버텍스 속성(attribute)을 설정한다.
        glEnableVertexAttribArray(0);
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
        }
    }

    // Unbind.
    glBindVertexArray(0);
}

void Example02::Initialize()
{
    CreateDefaultShader();
    CreateTriangle();
    CreateVertexBuffer();
}

void Example02::Render()
{
    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    // Bind VAO.
    glBindVertexArray(mVertexArrayObjectId);
    {
        // 버텍스 버퍼를 이용한 삼각형 렌더링.
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // 인덱스 버퍼(element buffer)를 이용한 삼각형 렌더링.
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void Example02::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();

    // 생성했던 버퍼들을 해제한다.
    DeleteVertexBuffer();
}

void Example02::DeleteVertexBuffer()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}