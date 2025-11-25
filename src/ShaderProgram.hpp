#pragma once
#include <vector>
#include <glad.h>
#include "UniformMaps.hpp"
#include "Shader.hpp"

class ShaderProgram
{
    public:
        const GLuint id;
        UniformLocationsMap uniformLocations;

        ShaderProgram(const std::vector<Shader>& shaders);
        ~ShaderProgram();

        void setUniforms(UniformValuesMap uniforms);

    private:
        const std::vector<Shader> shaders;
};