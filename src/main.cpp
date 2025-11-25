#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Uniforms.hpp"
#include "Shape.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const std::string WINDOW_TITLE = "yes";

glm::vec3 lightPosition = glm::vec3(1.2f, 1.f, 2.f);

glm::vec4 objectColor = glm::vec4(1.f, 0.5f, 0.2f, 1.f);
glm::vec4 lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);

glm::vec3 velocity = glm::vec3(0, 0, 0);
float speed = 0.03;

double lastFrame = 0;
double currentFrame = 0;
double deltaTime = 0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_A:
            if (action == GLFW_PRESS)
            {
                velocity.x = -speed;
            }
            else if (action == GLFW_RELEASE && velocity.x == -speed)
            {
                velocity.x = 0;
            }
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS)
            {
                velocity.x = speed;
            }
            else if (action == GLFW_RELEASE && velocity.x == speed)
            {
                velocity.x = 0;
            }
            break;
        case GLFW_KEY_W:
            if (action == GLFW_PRESS)
            {
                velocity.y = speed;
            }
            else if (action == GLFW_RELEASE && velocity.y == speed)
            {
                velocity.y = 0;
            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS)
            {
                velocity.y = -speed;
            }
            else if (action == GLFW_RELEASE && velocity.y == -speed)
            {
                velocity.y = 0;
            }
            break;
        case GLFW_KEY_UP:
            if (action == GLFW_PRESS)
            {
                velocity.z = -speed;
            }
            else if (action == GLFW_RELEASE && velocity.z == -speed)
            {
                velocity.z = 0;
            }
            break;
        case GLFW_KEY_DOWN:
            if (action == GLFW_PRESS)
            {
                velocity.z = speed;
            }
            else if (action == GLFW_RELEASE && velocity.z == speed)
            {
                velocity.z = 0;
            }
            break;
    }
}

std::vector<GLuint> getVertexIndices(size_t vertexCount)
{
    std::vector<GLuint> indices;
    if (vertexCount < 3)
    {
        std::cerr << "Warning: Polygon vertex count < 3\n";
        return indices;
    }
    indices.reserve((vertexCount - 2) * 4);
    for (size_t i = 1; i < vertexCount - 1; i++)
    {
        indices.push_back((GLuint)(0));
        indices.push_back((GLuint)(i));
        indices.push_back((GLuint)(i + 1));
    }
    return indices;
}

std::string readFile(const std::string& filepath)
{
    std::ifstream file{filepath};
    if (!file.is_open())
    {
        std::cerr << "Failed to open file at " << filepath << "\n";
        return (std::string)"";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return (std::string)buffer.str();
}

std::string getShaderFilepath(const std::string& shaderName)
{
    return "shaders/" + shaderName;
}

std::string getShaderSource(const std::string& shaderName)
{
    return readFile(getShaderFilepath(shaderName));
}

GLuint loadTexture(const char* filepath)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);

    if (!data)
    {
        std::cerr << "Failed to load texture at " << filepath << "\n";
        return 0;
    }

    GLenum format = (channels == 4)? GL_RGBA:GL_RGB;

    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureId;
}

GLuint generatePlainTexture(int width, int height, glm::vec4 color)
{
    std::vector<unsigned char> data(width * height * 4);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = (y * width + x) * 4;
            data[i] = color[0];
            data[i + 1] = color[1];
            data[i + 2] = color[2];
            data[i + 3] = color[3];
        }
    }

    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureId;
}

