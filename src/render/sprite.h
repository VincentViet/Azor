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
 private:
    int layer;
    Texture* texture_;
    static glm::vec4 quad[6];

 public:
    Sprite(const char* texture_name, const glm::vec2& position, int layer);
    void set_position(const glm::vec2& v);
};

#endif //AZOR_SRC_RENDER_SPRITE_H_
