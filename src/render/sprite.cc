//
// Created by vice on 15/07/2019.
//

#include "sprite.h"
#include <res/res.h>

glm::vec4 Sprite::quad[6]{
    glm::vec4(0.5f, 0.5f, 1.0f, 1.0f),
    glm::vec4(0.5f, -0.5f, 1.0f, 0.0f),
    glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
    glm::vec4(0.5f, -0.5f, 1.0f, 0.0f),
    glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f),
    glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f)
};

Sprite::Sprite(const char *texture_name, const glm::vec2 &position, int layer)
{
    texture_ = res::get_texture(texture_name);
    this->layer = layer;

}
void Sprite::set_position(const glm::vec2 &v)
{

}
