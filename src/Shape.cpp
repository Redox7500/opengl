#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <glad.h>
#include "ShaderProgram.hpp"
#include "Shape.hpp"

void generateVerticesFromPositions(std::vector<Vertex>& vertices, const std::vector<glm::vec3>& vertexPositions)
{
    vertices.reserve(vertexPositions.size());
    for (glm::vec3 vertexPosition:vertexPositions)
    {
        Vertex vertex = Vertex();
        vertex.position = vertexPosition;
        vertices.push_back(vertex);
    }
}

void generateVertexNormals(std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
    for (Vertex& vertex:vertices)
    {
        vertex.normal = glm::vec3(0.f);
    }

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        size_t index0 = indices[i];
        size_t index1 = indices[i + 1];
        size_t index2 = indices[i + 2];
        glm::vec3 position0 = vertices[index0].position;
        glm::vec3 position1 = vertices[index1].position;
        glm::vec3 position2 = vertices[index2].position;

        glm::vec3 edge1 = position1 - position0;
        glm::vec3 edge2 = position2 - position0;
        glm::vec3 faceNormal = glm::cross(edge1, edge2);
        if (glm::length(faceNormal) > 1e-4f)
        {
            faceNormal = glm::normalize(faceNormal);
        }
        else
        {
            faceNormal = glm::vec3(0.f);
        }

        vertices[index0].normal += faceNormal;
        vertices[index1].normal += faceNormal;
        vertices[index2].normal += faceNormal;
    }

    for (Vertex& vertex:vertices)
    {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

void generatePlanarUvs(std::vector<Vertex>& vertices, float scaleU=1.f, float scaleV=1.f, float offsetU=0.f, float offsetV=0.f)
{
    for (Vertex& vertex:vertices)
    {
        vertex.uv.x = vertex.position.x * scaleU + offsetU;
        vertex.uv.y = vertex.position.y * scaleV + offsetV;
    }
}

void generateCubeUvs(std::vector<Vertex>& vertices)
{
    if (vertices.size() != 24)
    {
        std::cerr << "Invalid number of vertices to generate cube UVs\n";
        return;
    }

    const std::vector<glm::vec2> uvTemplate = {
        glm::vec2(0.f, 0.f),
        glm::vec2(1.f, 0.f),
        glm::vec2(1.f, 1.f),
        glm::vec2(0.f, 1.f)
    };

    for (int face = 0; face < 6; face++)
    {
        for (int i = 0; i < 4; i++)
        {
            vertices[face * 4 + i].uv = uvTemplate[i];
        }
    }
}

Shape::Shape(const std::vector<glm::vec3>& vertexPositions, const std::vector<GLuint>& indices, const ShaderProgram& shaderProgram, const glm::mat4& transform)
    :transform(transform),
    indices(indices),
    shaderProgram(shaderProgram)
{
    std::vector<Vertex> vertices;
    generateVerticesFromPositions(vertices, vertexPositions);
    generateVertexNormals(vertices, indices);
    generateCubeUvs(vertices);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Shape::draw()
{
    glUseProgram(shaderProgram.id);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}