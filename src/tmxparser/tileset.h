//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_SRC_TMXPARSER_TILESET_H_
#define AZOR_SRC_TMXPARSER_TILESET_H_

#include <vector>
#include <cstdint>
#include <string>
#include <res/texture.h>
#include <common/rec.h>

namespace tmx{
struct TileSet
{
    int first_id;
    Texture* texture;
    std::vector<Rectangle> tiles;
    explicit TileSet(int first_id, Texture* texture):
        first_id(first_id), texture(texture)
    {}
};
}

#endif //AZOR_SRC_TMXPARSER_TILESET_H_
