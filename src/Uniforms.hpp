#pragma once
#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map>
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void setUniform(const GLint& location, float value) {glUniform1f(location, value);}
void setUniform(const GLint& location, double value) {glUniform1d(location, value);}
void setUniform(const GLint& location, int value) {glUniform1i(location, value);}
void setUniform(const GLint& location, bool value) {glUniform1i(location, static_cast<int>(value));}
void setUniform(const GLint& location, unsigned int value) {glUniform1ui(location, value);}

template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, float, Q>& value) {glUniform2fv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, double, Q>& value) {glUniform2dv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, int, Q>& value) {glUniform2iv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, bool, Q>& value) {glm::vec<2, int, Q> intValue(value); glUniform2iv(location, 1, glm::value_ptr(intValue));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<2, unsigned int, Q>& value) {glUniform2uiv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, float, Q>& value) {glUniform3fv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, double, Q>& value) {glUniform3dv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, int, Q>& value) {glUniform3iv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, bool, Q>& value) {glm::vec<3, int, Q> intValue(value); glUniform3iv(location, 1, glm::value_ptr(intValue));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<3, unsigned int, Q>& value) {glUniform3uiv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, float, Q>& value) {glUniform4fv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, double, Q>& value) {glUniform4dv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, int, Q>& value) {glUniform4iv(location, 1, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, bool, Q>& value) {glm::vec<4, int, Q> intValue(value); glUniform4iv(location, 1, glm::value_ptr(intValue));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::vec<4, unsigned int, Q>& value) {glUniform4uiv(location, 1, glm::value_ptr(value));}

template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 2, float, Q>& value) {glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 2, double, Q>& value) {glUniformMatrix2dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 3, float, Q>& value) {glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 3, double, Q>& value) {glUniformMatrix2x3dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 4, float, Q>& value) {glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<2, 4, double, Q>& value) {glUniformMatrix2x4dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 3, float, Q>& value) {glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 3, double, Q>& value) {glUniformMatrix3dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 2, float, Q>& value) {glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 2, double, Q>& value) {glUniformMatrix3x2dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 4, float, Q>& value) {glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<3, 4, double, Q>& value) {glUniformMatrix3x4dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 4, float, Q>& value) {glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 4, double, Q>& value) {glUniformMatrix4dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 2, float, Q>& value) {glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 2, double, Q>& value) {glUniformMatrix4x2dv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 3, float, Q>& value) {glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(value));}
template <glm::qualifier Q> void setUniform(const GLint& location, const glm::mat<4, 3, double, Q>& value) {glUniformMatrix4x3dv(location, 1, GL_FALSE, glm::value_ptr(value));}

void setUniform(const GLint& location, const std::vector<float>& values) {if (!values.empty()) {glUniform1fv(location, static_cast<GLsizei>(values.size()), values.data());} else {std::cerr << "Empty uniform values vector\n";}}
void setUniform(const GLint& location, const std::vector<int>& values) {if (!values.empty()) {glUniform1iv(location, static_cast<GLsizei>(values.size()), values.data());} else {std::cerr << "Empty uniform values vector\n";}}
void setUniform(const GLint& location, const std::vector<double>& values) {if (!values.empty()) {glUniform1dv(location, static_cast<GLsizei>(values.size()), values.data());} else {std::cerr << "Empty uniform values vector\n";}}
void setUniform(const GLint& location, const std::vector<bool>& values) {if (!values.empty()) {std::vector<int> intValues(values.begin(), values.end()); glUniform1iv(location, static_cast<GLsizei>(intValues.size()), intValues.data());} else {std::cerr << "Empty uniform values vector\n";}}
void setUniform(const GLint& location, const std::vector<unsigned int>& values) {if (!values.empty()) {glUniform1uiv(location, static_cast<GLsizei>(values.size()), values.data());} else {std::cerr << "Empty uniform values vector\n";}}

