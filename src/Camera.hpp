#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        glm::mat4 transform = translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 5.f));
        glm::mat4 projection;

        Camera();
        Camera(const glm::mat4& transform, float fov, float aspect, float near, float far);
        Camera(const glm::mat4& transform);
        Camera(float fov, float aspect, float near, float far);

        void setFov(float value);
        void setAspect(float value);
        void setZNear(float value);
        void setZFar(float value);

    private:
        float fov = glm::radians(45.f);
        float aspect = 4.f/3.f;
        float zNear = 0.01f;
        float zFar = 1000.f;

        void updateProjection();
};