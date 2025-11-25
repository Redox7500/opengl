#include <iostream>
#include <string>
#include <glad.h>
#include "Shader.hpp"

Shader::Shader(const std::string& source, GLenum type)
    :source(source),
    id(glCreateShader(type))
{
    const char* shaderSourcePointer = source.c_str();
    glShaderSource(id, 1, &shaderSourcePointer, nullptr);
    
    glCompileShader(id);
    int compiled;
    char infoLog[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader compilation failed\n" << infoLog << "\n";
    }
}

Shader::~Shader()
{
    glDeleteShader(id);
}