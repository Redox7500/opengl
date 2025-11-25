#pragma once
#include <vector>
#include <variant>
#include <unordered_map>
#include <glad.h>
#include <glm/glm.hpp>

namespace uniforms
{
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

    void setUniform(const GLint& location, float value);
    void setUniform(const GLint& location, double value);
    void setUniform(const GLint& location, int value);
    void setUniform(const GLint& location, bool value);
    void setUniform(const GLint& location, unsigned int value);

    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, int, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, bool, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, unsigned int, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, int, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, bool, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, unsigned int, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, int, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, bool, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, unsigned int, Q>& value);

    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 2, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 2, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 3, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 3, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 4, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 4, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 3, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 3, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 2, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 2, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 4, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 4, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 4, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 4, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 2, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 2, double, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 3, float, Q>& value);
    template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 3, double, Q>& value);

    void setUniform(const GLint& location, const std::vector<float>& values);
    void setUniform(const GLint& location, const std::vector<int>& values);
    void setUniform(const GLint& location, const std::vector<double>& values);
    void setUniform(const GLint& location, const std::vector<bool>& values);
    void setUniform(const GLint& location, const std::vector<unsigned int>& values);

    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, int, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, bool, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, unsigned int, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, int, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, bool, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, unsigned int, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, int, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, bool, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, unsigned int, Q>>& values);

    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 2, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 2, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 3, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 3, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 4, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 4, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 3, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 3, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 2, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 2, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 4, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 4, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 4, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 4, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 2, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 2, double, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 3, float, Q>>& values);
    template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 3, double, Q>>& values);

    void setUniform(GLint location, UniformValue value);
}