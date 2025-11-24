#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "UniformMaps.hpp"
#include "ShaderProgram.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Shape
{
    public:
        Shape(const std::vector<glm::vec3>& vertexPositions, const std::vector<GLuint>& indices, const ShaderProgram& _shaderProgram);
        ~Shape();

        void draw(const UniformValuesMap& uniforms);
    
    private:
        const std::vector<GLuint> indices;
        unsigned int VAO, VBO, EBO;
        const ShaderProgram shaderProgram;
};