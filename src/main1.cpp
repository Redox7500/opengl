#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shape.hpp"
#include "Shader.hpp"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const std::string WINDOW_TITLE = "";
glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);
glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -4.f));
glm::mat4 model = glm::mat4(1.);

GLFWwindow* tryCreateWindow(unsigned int majorVersion, unsigned int minorVersion)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr);
    return window;
}

GLFWwindow* createHighestVersionWindow(unsigned int maxMajorVersion, unsigned int maxMinorVersion)
{
    GLFWwindow* retWindow = nullptr;
    for (unsigned int majorVersion = maxMajorVersion; majorVersion >= 3 && !retWindow; majorVersion--)
    {
        for (unsigned int minorVersion = maxMinorVersion; minorVersion >= 0 && !retWindow; minorVersion--)
        {
            retWindow = tryCreateWindow(majorVersion, minorVersion);
            if (retWindow)
            {
                std::cout << "Got context: OpenGL " << majorVersion << "." << minorVersion << "\n";
            }
        }
    }
    return retWindow;
}

std::string getGLSLVersionString(const char* glslVersion)
{
    std::string version = glslVersion;
    size_t spaceIndex = version.find(" ");
    if (spaceIndex != std::string::npos)
    {
        version = version.substr(0, spaceIndex);
    }
    size_t dotIndex = version.find(".");
    if (dotIndex != std::string::npos)
    {
        version.erase(dotIndex, 1);
    }
    return "#version " + version + " core\n";
}

std::vector<unsigned int> getVertexIndices(size_t vertexCount)
{
    std::vector<unsigned int> indices;
    if (vertexCount < 3)
    {
        std::cout << "Warning: Polygon vertex count < 3\n";
        return indices;
    }
    indices.reserve((vertexCount - 2) * 3);
    for (size_t i = 1; i < vertexCount - 1; i++)
    {
        indices.push_back((unsigned int)(0));
        indices.push_back((unsigned int)(i));
        indices.push_back((unsigned int)(i + 1));
    }
    return indices;
}

std::vector<glm::vec3> circle(float radius, unsigned int points)
{
    std::vector<glm::vec3> vertices;
    const float deltaAngle = glm::pi<float>() * 2 / points;
    for (unsigned int i = 0; i < points; i++)
    {
        vertices.push_back(glm::vec3(glm::cos(deltaAngle * i) * radius, glm::sin(deltaAngle * i) * radius, 0));
    }
    return vertices;
}

int main()
{
    glfwInit();
    GLFWwindow* window = createHighestVersionWindow((unsigned int)4, (unsigned int)6);
    if (!window)
    {
        std::cout << "Failed to create any OpenGL 3.x+ context\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const char* glslVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    const std::string glslVersionString = getGLSLVersionString(glslVersion);
    std::cout << "Shader language version: " << glslVersion << "\n";
    const std::string vertexShaderSourceString = glslVersionString +
    R"(layout(location = 0) in vec3 aPosition;
    layout(location = 1) in vec3 aNormal;
    layout(location = 2) in vec2 aTextureCoordinate;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    out vec3 FragmentPosition;
    out vec3 Normal;
    out vec2 TextureCoordinate;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPosition, 1.0);
        vec4 worldPosition = model * vec4(aPosition, 1.0);
        FragmentPosition = worldPosition.xyz;
        Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
        TextureCoordinate = aTextureCoordinate;
    })";
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSourcePointer = vertexShaderSourceString.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex shader compilation failed\n" << infoLog << "\n";
        glfwTerminate();
        return -1;
    }
    const std::string fragmentShaderSourceString = glslVersionString +
    R"(out vec4 FragmentColor;

    in vec3 FragmentPosition;
    in vec3 Normal;

    uniform vec3 lightPosition;
    uniform vec3 viewPosition;
    uniform vec4 lightColor;
    uniform vec4 objectColor;

    void main()
    {
        float ambientStrength = 0.0;
        float diffuseStrength = 1.0;
        float specularStrength = 0.0;

        vec4 ambient = ambientStrength * lightColor;

        vec3 lightDirection = normalize(lightPosition - FragmentPosition);
        float difference = max(dot(Normal, lightDirection), 0.0);
        vec4 diffuse = diffuseStrength * difference * lightColor;

        vec3 viewDirection = normalize(viewPosition - FragmentPosition);
        vec3 reflectDirection = reflect(-lightDirection, Normal);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 64);
        vec4 specular = specularStrength * spec * lightColor;

        FragmentColor = (ambient + diffuse + specular) * objectColor;
    })";
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourcePointer = fragmentShaderSourceString.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment shader compilation failed\n" << infoLog << "\n";
        glfwTerminate();
        return -1;
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Shader program linking failed\n" << infoLog << "\n";
        glfwTerminate();
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    const std::vector<glm::vec3> vertices = circle(0.3f, 100);
    Shape shape{vertices, getVertexIndices(vertices.size()), shaderProgram};

    double lastFrame = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        double currentFrame = glfwGetTime();
        double deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        model = glm::rotate(model, (float)deltaTime, glm::vec3(1, 0, 0));

        shape.draw(projection, view, model, glm::vec3(1.2f, 1.f, 2.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 0.5f, 0.2f, 1.f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}