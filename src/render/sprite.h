//
// Created by vice on 15/07/2019.
//

#ifndef AZOR_SPRITE_H_
#define AZOR_SPRITE_H_

#include <glm/glm.hpp>
#include <res/texture.h>

class Sprite
{
    friend class SpriteBatch;
    friend void computed_data(Sprite* sprite);
    static glm::vec2 quad_pos[6];
    static glm::vec2 quad_tex_coord[6];
 private:
    Texture* texture_;
    glm::vec4 data_[6]{};
    glm::vec2 position_{};

 public:
    Sprite(Texture* texture, const glm::vec2& position);
    Sprite(const char* texture_name, const glm::vec2& position);
    void set_position(const glm::vec2& v);
};

#endif //AZOR_SRC_RENDER_SPRITE_H_