template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, float, Q>>& values) {if (!values.empty()) {glUniform2fv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, double, Q>>& values) {if (!values.empty()) {glUniform2dv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, int, Q>>& values) {if (!values.empty()) {glUniform2iv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, bool, Q>>& values) {if (!values.empty()) {std::vector<glm::vec<2, int, Q>> intValues(values.begin(), values.end()); glUniform2iv(location, static_cast<GLsizei>(intValues.size()), reinterpret_cast<const GLint*>(intValues.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<2, unsigned int, Q>>& values) {if (!values.empty()) {glUniform2uiv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, float, Q>>& values) {if (!values.empty()) {glUniform3fv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, double, Q>>& values) {if (!values.empty()) {glUniform3dv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, int, Q>>& values) {if (!values.empty()) {glUniform3iv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, bool, Q>>& values) {if (!values.empty()) {std::vector<glm::vec<3, int, Q>> intValues(values.begin(), values.end()); glUniform3iv(location, static_cast<GLsizei>(intValues.size()), reinterpret_cast<const GLint*>(intValues.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<3, unsigned int, Q>>& values) {if (!values.empty()) {glUniform3uiv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, float, Q>>& values) {if (!values.empty()) {glUniform4fv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, double, Q>>& values) {if (!values.empty()) {glUniform4dv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, int, Q>>& values) {if (!values.empty()) {glUniform4iv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, bool, Q>>& values) {if (!values.empty()) {std::vector<glm::vec<4, int, Q>> intValues(values.begin(), values.end()); glUniform4iv(location, static_cast<GLsizei>(intValues.size()), reinterpret_cast<const GLint*>(intValues.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::vec<4, unsigned int, Q>>& values) {if (!values.empty()) {glUniform4uiv(location, static_cast<GLsizei>(values.size()), reinterpret_cast<const GLuint*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}

template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 2, float, Q>>& values) {if (!values.empty()) {glUniformMatrix2fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 2, double, Q>>& values) {if (!values.empty()) {glUniformMatrix2dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 3, float, Q>>& values) {if (!values.empty()) {glUniformMatrix2x3fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 3, double, Q>>& values) {if (!values.empty()) {glUniformMatrix2x3dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 4, float, Q>>& values) {if (!values.empty()) {glUniformMatrix2x4fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<2, 4, double, Q>>& values) {if (!values.empty()) {glUniformMatrix2x4dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 3, float, Q>>& values) {if (!values.empty()) {glUniformMatrix3fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 3, double, Q>>& values) {if (!values.empty()) {glUniformMatrix3dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 2, float, Q>>& values) {if (!values.empty()) {glUniformMatrix3x2fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 2, double, Q>>& values) {if (!values.empty()) {glUniformMatrix3x2dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 4, float, Q>>& values) {if (!values.empty()) {glUniformMatrix3x4fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<3, 4, double, Q>>& values) {if (!values.empty()) {glUniformMatrix3x4dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 4, float, Q>>& values) {if (!values.empty()) {glUniformMatrix4fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 4, double, Q>>& values) {if (!values.empty()) {glUniformMatrix4dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 2, float, Q>>& values) {if (!values.empty()) {glUniformMatrix4x2fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 2, double, Q>>& values) {if (!values.empty()) {glUniformMatrix4x2dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 3, float, Q>>& values) {if (!values.empty()) {glUniformMatrix4x3fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLfloat*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}
template <glm::qualifier Q> void setUniform(const GLint& location, const std::vector<glm::mat<4, 3, double, Q>>& values) {if (!values.empty()) {glUniformMatrix4x3dv(location, static_cast<GLsizei>(values.size()), GL_FALSE, reinterpret_cast<const GLdouble*>(values.data()));} else {std::cerr << "Empty uniform values vector\n";}}

void setUniform(GLint location, const UniformValue& value)
{
    std::visit([&](auto&& v) {
        using T = std::decay_t<decltype(v)>;
        setUniform(location, v);
    }, value);
}