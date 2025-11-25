#include <glm/glm.hpp>
#include "Camera.hpp"

Camera::Camera()
{
    updateProjection();
}

Camera::Camera(const glm::mat4& transform, float fov, float aspect, float zNear, float zFar)
    :transform(transform),
    fov(fov),
    aspect(aspect),
    zNear(zNear),
    zFar(zFar)
{
    updateProjection();
}

Camera::Camera(const glm::mat4& transform)
    :transform(transform)
{
    updateProjection();
}

Camera::Camera(float fov, float aspect, float zNear, float zFar)
    :fov(fov),
    aspect(aspect),
    zNear(zNear),
    zFar(zFar)
{
    updateProjection();
}

void Camera::setFov(float value)
{
    fov = value;
    updateProjection();
}

void Camera::setAspect(float value)
{
    aspect = value;
    updateProjection();
}

void Camera::setZNear(float value)
{
    zNear = value;
    updateProjection();
}

void Camera::setZFar(float value)
{
    zFar = value;
    updateProjection();
}

void Camera::updateProjection()
{
    projection = glm::perspective(fov, aspect, zNear, zFar);
}