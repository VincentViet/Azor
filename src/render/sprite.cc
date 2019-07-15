//
// Created by vice on 15/07/2019.
//

#include "sprite.h"
#include <res/res.h>
#include <glm/gtc/matrix_transform.hpp>

glm::vec2 Sprite::quad_pos[6]{
    glm::vec2(0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
    glm::vec2(-0.5f, 0.5f),
    glm::vec2(0.5f, -0.5f),
    glm::vec2(-0.5f, -0.5f),
    glm::vec2(-0.5f, 0.5f)
};

glm::vec2 Sprite::quad_tex_coord[6]{
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f)
};

void computed_data(Sprite* sprite){
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(sprite->position_, 0.0));
    model = glm::scale(model, glm::vec3(sprite->texture_->width / 2.0f, sprite->texture_->height / 2.0f, 0));
    for (int i = 0; i < 6; ++i)
    {
        sprite->data_[i] =
            model *
                glm::vec4(Sprite::quad_pos[i], 0, 1) +
                glm::vec4(0, 0, Sprite::quad_tex_coord[i]) -
                glm::vec4(0, 0, 0, 1);
    }

    int a = 10;
}

Sprite::Sprite(const char *texture_name, const glm::vec2 &position)
    : position_(position)
{
    texture_ = res::get_texture(texture_name);
    computed_data(this);
}
void Sprite::set_position(const glm::vec2 &v)
{
    position_ = v;
    computed_data(this);
}
