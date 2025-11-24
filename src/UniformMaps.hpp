#pragma once
#include <vector>
#include <variant>
#include <unordered_map>
#include <glad.h>
#include <glm/glm.hpp>

using UniformValue = std::variant<
    float, double, int, bool, unsigned int,
    glm::vec2, glm::vec3, glm::vec4,
    glm::mat2x2, glm::mat2x3, glm::mat2x4,
    glm::mat3x2, glm::mat3x3, glm::mat3x4,
    glm::mat4x2, glm::mat4x3, glm::mat4x4,
    std::vector<float>, std::vector<int>, std::vector<bool>,
    std::vector<glm::vec1>, std::vector<glm::vec2>, std::vector<glm::vec3>, std::vector<glm::vec4>,
    std::vector<glm::mat2>, std::vector<glm::mat2x3>, std::vector<glm::mat2x4>,
    std::vector<glm::mat3>, std::vector<glm::mat3x2>, std::vector<glm::mat3x4>,
    std::vector<glm::mat4>, std::vector<glm::mat4x2>, std::vector<glm::mat4x3>
>;
using UniformValuesMap = std::unordered_map<std::string, UniformValue>;
using UniformLocationsMap = std::unordered_map<std::string, GLint>;