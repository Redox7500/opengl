#pragma once
#include <vector>
#include <glad.h>
#include <glm/glm.hpp>
#include "UniformMaps.hpp"
#include "UniformSetting.hpp"

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