#pragma once
#include <vector>
#include <glad.h>
#include "Uniforms.hpp"
#include "Shader.hpp"

class ShaderProgram
{
    public:
        const GLuint id;
        uniforms::UniformLocationsMap uniformLocations;

        ShaderProgram(const std::vector<Shader>& shaders);
        ~ShaderProgram();

        void setUniforms(uniforms::UniformValuesMap uniforms);

    private:
        const std::vector<Shader> shaders;
};