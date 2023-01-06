#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    {
        GLuint vertexShaderID;
        if(!createShader(vertexShaderSource, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER Compile-time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if(!createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER Compile0time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if(!success) // if errors
        {
            GLchar InfoLog[1024];
            glGetProgramInfoLog(m_ID, 1024, nullptr, InfoLog); // get error message

            std::cerr << "ERROR::SHADER: Link-time error:\n" << InfoLog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;

        return *this;
    }

    bool ShaderProgram::createShader( const std::string& source, const GLenum shaderType, GLuint& shaderID )
    {
        shaderID = glCreateShader(shaderType); // created shader address -> shaderID (type example: GL_VERTEX_SHADER)
        const char* code = source.c_str(); // string -> char*
        glShaderSource(shaderID, 1, &code, nullptr); // define source for shader
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success); // get error code (0 if no error)
        if(!success) // if errors
        {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, InfoLog); // get error message

            std::cerr << "ERROR::SHADER: Compile-time error:\n" << InfoLog << std::endl;

            return false;
        }

        return true;
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }
}
