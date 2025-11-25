#pragma once
#include <string>
#include <glad.h>

class Shader
{
    public:
        const std::string source;
        GLuint id;

        Shader(const std::string& source, GLenum type);
        ~Shader();
};