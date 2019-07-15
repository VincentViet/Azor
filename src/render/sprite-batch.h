//
// Created by vice on 14/07/2019.
//

#ifndef AZOR_SPRITE_BATCH_H_
#define AZOR_SPRITE_BATCH_H_

#include "sprite.h"
#include <map>
#include <vector>

class SpriteBatch
{
 private:
    std::map<uint32_t , std::vector<float>> batches;
    std::vector<uint32_t> textures;
    std::vector<uint32_t> vao;
 public:
    SpriteBatch() = default;
    ~SpriteBatch() = default;

    void begin();
    void end();

    void draw(const Sprite& sprite);
};

#endif //AZOR_SPRITE_BATCH_H_