void bindTexture(GLuint textureId, int number)
{
    glActiveTexture(GL_TEXTURE0 + number);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

std::vector<glm::vec3> circle(float radius, unsigned int points)
{
    std::vector<glm::vec3> vertices;
    const float deltaAngle = -glm::pi<float>() * 2 / points;
    for (unsigned int i = 0; i < points; i++)
    {
        vertices.push_back(glm::vec3(glm::cos(deltaAngle * i) * radius, glm::sin(deltaAngle * i) * radius, 0));
    }
    return vertices;
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr);
    if (!window)
    {
        throw std::runtime_error("Failed to create an OpenGL context\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD\n");
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "Shader language version " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    const std::string vertexShaderSource = getShaderSource("phong.vert");
    const Shader vertexShader{vertexShaderSource, GL_VERTEX_SHADER};
    const std::string fragmentShaderSource = getShaderSource("phong.frag");
    const Shader fragmentShader{fragmentShaderSource, GL_FRAGMENT_SHADER};

    ShaderProgram shaderProgram{{vertexShader, fragmentShader}};

    const std::vector<glm::vec3> vertices = {
        glm::vec3(-1.f, -1.f,  1.f),
        glm::vec3(1.f, -1.f,  1.f),
        glm::vec3(1.f,  1.f,  1.f),
        glm::vec3(-1.f,  1.f,  1.f),

        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f, -1.f),
        glm::vec3(1.f,  1.f, -1.f),
        glm::vec3(-1.f,  1.f, -1.f),

        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(-1.f, -1.f,  1.f),
        glm::vec3(-1.f,  1.f,  1.f),
        glm::vec3(-1.f,  1.f, -1.f),

        glm::vec3(1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f,  1.f),
        glm::vec3(1.f,  1.f,  1.f),
        glm::vec3(1.f,  1.f, -1.f),

        glm::vec3(-1.f,  1.f, -1.f),
        glm::vec3(1.f,  1.f, -1.f),
        glm::vec3(1.f,  1.f,  1.f),
        glm::vec3(-1.f,  1.f,  1.f),

        glm::vec3(-1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f, -1.f),
        glm::vec3(1.f, -1.f,  1.f),
        glm::vec3(-1.f, -1.f,  1.f)
    };
    std::vector<GLuint> indices = {
        0, 1, 2, 2, 3, 0,
        4, 6, 5, 4, 7, 6,
        8, 9, 10, 10, 11, 8,
        12, 14, 13, 12, 15, 14,
        16, 18, 17, 16, 19, 18,
        20, 21, 22, 22, 23, 20
    };

    Shape shape{vertices, indices, shaderProgram};

    Camera camera{};
    camera.setAspect((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

    // GLuint albedoMap = generatePlainTexture(1, 1, glm::vec4(255.f, 0.f, 0.f, 255.f));
    // // GLuint albedoMap;
    // // glGenTextures(1, &albedoMap);
    // // glBindTexture(GL_TEXTURE_2D, albedoMap);
    // // unsigned char white[4] = {255, 255, 255, 255};
    // // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // // glBindTexture(GL_TEXTURE_2D, 0);
    // int albedoMapNumber = 0;
    // // bindTexture(albedoMap, albedoMapNumber);
    // GLuint metallicMap = generatePlainTexture(1, 1, glm::vec4(127.f, 0.f, 0.f, 0.f));
    // int metallicMapNumber = 1;
    // // bindTexture(metallicMap, metallicMapNumber);
    // GLuint roughnessMap = generatePlainTexture(1, 1, glm::vec4(127.f, 0.f, 0.f, 0.f));
    // int roughnessMapNumber = 2;
    // // bindTexture(roughnessMap, roughnessMapNumber);
    // GLuint aoMap = generatePlainTexture(1, 1, glm::vec4(127.f, 0.f, 0.f, 0.f));
    // int aoMapNumber = 3;
    // bindTexture(aoMap, aoMapNumber);
    glUseProgram(shaderProgram.id);
    // bindTexture(albedoMap, albedoMapNumber);
    // bindTexture(metallicMap, metallicMapNumber);
    // bindTexture(roughnessMap, roughnessMapNumber);
    // bindTexture(aoMap, aoMapNumber);

    while (!glfwWindowShouldClose(window))
    {
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error: " << error << "\n";
        }

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        shape.transform = glm::translate(shape.transform, velocity);

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.setUniforms({
            {"uProjection", camera.projection},
            {"uView", glm::inverse(camera.transform)},
            {"uModel", shape.transform},
            {"uViewPosition", glm::vec3(glm::inverse(camera.transform)[3])},
            {"uLightPosition", lightPosition},
            {"uObjectColor", objectColor},
            {"uLightColor", lightColor}
        });
        shape.draw();
        // shape.draw({
        //     {"uProjection", projection},
        //     {"uView", view},
        //     {"uModel", model},
        //     {"uViewPosition", glm::vec3(glm::inverse(view)[3])},
        //     {"uLightDirection", glm::vec3(-1.f, -1.f, -1.f)},
        //     {"uLightColor", lightColor},
        //     {"uAlbedoMap", albedoMapNumber},
        //     {"uMetallicMap", metallicMapNumber},
        //     {"uRoughnessMap", roughnessMapNumber},
        //     {"uAoMap", aoMapNumber}
        // });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}