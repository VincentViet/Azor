//
// Created by vice on 18/07/2019.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec2 &position, int width, int height)
    : m_followed(nullptr)
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
    AABB bound (pos, m_bound.getSize().x, m_bound.getSize().y);

//    if (clamp(bound, m_clamp)){
//        m_bound.setPos(pos);
//        m_view = glm::translate(identity, glm::vec3(-pos, 0.0f));
//    }

    m_bound.setPos(pos);
    m_view = glm::translate(identity, glm::vec3(-pos, 0.0f));
}
const AABB& Camera::getBound()
{
    return m_bound;
}
void Camera::setClamp(const AABB &aabb)
{
    m_clamp = aabb;
}
void Camera::followed(Entity *entity)
{
    m_followed = entity;
}
void Camera::update()
{
    if (m_followed){
        if (m_followed->getBound().getPos().x >= m_bound.getPos().x)
            setPosition(m_followed->getBound().getPos());
    }
}
