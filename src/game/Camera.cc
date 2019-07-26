//
// Created by vice on 18/07/2019.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(const glm::vec2 &position, int width, int height)
{
    m_view = glm::mat4(1.0);
    m_projection =  glm::ortho(
        0.0f,
        (float)width,
        (float)height,
        0.0f);

    m_bound = AABB(position, width, height);
}
glm::mat4& Camera::getView()
{
    return m_view;
}
glm::mat4& Camera::getProjection(){
    return m_projection;
}
void Camera::setPosition(const glm::vec2 &pos)
{
    glm::mat4 identity(1.0);
    m_bound.setPos(pos);
    m_view = glm::translate(identity, glm::vec3(-pos, 0.0f));
}
const AABB& Camera::getBound()
{
    return m_bound;
}
