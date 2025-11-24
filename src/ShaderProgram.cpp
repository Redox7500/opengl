#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <glad.h>
#include "UniformMaps.hpp"
#include "ShaderProgram.hpp"

std::vector<std::string> findUniformNames(const std::string& source)
{
    std::vector<std::string> ret;
    const std::regex pattern(R"(uniform\s+[a-zA-Z0-9_]+\s+([a-zA-Z0-9_\[\]]+(?:\s*,\s*[a-zA-Z0-9_\[\]]+)*))");
    std::smatch match;

    auto it = source.cbegin();
    while (std::regex_search(it, source.cend(), match, pattern))
    {
        std::string names = match[1];
        
        std::istringstream ss(names);
        std::string name;
        while (std::getline(ss, name, ','))
        {
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);

            auto bracketPosition = name.find('[');
            if (bracketPosition != std::string::npos)
            {
                name = name.substr(0, bracketPosition);
            }

            ret.push_back(name);
        }
        
        it = match.suffix().first;
    }

    return ret;
}

ShaderProgram::ShaderProgram(const std::vector<Shader>& _shaders)
    :shaders(_shaders),
    id(glCreateProgram())
{
    for (const Shader& shader:shaders)
    {
        glAttachShader(id, shader.id);
    }

    char infoLog[1024];

    glLinkProgram(id);
    int linked;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader program linking failed\n" << infoLog << "\n";
    }

    // GLuint temporaryVAO;
    // glGenVertexArrays(1, &temporaryVAO);
    // glBindVertexArray(temporaryVAO);
    // glValidateProgram(id);
    // glBindVertexArray(0);
    // glDeleteVertexArrays(1, &temporaryVAO);
    // int validated;
    // glGetProgramiv(id, GL_VALIDATE_STATUS, &validated);
    // if (!validated)
    // {
    //     glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
    //     std::cerr << "Shader program validation failed\n" << infoLog << "\n";
    // }
    glUseProgram(id);

    for (const Shader& shader:shaders)
    {
        std::vector<std::string> uniformNames = findUniformNames(shader.source);
        for (const std::string& name:uniformNames)
        {
            const GLint location = glGetUniformLocation(id, name.c_str());
            if (location == -1)
            {
                std::cerr << "Location of uniform " << name.c_str() << " not found" << "\n";
                continue;
            }
            uniformLocations[name] = location;
        }
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}