#pragma once
#include <glad.h>
#include "UniformMaps.hpp"
#include "Shader.hpp"

class ShaderProgram
{
    public:
        ShaderProgram(const std::vector<Shader>& _shaders);
        ~ShaderProgram();

        const GLuint id;
        UniformLocationsMap uniformLocations;

    private:
        const std::vector<Shader> shaders;
};