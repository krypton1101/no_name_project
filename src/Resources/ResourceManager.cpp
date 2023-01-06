#include <sstream>
#include <fstream>
#include <iostream>

#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t lastSlash = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, lastSlash);
}

std::string ResourceManager::getFileString(const std::string& relativePath) const
{
    std::ifstream f;
    f.open(m_path + "/" + relativePath.c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open())
    {
        std::cerr << "Failed open file: " << relativePath.c_str() << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if(vertexString.empty())
    {
        std::cerr << "Vertex shader is empty!" << std::endl;
        return nullptr;
    }

    std::string fragmentSting = getFileString(fragmentPath);
    if(fragmentPath.empty())
    {
        std::cerr << "Fragment shader is empty!" << std::endl;
        return nullptr;
    }
    
    std::shared_ptr<Renderer::ShaderProgram>& newShader = m_sharedPrograms.emplace(shaderName,
        std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentSting)).first->second;

    if(newShader->isCompiled()) return newShader;
    std::cerr << "Can't load shader program:\n" << 
        "Vertex: " << vertexPath << "\n" << 
        "Fragment: " << fragmentPath << std::endl;
    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
    ShaderProgramsMap::const_iterator iterator = m_sharedPrograms.find(shaderName);

    if(iterator != m_sharedPrograms.end()) return iterator -> second;
    std::cerr << "Can't find shader program: " << shaderName << std::endl;
    return nullptr;
}