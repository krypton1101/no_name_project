#pragma once

#include <string>
#include <glad/glad.h>

namespace Renderer
{
    class ShaderProgram
    {
    private:
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    public:
        ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~ShaderProgram();

        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept; // move operator (from another to this)
        ShaderProgram(ShaderProgram&&) noexcept; // move constructor (from existing object)

        bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
        bool isCompiled() { return m_isCompiled; }
        void use() const;
    };
} // namespace Renderer
