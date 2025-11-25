#pragma once
#include <vector>
#include <glm/glm.hpp>
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
        glm::mat4 transform;

        Shape(const std::vector<glm::vec3>& vertexPositions, const std::vector<GLuint>& indices, const ShaderProgram& shaderProgram, const glm::mat4& transform=glm::mat4(1.f));
        ~Shape();

        void draw();
    
    private:
        const std::vector<GLuint> indices;
        unsigned int VAO, VBO, EBO;
        const ShaderProgram shaderProgram;
};