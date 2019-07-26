//
// Created by vice on 15/07/2019.
//

#include "Sprite.h"
#include <resources/resources.h>
#include <glm/gtc/matrix_transform.hpp>

glm::vec2 Sprite::quad[6]{
    glm::vec2(0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
    glm::vec2(-0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
    glm::vec2(-0.5f, -0.5f),
    glm::vec2(-0.5f, 0.5f)
};

//void compute_data(Sprite* sprite){
//
//}

Sprite::Sprite(Texture* texture)
{
    m_texture = texture;
    m_direction = 1;
}
Sprite::Sprite(const char *texture_name)
{
    m_texture = resources::getTexture(texture_name);
    m_direction = 1;
}
void Sprite::setPosition(const glm::vec2 &v)
{
    m_position = v;
}
void Sprite::setPosition(const float *v)
{
    m_position.x = v[0];
    m_position.y = v[1];
}
void Sprite::setRectangle(const AABB &rectangle)
{
    m_rectangle = rectangle;
}

glm::vec4* Sprite::getData()
{
    float x, y;

    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(m_position, 0.0));

    auto size = m_rectangle.getSize();
    model = glm::scale(model, glm::vec3((float)m_direction * size.x, size.y, 0));

    // 0
    x = m_rectangle.min.x / (float)m_texture->width;
    y = m_rectangle.min.y / (float)m_texture->height;
    m_data[0] =
        model *
            glm::vec4(quad[0], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, x + size.x / (float)m_texture->width, y);

    // 1
    m_data[1] =
        model *
            glm::vec4(quad[1], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, m_rectangle.max.x / (float)m_texture->width, m_rectangle.max.y /(float) m_texture->height);

    // 2
    m_data[2] =
        model *
            glm::vec4(quad[2], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, x, y);

    // 1
    m_data[3] =
        model *
            glm::vec4(quad[3], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, m_rectangle.max.x / (float)m_texture->width, m_rectangle.max.y / (float)m_texture->height);

    // 3
    m_data[4] =
        model *
            glm::vec4(quad[4], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, x, y + size.y / (float)m_texture->height);

    // 2
    m_data[5] =
        model *
            glm::vec4(quad[5], 0, 1) -
            glm::vec4(0, 0, 0, 1)+
            glm::vec4(0, 0, x, y);

    return m_data;
}
Texture *Sprite::getTexture() const
{
    return m_texture;
}
void Sprite::setDirection(int direction)
{
    m_direction = direction;
}
