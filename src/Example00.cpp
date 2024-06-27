#include "Example00.h"

#include <iostream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Example00::Example00()
{
    mTitle = "Example00_Triangle";
}

Example00::~Example00()
{
}

void Example00::CreateDefaultShader()
{
    // 버텍스 셰이더 코드.
    std::string vertexCode = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);
        }
    )";

    // 프래그먼트 셰이더 코드.
    std::string fragmentCode = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0); // 빨간색으로 설정
        }
    )";

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

void Example00::CheckShaderCompileErrors(unsigned int shader, std::string type)
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

void Example00::DeleteDefaultShader()
{
    glDeleteProgram(mDefaultShaderID);
}

void Example00::CreateTriangle()
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

unsigned int VBO, VAO;
void Example00::CreateVertexBuffer()
{
    // 버텍스 데이터 설정 (라인을 그리기 위한 두 점 설정)
    float vertices[] = {
          -1.0f, 1.0f, 0.0f,
          1.0f, -1.0f, 0.0f,

          1.0f, 1.0f, 0.0f,
          -1.0f, -1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 버텍스 속성 포인터 설정
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // 바인딩 해제
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Example00::Initialize()
{
    CreateDefaultShader();
    CreateTriangle();
    CreateVertexBuffer();
}

void Example00::Render()
{
    // 렌더링에 적용할 셰이더 프로그램을 설정한다.
    glUseProgram(mDefaultShaderID);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
}

void Example00::CleanUp()
{
    // 셰이더 프로그램을 해제한다.
    DeleteDefaultShader();

    // 생성했던 버퍼들을 해제한다.
    DeleteVertexBuffer();
}

void Example00::DeleteVertexBuffer()
{
    glDeleteVertexArrays(1, &mVertexArrayObjectId);
    glDeleteBuffers(1, &mVertexBufferObjectId);
    glDeleteBuffers(1, &mElementBufferObjectId);
}