//
// Created by vice on 25/07/2019.
//

#include "Tile.h"
#include <glm/gtc/matrix_transform.hpp>

Tile::Tile(int id, Texture *texture, const AABB &bound, const AABB &rectangle)
    : Sprite(texture), m_id(id), m_bound(bound), m_factor(1.0)
{
    m_rectangle = rectangle;
    m_camera = nullptr;
    m_position = m_bound.getPos();
}

void Tile::setCamera(Camera *camera)
{
    m_camera = camera;
}

const AABB& Tile::getBound()
{
    return m_bound;
}
glm::vec4* Tile::getData()
{
    if (m_camera && m_id){
        const glm::mat4& view = m_camera->getView();
        float x, y;

        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(m_position, 0.0));

        auto size = m_rectangle.getSize();
        model = glm::scale(model, glm::vec3(size.x * m_factor.x, size.y * m_factor.y, 0));

        // 0
        x = m_rectangle.min.x / m_texture->width;
        y = m_rectangle.min.y / m_texture->height;
        m_data[0] =
            view  *
                model *
                glm::vec4(quad[0], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, x + size.x / m_texture->width, y);

        // 1
        m_data[1] =
            view  *
                model *
                glm::vec4(quad[1], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, m_rectangle.max.x / m_texture->width, m_rectangle.max.y / m_texture->height);

        // 2
        m_data[2] =
            view  *
                model *
                glm::vec4(quad[2], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, x, y);

        // 1
        m_data[3] =
            view  *
                model *
                glm::vec4(quad[3], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, m_rectangle.max.x / m_texture->width, m_rectangle.max.y / m_texture->height);

        // 3
        m_data[4] =
            view  *
                model *
                glm::vec4(quad[4], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, x, y + size.y / m_texture->height);

        // 2
        m_data[5] =
            view  *
                model *
                glm::vec4(quad[5], 0, 1) -
                glm::vec4(0, 0, 0, 1)+
                glm::vec4(0, 0, x, y);

        return m_data;
    }

    return nullptr;
}

bool Tile::isValid() const
{
    return m_id;
}
void Tile::setFactor(const glm::vec2 &factor)
{
    m_factor = factor;
}
