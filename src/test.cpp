#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <glm/glm.hpp>
#include <typeinfo>
#include "UniformMap.hpp"

// using UniformValue = std::variant<
//     float, int, bool,
//     glm::vec1, glm::vec2, glm::vec3, glm::vec4,
//     glm::mat2x2, glm::mat2x3, glm::mat2x4,
//     glm::mat3x2, glm::mat3x3, glm::mat3x4,
//     glm::mat4x2, glm::mat4x3, glm::mat4x4,
//     std::vector<float>, std::vector<int>, std::vector<bool>,
//     std::vector<glm::vec1>, std::vector<glm::vec2>, std::vector<glm::vec3>, std::vector<glm::vec4>,
//     std::vector<glm::mat2>, std::vector<glm::mat2x3>, std::vector<glm::mat2x4>,
//     std::vector<glm::mat3>, std::vector<glm::mat3x2>, std::vector<glm::mat3x4>,
//     std::vector<glm::mat4>, std::vector<glm::mat4x2>, std::vector<glm::mat4x3>
// >;
// using UniformMap = std::unordered_map<std::string, UniformValue>;

// struct Uniform
// {
//     std::string name;
//     UniformValue value;

//     Uniform(const std::string& _name, const UniformValue& _value)
//         :name(_name),
//         value(_value)
//     {

//     }
// };
template <typename T>
struct is_glm_vec:std::false_type {};

template <glm::length_t L, typename T, glm::qualifier Q>
struct is_glm_vec<glm::vec<L, T, Q>>:std::true_type {};

template <typename T>
constexpr bool is_glm_vec_v = is_glm_vec<T>::value;

template <typename T>
struct is_glm_mat:std::false_type {};

template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct is_glm_mat<glm::mat<C, R, T, Q>>:std::true_type {};

template <typename T>
constexpr bool is_glm_mat_v = is_glm_mat<T>::value;

template <typename T>
struct is_vector:std::false_type {};

template <typename T, typename A>
struct is_vector<std::vector<T, A>>:std::true_type {};

template <typename T>
constexpr bool is_vector_v = is_vector<T>::value;

template <typename Variant>
bool isGlmVector(const Variant& value)
{
    return std::visit([](auto&& v) -> bool {
        using T = std::decay_t<decltype(v)>;
        return is_glm_vec_v<T>;
    }, value);
}

int main()
{
    UniformValuesMap uniforms = {
        {"a", glm::vec3(1, 2, 3)},
        {"cd", 0.1f}
    };
    std::cout << isGlmVector(uniforms.at("cd"));
    return 0;
}