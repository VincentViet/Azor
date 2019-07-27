//
// Created by vice on 15/07/2019.
//

#ifndef AZOR_SPRITE_H_
#define AZOR_SPRITE_H_

#include <glm/glm.hpp>
#include <common/AABB.h>
#include <resources/Texture.h>

class Sprite
{
 protected:
    Texture*    m_texture;
    glm::vec4   m_data[6]{};
    glm::vec2   m_position{};
    glm::vec2   m_factor;
    AABB        m_rectangle;
    int         m_direction;

    static glm::vec2 quad[6];

 public:
    explicit    Sprite(Texture* texture);
    explicit    Sprite(const char* texture_name);
    void        setPosition(const glm::vec2& v);
    void        setPosition(const float* v);
    void        setFactor(const glm::vec2& factor);
    void        setDirection(int direction);
    void        setRectangle(const AABB& rectangle);

    Texture*    getTexture() const;
    virtual glm::vec4*  getData();
};

#endif //AZOR_SRC_RENDER_SPRITE_H_
