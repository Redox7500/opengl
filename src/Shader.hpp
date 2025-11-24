#pragma once
#include <string>
#include <glad.h>

class Shader
{
    public:
        Shader(const std::string& _source, GLenum type);
        ~Shader();

        const std::string source;
        GLuint id;
};